#include "HazardClasses/PathfindingState.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/PathfindingNode.hpp"
#include "HazardStructs/PathfindingNodesBlock.hpp"

void PathfindingState::SetStartAndTargetCoordinates(int32_t startX, int32_t startY, int32_t targetX, int32_t targetY) {

  int32_t loopIndex;
  PathfindingNode** ptr;

  this->nodeAllocation_1->next = WrapperRelated;
  WrapperRelated = this->nodeAllocation_2;
  this->nodeAllocation_1 = WrapperRelated;
  this->nodeAllocation_2 = WrapperRelated;
  WrapperRelated = WrapperRelated->next;
  this->countNodesUsed = 0;
  this->nodeAllocation_2->next = nullptr;
  this->currentBestNode = nullptr;
  this->currentlyProcessedNode = nullptr;
  this->headCircularPathList = nullptr;
  ptr = this->startOfArray;
  for (loopIndex = 256; loopIndex != 0; loopIndex = loopIndex + -1) {
    *ptr = nullptr;
    ptr = ptr + 1;
  }
  this->currentCoord1 = startX;
  this->currentCoord2 = startY;
  this->currentPathCost = 0;
  this->currentDirection = -1;
  this->targetPackedCoordinate = (targetY * 0x10000) + targetX;
}
