#ifndef _HttpMessageBus_h
#define _HttpMessageBus_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <set>
#include "MessageBus.h"
#include "JsonSerializationProvider.h"

class HttpMessageBus : public MessageBus
{
private:
	String serverHost;
 	JsonSerializationProvider* provider;
	std::set<const char*> topics;
	ulong lastPulledTime;

	bool PostJson(const char* path, const String& postPayload);
	bool GetJson(const char* path, String& payload);

	void PullMessageForTopic(const char* topic);

public:
	HttpMessageBus(const char* serverHost, JsonSerializationProvider* provider, MessageHandler* handler);
	virtual ~HttpMessageBus();

public:
	virtual bool Publish(const char* topic, JsonObject& message);
	virtual void Subscribe(const char* topic);
	virtual void Unsubscribe(const char* topic);

	virtual void Loop();
};

#endif
