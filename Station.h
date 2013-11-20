#ifndef Station_h
#define Station_h

#include "Servo.h"
#include "Signal.h"
#include "Train.h"

class Station : public Signal {
public:
  Station(Signal *masterSignal, Signal *slaveSignal, int crossingServoPin);
  void setNextSignal(Signal *nextSignal);
  boolean check();
  boolean canEnter(Train *train);
  boolean enter(Train *train);
  
  // for debug
  void printTrainIfExists();

private:
  // 主本線と副本線
  Signal *masterSignal, *slaveSignal;
  Servo crossingServo;
  int crossingServoPin;
  static const int SERVO_ANGLE_MASTER = 30;
  static const int SERVO_ANGLE_SLAVE = 0;
  int currentServoAngle;
  
  boolean isTrainOnCrossing();
  void changeCrossing(int servoAngle);
};

#endif
