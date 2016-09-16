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
    auto& code = command["code"].asObject();
    auto codeType = code["type"].asString();
    auto codeData = code["data"].as<ulong>();
    auto codeBits = code["bits"].as<uint>();

    if (strcmp(codeType, "NEC"))
    {
      Serial.printf("[IR-out] Sending code type: %s, bits: %d, data: %s\n", codeType, codeBits, String(codeData, HEX).c_str());
      _irsend.sendNEC(codeData, codeBits);
    }
    else
    {
      Serial.printf("[IR-out] Unsupported code type: %s\n", codeType);
    }
}
