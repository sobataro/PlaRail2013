#include "SchmidtTrigger.h"

SchmidtTrigger::SchmidtTrigger(int pin, int count, int threshold) : Debounce() {
  this->pin = pin;
  this->values = (int *) malloc(count * sizeof(int));
  this->threshold = threshold;
  this->pointer = 0;
  this->count = count;
  
  pinMode(pin, INPUT);
  int defaultValue = digitalRead(pin);
  for (int i = 0; i < count; i++) {
    values[i] = defaultValue;
  }
}

SchmidtTrigger::~SchmidtTrigger() {
  free(values);
}

int SchmidtTrigger::check() {
  values[pointer] = digitalRead(pin);
  
  int sum = 0;
  for (int i = 0; i < count; i++) sum += values[i];
  
  pointer = (pointer + 1) % count;
  return threshold < sum;
}

