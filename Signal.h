#ifndef Signal_h
#define Signal_h

#include "PlaRail.h"
#include "Train.h"
#include "SchmidtTrigger.h"

class Signal {
public:
  enum State {
    NO_TRAIN, RUNNING, APPROACHING, PASSING
  };

  Signal(Block block, Train *initialTrain, State initialState, int preCdsPin, int mainCdsPin, int signalPin);
  
  virtual void setNextSignal(Signal *nextSignal);
  Signal* getNextSignal();
  
  // called by each loop()
  virtual boolean check();
  
  // called by previous signal
  virtual boolean canEnter(Train *train);
  virtual boolean enter(Train *train);
  
  // override this signal to red
  void override();

  State getState();
  Train* getTrain();
  Block getBlock();

  static const int GREEN = HIGH;
  static const int RED = LOW;
  int getColor();

  void restrict();
  void release();
  
  // for debug
  virtual boolean printTrainIfExists();

protected:
  Signal();
  virtual void setApproaching();
  virtual void setPassing();
  virtual void setNoTrain();

//private:
  Block block;
  Signal *nextSignal;
  SchmidtTrigger *preCds, *mainCds;
  int signalPin;
  int lastPre, lastMain;
  Train *existingTrain;
  State state, previousState;
  
  boolean restricted;

  void print(int preCds, int mainCds);
  
  int color;
};

#endif
