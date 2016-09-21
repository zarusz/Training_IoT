#ifndef _DHT22FeatureController_h
#define _DHT22FeatureController_h

#include "FeatureController.h"
#include "DHT.h"

class DHT22FeatureController : public FeatureController
{
protected:
  int _pin;
  const char* _topic;
  DHT _dht;
  ulong _lastMeasure;
  ulong _lastWasTemp;

  void PublishMeasureEvent(bool isTemp, float value);

public:
  DHT22FeatureController(int port, DeviceContext* context, int pin, const char* topic);

  // override of FeatureController
  virtual void PopulateDescriptions(JsonArray& featureDescriptions);
  virtual void Loop();
};

#endif
