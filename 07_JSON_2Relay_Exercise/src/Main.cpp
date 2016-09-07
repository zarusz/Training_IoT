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

#define LED2_PIN 12
#define LED2_PORT 2

#define LED3_PIN 14
#define LED3_PORT 3

#define SWITCH1_PIN 4
#define SWITCH1_PORT 4

#define SWITCH2_PIN 5
#define SWITCH2_PORT 5

#define FEATURE_TYPE_LED "led"
#define FEATURE_TYPE_SWITCH "switch"

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
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  // initialize LED to off
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED3_PIN, LOW);

  pinMode(SWITCH1_PIN, OUTPUT);
  pinMode(SWITCH2_PIN, OUTPUT);
  // initialize SWITCH to off
  digitalWrite(SWITCH1_PIN, HIGH);
  digitalWrite(SWITCH2_PIN, HIGH);

  connectWiFi();
}

String createDeviceDescriptionJson()
{
  StaticJsonBuffer<512> jsonBuffer;

  JsonObject& root = jsonBuffer.createObject();
  root["deviceId"] = device_id;
  JsonArray& features = root.createNestedArray("features");

  JsonObject& featureLed1 = jsonBuffer.createObject();
  featureLed1["type"] = FEATURE_TYPE_LED;
  featureLed1["port"] = LED1_PORT;
  features.add(featureLed1);

  JsonObject& featureLed2 = jsonBuffer.createObject();
  featureLed2["type"] = FEATURE_TYPE_LED;
  featureLed2["port"] = LED2_PORT;
  features.add(featureLed2);

  JsonObject& featureLed3 = jsonBuffer.createObject();
  featureLed3["type"] = FEATURE_TYPE_LED;
  featureLed3["port"] = LED3_PORT;
  features.add(featureLed3);

  JsonObject& featureSwitch1 = jsonBuffer.createObject();
  featureSwitch1["type"] = FEATURE_TYPE_SWITCH;
  featureSwitch1["port"] = SWITCH1_PORT;
  features.add(featureSwitch1);

  JsonObject& featureSwitch2 = jsonBuffer.createObject();
  featureSwitch2["type"] = FEATURE_TYPE_SWITCH;
  featureSwitch2["port"] = SWITCH2_PORT;
  features.add(featureSwitch2);

  char buffer[512];
  root.printTo(buffer, sizeof(buffer));
  return String(buffer);
}

bool postJson(const String& path, const String& postPayload)
{
  bool success = false;
  String url = String("http://") + server_host + path;

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
  return postJson("/api/device/register", msgJson);
}

bool getJson(const String& path, String& payload)
{
  bool success = false;
  String url = String("http://") + server_host + path;
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

bool popDeviceCommand(String& commandJson)
{
  String path = String("/api/device/") + device_id;
  // getJson succeeds and non-empty response payload
  return getJson(path, commandJson) && commandJson.length() > 0;
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
    int pin = -1;
    switch (port)
    {
      case LED1_PORT:
        pin = LED1_PIN;
        break;
      case LED2_PORT:
        pin = LED2_PIN;
        break;
      case LED3_PORT:
        pin = LED3_PIN;
        break;
    }
    if (pin != -1)
      digitalWrite(pin, on ? HIGH : LOW);
  }
  else if (strcmp(type, FEATURE_TYPE_SWITCH) == 0)
  {
    // handle LED type
    const bool on = command["on"].as<bool>();
    int pin = -1;
    switch (port)
    {
      case SWITCH1_PORT:
        pin = SWITCH1_PIN;
        break;
      case SWITCH2_PORT:
        pin = SWITCH2_PIN;
        break;
    }
    if (pin != -1)
      digitalWrite(pin, on ? LOW : HIGH);
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
  // check if there is next command
  if (popDeviceCommand(commandJson))
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
