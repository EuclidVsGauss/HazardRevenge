#ifndef HAZARD_RGBCOLOR_HPP
#define HAZARD_RGBCOLOR_HPP
#include "HazardTypedef.hpp"

struct RgbColor {
  signed char red;
  signed char green;
  signed char blue;
};
typedef struct RgbColor RgbColor, *PRgbColor;

#endif
