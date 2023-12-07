// This file was autogenerated by some hot garbage in the `uniffi` crate.
// Trust me, you don't want to mess with it!

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// The following structs are used to implement the lowest level
// of the FFI, and thus useful to multiple uniffied crates.
// We ensure they are declared exactly once, with a header guard, UNIFFI_SHARED_H.
#ifdef UNIFFI_SHARED_H
    // We also try to prevent mixing versions of shared uniffi header structs.
    // If you add anything to the #else block, you must increment the version suffix in UNIFFI_SHARED_HEADER_V4
    #ifndef UNIFFI_SHARED_HEADER_V4
        #error Combining helper code from multiple versions of uniffi is not supported
    #endif // ndef UNIFFI_SHARED_HEADER_V4
#else
#define UNIFFI_SHARED_H
#define UNIFFI_SHARED_HEADER_V4
// ⚠️ Attention: If you change this #else block (ending in `#endif // def UNIFFI_SHARED_H`) you *must* ⚠️
// ⚠️ increment the version suffix in all instances of UNIFFI_SHARED_HEADER_V4 in this file.           ⚠️

typedef struct RustBuffer
{
    int32_t capacity;
    int32_t len;
    uint8_t *_Nullable data;
} RustBuffer;

typedef int32_t (*ForeignCallback)(uint64_t, int32_t, const uint8_t *_Nonnull, int32_t, RustBuffer *_Nonnull);

// Task defined in Rust that Swift executes
typedef void (*UniFfiRustTaskCallback)(const void * _Nullable, int8_t);

// Callback to execute Rust tasks using a Swift Task
//
// Args:
//   executor: ForeignExecutor lowered into a size_t value
//   delay: Delay in MS
//   task: UniFfiRustTaskCallback to call
//   task_data: data to pass the task callback
typedef int8_t (*UniFfiForeignExecutorCallback)(size_t, uint32_t, UniFfiRustTaskCallback _Nullable, const void * _Nullable);

typedef struct ForeignBytes
{
    int32_t len;
    const uint8_t *_Nullable data;
} ForeignBytes;

// Error definitions
typedef struct RustCallStatus {
    int8_t code;
    RustBuffer errorBuf;
} RustCallStatus;

// ⚠️ Attention: If you change this #else block (ending in `#endif // def UNIFFI_SHARED_H`) you *must* ⚠️
// ⚠️ increment the version suffix in all instances of UNIFFI_SHARED_HEADER_V4 in this file.           ⚠️
#endif // def UNIFFI_SHARED_H

// Continuation callback for UniFFI Futures
typedef void (*UniFfiRustFutureContinuation)(void * _Nonnull, int8_t);

