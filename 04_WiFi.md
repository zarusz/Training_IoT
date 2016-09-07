### 04. First WiFi Connection (04_WiFi)

ESP8266 has a built in WiFi module. We can interface with it using the [WiFi](https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/station-class.md#station-class) class.
The ESP WiFi can work in one of the 3 modes:
* soft access point (AP),
* station (STA),
* mixed (both AP and STA).

This sample program connects to the specified secured network and prints out the IP/MAC address of the ESP (client WiFi mode).
It also uses a LED to indicate the connection status - when lit the WiFi connection is established.

Here is the program:

```cpp
#include <Arduino.h>
// reference the ESP WiFi headers
#include <ESP8266WiFi.h>

#define STATUS_LED 13

// update with you network SSID and password
const char* ssid     = "IoT_Network";
const char* password = "IoT_Password";

void connectWiFi() {
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Connect to a WiFi network
  WiFi.begin(ssid, password);
  // Wait until the connection is established
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
}

void printWiFiDetails()
{
  // print the IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP: ");
  Serial.println(ip);

  // print the gateway address:
  IPAddress gatewayIp = WiFi.gatewayIP();
  Serial.print("Gateway: ");
  Serial.println(gatewayIp);

  // print the MAC address
  String mac = WiFi.macAddress();
  Serial.print("MAC: ");
  Serial.println(mac);
}

void setup()
{
  // connect the serial port
  Serial.begin(115200);

  // initialize the status LED
  pinMode(STATUS_LED, OUTPUT);

  connectWiFi();
  printWiFiDetails();
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    // LED off - indicate that we are not connected
    digitalWrite(STATUS_LED, LOW);

    Serial.println("WiFi not connected.");
    delay(1000);
    return;
  }

  // LED on - indicate that we are connected
  digitalWrite(STATUS_LED, HIGH);
}
```

When the program runs the *Serial Monitor* outputs:
```
Connecting to IoT_Network
..
WiFi connected
IP: 192.168.2.148
Gateway: 192.168.2.1
MAC: 5C:CF:7F:89:2D:E4
```

Note that the program checks if the WiFi network is disconnected.
For example when the WiFi router is unplugged the LED becomes off and the program outputs:
```
WiFi not connected.
WiFi not connected.
```

However, when you plug the router back the `WiFi` class automatically joins the network and LED turns on (see [`WiFi.setAutoConnect()`](https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/station-class.md#setautoconnect)).

#### Reference
* [WiFi.begin()](https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/station-class.md#begin)
* [WiFi.status()](https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/station-class.md#status)
* [WiFi.localIP()](https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/station-class.md#localip)
* [WiFi.gatewayIP()](https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/station-class.md#gatewayip)
* [WiFi.macAddress()](https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/station-class.md#macaddress)

#### Worth reading at home
* [ESP-Arduino WiFi Docs](https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/station-class.md)
* [ESP-Arduino WiFi Examples](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi/examples)
* [WiFi Library (Arduino)](https://www.arduino.cc/en/Reference/WiFi)
