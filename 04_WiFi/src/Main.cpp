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

void connectToNetwork() {
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Connect to a WiFi network
  WiFi.begin(ssid, password);
  // Wait until the connection is established
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
}

void setup()
{
  // connect the serial port
  Serial.begin(115200);

  pinMode(STATUS_LED, OUTPUT);
  // LED off - will indicate we're not connected to WiFi yet
  digitalWrite(STATUS_LED, LOW);

  connectToNetwork();

  // LED on - will indicate that we're connected
  digitalWrite(STATUS_LED, HIGH);

  // print the IP address
  IPAddress ip = WiFi.localIP();
  Serial.println("IP address: ");
  Serial.println(ip);

  // print the MAC address
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.println("MAC address: ");
  for (int i = 5; i >= 0; i--)
    Serial.print(mac[i], HEX);

  Serial.println("");
}

void loop()
{
  delay(50);
}
