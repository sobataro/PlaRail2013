#ifndef Signal_h
#define Signal_h

#include "PlaRail.h"
#include "Train.h"

class Signal {
public:
  enum State {
    NO_TRAIN, RUNNING, APPROACHING, PASSING
  };

  Signal(Block block, Train *initialTrain, int preCdsPin, int mainCdsPin, int signalPin);
  
  // called by each loop()
  boolean check(Signal *nextSignal);
  
  State getState();
  
  Block getBlock(Train *train);
  
  // called by previous signal
  boolean canEnter(Train *train);
  
  boolean enter(Train *train);
  
  void clear();

private:
  Block block;
  int preCdsPin;
  int mainCdsPin;
  int signalPin;
  Train *existingTrain;
  State state, previousState;
  
  void setSignal();
  
  static const int GREEN = HIGH;
  static const int RED = LOW;
};

#endif
