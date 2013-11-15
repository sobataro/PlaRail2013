#include "Train.h"

Train::Train(TrainType type, int pos) {
  this->type = type;
  setPos(pos);
  this->speed = MIN_SPEED;
}

TrainType Train::getType() {
  return type;
}

int Train::getPos() {
  return pos;
}

void Train::setPos(int pos) {
  this->pos = pos;
}

int Train::getSpeed() {
  return speed;
}

void Train::accelerate() {
  if (speed < MAX_SPEED) speed++;
}

void Train::decelerate() {
  if (MIN_SPEED < speed) speed--;
}

