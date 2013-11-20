#include "Station.h"

Station::Station(Signal *masterSignal, Signal *slaveSignal, int crossingServoPin) : Signal::Signal() {
  this->masterSignal = masterSignal;
  this->slaveSignal = slaveSignal;
  this->crossingServoPin = crossingServoPin;
  crossingServo.attach(crossingServoPin);
  changeCrossing(SERVO_ANGLE_MASTER);
}

boolean Station::check(Signal *nextSignal) {
//  Serial.println("check");
//  Serial.println(nextSignal->getBlock());
  int check = 0;
  check += masterSignal->check(nextSignal);
  check += slaveSignal->check(nextSignal);
  
  if (!masterSignal->canEnter(NULL)) {
    // override slave's signal to red
    slaveSignal->restrict();
  } else {
    slaveSignal->release();
  }
  /*
  if (!masterSignal->canEnter(NULL)) {
    Serial.println("master exists");
    check += slaveSignal->check(masterSignal);
  } else {
    check += slaveSignal->check(nextSignal);
  }
  */
  return check;
}

void Station::printTrainIfExists() {
  masterSignal->printTrainIfExists();
  slaveSignal->printTrainIfExists();
}

void Station::changeCrossing(int servoAngle) {
  currentServoAngle = servoAngle;
  crossingServo.write(servoAngle);
}

boolean Station::canEnter(Train *train) {
//  Serial.print("Station::canEnter(): ");
  // TODO: change the way (crossing) for the approaching train
  /*
  Serial.print("Station::canEnter(");
  Serial.print((long) train);
  Serial.println(")");
  */
  if (train == NULL) {
    // 現在開通している方
    if (currentServoAngle == SERVO_ANGLE_MASTER) {
//      Serial.println("NULL, MASTER");
      return masterSignal->canEnter(train);
    } else {
//      Serial.println("NULL, SLAVE");
      return slaveSignal->canEnter(train);
    }
  } else if (train->getType() == EXPRESS) {
    // goto 主本線
//    Serial.println("EXPRESS");
    changeCrossing(SERVO_ANGLE_MASTER);
    return masterSignal->canEnter(train);
  } else if (train->getType() == RAPID) {
    // goto 副本線
//    Serial.println("RAPID");
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
