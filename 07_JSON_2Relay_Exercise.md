### 07. Exercise from 06. (07_RemoteControl_JSON_Device_Exercise)

The exercises from the previous step are in the `06_RemoteControl_JSON_Device_Exercise` folder.

We defined some constants for the LEDs and switches:
```cpp
#define LED1_PIN 13
#define LED1_PORT 1

#define LED2_PIN 12
#define LED2_PORT 2

#define LED3_PIN 14
#define LED3_PORT 3

#define SWITCH1_PIN 4
#define SWITCH1_PORT 4

#define SWITCH2_PIN 5
#define SWITCH2_PORT 5

#define FEATURE_TYPE_LED "led"
#define FEATURE_TYPE_SWITCH "switch"
```

The device description message adds 2 more LEDs and 2 switches:
```cpp
String createDeviceDescriptionJson()
{
  StaticJsonBuffer<512> jsonBuffer;

  JsonObject& root = jsonBuffer.createObject();
  root["deviceId"] = device_id;
  JsonArray& features = root.createNestedArray("features");

  JsonObject& featureLed1 = jsonBuffer.createObject();
  featureLed1["type"] = FEATURE_TYPE_LED;
  featureLed1["port"] = LED1_PORT;
  features.add(featureLed1);

  JsonObject& featureLed2 = jsonBuffer.createObject();
  featureLed2["type"] = FEATURE_TYPE_LED;
  featureLed2["port"] = LED2_PORT;
  features.add(featureLed2);

  JsonObject& featureLed3 = jsonBuffer.createObject();
  featureLed3["type"] = FEATURE_TYPE_LED;
  featureLed3["port"] = LED3_PORT;
  features.add(featureLed3);

  JsonObject& featureSwitch1 = jsonBuffer.createObject();
  featureSwitch1["type"] = FEATURE_TYPE_SWITCH;
  featureSwitch1["port"] = SWITCH1_PORT;
  features.add(featureSwitch1);

  JsonObject& featureSwitch2 = jsonBuffer.createObject();
  featureSwitch2["type"] = FEATURE_TYPE_SWITCH;
  featureSwitch2["port"] = SWITCH2_PORT;
  features.add(featureSwitch2);

  char buffer[512];
  root.printTo(buffer, sizeof(buffer));
  return String(buffer);
}
```

It looks like the buffer 512 is still sufficient. We should keep an eye on this and increse the buffer once our device handles more features.

The command handling method also changed:

```cpp
void handleCommand(JsonObject& command)
{
  // handle the command
  const char* type = command["type"].asString();
  const int port = command["port"].as<int>();
  if (strcmp(type, FEATURE_TYPE_LED) == 0)
  {
    // handle LED type
    const bool on = command["on"].as<bool>();
    int pin = -1;
    switch (port)
    {
      case LED1_PORT:
        pin = LED1_PIN;
        break;
      case LED2_PORT:
        pin = LED2_PIN;
        break;
      case LED3_PORT:
        pin = LED3_PIN;
        break;
    }
    if (pin != -1)
      digitalWrite(pin, on ? HIGH : LOW);
  }
  else if (strcmp(type, FEATURE_TYPE_SWITCH) == 0)
  {
    // handle LED type
    const bool on = command["on"].as<bool>();
    int pin = -1;
    switch (port)
    {
      case SWITCH1_PORT:
        pin = SWITCH1_PIN;
        break;
      case SWITCH2_PORT:
        pin = SWITCH2_PIN;
        break;
    }
    if (pin != -1)
      digitalWrite(pin, on ? LOW : HIGH);
  }
}
```

When the device starts it registers all the features it supports:
```json
{"deviceId":"my_device_id","features":[{"type":"led","port":1},{"type":"led","port":2},{"type":"led","port":3},{"type":"switch","port":4},{"type":"switch","port":5}]}
```

You can see this in the *Serial Monitor*:
```
Connecting to IoT_Network
..
WiFi connected
IP: 192.168.2.148
Connecting to http://iot-remotecontrol-2.azurewebsites.net/api/device/register
Payload: {"deviceId":"my_device_id","features":[{"type":"led","port":1},{"type":"led","port":2},{"type":"led","port":3},{"type":"switch","port":4},{"type":"switch","port":5}]}
[HTTP] POST... response code: 200, description:
```
