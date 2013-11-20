#include "Debounce.h"

Debounce::Debounce(int pin, long delayMillis) {
  this->pin = pin;
  this->delayMillis = delayMillis;
  pinMode(pin, INPUT);
  this->state = LOW;
  lastChangedMillis = 0;
}

int Debounce::check() {
  int currentState = digitalRead(pin);
  if (currentState != state && millis() - lastChangedMillis > delayMillis) {
    state = currentState;
    lastChangedMillis = millis();
  }
  return state;
}
