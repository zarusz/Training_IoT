/*
 * Connects to a WiFi network and prints out the IP/MAC address.
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>

#define STATUS_LED 13

const char* ssid     = "(network ssid here)";
const char* password = "(network password here)";

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
  // Connect the serial port port.
  Serial.begin(115200);
  delay(50);

  // initialize LED digital pin as an output.
  pinMode(STATUS_LED, OUTPUT);
  // the LED will signal if we're connected to WiFi
  digitalWrite(STATUS_LED, LOW);

  connectToNetwork();

  // the LED will indicate that we're connected
  digitalWrite(STATUS_LED, HIGH);

  // print the IP address
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  // print the MAC address
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.println("MAC address: ");
  for (int i = 5; i >= 0; i--)
  {
    Serial.print(mac[i], HEX);
  }
  Serial.println("");
}

void loop()
{
}
