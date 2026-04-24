# Non-blocking Retry Logic Strategy

To avoid blocking the main execution loop (Communication Sentry Lab), use `millis()` instead of `delay()`.

## Example Pattern

```cpp
unsigned long lastRetryTime = 0;
const unsigned long retryInterval = 5000; // 5 seconds

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    if (millis() - lastRetryTime > retryInterval) {
      Serial.println("Attempting to reconnect...");
      WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
      lastRetryTime = millis();
    }
  }
  
  // Other tasks (e.g., sensor sampling) continue to run here
}
```
