#ifndef HAZARD_TUPLESHORTS_HPP
#define HAZARD_TUPLESHORTS_HPP
#include "HazardTypedef.hpp"

struct Size2D {
  uint16_t defaultRightBound;
  uint16_t defaultLeftBound;
};
typedef struct Size2D Size2D, *PSize2D;

#endif
