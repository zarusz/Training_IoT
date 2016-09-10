// MainApp.h

#ifndef _MAINAPP_h
#define _MAINAPP_h

#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "DeviceConfig.h"
#include "Feature/FeatureController.h"
#include "Transport/MessageBus.h"
#include "Transport/HttpMessageBus.h"

#include <vector>
#include <memory>

class MainApp : public DeviceContext, public MessageHandler
{
private:
	DeviceConfig _deviceConfig;
	JsonSerializationProvider _serializationProvider;
	HttpMessageBus _messageBus;
	//WiFiClient espClient;
	//PubSubClient pubSubClient;
	//String deviceInTopic;
	//DeviceDescription deviceDescription;
	std::vector<FeatureController*> _features;

	ulong lastMsg = 0;
	char msg[256];
	int value = 0;

public:
	MainApp();
	virtual ~MainApp();

	void Init();
	void Loop();

	// from DeviceContext
	virtual DeviceConfig& GetConfig() { return _deviceConfig; }
  virtual MessageBus& GetMessageBus() { return _messageBus; }

	// from MessageHandler
	virtual void Handle(const char* topic, JsonObject& message);

protected:
	void SetupWifi();
	//void ReconnectPubSub();

	//bool DecodeMessage(byte* payload, unsigned int length, const pb_field_t* msg_fields, void* msg) const;
	//bool EncodeMessage(byte* payload, unsigned int maxLength, unsigned int& length, const pb_field_t* msg_fields, const void* msg) const;

	//void DebugRetrievedMessage(const char* topic, byte* payload, unsigned int length);

	void OnStart();
	void OnStop();
	void OnLoop();

	void SendDeviceDescription();
	void OnCommand(JsonObject& command);

public:
	//bool PublishMessage(const char* topic, const pb_field_t* msg_fields, const void* msg);
};


#endif
