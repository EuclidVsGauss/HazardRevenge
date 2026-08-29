#include "HazardClasses/PathfindingState.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/PathfindingNode.hpp"

int32_t PathfindingState::IsCoordinateVisited(int32_t param_1, int32_t param_2) {
  PathfindingNode* currentHashNode;
  int32_t cutoffPathCost;

  if (this->currentBestNode != nullptr) {
    cutoffPathCost = this->currentBestNode->pathCostToThisNode + -10;
  }
  else {
    cutoffPathCost = 0;
  }
  for (currentHashNode = this->startOfArray[param_2]; (currentHashNode != nullptr && (currentHashNode->pathCostToThisNode > cutoffPathCost)); currentHashNode = currentHashNode->nextNodeInHashBucket) {
    if (currentHashNode->hashedPositionKey == param_1) {
      return 1;
    }
  }
  return 0;
}
