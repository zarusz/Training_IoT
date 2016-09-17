#ifndef _MotionSensorFeatureController_h
#define _MotionSensorFeatureController_h

#include "FeatureController.h"
#include "DHT.h"

class MotionSensorFeatureController : public FeatureController
{
protected:
  int _pin;
  const char* _topic;
  ulong _lastChanged;
  ulong _lastRepeat;
  bool _lastMotion;

  void PublishMeasureEvent(bool motion);

public:
  MotionSensorFeatureController(int port, DeviceContext* context, int pin, const char* topic);

  // override of FeatureController
  virtual void Loop();
};

#endif
