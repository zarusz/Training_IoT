/*
 * Connects to a WiFi network and prints out the IP/MAC address.
 */

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
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  for (int i = 5; i >= 0; i--)
    Serial.print(mac[i], HEX);

  Serial.println("");
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
