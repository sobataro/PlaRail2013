#include "Train.h"

Train::Train(TrainType type, Block pos, int pwmPinA, int pwmPinB) {
  this->type = type;
  setPos(pos);
  this->speed = MIN_SPEED;
  restricted = false;
  
  this->pwmPinA = pwmPinA;
  this->pwmPinB = pwmPinB;
  pinMode(pwmPinA, OUTPUT);
  pinMode(pwmPinB, OUTPUT);
}

TrainType Train::getType() {
  return type;
}

Block Train::getPos() {
  return pos;
}

void Train::setPos(Block pos) {
  this->pos = pos;
}

const int Train::pwmDuty[] = {0, 144, 192, 255};
//const int Train::pwmDuty[] = {0, 255, 255, 255};

int Train::getSpeed() {
  return this->speed;
}

void Train::setSpeed(int speed) {
  if (isRestricted()) {
    speed = MIN_SPEED;
  }
  if (MIN_SPEED <= speed && speed <= MAX_SPEED) {
    this->speed = speed;
    if (speed == MIN_SPEED) {
      analogWrite(pwmPinA, 255);
      analogWrite(pwmPinB, 255);
    } else {
      analogWrite(pwmPinB, 0);
      analogWrite(pwmPinA, pwmDuty[speed]);
    }
  }
}

void Train::accelerate() {
  setSpeed(this->speed + 1);
}

void Train::decelerate() {
  setSpeed(this->speed - 1);
}

boolean Train::isRestricted() {
  return restricted;
}

void Train::restrict() {
  restricted = true;
  setSpeed(MIN_SPEED);
  print();
  Serial.println(" restricted");
}

void Train::release() {
  restricted = false;
  print();
  Serial.println(" released");
}

void Train::print() {
  Serial.print(getType() == EXPRESS ? "Express" : "Rapid");
  Serial.print("[");
  Serial.print(isRestricted() ? "RESTRICTED" : "released");
  Serial.print(",speed=");
  Serial.print(getSpeed());
  Serial.print(",pos=");
  Serial.print(getPos());
  Serial.print("]");
}
