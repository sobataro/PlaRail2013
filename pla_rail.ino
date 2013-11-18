#include "Arduino.h"
#include "PlaRail.h"
#include "CTC.h"

CTC *ctc;

void setup() {
  Serial.begin(9600);
  
  ctc = new CTC();
  
  for (int i = lowestDebug; i <= highestDebug; i++) {
    pinMode(i, OUTPUT);
  }
}

int pwm = 0;
void loop() {
  ctc->loop();
  delay(1000);
}
