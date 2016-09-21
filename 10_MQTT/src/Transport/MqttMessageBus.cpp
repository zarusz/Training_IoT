#include "MqttMessageBus.h"
#include <ESP8266HTTPClient.h>
#include "../Utils/TimeUtil.h"
#include <algorithm>

// We assume there will be only 1 instance crated.
// We need this in the static
MqttMessageBus* Singleton;

MqttMessageBus::MqttMessageBus(const char* serverHost, int serverPort,
  JsonSerializationProvider* serializationProvider,
  MessageHandler* handler, const char* deviceId)
  : _mqttClient(_espClient)
{
  _serverHost = serverHost;
  _serverPort = serverPort;
  _serializationProvider = serializationProvider;
  _deviceId = deviceId;
  SetHandler(handler);

  _mqttClient.setServer(_serverHost, _serverPort);
  _mqttClient.setCallback(MqttMessageCallback);

  // We will need the reference in the static callback
  Singleton = this;
}

MqttMessageBus::~MqttMessageBus()
{
}

bool MqttMessageBus::Publish(const char* topic, JsonObject& message)
{
  String payload = _serializationProvider->Serialize(message);
  Serial.printf("[MQTT] Publish to topic: '%s', message: '%s'\n", topic, payload.c_str());
  return _mqttClient.publish(topic, payload.c_str());
}

void MqttMessageBus::Subscribe(const char* topic)
{
  if (_topics.find(topic) != _topics.end())
  {
    // already subscribed
    return;
  }

  // remember the topics we subscribed
  _topics.insert(topic);
  // if mqtt connected then subscribe
  if (_mqttClient.connected())
  {
    _mqttClient.subscribe(topic);
  }
}

void MqttMessageBus::Unsubscribe(const char* topic)
{
  // forget about the topic
  if (_topics.erase(topic) > 0)
  {
    // if mqtt connected then unsubscribe
    if (_mqttClient.connected())
    {
      _mqttClient.unsubscribe(topic);
    }
  }
}

void MqttMessageBus::ReconnectMqtt()
{
  // Loop until we're reconnected
   while (!_mqttClient.connected())
   {
     // Create a random client ID
     String clientId = String(_deviceId) + "-" + String(random(0xffff), HEX);
     Serial.printf("[MQTT] Attempting MQTT connection (ClientId: %s)...\n", clientId.c_str());

     // Attempt to connect
     if (_mqttClient.connect(clientId.c_str()))
     {
       Serial.println("[MQTT] Connected");

       // Subscribe to all the topics
       std::for_each(_topics.begin(), _topics.end(), [this](const char* topic) {
         Serial.printf("[MQTT] Subscribing to topic: '%s'\n", topic);
         _mqttClient.subscribe(topic);
       });
     }
     else
     {
       Serial.print("[MQTT] Failed to connect, rc=");
       Serial.print(_mqttClient.state());
       Serial.println(" try again in 5 seconds");
       // Wait 5 seconds before retrying
       delay(5000);
     }
   }
}

void MqttMessageBus::Loop()
{
  if (!_mqttClient.connected())
  {
    ReconnectMqtt();
  }
  _mqttClient.loop();
}

void MqttMessageBus::MqttMessageCallback(char* topic, byte* payload, unsigned int length)
{
  if (Singleton)
    Singleton->MessageCallback(topic, payload, length);
}

void MqttMessageBus::MessageCallback(char* topic, byte* payload, unsigned int length)
{
  char payloadChars[512];
  if (length >= 512)
  {
      Serial.printf("[MQTT] Buffer too small to read message from topic '%s'\n.", topic);
      return;
  }

  memcpy(payloadChars, payload, length);
  // set null terminator
  payloadChars[length] = 0;

  Serial.printf("[MQTT] Received on topic: '%s', message: '%s'\n", topic, payloadChars);

  String payloadString = payloadChars;
  JsonObject& message = _serializationProvider->Deserialize(payloadString);
  // check if deserialization was fine
  if (!message.success())
  {
    Serial.printf("[MQTT] Could not deserialize JSON message from topic '%s'\n.", topic);
    return;
  }

  // check if message handler is set
  if (handler)
      handler->Handle(topic, message);
}
