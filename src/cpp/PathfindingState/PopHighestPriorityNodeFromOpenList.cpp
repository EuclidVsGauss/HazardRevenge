#include "HazardClasses/PathfindingState.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/PathfindingNode.hpp"

PathfindingNode* __fastcall PathfindingState::PopHighestPriorityNodeFromOpenList() {
  PathfindingNode* targetNode;
  PathfindingNode* nextNode;

  targetNode = this->headCircularPathList;
  if ((targetNode != nullptr) && (nextNode = targetNode->nextInOpenList, this->headCircularPathList = nextNode, targetNode != nextNode)) {
    targetNode->nextInOpenList->previousInOpenList = targetNode->previousInOpenList;
    targetNode->previousInOpenList->nextInOpenList = targetNode->nextInOpenList;
    return targetNode;
  }
  this->headCircularPathList = nullptr;
  return targetNode;
}
