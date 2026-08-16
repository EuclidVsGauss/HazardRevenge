#ifndef HAZARD_RNGHITHELPER16_HPP
#define HAZARD_RNGHITHELPER16_HPP
#include "HazardTypedef.hpp"

struct DirectionOffsets {
  int32_t DeltaX1;
  int32_t DeltaY1;
  int32_t DeltaX2;
  int32_t DeltaY2;
};
typedef struct DirectionOffsets DirectionOffsets, *PDirectionOffsets;

#endif
