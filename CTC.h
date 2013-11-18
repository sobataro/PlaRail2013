#ifndef CTC_h
#define CTC_h

#include "PlaRail.h"
#include "Train.h"
#include "Signal.h"

class CTC {
public:
  CTC();
  
  Block getWay(Train *train);
  
  void loop();
  
private:
  Train *chuoRapid, *nex;
  static const int NUM_SIGNALS = 7;
  Signal *signals[NUM_SIGNALS];
  
  void accelTest();
  void maxSpeedTest();
};

#endif
