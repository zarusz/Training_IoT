#ifndef _MessageBus_h
#define _MessageBus_h

#include <Arduino.h>
#include <ArduinoJson.h>

class MessageHandler
{
public:
	virtual void Handle(const char* topic, JsonObject& message) = 0;
};

class MessageBus
{
protected:
	MessageHandler* handler;

public:
	virtual bool Publish(const char* topic, JsonObject& message) = 0;
	virtual void Subscribe(const char* topic) = 0;
	virtual void Unsubscribe(const char* topic) = 0;
	virtual void SetHandler(MessageHandler* handler);
};

#endif
