/*
 * Connects to a WiFi network and prints out the IP/MAC address.
 */

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
