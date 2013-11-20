#include "PushSwitch.h"

PushSwitch::PushSwitch(int pin, long delayMillis, int defaultState) : Debounce(pin, delayMillis) {
  this->defaultState = defaultState;
  this->state = defaultState;
}

int PushSwitch::check() {
  int currentState = digitalRead(pin);
  if (currentState != state && millis() - lastChangedMillis > delayMillis) {
    state = currentState;
    lastChangedMillis = millis();
    return state;
  }
  return defaultState;
}
