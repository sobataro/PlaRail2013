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
  
  /*
  pinMode(38, INPUT);
  pinMode(39, INPUT);
  pinMode(40, OUTPUT);
  pinMode(41, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(43, OUTPUT);
  */
  
  /*
  for (int i = lowestDebug; i <= highestDebug; i++) {
    pinMode(i, OUTPUT);
  }
  */
}

void loop() {
  ctc->loop();
  

  /*
  if (digitalRead(39) == HIGH) {
    Serial.println("38high");
    digitalWrite(40, HIGH);
    digitalWrite(41, HIGH);
    digitalWrite(42, HIGH);
    digitalWrite(43, HIGH);
  } else {
    digitalWrite(40, LOW);
    digitalWrite(41, LOW);
    digitalWrite(42, LOW);
    digitalWrite(43, LOW);
  }
  */
  
  delay(10);
}
