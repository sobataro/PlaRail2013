#ifndef Train_h
#define Train_h

#include "Arduino.h"
#include "PlaRail.h"

class Train {
public:
  Train(TrainType type, Block pos, int pwmPinA, int pwmPinB);
  
  TrainType getType();
  Block getPos();
  void setPos(Block pos);
  int getSpeed();
  void setSpeed(int speed);
  void accelerate();
  void decelerate();

  static const int MIN_SPEED = 0;
  static const int MAX_SPEED = 4;
private:
  TrainType type;
  Block pos;
  int speed;
  static const int pwmDuty[MAX_SPEED - MIN_SPEED + 1];
  int pwmPinA;
  int pwmPinB;
};

#endif
