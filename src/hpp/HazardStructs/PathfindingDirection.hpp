#ifndef HAZARD_EYERELATEDARRAY_HPP
#define HAZARD_EYERELATEDARRAY_HPP
#include "HazardStructs/PathfindingCollisionOffset.hpp"
#include "HazardTypedef.hpp"

struct PathfindingDirection {
  int32_t direction1;
  int32_t direction2;
  int32_t directionIndex;
  int32_t collisionCheckCount;
  PathfindingCollisionOffset collisionOffsets[3];
};
typedef struct PathfindingDirection PathfindingDirection, *PPathfindingDirection;

#endif
