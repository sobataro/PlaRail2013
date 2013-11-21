#ifndef CTC_h
#define CTC_h

#include "Arduino.h"
#include "PlaRail.h"
#include "Train.h"
#include "Signal.h"
#include "Station.h"
#include "DepartureSignal.h"
#include "Controller.h"

class CTC {
public:
  CTC();
  
  Block getWay(Train *train);
  
  void loop();
  
private:
  Train *chuoRapid, *nex;
  Signal *signals[NUM_REAL_SIGNALS];
  Controller *controller;
  
  void trainsPrint();
  
  void accelTest();
  void maxSpeedTest();
};

#endif
