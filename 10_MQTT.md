### 09. MQTT Broker (`09_MQTT`)
This sample moves our existing solution on the MQTT protocol.
This will make the IoT solution more robust.   

ToDo

Library [PubSubClient](http://platformio.org/lib/show/89/PubSubClient).

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

```
[MainApp] Connecting to IoT_Network
..
[MainApp] WiFi connected
[MainApp] IP: 192.168.2.109
[MainApp] Starting...
Sending DeviceDescription...
[MQTT] Publish to topic: 'register', message: '{"deviceId":"my_device_id","features":[{"port":4,"type":"switch"},{"port":5,"type":"switch"},{"port":1,"type":"led"},{"port
":6,"type":"temperatureSensor"},{"port":6,"type":"humiditySensor"},{"port":7,"type":"motionSensor"}]}'
[MainApp] Started.
[MQTT] Attempting MQTT connection (ClientId: my_device_id-782a)...
[MQTT] Connected
[MQTT] Subscribing to topic: my_device_id
[DHT22] Humidity: 60 %
[MQTT] Publish to topic: 'sensor', message: '{"port":6,"deviceId":"my_device_id","type":"humiditySensor","humidity":60.70}'
[MotionSensor] Motion: 1
[MQTT] Publish to topic: 'sensor', message: '{"port":7,"deviceId":"my_device_id","type":"motionSensor","motion":true}'
[DHT22] Temperature: 25 C
[MQTT] Publish to topic: 'sensor', message: '{"port":6,"deviceId":"my_device_id","type":"temperatureSensor","temperature":25.00}'
```
