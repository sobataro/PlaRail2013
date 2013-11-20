#include "Train.h"

Train::Train(TrainType type, Block pos, int pwmPinA, int pwmPinB) {
  this->type = type;
  setPos(pos);
  this->speed = MIN_SPEED;
  
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

const int Train::pwmDuty[] = {0, 144, 192, 255};

void Train::setPos(Block pos) {
  this->pos = pos;
}

int Train::getSpeed() {
  return speed;
}

void Train::setSpeed(int speed) {
  if (MIN_SPEED <= speed && speed <= MAX_SPEED) {
    this->speed = speed;
    analogWrite(pwmPinB, 0);
    analogWrite(pwmPinA, pwmDuty[speed]);
  }
}

void Train::accelerate() {
  setSpeed(speed + 1);
}

void Train::decelerate() {
  setSpeed(speed - 1);
}

