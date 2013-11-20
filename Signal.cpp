#include "Signal.h"

Signal::Signal(Block block, Train *initialTrain, State initialState, int preCdsPin, int mainCdsPin, int signalPin) {
  this->block = block;
  this->existingTrain = initialTrain;
  this->state = initialState;
  this->preCdsPin = preCdsPin;
  this->mainCdsPin = mainCdsPin;
  this->signalPin = signalPin;
  release();
  
  pinMode(preCdsPin, INPUT);
  pinMode(mainCdsPin, INPUT);
  pinMode(signalPin, OUTPUT);
}

Signal::Signal() {
}

Train* Signal::getTrain() {
  return existingTrain;
}

Signal::State Signal::getState() {
  return state;
}

void Signal::setNextSignal(Signal *nextSignal) {
  this->nextSignal = nextSignal;
}

boolean Signal::check() {
  // check if the next train is approaching
  const int pre = digitalRead(preCdsPin);
  const int main = digitalRead(mainCdsPin);
  
  if (pre == HIGH && main == LOW && state == RUNNING) {
    Serial.println("change to approaching");
    // the train is approaching to this signal
    state = APPROACHING;
    if (restricted || !nextSignal->canEnter(existingTrain)) {
      // slow down the train for stop
      if (Train::MIN_SPEED + 1 < existingTrain->getSpeed()) {
        existingTrain->setSpeed(Train::MIN_SPEED + 1);
        Serial.print("slow down train #");
        Serial.println(existingTrain->getType());
      }
    }
  }
  if (pre == HIGH && main == HIGH && state == APPROACHING) {
    Serial.println("change to passing");
    state = PASSING;
    if (restricted || !nextSignal->canEnter(existingTrain)) {
      // stop the train
      existingTrain->setSpeed(Train::MIN_SPEED);
    }
  }
  if (state == PASSING && pre == LOW && main == LOW) {
    // the train leaves; clear this block
    Serial.println("change to no_train");
    state = NO_TRAIN;
    nextSignal->enter(existingTrain);
    existingTrain = NULL;
  }
  // change the signal
  if (restricted || !nextSignal->canEnter(existingTrain)) {
    // lights red
    digitalWrite(signalPin, RED);
    if (existingTrain != NULL && !existingTrain->isRestricted()) {
      existingTrain->restrict();
    }
  } else {
    // lights green
    digitalWrite(signalPin, GREEN);
    if (existingTrain != NULL && existingTrain->isRestricted()) {
      existingTrain->release();
    }
  }
  
  boolean stateChanged = state != previousState;
//  boolean stateChanged = state != previousState || lastPre != pre || lastMain != main;
//  lastPre = pre;
//  lastMain = main;
//  if (stateChanged) print(pre, main);
  
  // save current state for next check()
  previousState = state;
  
  return stateChanged;
}

void Signal::print(int preCds, int mainCds) {
    Serial.print("Sig");
    Serial.print(block);
    Serial.print("=(");
    Serial.print(mainCds);
    Serial.print(preCds);
    Serial.print(",");
    Serial.print(state);
    Serial.print(",");
    if (existingTrain == NULL) {
      Serial.print("NULL");
    } else {
      existingTrain->print();
    }
    Serial.println(")");
}

void Signal::restrict() {
  restricted = true;
  if (existingTrain != NULL && !existingTrain->isRestricted()) {
    existingTrain->restrict();
  }
}

void Signal::release() {
  restricted = false;
  if (nextSignal->canEnter(existingTrain) && existingTrain != NULL && existingTrain->isRestricted()) {
    existingTrain->release();
  }
}

void Signal::printTrainIfExists() {
  if (existingTrain != NULL) {
    Serial.print("[");
    Serial.print(getBlock());
    Serial.print(",");
    Serial.print(existingTrain->getType() == EXPRESS ? "EXPRESS" : "RAPID");
    Serial.print("]");
  }
}

boolean Signal::canEnter(Train *train) {
  return existingTrain == NULL;
}

boolean Signal::enter(Train *train) {
  if (canEnter(train)) {
    existingTrain = train;
    state = RUNNING;
    return true;
  } else {
    return false;
  }
}

Block Signal::getBlock() {
  return block;
}
