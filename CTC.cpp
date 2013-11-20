#include "CTC.h"

CTC::CTC() {
  Serial.println("");
  Serial.println("CTC init()");
  Serial.println("");
  
  // init train
  TCCR5B = (TCCR5B & 0xF8) | 0x05; // set motor PWM to 30Hz
  nex = new Train(EXPRESS, CHOFU_MASTER, 44, 45);
  TCCR4B = (TCCR4B & 0xF8) | 0x05; // set motor PWM to 30Hz
  chuoRapid = new Train(RAPID, CHOFU_SLAVE, 6, 7);
  
  signals[FUDA_2] = new Signal(FUDA_2, NULL, Signal::NO_TRAIN, 13, 12, 11);
  signals[FUDA_1] = new Signal(FUDA_1, NULL, Signal::NO_TRAIN, 10, 9, 8);
  signals[FUDA] = new Signal(FUDA, NULL, Signal::NO_TRAIN, 22, 3, 2);
  signals[CHOFU_2] = new Signal(CHOFU_2, NULL, Signal::NO_TRAIN, 24, 25, 26);
  signals[CHOFU_1] = new Signal(CHOFU_1, NULL, Signal::NO_TRAIN, 28, 29, 27);
  
  Signal *chofuMaster = new Signal(CHOFU_MASTER, nex, Signal::PASSING, 32, 33, 34);
  Signal *chofuSlave = new Signal(CHOFU_SLAVE, chuoRapid, Signal::PASSING, 36, 37, 35);
  signals[CHOFU] = new Station(chofuMaster, chofuSlave, 5);
  
  int greenLedPins[] = {43, 42, 41};
  controller = new Controller(chuoRapid, 39, 38, 40, greenLedPins);
}

void CTC::loop() {
//  accelTest();
  int changed = 0;
//  nex->setSpeed(2);
  
  for (int i = 0; i < NUM_SIGNALS; i++) {
    changed += signals[i]->check(signals[(i + 1) % NUM_SIGNALS]);
  }
  controller->check();
  if (changed) {
    Serial.println("");
    trainsPrint();
    Serial.println("");
  }
}

void CTC::trainsPrint() {
  Serial.print("Trains: ");
  for (int i = 0; i < NUM_SIGNALS; i++) {
    signals[i]->printTrainIfExists();
  }
  Serial.println("");
}

void CTC::accelTest() {
  for (int i = Train::MIN_SPEED; i <= Train::MAX_SPEED; i++) {
    nex->setSpeed(i);
    chuoRapid->setSpeed(i);
    if (0 < i) {
      digitalWrite(i + lowestDebug - 1, HIGH);
    } else {
      for (int j = lowestDebug; j <= highestDebug; j++)
        digitalWrite(j, LOW);
    }
    delay(3000);
  }
}

void CTC::maxSpeedTest() {
  nex->setSpeed(Train::MAX_SPEED);
  chuoRapid->setSpeed(Train::MAX_SPEED);
}

Block CTC::getWay(Train *train) {
  Block next;
  switch (train->getPos()) {
  case CHOFU_MASTER:
  case CHOFU_SLAVE:
    next = FUDA_2;
    break;
  case CHOFU_1:
    if (train->getType() == EXPRESS) next = CHOFU_MASTER;
    else next = CHOFU_SLAVE;
    break;
  default:
    next = (Block) (train->getPos() + 1);
  }
  return next;
}
