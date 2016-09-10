#include "LedFeatureController.h"

#define FEATURE_TYPE_LED "led"

LedFeatureController::LedFeatureController(int port, DeviceContext* context, int pin)
  : SwitchFeatureController(port, context, pin, true)
{
  type = FEATURE_TYPE_LED;
}
