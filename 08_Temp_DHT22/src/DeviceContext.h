#ifndef _DeviceContext_h
#define _DeviceContext_h

#include <ArduinoJson.h>

#include "DeviceConfig.h"
#include "Transport/MessageBus.h"

class DeviceContext
{
public:
  virtual DeviceConfig& GetConfig() = 0;
  virtual MessageBus& GetMessageBus() = 0;
};

#endif
