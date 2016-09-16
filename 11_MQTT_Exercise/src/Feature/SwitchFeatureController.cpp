#include "SwitchFeatureController.h"

#define FEATURE_TYPE_SWITCH "switch"

SwitchFeatureController::SwitchFeatureController(int port, DeviceContext* context, int pin, bool onIsHigh)
  : FeatureController(port, FEATURE_TYPE_SWITCH, context)
{
  _pin = pin;
  _onIsHigh = onIsHigh;

  pinMode(_pin, OUTPUT);
  SetState(false);
}

void SwitchFeatureController::Handle(JsonObject& command)
{
  Serial.println("[SWITCH] Handle");

  const bool on = command["on"].as<bool>();

  Serial.printf("[SWITCH] SwitchCommand for port %d with %s.\n", _port, on ? "turn on" : "turn off");
  SetState(on);
}

void SwitchFeatureController::SetState(bool on)
{
  auto onState = on ? (_onIsHigh ? HIGH : LOW) : (_onIsHigh ? LOW : HIGH);
  digitalWrite(_pin, onState);
}
