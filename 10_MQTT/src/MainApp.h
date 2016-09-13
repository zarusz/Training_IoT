// MainApp.h

#ifndef _MAINAPP_h
#define _MAINAPP_h

#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "DeviceConfig.h"
#include "Feature/FeatureController.h"
#include "Transport/MessageBus.h"
#include "Transport/MqttMessageBus.h"

#include <vector>
#include <memory>

class MainApp : public DeviceContext, public MessageHandler
{
private:
	DeviceConfig _deviceConfig;
	JsonSerializationProvider _serializationProvider;
	MqttMessageBus _messageBus;
	std::vector<FeatureController*> _features;

public:
	MainApp();
	virtual ~MainApp();

	void Init();
	void Loop();

	// from DeviceContext
	virtual DeviceConfig& GetConfig() { return _deviceConfig; }
  virtual MessageBus& GetMessageBus() { return _messageBus; }
	virtual JsonSerializationProvider& GetSerializationProvider() { return _serializationProvider; }

	// from MessageHandler
	virtual void Handle(const char* topic, JsonObject& message);

protected:
	void SetupWifi();

	void OnStart();
	void OnStop();
	void OnLoop();

	bool _sentDeviceDescription;
	bool SendDeviceDescription();
	void OnCommand(JsonObject& command);
	void OnMessage(JsonObject& command, const char* topic);
};


#endif
