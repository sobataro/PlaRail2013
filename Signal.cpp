#include "Signal.h"

Signal::Signal(Block block, Train *initialTrain, State initialState, int preCdsPin, int mainCdsPin, int signalPin) {
  this->block = block;
  this->existingTrain = initialTrain;
  this->state = initialState;
  this->preCds = new SchmidtTrigger(preCdsPin, 20, 10);
  this->mainCds = new SchmidtTrigger(mainCdsPin, 20, 10);
  this->signalPin = signalPin;
  restricted = false;
  
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

Signal* Signal::getNextSignal() {
  return nextSignal;
}

void Signal::setApproaching() {
  Serial.print(getBlock());
  Serial.println(": change to approaching");
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

void Signal::setPassing() {
  Serial.print(getBlock());
  Serial.println(": change to passing");
  state = PASSING;
  if (restricted || !nextSignal->canEnter(existingTrain)) {
    // stop the train
    existingTrain->restrict();
  }
}

void Signal::setNoTrain() {
  // the train leaves; clear this block
  Serial.print(getBlock());
  Serial.println(": change to no_train");
  state = NO_TRAIN;
  nextSignal->enter(existingTrain);
  existingTrain = NULL;
}

boolean Signal::check() {
  // check if the next train is approaching
  const int pre = preCds->check();
  const int main = mainCds->check();
  
  if (pre == HIGH && main == LOW && state == RUNNING) {
    setApproaching();
  }
  if (pre == HIGH && main == HIGH && state == APPROACHING) {
    setPassing();
  }
  if (state == PASSING && pre == LOW && main == LOW && nextSignal->canEnter(existingTrain)) { // last condition for noise tolerant
    setNoTrain();
  }
  // change the signal
  if (restricted || !nextSignal->canEnter(existingTrain)) {
    // lights red
    color = RED;
    if (existingTrain != NULL && state == PASSING && !existingTrain->isRestricted()) {
      existingTrain->restrict();
    }
  } else {
    // lights green
    color = GREEN;
    if (existingTrain != NULL && existingTrain->isRestricted()) {
      existingTrain->release();
    }
  }
  digitalWrite(signalPin, color);
  
  boolean stateChanged = state != previousState;
//  boolean stateChanged = state != previousState || lastPre != pre || lastMain != main;
//  lastPre = pre;
//  lastMain = main;
//  if (stateChanged) print(pre, main);
  
  // save current state for next check()
  previousState = state;
  
  return stateChanged;
}

int Signal::getColor() {
  return color;
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
  /*
  if (existingTrain != NULL && !existingTrain->isRestricted()) {
    existingTrain->restrict();
  }
  */
}

void Signal::release() {
  restricted = false;
  if (nextSignal->canEnter(existingTrain) && existingTrain != NULL && existingTrain->isRestricted()) {
    existingTrain->release();
  }
}

boolean Signal::printTrainIfExists() {
  if (existingTrain != NULL) {
    existingTrain->print();
    return true;
  } else {
    return false;
  }
}

boolean Signal::canEnter(Train *train) {
  return existingTrain == NULL;
}

boolean Signal::enter(Train *train) {
  if (canEnter(train)) {
    existingTrain = train;
    existingTrain->setPos(getBlock());
    state = RUNNING;
    return true;
  } else {
    return false;
  }
}

Block Signal::getBlock() {
  return block;
}
