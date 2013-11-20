#ifndef Controller_h
#define Controller_h

#include "Arduino.h"
#include "PlaRail.h"
#include "Debounce.h"
#include "PushSwitch.h"
#include "Train.h"
#include "Signal.h"

class Controller {
public:
  Controller(Train *train, int accelButtonPin, int decelButtonPin, int redLedPin, int greenLedPins[Train::SPEED_LEVELS], Signal* signals[NUM_REAL_SIGNALS]);
  ~Controller();
  void check();
  
private:
  Train *train;
  Signal* *signals;
  PushSwitch *accelButton;
  PushSwitch *decelButton;
  int redLedPin;
  int greenLedPins[Train::SPEED_LEVELS];
};

#endif
