#include "SwitchFeatureController.h"

#define FEATURE_TYPE_SWITCH "switch"

SwitchFeatureController::SwitchFeatureController(int port, DeviceContext* context, int pin, bool onIsHigh)
  : FeatureController(port, FEATURE_TYPE_SWITCH, context)
{
  this->pin = pin;
  this->onIsHigh = onIsHigh;

  pinMode(pin, OUTPUT);
  SetState(false);
}

void SwitchFeatureController::Handle(JsonObject& command)
{
  Serial.println("SwitchFeatureController:Handle");

  const bool on = command["on"].as<bool>();

  Serial.printf("SwitchCommand for port %d with %s.\n", port, on ? "turn on" : "turn off");
  SetState(on);
}

void SwitchFeatureController::SetState(bool on)
{
  auto onState = on ? (onIsHigh ? HIGH : LOW) : (onIsHigh ? LOW : HIGH);
  digitalWrite(pin, onState);
}

void SwitchFeatureController::Loop()
{
  // nothing to do for a switch
}
