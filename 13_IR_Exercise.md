## 13. Example solution for exercise from (`12_IR`)

Lets look at key elements of the program.

### Source highlights

4 files were added:
```
Feature\IRInFeatureController.h
Feature\IRInFeatureController.cpp
Feature\IROutFeatureController.h
Feature\IROutFeatureController.cpp
```
The `IRInFeatureController` class handles the IR receiver. It imports the `IRremoteESP8266.h` library and uses the `IRrecv` class. The `loop()` method captures any IR signals and outputs to serial.

The `IROutFeatureController` class handles the IR transceiver. It uses the `IRsend` class to handle the command send.
The handles incoming commands and translates them into IR signals in the `Handle()` method.

Lastly the `MainApp` constructor instantiates and configures ports/pins of the new IR features.

### Running the sample

When the device starts it publishes the device description:
```
[MainApp] Sending DeviceDescription...
[MQTT] Publish to topic: 'register', message: '{"deviceId":"my_device_id","features":[{"port":8,"type":"ir_in"},{"port":9,"type":"ir_in"},{"port":10,"type":"ir_in"}]}'
```

When POWER button is pressed on the LED remote, our device outputs:
```
[IR-in] Encoding  : NEC
[IR-in] Code      : FF02FD (32 bits)
```
