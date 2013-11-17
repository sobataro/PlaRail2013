#include "CTC.h"

  int preCds = 13;
  int mainCds = 12;
  int signal = 11;

CTC::CTC() {
  // init train
  TCCR5B = (TCCR5B & 0xF8) | 0x05; // set motor PWM to 30Hz
  nex = new Train(EXPRESS, CHOFU_MAIN, 44, 45);
  TCCR4B = (TCCR4B & 0xF8) | 0x05; // set motor PWM to 30Hz
  chuoRapid = new Train(RAPID, CHOFU_SUB, 6, 7);
  
  pinMode(preCds, INPUT);
  pinMode(mainCds, INPUT);
  pinMode(signal, OUTPUT);
}

void CTC::loop() {
  for (int i = 0; i < 5; i++) {
    nex->setSpeed(i);
    chuoRapid->setSpeed(i);
    
    if (i % 2) {
      digitalWrite(signal, HIGH);
    } else {
      digitalWrite(signal, LOW);
    }
    Serial.print("pre=");
    Serial.print(digitalRead(preCds));
    Serial.print(" main=");
    Serial.println(digitalRead(mainCds));
    
    if (0 < i) {
      digitalWrite(i + lowestDebug - 1, HIGH);
    } else {
      for (int j = lowestDebug; j <= highestDebug; j++)
        digitalWrite(j, LOW);
    }
    delay(2000);
  }
}

Block CTC::nextBlock(Train *train) {
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
