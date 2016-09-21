## Extras

### Exceptions

Sometime the program causes runtime errors that cause the chip to reboot and enter invalid state. ESP provides some diagnostic information when an error happens:

```
Exception (28):
epc1=0x40221a46 epc2=0x00000000 epc3=0x00000000 excvaddr=0x00000000 depc=0x00000000

ctx: sys
sp: 3ffff850 end: 3fffffb0 offset: 01a0

>>>stack>>>
3ffff9f0:  00000001 00000004 3ffe99b4 00000002
...
3fffffa0:  400201e9 efac3ebe ffffff01 55aa55aa
<<<stack<<<
```

See the list of exceptions [Exception Causes (EXCCAUSE)](https://github.com/esp8266/Arduino/blob/master/doc/exception_causes.md)

### Upgrading ESP to newer Espressif SDK

To upgrade your ESP8266 with the latest firmware, you need:

1. The [Flash Download Tool](http://www.espressif.com/en/support/download/other-tools)
2. The [official SDK](http://espressif.com/en/support/download/sdks-demos) from Espressif.

Typically you will need the *NONOS* SDK. For example `ESP8266 NONOS SDK V1.5.4`.

There is a really [great article](http://www.allaboutcircuits.com/projects/update-the-firmware-in-your-esp8266-wi-fi-module/) on the upgrade procedure.
