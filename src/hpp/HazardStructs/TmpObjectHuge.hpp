#ifndef HAZARD_TMPOBJECTHUGE_HPP
#define HAZARD_TMPOBJECTHUGE_HPP
#include "HazardTypedef.hpp"

struct TmpObjectHuge {
  int16_t start[262144];
  int16_t last_1024b[512];
};
typedef struct TmpObjectHuge TmpObjectHuge, *PTmpObjectHuge;

#endif
