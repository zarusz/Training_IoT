### LED Blink - ESP-Arduino Hello World (01_Blink)

This is a traditional *Hello World* sample for the *ESP8266* board and *Arduino* framework. The sample turns on/off a LED using a GPIO pin and prints the famous `Hello World!`.

#### Objectives
* Learn to use PlatformIO.
* Understand the basic program structure.
* Learn how to connect ESP8266 and how to upload a program (flash).
* Learn how to use GPIO pins to drive a LED.

#### Hardware

First lets connect the hardware...

![](assets/01_blink_bb.png "Schematic for 01_blink sample")

Connections of ESP8266 pins:
* `RST` of ESP8266 connected via a push switch to `LOW`.
  * When the button gets pressed it will restart our program (and the chip).
* `EN` is connected to `HIGH` to *enable* the chip.
  * The chip enters *sleep mode* if connected to `LOW` (or not connected at all).  
  * *Sleep mode* is used to lower the power consumption.
* `GND` and `3V3` is connected to `GND` and voltage `3.3V` respectively.      

The sample program will blink a LED. The LED's cathode (shorter leg) is connected to `GND` and the anode is connected via a 220&#937; resistor to the GPIO pin `#13`. The resistor is needed to limit the current on the LED (not to burn it).

![](assets/diode_a_sm.png "Schematic for 01_blink sample")

#### Software

The structure of the project files comes from the [Platform IO](http://platformio.org/). The underlying programming language is C++. The most interesting part of the sample is located in the main program file `src\Main.cpp`:

```cpp
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
```
The name of the main file can be whatever you like, but it needs to have a meaningful C++ extension (e.g. `.cpp` or `.c`) and has to be located under `src` folder.

Some explanation on the code...

Any program should have exactly one `setup()` and `loop()` functions defined. The `setup()` is executed only once - when the chip starts (when powered or reset); after that `loop()` is executed repeatedly.

The `#include <Arduino.h>` brings in all the Arduino framework functions.

The `Serial` enables us to send (and recieve) some characters into the `Serial Monitor`. This is useful to output diagnostic information to debug our program.

Lets run the program:
* Compile using PlatformIO
* Put the ESP into *UART Boatloader* mode
	* Set `GPIO0` to *PullDown*
	* Press `RESET` button briefly
* Upload program using PlatformIO
* Open `Serial Monitor` in PlatformIO
* Set `GPIO0` to loose (or *PullUp*)
* Press `RESET` button briefly

When all is successful the LED will blink and the output from the *Serial Monitor* will have the `Hello World!` line:

![Montior output for 01_Blink sample](assets/01_blink_monitor.png "Montior output for 01_Blink sample")

#### Arduino Reference
* [`pinMode(pin, mode)`](https://www.arduino.cc/en/Reference/PinMode)
* [`digitalWrite(pin, value)`](https://www.arduino.cc/en/Reference/DigitalWrite)
* [`delay(ms)`](https://www.arduino.cc/en/Reference/Delay)
* [`setup()`](https://www.arduino.cc/en/Reference/Setup)
* [`loop()`](https://www.arduino.cc/en/Reference/Loop)
* [`Serial.begin()`](https://www.arduino.cc/en/Serial/Begin)
* [`Serial.print()`](https://www.arduino.cc/en/Serial/Print)

#### Worth reading (at home)

* [Diode and LED Polarity](https://learn.sparkfun.com/tutorials/polarity/diode-and-led-polarity)
* [Serial Reference](https://www.arduino.cc/en/Reference/Serial)

#### Exercise

1. Connect the hardware parts and upload the program to ESP.
	* Connect the USB-TTL converter.
	* Open the `01_blink` project in PlatformIO.
	* Build / Upload (ensure ESP is in upload mode).
2. Modify the program to make the LED emit [SOS signal](https://en.wikipedia.org/wiki/SOS) (`...---...`)
  * Change & upload the program.
3. Blink 3 LEDs one after another
  * Connect 2 more LEDs (green and yellow) to GPIO pins `#16` and `#12`.
  * Change and upload the program.
