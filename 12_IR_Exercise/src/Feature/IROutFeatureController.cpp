#include "IROutFeatureController.h"

#define FEATURE_TYPE_IR_OUT "ir_out"

IROutFeatureController::IROutFeatureController(int port, DeviceContext* context, int pin)
  : FeatureController(port, FEATURE_TYPE_IR_OUT, context),
    _irsend(pin)
{
  _irsend.begin();  // Start the transceiver
}

void IROutFeatureController::Handle(JsonObject& command)
{
  auto codeType = command["codeType"].asString();
  auto& codeData = command["codeData"].asArray();

  if (strcmp(codeType, "NEC") == 0)
  {
    for(auto i = 0; i < codeData.size(); i++)
    {
      auto data = codeData[i]["data"].as<ulong>();
      auto bits = codeData[i]["bits"].as<uint>();

      Serial.printf("[IR-out] Sending code type: %s, bits: %d, data: %s\n", codeType, bits, String(data, HEX).c_str());
      _irsend.sendNEC(data, bits);
    }
  }
  else
  {
    Serial.printf("[IR-out] Unsupported code type: %s\n", codeType);
  }
}
