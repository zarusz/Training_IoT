/*
 * Emit SOS signal using an LED
 */

#include <Arduino.h>

#define LED 13

#define INTERVAL_MS 250
#define PATTERN_LEN 9
// The SOS pattern ...---...
int pattern[PATTERN_LEN] = { 1, 1, 1, 2, 2, 2, 1, 1, 1 };

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED, OUTPUT);
}

void loop()
{
  for (int i = 0; i < PATTERN_LEN; i++)
  {
    // turn the LED on
    digitalWrite(LED, HIGH);
    // wait few intervals
    delay(INTERVAL_MS * pattern[i]);
    // turn the LED off
    digitalWrite(LED, LOW);
    // wait one intervals
    delay(INTERVAL_MS);
  }
}
