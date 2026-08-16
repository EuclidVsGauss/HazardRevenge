#ifndef HAZARD_CURSORRELATED_HPP
#define HAZARD_CURSORRELATED_HPP
#include "HazardTypedef.hpp"

struct ClickableRectangle3 {
  int32_t upperX;
  int32_t upperY;
  int32_t lowerX;
  int32_t lowerY;
  int32_t indexLike2;
  int32_t indexLike;
};
typedef struct ClickableRectangle3 ClickableRectangle3, *PClickableRectangle3;

#endif
