/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

// reference the arduino framework
#include <Arduino.h>

// the LED's GPIO pin number
#define LED 13

void setup()
{
  // initialize serial communication
  Serial.begin(115200);

  Serial.println("");
  Serial.println("Hello World!");
  Serial.println("");

  // initialize LED digital pin as an output.
  pinMode(LED, OUTPUT);
}

void loop()
{
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED, HIGH);
  // wait for a second
  delay(1000);
  // turn the LED off by making the voltage LOW
  digitalWrite(LED, LOW);
   // wait for a second
  delay(1000);
}
