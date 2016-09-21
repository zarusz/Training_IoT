#ifndef _IROutFeatureController_h
#define _IROutFeatureController_h

#include "FeatureController.h"

#include <IRremoteESP8266.h>

class IROutFeatureController : public FeatureController
{
private:
  IRsend _irsend;

public:
  IROutFeatureController(int port, DeviceContext* context, int pin);

protected:
  virtual void Handle(JsonObject& command);
};

#endif
