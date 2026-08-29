#ifndef HAZARD_WINDOWRELATEDOUTER_HPP
#define HAZARD_WINDOWRELATEDOUTER_HPP
#include "HazardTypedef.hpp"

struct ClickableRectangle2 {
  int32_t lowerX;
  int32_t lowerY;
  int32_t upperX;
  int32_t upperY;
  int32_t actionFrame;
  int32_t switchCommand;
};
typedef struct ClickableRectangle2 ClickableRectangle2, *PClickableRectangle2;

#endif
