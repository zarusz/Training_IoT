#ifndef _IRInFeatureController_h
#define _IRInFeatureController_h

#include "FeatureController.h"

#include <IRremoteESP8266.h>

class IRInFeatureController : public FeatureController
{
private:
  IRrecv _irrecv;

  void DumpInfo(decode_results* results);

public:
  IRInFeatureController(int port, DeviceContext* context, int pin);

  virtual void Loop();
};

#endif
