### 11. Exercise for (`10_MQTT`)


We have modified the `Transport/MqttMessageBus.cpp` in two places:

```cpp
#define OFFLINE_MESSAGE "{ \"online\": false }"
#define ONLINE_MESSAGE "{ \"online\": true }"

void MqttMessageBus::ReconnectMqtt()
{
  // Loop until we're reconnected
   while (!_mqttClient.connected())
   {
     // Create a random client ID
     String clientId = String(_deviceId) + "-" + String(random(0xffff), HEX);
     Serial.printf("[MQTT] Attempting MQTT connection (ClientId: %s)...\n", clientId.c_str());

     // Attempt to connect
     String statusTopic = String(_deviceId) + "/status";
     // boolean connect(const char* id, const char* willTopic, uint8_t willQos, boolean willRetain, const char* willMessage);
     if (_mqttClient.connect(clientId.c_str(), statusTopic.c_str(), MQTTQOS0, true, OFFLINE_MESSAGE))
     {
       // ...

       // boolean publish(const char* topic, const char* payload, boolean retained);
       PublishInternal(statusTopic.c_str(), ONLINE_MESSAGE, true);
     }
     else
     {
       // ...
     }
   }
}
```

In short we pass the last will message during `connect()` and specify the retain flag.
Also soon after device connect we also send an online message with retain flag to that same topic.


Notice that we extracted `PublishInternal` method from public `Publish`:

```cpp
bool MqttMessageBus::Publish(const char* topic, JsonObject& message)
{
  String payload = _serializationProvider->Serialize(message);
  return PublishInternal(topic, payload.c_str(), false);
}

bool MqttMessageBus::PublishInternal(const char* topic, const char* payload, bool retain)
{
  Serial.printf("[MQTT] Publish to topic: '%s', message: '%s'\n", topic, payload);
  return _mqttClient.publish(topic, payload, retain);
}
```


Lets test this...

After the device start, we subscribe to the `my_device_id/status` topic:
```
$ mosquitto_sub -t my_device_id/status
{ "online": true }
```

This is expected as the message was *retained*, which means any new subscriber will receive the last *good known value*.

When we now unplug the device, after few seconds Mosquitto detects, the client is offline and sends the *last will message (LWT)*

```
{ "online": false }
```
