#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/PathfindingState.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/PathfindingNode.hpp"
#include "HazardStructs/PathfindingNodesBlock.hpp"

PathfindingState::PathfindingState(GridHandler* gridHandler) {
  PathfindingNodesBlock* newAllocationNode;
  int32_t i;
  PathfindingNode** arrayIterator;

  this->gridHandler = gridHandler;
  if (WrapperRelated != nullptr) {
    this->nodeAllocation_1 = WrapperRelated;
    this->nodeAllocation_2 = WrapperRelated;
    WrapperRelated = WrapperRelated->next;
  }
  else {
    newAllocationNode = new PathfindingNodesBlock;
    this->nodeAllocation_1 = newAllocationNode;
    this->nodeAllocation_2 = newAllocationNode;
  }
  this->nodeAllocation_2->next = nullptr;
  this->countNodesUsed = 0;
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
  arrayIterator = this->startOfArray;
  for (i = 256; i != 0; i = i + -1) {
    *arrayIterator = nullptr;
    arrayIterator = arrayIterator + 1;
  }
  this->currentPathCost = 0;
  this->currentDirection = -1;
}
