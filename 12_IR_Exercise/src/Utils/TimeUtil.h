#ifndef _TimeUtil_h
#define _TimeUtil_h

#include <Arduino.h>

class TimeUtil
{
public:
  static bool IntervalPassed(ulong& lastTimeMs, uint intervalMs)
  {
      ulong now = millis();
      if (now - lastTimeMs < intervalMs) {
          // the time has not elapsed
          return false;
      }
      lastTimeMs = now;
      return true;
  }
};

#endif
