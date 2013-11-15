#include "Arduino.h"
#include "Train.h"

const int pwmA0 = 6;
const int pwmA1 = 7;
const int pwmB0 = 44;
const int pwmB1 = 45;

const int lowestDebug = 46;
const int highestDebug = 49;

void setup() {
  Serial.begin(9600);
  
  // init train motor PWM
  TCCR4B = (TCCR4B & 0xF8) | 0x05;
  pinMode(pwmA0, OUTPUT);
  pinMode(pwmA1, OUTPUT);
  TCCR5B = (TCCR5B & 0xF8) | 0x05;
  pinMode(pwmB0, OUTPUT);
  pinMode(pwmB1, OUTPUT);
  
  for (int i = lowestDebug; i <= highestDebug; i++) {
    pinMode(i, OUTPUT);
  }
}


int pwm = 0;
void loop() {
  for (int i = 0; i < 5; i++) {
    analogWrite(pwmA1, 0);
    analogWrite(pwmB1, 0);

    int pwm = i * 64;
    if (255 < pwm) pwm = 255;

    Serial.println(pwm);
    
    if (0 < i) {
      digitalWrite(i + lowestDebug - 1, HIGH);
    } else {
      for (int j = lowestDebug; j <= highestDebug; j++)
        digitalWrite(j, LOW);
    }
    
    analogWrite(pwmA0, pwm);
    analogWrite(pwmB0, pwm);
    delay(2000);
  }
}
