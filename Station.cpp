#include "Station.h"

Station::Station(Signal *masterSignal, Signal *slaveSignal, int crossingServoPin) : Signal::Signal() {
  this->masterSignal = masterSignal;
  this->slaveSignal = slaveSignal;
  this->crossingServoPin = crossingServoPin;
  crossingServo.attach(crossingServoPin);
  changeCrossing(SERVO_ANGLE_MASTER);
}

void Station::setNextSignal(Signal *nextSignal) {
  masterSignal->setNextSignal(nextSignal);
  slaveSignal->setNextSignal(nextSignal);
}

boolean Station::check() {
  int check = 0;

  check += masterSignal->check();
  if (!masterSignal->canEnter(NULL)) {
    // override slave's signal to red
    slaveSignal->restrict();
  } else {
    slaveSignal->release();
  }
  check += slaveSignal->check();

  return check;
}

boolean Station::printTrainIfExists() {
  return masterSignal->printTrainIfExists() + slaveSignal->printTrainIfExists();
}

void Station::changeCrossing(int servoAngle) {
  currentServoAngle = servoAngle;
  crossingServo.write(servoAngle);
}

boolean Station::isTrainOnCrossing() {
  return masterSignal->getState() == Signal::RUNNING || slaveSignal->getState() == Signal::RUNNING;
}

boolean Station::canEnter(Train *train) {
  if (isTrainOnCrossing()) {
    return false;
  }
  if (train == NULL) {
    // 現在開通している方
    if (currentServoAngle == SERVO_ANGLE_MASTER) {
      return masterSignal->canEnter(train);
    } else {
      return slaveSignal->canEnter(train);
    }
  } else if (train->getType() == EXPRESS) {
    // goto 主本線
    changeCrossing(SERVO_ANGLE_MASTER);
    return masterSignal->canEnter(train);
  } else if (train->getType() == RAPID) {
    // goto 副本線
    changeCrossing(SERVO_ANGLE_SLAVE);
    return slaveSignal->canEnter(train);
  }
}

boolean Station::enter(Train *train) {
  Serial.println("Station::enter()");
  switch (train->getType()) {
  case EXPRESS:
    // goto 主本線
    return masterSignal->enter(train);
    break;
  case RAPID:
    // goto 副本線
    return slaveSignal->enter(train);
    break;
  }
}

