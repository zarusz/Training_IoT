#ifndef _SwitchFeatureController_h
#define _SwitchFeatureController_h

#include "FeatureController.h"

class SwitchFeatureController : public FeatureController
{
protected:
  int pin;
  bool onIsHigh;

  void SetState(bool on);

public:
  SwitchFeatureController(int port, DeviceContext* context, int pin, bool onIsHigh);

  virtual void Handle(JsonObject& command);
  virtual void Loop();
};

#endif
