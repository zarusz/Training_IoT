/*
 * Turns on one of the three LEDs one after another
 */

#include <Arduino.h>

#define LED_COUNT 3

int led_pins[LED_COUNT] = { 14, 12, 13 };
int led_active = 0;

void setup()
{
  for (int i = 0; i < LED_COUNT; i++)
  {
    int led_pin = led_pins[i];
    // initialize LED digital pin as an output.
    pinMode(led_pin, OUTPUT);
    // ensure the pin is LOW on start
    digitalWrite(led_pin, LOW);
  }
}

void loop()
{
  // get the currently active LED pin
  int led_pin = led_pins[led_active];

  // turn the LED on (HIGH is the voltage level)
  digitalWrite(led_pin, HIGH);
  // wait for a second
  delay(1000);
  // turn the LED off by making the voltage LOW
  digitalWrite(led_pin, LOW);

  // determine next active LED.
  led_active = (led_active + 1) % LED_COUNT;
}
