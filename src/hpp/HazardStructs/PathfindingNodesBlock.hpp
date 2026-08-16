#ifndef HAZARD_PathfinderNodes_HPP
#define HAZARD_PathfinderNodes_HPP

#include "HazardTypedef.hpp"
#include "PathfindingNode.hpp"

struct PathfindingNode;

struct PathfindingNodesBlock {
  PathfindingNode listEyeRelated[2048];
  PathfindingNodesBlock* next;
};
typedef struct PathfindingNodesBlock PathfindingNodesBlock, *PPathfindingNodesBlock;

#endif
