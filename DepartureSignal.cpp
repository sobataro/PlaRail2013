#include "DepartureSignal.h"

DepartureSignal::DepartureSignal(Block block, Train *initialTrain, State initialState, int preCdsPin, int mainCdsPin, int signalPin, long stopMillis) :
  Signal(block, initialTrain, initialState, preCdsPin, mainCdsPin, signalPin) {
  Serial.println("departure signal");
  this->stopMillis = stopMillis;
}

boolean DepartureSignal::check() {
  // check if the next train is approaching
  const int pre = preCds->check();
  const int main = mainCds->check();
  
  if (pre == HIGH && main == LOW && state == RUNNING) {
    setApproaching();
    existingTrain->setSpeed(1);
  }
  if (pre == HIGH && main == HIGH && state == APPROACHING) {
    Serial.println("stop!");
    Serial.println(stopMillis);
    setPassing();
    lastStoppedMillis = millis();
  }
  if (stopMillis < millis() - lastStoppedMillis) {
    existingTrain->setSpeed(1);
  } else {
    existingTrain->setSpeed(0);
  }
  
  if (state == PASSING && pre == LOW && main == LOW && nextSignal->canEnter(existingTrain)) { // last condition for noise tolerant
    setNoTrain();
  }
  // change the signal
  if (restricted || !nextSignal->canEnter(existingTrain)) {
    // lights red
    color = RED;
    if (existingTrain != NULL && state == PASSING) {
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

boolean DepartureSignal::enter(Train *train) {
  train->setSpeed(1);
  return Signal::enter(train);
}
