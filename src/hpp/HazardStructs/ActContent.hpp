#ifndef HAZARD_ACTCONTENT_HPP
#define HAZARD_ACTCONTENT_HPP
#include "HazardTypedef.hpp"

struct ActContent {
  char actionName[16];
  int32_t numberFrames;
  int32_t* ptrFrameStart;
};
typedef struct ActContent ActContent, *PActContent;

#endif
