#ifndef SchmidtTrigger_h
#define SchmidtTrigger_h

#include "Arduino.h"
#include "Debounce.h"
#include "stdlib.h"

class SchmidtTrigger : public Debounce {
public:
  SchmidtTrigger(int pin, int count, int threshold);
  ~SchmidtTrigger();
  int check();
  
private:
  int count;
  int pointer;
  int threshold;
  int *values;
};

#endif
