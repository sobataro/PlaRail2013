#ifndef Controller_h
#define Controller_h

#include "Arduino.h"
#include "Debounce.h"
#include "PushSwitch.h"
#include "Train.h"

class Controller {
public:
  Controller(Train *train, int accelButtonPin, int decelButtonPin, int redLedPin, int greenLedPins[Train::SPEED_LEVELS]);
  ~Controller();
  void check();
  
private:
  Train *train;
  PushSwitch *accelButton;
  PushSwitch *decelButton;
  int redLedPin;
  int greenLedPins[Train::SPEED_LEVELS];
};

#endif
