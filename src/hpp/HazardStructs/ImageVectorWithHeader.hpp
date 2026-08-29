#ifndef HAZARD_IMAGEVECTORWITHHEADER_HPP
#define HAZARD_IMAGEVECTORWITHHEADER_HPP
#include "HazardTypedef.hpp"

struct ImageVectorWithHeader {
  int32_t spriteCoordX;
  int32_t spriteCoordY;
  int32_t spriteWidth1;
  int32_t spriteWidth2;
  int16_t** startOfImageAddress;
  int16_t varibleArray[1];
};
typedef struct ImageVectorWithHeader ImageVectorWithHeader, *PImageVectorWithHeader;

#endif
