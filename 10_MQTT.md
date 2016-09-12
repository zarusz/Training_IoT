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
