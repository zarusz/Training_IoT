### 09. Exercise from (`08_Temp_DHT22`)

```
[DHT22] Humidity: 65 %
[HTTP] Connecting to http://iot-remotecontrol-2.azurewebsites.net/api/device/sensor
[HTTP] Payload: {"port":7,"deviceId":"my_device_id","type":"humiditySensor","humidity":65.30}
[HTTP] POST... response code: 200, description:
```

```
[DHT22] Temperature: 23 C
[HTTP] Connecting to http://iot-remotecontrol-2.azurewebsites.net/api/device/sensor
[HTTP] Payload: {"port":7,"deviceId":"my_device_id","type":"temperatureSensor","temperature":23.80}
[HTTP] POST... response code: 200, description:
[HTTP] Connecting to http://iot-remotecontrol-2.azurewebsites.net/api/device/my_device_id
```
```
Connecting to IoT_Network
..
WiFi connected
IP: 192.168.2.148
Starting...
Sending DeviceDescription...
[HTTP] Connecting to http://iot-remotecontrol-2.azurewebsites.net/api/device/register
[HTTP] Payload: {"deviceId":"my_device_id","features":[{"port":4,"type":"switch"},{"port":5,"type":"switch"},{"port":1,"type":"led"},{"port":2,"type":"led"},{"port":7,"type":"temperatureSensor"},{"port":7,"type":"humiditySensor"}]}
[HTTP] POST... response code: 200, description:
Started.
```

```json
{
	"deviceId": "my_device_id",
	"features": [{
		"port": 4,
		"type": "switch"
	},
	{
		"port": 5,
		"type": "switch"
	},
	{
		"port": 1,
		"type": "led"
	},
	{
		"port": 6,
		"type": "temperatureSensor"
	},
	{
		"port": 6,
		"type": "humiditySensor"
	}]
}
```
