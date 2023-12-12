use super::api_call;
use crate::models::Conversation;
use crate::Result;
use crate::{
    models::{ListUserResult, Topic},
    services::USERS_LIMIT,
    utils::now_millis,
};

pub async fn get_topic(endpoint: &str, token: &str, topic_id: &str) -> Result<Topic> {
    api_call(endpoint, &format!("/topic/info/{}", topic_id), token, None)
        .await
        .map(|mut topic: Topic| {
            topic.cached_at = now_millis();
            if !topic.icon.is_empty() && !topic.icon.starts_with("http") {
                topic.icon = format!("{}{}", endpoint.trim_end_matches('/'), topic.icon);
            }
            topic
        })
}

pub async fn get_topic_members(
    endpoint: &str,
    token: &str,
    topic_id: &str,
    updated_at: &str,
    limit: u32,
) -> Result<ListUserResult> {
    let data = serde_json::json!({
        "topicId": topic_id,
        "limit": limit.min(USERS_LIMIT),
        "updatedAt":updated_at,
    })
    .to_string();

    api_call(
        endpoint,
        &format!("/topic/members/{}", topic_id),
        token,
        Some(data),
    )
    .await
    .map(|mut lr: ListUserResult| {
        lr.items.iter_mut().for_each(|user| {
            user.cached_at = now_millis();
            if !user.avatar.is_empty() && !user.avatar.starts_with("http") {
                user.avatar = format!("{}{}", endpoint.trim_end_matches('/'), user.avatar);
            }
        });
        lr
    })
}

pub async fn create_topic(
    endpoint: &str,
    token: &str,
    name: &str,
    icon: &str,
    members: Vec<String>,
) -> Result<Topic> {
    let data = serde_json::json!({
        "name": name,
        "icon": icon,
        "members": members
    })
    .to_string();
    api_call(endpoint, "/topic/create", token, Some(data)).await
}

pub async fn create_chat(endpoint: &str, token: &str, user_id: &str) -> Result<Conversation> {
    api_call(endpoint, &format!("/topic/create/{}", user_id), token, None).await
}

pub async fn join_topic(
    endpoint: &str,
    token: &str,
    topic_id: &str,
    message: &str,
    source: &str,
) -> Result<()> {
    let data = serde_json::json!({
        "message": message,
        "source": source,
    })
    .to_string();

    api_call(
        endpoint,
        &format!("/topic/knock/{}", topic_id),
        token,
        Some(data),
    )
    .await
    .map(|_: bool| ())
}

pub async fn invite_topic_member(
    endpoint: &str,
    token: &str,
    topic_id: &str,
    user_id: &str,
) -> Result<()> {
    api_call(
        endpoint,
        &format!("/topic/invite/{}/{}", topic_id, user_id),
        token,
        None,
    )
    .await
    .map(|_: bool| ())
}
