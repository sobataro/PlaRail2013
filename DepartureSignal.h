#ifndef DepartureSignal_h
#define DepartureSignal_h

#include "Arduino.h"
#include "Signal.h"

class DepartureSignal : public Signal {
public:
  DepartureSignal(Block block, Train *initialTrain, State initialState, int preCdsPin, int mainCdsPin, int signalPin, long stopMillis);
  boolean check();
  boolean enter(Train *train);
private:
  long stopMillis;
  long lastStoppedMillis;
};

#endif
