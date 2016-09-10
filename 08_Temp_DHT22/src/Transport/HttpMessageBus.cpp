#include "HttpMessageBus.h"
#include <ESP8266HTTPClient.h>
#include "../Utils/TimeUtil.h"
#include <algorithm>

// pull every 2s
#define PULL_INTERVAL 2000

HttpMessageBus::HttpMessageBus(const char* serverHost, JsonSerializationProvider* serializationProvider, MessageHandler* handler)
{
  _serverHost = serverHost;
  _serializationProvider = serializationProvider;
  SetHandler(handler);
}

HttpMessageBus::~HttpMessageBus()
{
}

bool HttpMessageBus::Publish(const char* topic, JsonObject& message)
{
  String payload = _serializationProvider->Serialize(message);
  PostJson(topic, payload);
}

void HttpMessageBus::Subscribe(const char* topic)
{
  // remember the topics
  _topics.insert(topic);
}

void HttpMessageBus::Unsubscribe(const char* topic)
{
  _topics.erase(topic);
}

void HttpMessageBus::Loop()
{
  if (!TimeUtil::IntervalPassed(_lastPullTimeMs, PULL_INTERVAL))
    return;

  // The new C++11 lambda for each
  std::for_each(_topics.begin(), _topics.end(), [this](const char* topic) {
    PullMessageForTopic(topic);
  });
}

void HttpMessageBus::PullMessageForTopic(const char* topic)
{
  String payload;
  if (GetJson(topic, payload))
  {
    JsonObject& message = _serializationProvider->Deserialize(payload);
    // check if deserialization was fine
    if (message.success())
    {
        // check if message handler is set
        if (handler)
            handler->Handle(topic, message);
    }
  }
}

bool HttpMessageBus::PostJson(const char* path, const String& postPayload)
{
  bool success = false;
  String url = _serverHost + path;

  Serial.printf("[HTTP] Connecting to %s\n", url.c_str());
  Serial.printf("[HTTP] Payload: %s\n", postPayload.c_str());

  HTTPClient http;
  http.begin(url);
  // tell the server we're posting JSON
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.POST(postPayload);
  if (httpCode > 0)
  {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] POST... response code: %d, description: %s\n", httpCode, http.errorToString(httpCode).c_str());

    // file found at server
    if (httpCode == HTTP_CODE_OK)
      success = true;
  }
  else
  {
    Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
  return success;
}

bool HttpMessageBus::GetJson(const char* path, String& payload)
{
  bool success = false;
  String url = _serverHost + path;
  Serial.printf("[HTTP] Connecting to %s\n", url.c_str());

  HTTPClient http;
  http.begin(url);

  int httpCode = http.GET();
  if (httpCode > 0)
  {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);

    // file found at server
    if (httpCode == HTTP_CODE_OK)
    {
      success = true;
      payload = http.getString();
      Serial.printf("[HTTP] Response: %s\n", payload.length() > 0 ? payload.c_str() : "(empty)");
    }
  }
  else
  {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
  return success;
}
