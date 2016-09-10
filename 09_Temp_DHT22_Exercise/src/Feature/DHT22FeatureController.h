#ifndef _DHT22FeatureController_h
#define _DHT22FeatureController_h

#include "FeatureController.h"
#include "DHT.h"

class DHT22FeatureController : public FeatureController
{
protected:
  int _pin;
  DHT _dht;
  ulong _lastMeasureT;
  ulong _lastMeasureH;

  void PublishMeasureEvent(bool isTemp, float value);

public:
  DHT22FeatureController(int port, DeviceContext* context, int pin);

  // override of FeatureController
  virtual void PopulateDescriptions(JsonArray& featureDescriptions);
  virtual bool CanHandle(JsonObject& command);

  virtual void Handle(JsonObject& command);
  virtual void Loop();
};

#endif
