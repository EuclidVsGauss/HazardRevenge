#ifndef HAZARD_EYERELATEDSTRUCT_HPP
#define HAZARD_EYERELATEDSTRUCT_HPP
#include "HazardTypedef.hpp"

struct PathfindingNode {
  int16_t usedForPos1;
  int16_t usedForPos2;
  int16_t pathCostToThisNode;
  byte unused1[2];
  int32_t hashedPositionKey;
  byte directionFromParent;
  byte unused2[3];
  PathfindingNode* linkToParentNode;
  PathfindingNode* nextNodeInHashBucket;
  PathfindingNode* previousInOpenList;
  PathfindingNode* nextInOpenList;
};
typedef struct PathfindingNode PathfindingNode, *PPathfindingNode;

#endif
