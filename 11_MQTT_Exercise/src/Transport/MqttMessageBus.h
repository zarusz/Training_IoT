#ifndef _MqttMessageBus_h
#define _MqttMessageBus_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <set>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "MessageBus.h"
#include "JsonSerializationProvider.h"

class MqttMessageBus : public MessageBus
{
private:
	const char* _serverHost;
	int _serverPort;
 	JsonSerializationProvider* _serializationProvider;
	const char* _deviceId;
	std::set<const char*> _topics;

	WiFiClient _espClient;
	PubSubClient _mqttClient;

	void ReconnectMqtt();
	static void MqttMessageCallback(char* topic, byte* payload, unsigned int length);
	void MessageCallback(char* topic, byte* payload, unsigned int length);
	bool PublishInternal(const char* topic, const char* payload, bool retain);

public:
	MqttMessageBus(const char* serverHost, int serverPort, JsonSerializationProvider* serializationProvider, MessageHandler* handler, const char* deviceId);
	virtual ~MqttMessageBus();

public:
	virtual bool Publish(const char* topic, JsonObject& message);
	virtual void Subscribe(const char* topic);
	virtual void Unsubscribe(const char* topic);

	virtual void Loop();
};

#endif
