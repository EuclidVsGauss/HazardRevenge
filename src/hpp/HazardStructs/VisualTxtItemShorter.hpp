#ifndef HAZARD_VISUALTXTITEMSHORTER_HPP
#define HAZARD_VISUALTXTITEMSHORTER_HPP
#include "HazardTypedef.hpp"

struct VisualTxtItemShorter {
  int32_t samplingRate;
  char visualSoundName[20];
  char visualMovieName[20];
};
typedef struct VisualTxtItemShorter VisualTxtItemShorter, *PVisualTxtItemShorter;

#endif
