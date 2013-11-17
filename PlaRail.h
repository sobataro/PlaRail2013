#ifndef PlaRail_h
#define PlaRail_h

const int pwmA0 = 6;
const int pwmA1 = 7;
const int pwmB0 = 44;
const int pwmB1 = 45;

const int lowestDebug = 46;
const int highestDebug = 49;

enum TrainType {
  RAPID, EXPRESS
};

enum Block {
  CHOFU_MAIN, CHOFU_SUB, FUDA_2, FUDA_1, FUDA, CHOFU_2, CHOFU_1
};

#endif
