/*
 * Connects to a WiFi network and prints out the IP/MAC address.
 */

#include <Arduino.h>
// reference the ESP WiFi headers
#include <ESP8266WiFi.h>
// reference the HTTPClient headers
#include <ESP8266HTTPClient.h>

#define STATUS_LED 13

// update with you network SSID and password
const char* ssid     = "IoT_Network";
const char* password = "IoT_Password";

// update with the host for the 06_RemoteControl_App ASP.NET Web App
const char* server_host = "iot-remotecontrolapp.azurewebsites.net";
// we access over standard HTTP port
const int server_port = 80;

// update with a unique device id (only alphanumeric characters)
const char* device_id = "my_device_id";

void connectWiFi() {
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
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void setup()
{
  // connect the serial port
  Serial.begin(115200);

  pinMode(STATUS_LED, OUTPUT);
  // initialize LED to off
  digitalWrite(STATUS_LED, LOW);

  connectWiFi();
}

bool tryGetDeviceState(String& payload)
{
  bool success = false;
  String url = String("http://") + server_host + "/api/device/" + device_id + "/state";
  Serial.print("Connecting to ");
  Serial.println(url);

  HTTPClient http;
  http.begin(url);

  int httpCode = http.GET();
  if (httpCode > 0)
  {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);

    // file found at server
    if (httpCode == HTTP_CODE_OK)
    {
      payload = http.getString();
      Serial.println("Response:");
      Serial.println(payload);
      success = true;
    }
  }
  else
  {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();

  Serial.println("Closing connection");
  Serial.println();
  return success;
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("WiFi not connected.");
    delay(1000);
    return;
  }

  String payload;
  if (tryGetDeviceState(payload))
  {
    digitalWrite(STATUS_LED, payload == "1" ? HIGH : LOW);
  }
  delay(2000);
}
