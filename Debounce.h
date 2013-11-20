#ifndef Debounce_h
#define Debounce_h

#include "Arduino.h"

class Debounce {
public:
  Debounce(int pin, long delayMillis);
  virtual int check();
  
protected:
  int pin;
  int state;
  long lastChangedMillis;
  long delayMillis;
};

#endif