// Scaffolding functions
void uniffi_restsend_ffi_fn_free_rsclient(void*_Nonnull ptr, RustCallStatus *_Nonnull out_status
);
void*_Nonnull uniffi_restsend_ffi_fn_constructor_rsclient_new(RustBuffer root_path, RustBuffer db_name, RustBuffer info, RustCallStatus *_Nonnull out_status
);
void uniffi_restsend_ffi_fn_method_rsclient_app_active(void*_Nonnull ptr, RustCallStatus *_Nonnull out_status
);
void uniffi_restsend_ffi_fn_method_rsclient_app_deactivate(void*_Nonnull ptr, RustCallStatus *_Nonnull out_status
);
void* _Nonnull uniffi_restsend_ffi_fn_method_rsclient_connect(void*_Nonnull ptr, uint64_t callback
);
RustBuffer uniffi_restsend_ffi_fn_method_rsclient_get_conversation(void*_Nonnull ptr, RustBuffer topic_id, RustCallStatus *_Nonnull out_status
);
void uniffi_restsend_ffi_fn_method_rsclient_remove_conversation(void*_Nonnull ptr, RustBuffer topic_id, RustCallStatus *_Nonnull out_status
);
void uniffi_restsend_ffi_fn_method_rsclient_set_conversation_mute(void*_Nonnull ptr, RustBuffer topic_id, int8_t mute, RustCallStatus *_Nonnull out_status
);
void uniffi_restsend_ffi_fn_method_rsclient_set_conversation_read(void*_Nonnull ptr, RustBuffer topic_id, RustCallStatus *_Nonnull out_status
);
void uniffi_restsend_ffi_fn_method_rsclient_set_conversation_sticky(void*_Nonnull ptr, RustBuffer topic_id, int8_t sticky, RustCallStatus *_Nonnull out_status
);
void uniffi_restsend_ffi_fn_method_rsclient_shutdown(void*_Nonnull ptr, RustCallStatus *_Nonnull out_status
);
void uniffi_restsend_ffi_fn_method_rsclient_sync_conversations(void*_Nonnull ptr, RustBuffer updated_at, uint32_t limit, uint64_t callback, RustCallStatus *_Nonnull out_status
);
void uniffi_restsend_ffi_fn_init_callback_rscallback(ForeignCallback _Nonnull callback_stub, RustCallStatus *_Nonnull out_status
);
void uniffi_restsend_ffi_fn_init_callback_rssyncconversationscallback(ForeignCallback _Nonnull callback_stub, RustCallStatus *_Nonnull out_status
);
RustBuffer uniffi_restsend_ffi_fn_func_get_current_user(RustBuffer root_path, RustCallStatus *_Nonnull out_status
);
void uniffi_restsend_ffi_fn_func_init_log(RustBuffer level, int8_t is_test, RustCallStatus *_Nonnull out_status
);
void* _Nonnull uniffi_restsend_ffi_fn_func_login(RustBuffer endpoint, RustBuffer user_id, RustBuffer password
);
void uniffi_restsend_ffi_fn_func_set_current_user(RustBuffer root_path, RustBuffer user_id, RustCallStatus *_Nonnull out_status
);
RustBuffer ffi_restsend_ffi_rustbuffer_alloc(int32_t size, RustCallStatus *_Nonnull out_status
);
RustBuffer ffi_restsend_ffi_rustbuffer_from_bytes(ForeignBytes bytes, RustCallStatus *_Nonnull out_status
);
void ffi_restsend_ffi_rustbuffer_free(RustBuffer buf, RustCallStatus *_Nonnull out_status
);
RustBuffer ffi_restsend_ffi_rustbuffer_reserve(RustBuffer buf, int32_t additional, RustCallStatus *_Nonnull out_status
);
void ffi_restsend_ffi_rust_future_continuation_callback_set(UniFfiRustFutureContinuation _Nonnull callback
);
void ffi_restsend_ffi_rust_future_poll_u8(void* _Nonnull handle, void* _Nonnull uniffi_callback
);
void ffi_restsend_ffi_rust_future_cancel_u8(void* _Nonnull handle
);
void ffi_restsend_ffi_rust_future_free_u8(void* _Nonnull handle
);
uint8_t ffi_restsend_ffi_rust_future_complete_u8(void* _Nonnull handle, RustCallStatus *_Nonnull out_status
);
void ffi_restsend_ffi_rust_future_poll_i8(void* _Nonnull handle, void* _Nonnull uniffi_callback
);
void ffi_restsend_ffi_rust_future_cancel_i8(void* _Nonnull handle
);
void ffi_restsend_ffi_rust_future_free_i8(void* _Nonnull handle
);
int8_t ffi_restsend_ffi_rust_future_complete_i8(void* _Nonnull handle, RustCallStatus *_Nonnull out_status
);
void ffi_restsend_ffi_rust_future_poll_u16(void* _Nonnull handle, void* _Nonnull uniffi_callback
);
void ffi_restsend_ffi_rust_future_cancel_u16(void* _Nonnull handle
);
void ffi_restsend_ffi_rust_future_free_u16(void* _Nonnull handle
);
uint16_t ffi_restsend_ffi_rust_future_complete_u16(void* _Nonnull handle, RustCallStatus *_Nonnull out_status
);
void ffi_restsend_ffi_rust_future_poll_i16(void* _Nonnull handle, void* _Nonnull uniffi_callback
);
void ffi_restsend_ffi_rust_future_cancel_i16(void* _Nonnull handle
);
void ffi_restsend_ffi_rust_future_free_i16(void* _Nonnull handle
);
int16_t ffi_restsend_ffi_rust_future_complete_i16(void* _Nonnull handle, RustCallStatus *_Nonnull out_status
);
void ffi_restsend_ffi_rust_future_poll_u32(void* _Nonnull handle, void* _Nonnull uniffi_callback
);
void ffi_restsend_ffi_rust_future_cancel_u32(void* _Nonnull handle
);
void ffi_restsend_ffi_rust_future_free_u32(void* _Nonnull handle
);
uint32_t ffi_restsend_ffi_rust_future_complete_u32(void* _Nonnull handle, RustCallStatus *_Nonnull out_status
);
void ffi_restsend_ffi_rust_future_poll_i32(void* _Nonnull handle, void* _Nonnull uniffi_callback
);
void ffi_restsend_ffi_rust_future_cancel_i32(void* _Nonnull handle
);
void ffi_restsend_ffi_rust_future_free_i32(void* _Nonnull handle
);
int32_t ffi_restsend_ffi_rust_future_complete_i32(void* _Nonnull handle, RustCallStatus *_Nonnull out_status
);
void ffi_restsend_ffi_rust_future_poll_u64(void* _Nonnull handle, void* _Nonnull uniffi_callback
);
void ffi_restsend_ffi_rust_future_cancel_u64(void* _Nonnull handle
);
void ffi_restsend_ffi_rust_future_free_u64(void* _Nonnull handle
);
uint64_t ffi_restsend_ffi_rust_future_complete_u64(void* _Nonnull handle, RustCallStatus *_Nonnull out_status
);
void ffi_restsend_ffi_rust_future_poll_i64(void* _Nonnull handle, void* _Nonnull uniffi_callback
);
void ffi_restsend_ffi_rust_future_cancel_i64(void* _Nonnull handle
);
void ffi_restsend_ffi_rust_future_free_i64(void* _Nonnull handle
);
int64_t ffi_restsend_ffi_rust_future_complete_i64(void* _Nonnull handle, RustCallStatus *_Nonnull out_status
);
void ffi_restsend_ffi_rust_future_poll_f32(void* _Nonnull handle, void* _Nonnull uniffi_callback
);
void ffi_restsend_ffi_rust_future_cancel_f32(void* _Nonnull handle
);
void ffi_restsend_ffi_rust_future_free_f32(void* _Nonnull handle
);
float ffi_restsend_ffi_rust_future_complete_f32(void* _Nonnull handle, RustCallStatus *_Nonnull out_status
);
void ffi_restsend_ffi_rust_future_poll_f64(void* _Nonnull handle, void* _Nonnull uniffi_callback
);
void ffi_restsend_ffi_rust_future_cancel_f64(void* _Nonnull handle
);
void ffi_restsend_ffi_rust_future_free_f64(void* _Nonnull handle
);
double ffi_restsend_ffi_rust_future_complete_f64(void* _Nonnull handle, RustCallStatus *_Nonnull out_status
);
void ffi_restsend_ffi_rust_future_poll_pointer(void* _Nonnull handle, void* _Nonnull uniffi_callback
);
void ffi_restsend_ffi_rust_future_cancel_pointer(void* _Nonnull handle
);
void ffi_restsend_ffi_rust_future_free_pointer(void* _Nonnull handle
);
void*_Nonnull ffi_restsend_ffi_rust_future_complete_pointer(void* _Nonnull handle, RustCallStatus *_Nonnull out_status
);
void ffi_restsend_ffi_rust_future_poll_rust_buffer(void* _Nonnull handle, void* _Nonnull uniffi_callback
);
void ffi_restsend_ffi_rust_future_cancel_rust_buffer(void* _Nonnull handle
);
void ffi_restsend_ffi_rust_future_free_rust_buffer(void* _Nonnull handle
);
RustBuffer ffi_restsend_ffi_rust_future_complete_rust_buffer(void* _Nonnull handle, RustCallStatus *_Nonnull out_status
);
void ffi_restsend_ffi_rust_future_poll_void(void* _Nonnull handle, void* _Nonnull uniffi_callback
);
void ffi_restsend_ffi_rust_future_cancel_void(void* _Nonnull handle
);
void ffi_restsend_ffi_rust_future_free_void(void* _Nonnull handle
);
void ffi_restsend_ffi_rust_future_complete_void(void* _Nonnull handle, RustCallStatus *_Nonnull out_status
);
uint16_t uniffi_restsend_ffi_checksum_func_get_current_user(void
    
);
uint16_t uniffi_restsend_ffi_checksum_func_init_log(void
    
);
uint16_t uniffi_restsend_ffi_checksum_func_login(void
    
);
uint16_t uniffi_restsend_ffi_checksum_func_set_current_user(void
    
);
uint16_t uniffi_restsend_ffi_checksum_method_rsclient_app_active(void
    
);
uint16_t uniffi_restsend_ffi_checksum_method_rsclient_app_deactivate(void
    
);
uint16_t uniffi_restsend_ffi_checksum_method_rsclient_connect(void
    
);
uint16_t uniffi_restsend_ffi_checksum_method_rsclient_get_conversation(void
    
);
uint16_t uniffi_restsend_ffi_checksum_method_rsclient_remove_conversation(void
    
);
uint16_t uniffi_restsend_ffi_checksum_method_rsclient_set_conversation_mute(void
    
);
uint16_t uniffi_restsend_ffi_checksum_method_rsclient_set_conversation_read(void
    
);
uint16_t uniffi_restsend_ffi_checksum_method_rsclient_set_conversation_sticky(void
    
);
uint16_t uniffi_restsend_ffi_checksum_method_rsclient_shutdown(void
    
);
uint16_t uniffi_restsend_ffi_checksum_method_rsclient_sync_conversations(void
    
);
uint16_t uniffi_restsend_ffi_checksum_constructor_rsclient_new(void
    
);
uint16_t uniffi_restsend_ffi_checksum_method_rscallback_on_connected(void
    
);
uint16_t uniffi_restsend_ffi_checksum_method_rscallback_on_connecting(void
    
);
uint16_t uniffi_restsend_ffi_checksum_method_rscallback_on_token_expired(void
    
);
uint16_t uniffi_restsend_ffi_checksum_method_rscallback_on_net_broken(void
    
);
uint16_t uniffi_restsend_ffi_checksum_method_rscallback_on_kickoff_by_other_client(void
    
);
uint16_t uniffi_restsend_ffi_checksum_method_rscallback_on_system_request(void
    
);
uint16_t uniffi_restsend_ffi_checksum_method_rscallback_on_unknown_request(void
    
);
uint16_t uniffi_restsend_ffi_checksum_method_rscallback_on_topic_typing(void
    
);
uint16_t uniffi_restsend_ffi_checksum_method_rscallback_on_new_message(void
    
);
uint16_t uniffi_restsend_ffi_checksum_method_rscallback_on_topic_read(void
    
);
uint16_t uniffi_restsend_ffi_checksum_method_rscallback_on_conversations_updated(void
    
);
uint16_t uniffi_restsend_ffi_checksum_method_rscallback_on_conversations_removed(void
    
);
uint16_t uniffi_restsend_ffi_checksum_method_rssyncconversationscallback_on_success(void
    
);
uint16_t uniffi_restsend_ffi_checksum_method_rssyncconversationscallback_on_fail(void
    
);
uint32_t ffi_restsend_ffi_uniffi_contract_version(void
    
);

