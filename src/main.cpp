#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "api_config.h"

void setup() {
  Serial.begin(115200);

  // 1. WiFi Connection
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  // 2. HTTP GET Example (Digital Waiter Lab)
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(API_ENDPOINT_GET);
    
    int httpResponseCode = http.GET();
    
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("GET Response Code: " + String(httpResponseCode));
      Serial.println("Response: " + response);
    } else {
      Serial.println("Error on GET request: " + String(httpResponseCode));
    }
    http.end();
  }

  // 3. HTTP POST Example (Data Integrator Lab)
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(API_ENDPOINT_POST);
    http.addHeader("Content-Type", "application/json");

    // Create JSON document
    StaticJsonDocument<200> doc;
    doc["sensor"] = "temperature";
    doc["value"] = 25.5;
    
    String httpRequestData;
    serializeJson(doc, httpRequestData);

    int httpResponseCode = http.POST(httpRequestData);
    
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("POST Response Code: " + String(httpResponseCode));
      Serial.println("Response: " + response);
    } else {
      Serial.println("Error on POST request: " + String(httpResponseCode));
    }
    http.end();
  }
}

void loop() {
  // Implement non-blocking retry logic here using millis() (Communication Sentry Lab)
}
