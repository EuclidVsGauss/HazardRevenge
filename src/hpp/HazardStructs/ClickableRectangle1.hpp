#ifndef HAZARD_WINDOWRELATED_HPP
#define HAZARD_WINDOWRELATED_HPP
#include "HazardTypedef.hpp"

struct ClickableRectangle1 {
  int32_t lowerX;
  int32_t lowerY;
  int32_t upperX;
  int32_t upperY;
  int16_t short1;
  int16_t short2;
};
typedef struct ClickableRectangle1 ClickableRectangle1, *PClickableRectangle1;

#endif
