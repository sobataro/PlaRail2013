#include "Controller.h"

Controller::Controller(Train *train, int accelButtonPin, int decelButtonPin, int redLedPin, int greenLedPins[Train::SPEED_LEVELS]) {
  this->train = train;
  this->redLedPin = redLedPin;
  pinMode(redLedPin, OUTPUT);
  for (int i = 0; i < Train::SPEED_LEVELS; i++) {
    this->greenLedPins[i] = greenLedPins[i];
    pinMode(greenLedPins[i], OUTPUT);
  }
  accelButton = new PushSwitch(accelButtonPin, 200, HIGH);
  decelButton = new PushSwitch(decelButtonPin, 200, HIGH);
}

Controller::~Controller() {
  delete accelButton;
  delete decelButton;
  delete greenLedPins;
}

void Controller::check() {
  if (decelButton->check() == LOW) {
    train->decelerate();
    Serial.print("check: ");
    Serial.print(decelButton->check());
    Serial.print(", ");
    Serial.print(accelButton->check());
    Serial.print("   speed:");
    Serial.println(train->getSpeed());
  } else if (accelButton->check() == LOW) {
    train->accelerate();
    Serial.print("check: ");
    Serial.print(decelButton->check());
    Serial.print(", ");
    Serial.print(accelButton->check());
    Serial.print("   speed:");
    Serial.println(train->getSpeed());
  }
  
  for (int i = 0; i < Train::SPEED_LEVELS; i++) {
    digitalWrite(greenLedPins[i], i < train->getSpeed());
  }
}

