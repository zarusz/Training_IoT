#ifndef _SwitchFeatureController_h
#define _SwitchFeatureController_h

#include "FeatureController.h"

class SwitchFeatureController : public FeatureController
{
protected:
  int _pin;
  bool _onIsHigh;

  void SetState(bool on);

public:
  SwitchFeatureController(int port, DeviceContext* context, int pin, bool onIsHigh);

  // override of FeatureController
  virtual void Handle(JsonObject& command);
};

#endif
