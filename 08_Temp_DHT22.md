### 08. DHT22 - Temperature/Humidity Sensor (`08_Temp_DHT22`)

In this exercise we will:
* Connect an actual temperature and humidity sensors.
* Learn about DHT22 sensor.
* Push sensor readings to the web app.
* Apply some refactor to the previous device code in order to improve the app architecture.

The web app version from `06_JSON_2Relay_App` will be used.
The device code is in `08_Temp_DHT22`.

### After the refactoring

Up until now most of the code was more procedural C than object oriented C++. Also our solution now is capable of handling many endpoint types.

ToDo

### Running the device sketch

```
Connecting to IoT_Network
..
WiFi connected
IP: 192.168.2.148
Starting...
Sending DeviceDescription...
[HTTP] Connecting to http://iot-remotecontrol-2.azurewebsites.net/api/device/register
[HTTP] Payload: {"deviceId":"my_device_id","features":[{"type":"switch","port":4},{"type":"switch","port":5},{"type":"led","port":1},{"type":"led","port":2},{"type":"led","port
":3}]}
[HTTP] POST... response code: 200, description:
Started.
```

You can control the device from the test web app: http://iot-remotecontrol-2.azurewebsites.net/

### New Hardware Part: DHT22 - Humidity and Temperature Sensor

ToDo add pictures

### Exercise

Connect the DHT22 sensor and push humidity/temperature readings to web app:
  * Push the data every 10 seconds. Use the `TimeUtil::IntervalPassed()` method to avoid blocking the application loop.
  * The web app already understands `temperatureSensor` and `humiditySensor` feature types.
  * Add the relevant `*FeatureController` classes and register them in `MainApp` constructor.
