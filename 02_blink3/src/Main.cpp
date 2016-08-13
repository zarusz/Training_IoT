/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>

#define LED_COUNT 3

int led_pins[LED_COUNT] = { 14, 12, 13 };
int led_active = 0;

void setup()
{
  // initialize LED digital pin as an output.
  for (int i = 0; i < LED_COUNT; i++)
  {
    pinMode(led_pins[i], OUTPUT);
    digitalWrite(led_pins[i], LOW);
  }
}

void loop()
{
  int led_pin = led_pins[led_active];

  // turn the LED on (HIGH is the voltage level)
  digitalWrite(led_pin, HIGH);
  // wait for a second
  delay(1000);
  // turn the LED off by making the voltage LOW
  digitalWrite(led_pin, LOW);

  led_active = (led_active + 1) % LED_COUNT;
}
