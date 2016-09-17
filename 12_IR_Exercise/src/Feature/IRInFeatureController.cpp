#include "IRInFeatureController.h"

#define FEATURE_TYPE_IR_IN "ir_in"

IRInFeatureController::IRInFeatureController(int port, DeviceContext* context, int pin)
  : FeatureController(port, FEATURE_TYPE_IR_IN, context),
    _irrecv(pin)
{
  _irrecv.enableIRIn();  // Start the receiver
}

void IRInFeatureController::DumpInfo(decode_results* results)
{
  // Show Encoding standard
  Serial.print("[IR-in] Encoding  : ");
  switch (results->decode_type) {
    default:
    case UNKNOWN:      Serial.print("UNKNOWN");       break ;
    case NEC:          Serial.print("NEC");           break ;
    case SONY:         Serial.print("SONY");          break ;
    case RC5:          Serial.print("RC5");           break ;
    case RC6:          Serial.print("RC6");           break ;
    case DISH:         Serial.print("DISH");          break ;
    case SHARP:        Serial.print("SHARP");         break ;
    case JVC:          Serial.print("JVC");           break ;
    case SANYO:        Serial.print("SANYO");         break ;
    case MITSUBISHI:   Serial.print("MITSUBISHI");    break ;
    case SAMSUNG:      Serial.print("SAMSUNG");       break ;
    case LG:           Serial.print("LG");            break ;
    case WHYNTER:      Serial.print("WHYNTER");       break ;
    case AIWA_RC_T501: Serial.print("AIWA_RC_T501");  break ;
    case PANASONIC:    Serial.print("PANASONIC");     break ;
  }
  Serial.println("");

  // Show Code & length
  Serial.print("[IR-in] Code      : ");
  Serial.print(results->value, HEX);
  Serial.print(" (");
  Serial.print(results->bits, DEC);
  Serial.println(" bits)");
}

void IRInFeatureController::Loop()
{
  decode_results results;        // Somewhere to store the results
  if (_irrecv.decode(&results))  // Grab an IR code
  {
    DumpInfo(&results);          // Output the results
    _irrecv.resume();            // Prepare for the next value
  }
}
