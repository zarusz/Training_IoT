#ifndef _LedFeatureController_h
#define _LedFeatureController_h

#include "FeatureController.h"
#include "SwitchFeatureController.h"

class LedFeatureController : public SwitchFeatureController
{
public:
  LedFeatureController(int port, DeviceContext* context, int pin);
};

#endif
