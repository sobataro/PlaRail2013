#include "CTC.h"

CTC::CTC() {
  // init train
  TCCR5B = (TCCR5B & 0xF8) | 0x05; // set motor PWM to 30Hz
  nex = new Train(EXPRESS, CHOFU_MAIN, 44, 45);
  TCCR4B = (TCCR4B & 0xF8) | 0x05; // set motor PWM to 30Hz
  chuoRapid = new Train(RAPID, CHOFU_SUB, 6, 7);
  
  signals[FUDA_2] = new Signal(FUDA_2, chuoRapid, 13, 12, 11);
  signals[FUDA_1] = new Signal(FUDA_1, NULL, 10, 9, 8);
  signals[FUDA] = new Signal(FUDA, nex, 4, 3, 2);
  signals[CHOFU_2] = new Signal(CHOFU_2, NULL, 24, 25, 26);
  signals[CHOFU_1] = new Signal(CHOFU_1, NULL, 28, 29, 27);
  signals[CHOFU_MAIN] = new Signal(CHOFU_MAIN, NULL, 32, 33, 34);
  signals[CHOFU_SUB] = new Signal(CHOFU_SUB, NULL, 36, 37, 35);
}

void CTC::loop() {
  int changed = 0;
  for (int i = 0; i < 3; i++) {
    changed += signals[i]->check(signals[(i + 1) % 3]);
  }
  if (changed) {
    Serial.println("==============");
  }
}

void CTC::accelTest() {
  for (int i = 0; i < 5; i++) {
    nex->setSpeed(i);
    chuoRapid->setSpeed(i);
    if (0 < i) {
      digitalWrite(i + lowestDebug - 1, HIGH);
    } else {
      for (int j = lowestDebug; j <= highestDebug; j++)
        digitalWrite(j, LOW);
    }
    delay(2000);
  }
}

void CTC::maxSpeedTest() {
  nex->setSpeed(4);
  chuoRapid->setSpeed(4);
}

Block CTC::getWay(Train *train) {
  Block next;
  switch (train->getPos()) {
  case CHOFU_MAIN:
  case CHOFU_SUB:
    next = FUDA_2;
    break;
  case CHOFU_1:
    if (train->getType() == EXPRESS) next = CHOFU_MAIN;
    else next = CHOFU_SUB;
    break;
  default:
    next = (Block) (train->getPos() + 1);
  }
  return next;
}
