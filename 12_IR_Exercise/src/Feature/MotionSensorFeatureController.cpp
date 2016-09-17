#include "MotionSensorFeatureController.h"
#include "../Utils/TimeUtil.h"

#define FEATURE_TYPE_MOTION   "motionSensor"
#define CHANGE_INTERVAL      3000
#define REPEAT_INTERVAL      5000

MotionSensorFeatureController::MotionSensorFeatureController(int port, DeviceContext* context, int pin, const char* topic)
  : FeatureController(port, FEATURE_TYPE_MOTION, context)
{
  _pin = pin;
  _topic = topic;
  pinMode(_pin, INPUT);
}

void MotionSensorFeatureController::Loop()
{
  auto motion = digitalRead(_pin) == HIGH;
  auto send = false;
  // send when motion state changes (0->1 or 1->0)
  if ((motion != _lastMotion) && TimeUtil::IntervalPassed(_lastChanged, CHANGE_INTERVAL))
  {
    _lastMotion = motion;
    send = true;
  }
  // send when motion lasts but not often then repeat interval
  if (motion && TimeUtil::IntervalPassed(_lastRepeat, REPEAT_INTERVAL))
  {
    send = true;
  }

  if (send)
  {
    Serial.printf("[MotionSensor] Motion: %d\n", motion ? 1 : 0);
    PublishMeasureEvent(motion);
  }
}

void MotionSensorFeatureController::PublishMeasureEvent(bool motion)
{
    auto& measureEvent = _context->GetSerializationProvider().CreateMessage();
    measureEvent["port"] = _port;
    measureEvent["deviceId"] = _context->GetConfig().uniqueId;
    measureEvent["type"] = _type;
    measureEvent["motion"] = motion;

    // publish the event
    _context->GetMessageBus().Publish(_topic, measureEvent);
}
