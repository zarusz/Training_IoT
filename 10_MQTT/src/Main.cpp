/*
 * Connects to a WiFi network and prints out the IP/MAC address.
 */

// increase the message buffer size for the MQTT client
#define   MQTT_MAX_PACKET_SIZE		512

#include <Arduino.h>
#include "MainApp.h"

MainApp mainApp;

void setup()
{
  mainApp.Init();
}

void loop()
{
  mainApp.Loop();
}
