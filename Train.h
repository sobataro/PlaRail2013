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
  
  boolean isRestricted();
  void restrict();
  void release();
  
  void print();

  static const int MIN_SPEED = 0;
  static const int MAX_SPEED = 3;
  static const int SPEED_LEVELS = MAX_SPEED - MIN_SPEED + 1;
private:
  TrainType type;
  Block pos;
  int speed;
  boolean restricted;
  static const int pwmDuty[SPEED_LEVELS];
  int pwmPinA;
  int pwmPinB;
};

#endif
