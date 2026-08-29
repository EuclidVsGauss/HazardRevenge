#ifndef HAZARD_VISUALTXTITEM_HPP
#define HAZARD_VISUALTXTITEM_HPP
#include "HazardTypedef.hpp"

struct VisualTxtItem {
  int32_t samplingRate;
  char visualSoundName[20];
  char visualMovieName[20];
  byte byte3;
  byte byte4;
  byte unused1;
  byte unused2;
};
typedef struct VisualTxtItem VisualTxtItem, *PVisualTxtItem;

#endif
