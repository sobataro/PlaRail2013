#include "CTC.h"

CTC::CTC() {
//  chuo_rapid = Train();
}

Block CTC::nextBlock(Train *train) {
  Block next;
  switch (train->getPos()) {
  case CHOFU_MAIN:
  case CHOFU_SUB:
    next = FUDA_2;
    break;
  case CHOFU_1:
    if (train->getType() == EXPRESS) next = CHOFU_MAIN;
    else next = CHOFU_SUB;
    break;
  default:
    next = (Block) (train->getPos() + 1);
  }
  return next;
}
