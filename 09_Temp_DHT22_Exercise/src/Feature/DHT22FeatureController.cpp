#include "DHT22FeatureController.h"
#include "../Utils/TimeUtil.h"

#define FEATURE_TYPE_TEMPERATURE  "temperatureSensor"
#define FEATURE_TYPE_HUMIDITY     "humiditySensor"
#define MEASURE_INTERVAL          5000

DHT22FeatureController::DHT22FeatureController(int port, DeviceContext* context, int pin, const char* topic)
  : FeatureController(port, FEATURE_TYPE_TEMPERATURE, context),
    _dht(pin, DHT22)
{
  _pin = pin;
  _topic = topic;
  _dht.begin();
  _lastMeasure = millis();
  // postpone humidity measure by half the interval
  _lastWasTemp = false;
}

void DHT22FeatureController::PopulateDescriptions(JsonArray& featureDescriptions)
{
  PopulateDescription(featureDescriptions, FEATURE_TYPE_TEMPERATURE);
  PopulateDescription(featureDescriptions, FEATURE_TYPE_HUMIDITY);
}

void DHT22FeatureController::Loop()
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)

  if (!TimeUtil::IntervalPassed(_lastMeasure, MEASURE_INTERVAL))
  {
    return;
  }
  bool failed = false;

  _lastWasTemp = !_lastWasTemp;
  // when last temp was measured, this time measure humidity
  if (_lastWasTemp)
  {
    // Read humidity (%)
    float h = _dht.readHumidity();
    if (!isnan(h)) {
      Serial.printf("[DHT22] Humidity: %d %%\n", (int)h);
      PublishMeasureEvent(false, h);
    } else {
      failed = true;
    }
  }
  else
  {
    // Read temperature (Celsius)
    float t = _dht.readTemperature();
    if (!isnan(t)) {
      Serial.printf("[DHT22] Temperature: %d C\n", (int)t);
      PublishMeasureEvent(true, t);
    } else {
      failed = true;
    }
  }

  if (failed)
  {
    Serial.println("[DHT22] Failed to read from DHT sensor!");
  }
}

void DHT22FeatureController::PublishMeasureEvent(bool isTemp, float value)
{
    auto& measureEvent = _context->GetSerializationProvider().CreateMessage();
    measureEvent["port"] = _port;
    measureEvent["deviceId"] = _context->GetConfig().uniqueId;

    if (isTemp)
    {
      measureEvent["type"] = FEATURE_TYPE_TEMPERATURE;
      measureEvent["temperature"] = value;
    }
    else
    {
      measureEvent["type"] = FEATURE_TYPE_HUMIDITY;
      measureEvent["humidity"] = value;
    }

    // publish the event
    _context->GetMessageBus().Publish(_topic, measureEvent);
}
