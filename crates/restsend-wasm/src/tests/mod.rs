use restsend_sdk::utils::sleep;
use wasm_bindgen_test::*;
wasm_bindgen_test_configure!(run_in_browser);
mod conversations;

const ENDPOINT: &str = "https://chat.ruzhila.cn";
#[wasm_bindgen_test]
async fn test_sleep() {
    sleep(std::time::Duration::from_millis(100)).await;
}

#[wasm_bindgen_test]
async fn test_auth() {
    crate::account::signin(
        ENDPOINT.to_string(),
        "bob".to_string(),
        Some("bob:demo".to_string()),
        None,
    )
    .await
    .expect("auth fail");
}

#[wasm_bindgen_test]
async fn test_connect() {
    crate::setLogging(Some("debug".to_string()));
    let info = restsend_sdk::services::auth::login_with_password(
        ENDPOINT.to_string(),
        "bob".to_string(),
        "bob:demo".to_string(),
    )
    .await
    .expect("auth fail");

    let rs_client = crate::Client::new(serde_wasm_bindgen::to_value(&info).unwrap());
    rs_client.connect().await.expect("connect fail");
}
