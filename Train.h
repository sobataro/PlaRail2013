#ifndef Train_h
#define Train_h

#include "PlaRail.h"

class Train {
public:
  Train(TrainType type, int pos);
  
  TrainType getType();
  int getPos();
  void setPos(int pos);
  int getSpeed();
  void accelerate();
  void decelerate();

  static const int MIN_SPEED = 0;
  static const int MAX_SPEED = 4;
private:
  TrainType type;
  int pos;
  int speed;
};

#endif
