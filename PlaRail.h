#ifndef PlaRail_h
#define PlaRail_h

const int lowestDebug = 46;
const int highestDebug = 49;

const int NUM_SIGNALS = 6;
const int NUM_REAL_SIGNALS = NUM_SIGNALS + 2; // 2 for CHOFU_MASTER and CHOFU_SLAVE

enum TrainType {
  RAPID, EXPRESS
};

enum Block {
  FUDA_2, FUDA_1, FUDA, CHOFU_2, CHOFU_1, CHOFU, CHOFU_MASTER, CHOFU_SLAVE
};

#endif
