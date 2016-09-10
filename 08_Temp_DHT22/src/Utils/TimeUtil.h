#ifndef _TimeUtil_h
#define _TimeUtil_h

#include <Arduino.h>

class TimeUtil
{
public:
  static bool IntervalPassed(ulong& lastTime, uint interval)
  {
      ulong now = millis();
      if (now - lastTime < interval) {
          // the time has not elapsed
          return false;
      }
      lastTime = now;
      return true;
  }
};

#endif
