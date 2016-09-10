#include "HttpMessageBus.h"
#include <ESP8266HTTPClient.h>
#include "../Utils/TimeUtil.h"

// pull every 2s
#define PULL_INTERVAL 2000

HttpMessageBus::HttpMessageBus(const char* serverHost, JsonSerializationProvider* provider, MessageHandler* handler)
{
  this->serverHost = serverHost;
  this->provider = provider;
  SetHandler(handler);
}

HttpMessageBus::~HttpMessageBus()
{
}

bool HttpMessageBus::Publish(const char* topic, JsonObject& message)
{
  String payload = provider->Serialize(message);
  PostJson(topic, payload);
}

void HttpMessageBus::Subscribe(const char* topic)
{
  // remember the topics
  topics.insert(topic);
}

void HttpMessageBus::Unsubscribe(const char* topic)
{
  topics.erase(topic);
}

void HttpMessageBus::Loop()
{
  if (!TimeUtil::IntervalPassed(lastPulledTime, PULL_INTERVAL))
    return;

  for (auto topicIt = topics.begin(); topicIt != topics.end(); ++topicIt)
  {
    auto topic = *topicIt;
    PullMessageForTopic(topic);
  }
}

void HttpMessageBus::PullMessageForTopic(const char* topic)
{
  String payload;
  if (GetJson(topic, payload))
  {
    JsonObject& message = provider->Deserialize(payload);
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
  String url = serverHost + path;

  Serial.printf("Connecting to %s\n", url.c_str());
  Serial.printf("Payload: %s\n", postPayload.c_str());

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
    {
      success = true;
    }
  }
  else
  {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
  return success;
}

bool HttpMessageBus::GetJson(const char* path, String& payload)
{
  bool success = false;
  String url = serverHost + path;
  Serial.printf("Connecting to %s\n", url.c_str());

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
      Serial.printf("Response: %s\n", payload.length() > 0 ? payload.c_str() : "(empty)");
    }
  }
  else
  {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
  return success;
}
