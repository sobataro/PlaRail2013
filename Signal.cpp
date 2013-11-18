#include "Signal.h"

Signal::Signal(Block block, Train *initialTrain, int preCdsPin, int mainCdsPin, int signalPin) {
  this->block = block;
  this->existingTrain = initialTrain;
  this->preCdsPin = preCdsPin;
  this->mainCdsPin = mainCdsPin;
  this->signalPin = signalPin;
  
  if (existingTrain != NULL) {
    state = PASSING;
  } else {
    state = NO_TRAIN;
  }
  
  pinMode(preCdsPin, INPUT);
  pinMode(mainCdsPin, INPUT);
  pinMode(signalPin, OUTPUT);
}

boolean Signal::check(Signal *nextSignal) {
  // check if the next train is approaching
  int pre = digitalRead(preCdsPin);
  int main = digitalRead(mainCdsPin);
  
  if (pre == HIGH && state == RUNNING) {
    // the train is approaching to this signal
    state = APPROACHING;
    if (!nextSignal->canEnter(existingTrain)) {
      // TODO: slow down the train for stop
      if (Train::MAX_SPEED / 2 < existingTrain->getSpeed()) {
        existingTrain->setSpeed(Train::MAX_SPEED / 2);
        Serial.print("slow down train #");
        Serial.println(existingTrain->getType());
      }
    }
  }
  if (main == HIGH && state == APPROACHING) {
    state = PASSING;
    if (!nextSignal->canEnter(existingTrain)) {
      // stop the train
      existingTrain->setSpeed(Train::MIN_SPEED);
    }
  }
  if ((state == PASSING || state == APPROACHING) && pre == LOW && main == LOW) {
    // the train leaves; clear this block
    state = NO_TRAIN;
    nextSignal->enter(existingTrain);
    existingTrain = NULL;
  }
  
  // change the signal
  digitalWrite(signalPin, nextSignal->canEnter(existingTrain) ? GREEN : RED);

  boolean stateChanged = state != previousState;
  if (stateChanged) {
    Serial.print("Sig");
    Serial.print(block);
    Serial.print("=(");
    Serial.print(main);
    Serial.print(pre);
    Serial.print(",");
    Serial.print(state);
    Serial.println(")");
  }

  // save current state for next check()
  previousState = state;
  
  return stateChanged;
}

Signal::State Signal::getState() {
  return state;
}

Block Signal::getBlock(Train *train) {
  return block;
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

