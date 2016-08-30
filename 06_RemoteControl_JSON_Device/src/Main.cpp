/*
 * Connects to a WiFi network and prints out the IP/MAC address.
 */

#include <Arduino.h>
// reference the ESP WiFi headers
#include <ESP8266WiFi.h>
// reference the HTTPClient headers
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// update with you network SSID and password
const char* ssid     = "IoT_Network";
const char* password = "IoT_Password";

// update with the host for the 06_RemoteControl_App ASP.NET Web App
const char* server_host = "iot-remotecontrol-2.azurewebsites.net";
// we access over standard HTTP port
const int server_port = 80;

// update with a unique device id (only alphanumeric characters)
const char* device_id = "my_device_id";

#define LED1_PIN 13
#define LED1_PORT 1

#define FEATURE_TYPE_LED "led"

void connectWiFi() {
  Serial.printf("\nConnecting to %s\n", ssid);

  // Connect to a WiFi network
  WiFi.begin(ssid, password);
  // Wait until the connection is established
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.print("\nWiFi connected\n");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void setup()
{
  // connect the serial port
  Serial.begin(115200);

  pinMode(LED1_PIN, OUTPUT);
  // initialize LED to off
  digitalWrite(LED1_PIN, LOW);

  connectWiFi();
}

String createDeviceDescriptionJson()
{
  StaticJsonBuffer<512> jsonBuffer;

  JsonObject& featureLed = jsonBuffer.createObject();
  featureLed["type"] = FEATURE_TYPE_LED;
  featureLed["port"] = LED1_PORT;

  JsonObject& root = jsonBuffer.createObject();
  root["deviceId"] = device_id;

  JsonArray& features = root.createNestedArray("features");
  features.add(featureLed);

  char buffer[512];
  root.printTo(buffer, sizeof(buffer));
  return String(buffer);
}

bool sendRegisterDevice(const String& postPayload)
{
  bool success = false;
  String url = String("http://") + server_host + "/api/device/register";

  Serial.printf("Connecting to %s\n", url.c_str());
  Serial.printf("Payload: %s\n", postPayload.c_str());

  HTTPClient http;
  http.begin(url);
  // tell the server we're posting JSON
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.POST(postPayload);
  if (httpCode > 0)
  {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] POST... response code: %d, description: %s\n", httpCode, http.errorToString(httpCode).c_str());

    // file found at server
    if (httpCode == HTTP_CODE_OK)
    {
      success = true;
    }
  }
  else
  {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
  return success;
}

bool registerDevice()
{
  auto msgJson = createDeviceDescriptionJson();
  return sendRegisterDevice(msgJson);
}

bool popDeviceCommand(String& payload)
{
  bool success = false;
  String url = String("http://") + server_host + "/api/device/" + device_id;
  Serial.printf("Connecting to %s\n", url.c_str());

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
      success = true;
      payload = http.getString();
      Serial.printf("Response: %s\n", payload.length() > 0 ? payload.c_str() : "(empty)");
    }
  }
  else
  {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
  return success;
}

// handle the incomming command
void handleCommand(JsonObject& command)
{
  // handle the command
  const char* type = command["type"].asString();
  const int port = command["port"].as<int>();
  if (strcmp(type, FEATURE_TYPE_LED) == 0)
  {
    // handle LED type
    const bool on = command["on"].as<bool>();
    if (port == LED1_PORT)
    {
      // handle LED on port 1
      digitalWrite(LED1_PIN, on ? HIGH : LOW);
    }
  }
}

bool registered = false;

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("WiFi not connected.");
    delay(1000);
    return;
  }

  if (!registered)
  {
    registerDevice();
    registered = true;
  }

  String commandJson;
  // check if there is next command (non empty reponse)
  if (popDeviceCommand(commandJson) && commandJson.length() > 0)
  {
    // parse JSON command
    StaticJsonBuffer<256> jsonBuffer;
    JsonObject& command = jsonBuffer.parseObject(commandJson);
    if (!command.success())
    {
      Serial.println("parseObject() failed");
    }
    else
    {
      handleCommand(command);
    }
  }

  delay(2000);
}
