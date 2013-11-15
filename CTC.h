#ifndef CTC_h
#define CTC_h

#include "PlaRail.h"
#include "Train.h"

class CTC {
public:
  CTC();
  
  Block nextBlock(Train *train);
  
private:
  Train *chuoRapid;
  Train *nex;
};

#endif
