#ifndef PushSwitch_h
#define PushSwitch_h

#include "Debounce.h"

class PushSwitch : public Debounce {
public:
  PushSwitch(int pin, long delayMillis, int defaultState);
  int check();
private:
  int defaultState;
};

#endif
