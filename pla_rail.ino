#include "Arduino.h"
#include "PlaRail.h"
#include "CTC.h"
#include "Station.h"

// 38, 39
// 40, 41
// 42, 43

CTC *ctc;
Servo crossingServo;

void setup() {
  Serial.begin(9600);
  
  ctc = new CTC();
}

void loop() {
  ctc->loop();
  delay(10);
}

