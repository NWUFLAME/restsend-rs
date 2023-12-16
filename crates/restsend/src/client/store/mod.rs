use self::attachments::AttachmentInner;
use crate::callback::Callback;
use crate::models::{Attachment, ChatLogStatus};
use crate::services::response::Upload;
use crate::storage::{prepare, Storage};
use crate::utils::{elapsed, now_millis, spawn};
use crate::Result;
use crate::{
    callback::MessageCallback,
    request::{ChatRequest, ChatRequestType},
    MAX_RETRIES, MAX_SEND_IDLE_SECS,
};
use log::{debug, info, warn};
use std::sync::atomic::AtomicI64;
use std::{
    collections::{HashMap, VecDeque},
    sync::{
        atomic::{AtomicUsize, Ordering},
        Arc, Mutex,
    },
};
use tokio::sync::mpsc::UnboundedSender;

mod attachments;
mod conversations;
mod requests;
mod users;

pub fn is_cache_expired(cached_at: i64, expire_secs: i64) -> bool {
    (now_millis() - cached_at) / 1000 > expire_secs
}

pub struct PendingRequest {
    pub callback: Option<Box<dyn MessageCallback>>,
    pub req: ChatRequest,
    pub retry: AtomicUsize,
    pub updated_at: i64,
    pub last_fail_at: AtomicI64,
    pub can_retry: bool,
}

impl PendingRequest {
    pub fn new(req: ChatRequest, callback: Option<Box<dyn MessageCallback>>) -> Self {
        let can_retry = match ChatRequestType::from(&req.r#type) {
            ChatRequestType::Typing | ChatRequestType::Read => false,
            _ => true,
        };

        PendingRequest {
            callback,
            req,
            retry: AtomicUsize::new(0),
            can_retry,
            updated_at: now_millis(),
            last_fail_at: AtomicI64::new(0),
        }
    }

    pub fn is_expired(&self) -> bool {
        if !self.can_retry {
            return true;
        }
        let retry_count = self.retry.load(Ordering::Relaxed);
        retry_count >= MAX_RETRIES || elapsed(self.updated_at).as_secs() > MAX_SEND_IDLE_SECS
    }

    pub fn did_retry(&self) {
        self.retry.fetch_add(1, Ordering::Relaxed);
        self.last_fail_at.store(now_millis(), Ordering::Relaxed);
    }

    pub fn need_retry(&self, now: i64) -> bool {
        if !self.can_retry {
            return false;
        }

        let last_fail_at = self.last_fail_at.load(Ordering::Relaxed);
        if last_fail_at > 0 && now - last_fail_at >= 1 {
            self.last_fail_at.store(0, Ordering::Relaxed);
            true
        } else {
            false
        }
    }

    pub fn has_attachment(&self) -> bool {
        self.req
            .content
            .as_ref()
            .map(|c| c.attachment.is_some())
            .unwrap_or(false)
    }

    pub fn get_attachment(&self) -> Option<Attachment> {
        self.req.content.as_ref().and_then(|c| c.attachment.clone())
    }

    pub fn get_req_id(&self) -> String {
        self.req.id.clone()
    }
}

type PendingRequests = Arc<Mutex<HashMap<String, PendingRequest>>>;

pub(super) type ClientStoreRef = Arc<ClientStore>;
pub(super) type CallbackRef = Arc<Mutex<Option<Box<dyn Callback>>>>;
pub(super) struct ClientStore {
    user_id: String,
    endpoint: String,
    token: String,
    tmps: Mutex<VecDeque<String>>,
    outgoings: PendingRequests,
    msg_tx: Mutex<Option<UnboundedSender<String>>>,
    message_storage: Arc<Storage>,
    attachment_inner: AttachmentInner,
    pub(crate) callback: CallbackRef,
}

impl ClientStore {
    pub fn new(
        _root_path: &str,
        db_path: &str,
        endpoint: &str,
        token: &str,
        user_id: &str,
    ) -> Self {
        Self {
            user_id: user_id.to_string(),
            endpoint: endpoint.to_string(),
            token: token.to_string(),
            tmps: Mutex::new(VecDeque::new()),
            outgoings: Arc::new(Mutex::new(HashMap::new())),
            msg_tx: Mutex::new(None),
            message_storage: Arc::new(Storage::new(db_path)),
            attachment_inner: AttachmentInner::new(),
            callback: Arc::new(Mutex::new(None)),
        }
    }

    pub(super) fn migrate(&self) -> Result<()> {
        prepare(&self.message_storage)
    }

    pub(super) fn on_attachment_upload_success(
        store: ClientStoreRef,
        mut pending: PendingRequest,
        result: Upload,
    ) {
        info!(
            "upload success: file:{} url:{}",
            result.file_name, result.path
        );

        let content = pending.req.content.as_mut().unwrap();
        content.attachment.take();

        content.text = result.path;
        content.size = result.size;
        content.thumbnail = result.thumbnail;
        content.placeholder = result.file_name;

        let topic_id = pending.req.topic_id.clone();
        let chat_id = pending.req.chat_id.clone();

        // update database status
        if let Err(e) =
            store.update_outoing_chat_log_state(&topic_id, &chat_id, ChatLogStatus::Sending, None)
        {
            warn!("update_message_content failed: {}", e);
        }
        // requeue to send
        spawn(async move {
            ClientStore::add_pending_request(store, pending.req, pending.callback).await;
        });
    }

    pub(crate) fn process_timeout_requests(&self) {
        if self.outgoings.lock().unwrap().len() == 0 {
            return;
        }

        let outgoings_ref = self.outgoings.clone();
        let mut outgoings = outgoings_ref.lock().unwrap();
        let mut expired = Vec::new();
        let now = now_millis();

        for (req_id, pending) in outgoings.iter() {
            if pending.is_expired() {
                expired.push(req_id.clone());
            } else {
                if pending.need_retry(now) {
                    debug!("retry send: {}", req_id);
                    self.try_send(req_id.clone());
                }
            }
        }

        for req_id in expired {
            if let Some(pending) = outgoings.remove(&req_id) {
                pending
                    .callback
                    .map(|cb| cb.on_fail("send expired".to_string()));
            }
        }
    }
    pub fn shutdown(&self) {}
}
