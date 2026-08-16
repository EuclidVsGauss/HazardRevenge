#ifndef HAZARD_SUBENTRY_HPP
#define HAZARD_SUBENTRY_HPP
#include "HazardTypedef.hpp"

struct PathfindingCollisionOffset {
  int32_t offsetX;
  int32_t offsetY;
};
typedef struct PathfindingCollisionOffset PathfindingCollisionOffset, *PPathfindingCollisionOffset;

#endif
