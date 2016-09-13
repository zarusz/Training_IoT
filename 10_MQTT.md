### 09. MQTT Broker (`09_MQTT`)
This sample moves our existing solution on the MQTT protocol.
This will make the IoT solution more robust.   

ToDo

Library [PubSubClient](http://platformio.org/lib/show/89/PubSubClient).
[API Documentation](http://pubsubclient.knolleary.net/api.html).

```
PS E:\dev\work\training_iot\10_MQTT> platformio lib install "PubSubClient"
Library Storage: E:\dev\work\training_iot\10_MQTT\.piolibdeps
Looking for PubSubClient library in registry
Found: http://platformio.org/lib/show/89/PubSubClient
LibraryManager: Installing id=89
Downloading...
Unpacking...
PubSubClient @ 2.6 has been successfully installed!
```

Example for ESP8266:
https://github.com/knolleary/pubsubclient/blob/master/examples/mqtt_esp8266/mqtt_esp8266.ino

These are the files we've added and modified:
```
src/Feature/FeatureController.cpp
src/Feature/FeatureController.h
src/Transport/MqttMessageBus.cpp (+)
src/Transport/MqttMessageBus.h (+)
src/MainApp.cpp
src/MainApp.h
```

Running the device program outputs:

```
[MainApp] Connecting to IoT_Network
..
[MainApp] WiFi connected
[MainApp] IP: 192.168.2.109
[MainApp] Starting...
[MainApp] Started.

[MQTT] Attempting MQTT connection (ClientId: my_device_id-b936)...
[MQTT] Connected
[MQTT] Subscribing to topic: 'my_device_id'
[MainApp] Sending DeviceDescription...
[MQTT] Publish to topic: 'register', message: '{"deviceId":"my_device_id","features":[{"port":4,"type":"switch"},{"port":5,"type":"switch"},{"port":1,"type":"led"},{"port
":6,"type":"temperatureSensor"},{"port":6,"type":"humiditySensor"},{"port":7,"type":"motionSensor"}]}'
[DHT22] Humidity: 59 %
[MQTT] Publish to topic: 'sensor', message: '{"port":6,"deviceId":"my_device_id","type":"humiditySensor","humidity":59.80}'
[DHT22] Temperature: 25 C
[MQTT] Publish to topic: 'sensor', message: '{"port":6,"deviceId":"my_device_id","type":"temperatureSensor","temperature":25.00}'
```

```
pi@raspberrypi ~ $ mosquitto_sub -t register -t sensor
{"port":6,"deviceId":"my_device_id","type":"humiditySensor","humidity":59.80}
{"port":6,"deviceId":"my_device_id","type":"temperatureSensor","temperature":25.00}
{"port":6,"deviceId":"my_device_id","type":"humiditySensor","humidity":59.80}
@raspberrypi ~ $ mosquitto_sub -t register -t sensor
{"port":6,"deviceId":"my_device_id","type":"humiditySensor","humidity":59.80}
{"port":6,"deviceId":"my_device_id","type":"temperatureSensor","temperature":25.00}
{"port":6,"deviceId":"my_device_id","type":"temperatureSensor","temperature":25.00}
{"port":6,"deviceId":"my_device_id","type":"humiditySensor","humidity":59.90}
{"port":6,"deviceId":"my_device_id","type":"temperatureSensor","temperature":25.00}
```

### Control Web App

NuGet: [M2Mqtt](https://www.nuget.org/packages/M2Mqtt/)
[Reference how](https://m2mqtt.wordpress.com/using-mqttclient/) to use it.
