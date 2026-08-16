#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/PathfindingState.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/PathfindingNode.hpp"
#include "HazardStructs/PathfindingNodesBlock.hpp"

int32_t PathfindingState::PushOpenNode(PathfindingNode* parentNode, uint32_t xCoordinate, uint32_t yCoordinate, byte pathDirMod, int16_t pathCost) {
  PathfindingNode* bucketEntry;
  PathfindingNodesBlock* newAllocBlock;
  PathfindingNode* newNode;
  int32_t currentBestCost;
  int32_t maxAllowedCost;
  int32_t hashIndex;

  hashIndex = ((yCoordinate & 15) * 0x10) + (xCoordinate & 15);
  if (this->currentBestNode != nullptr) {
    currentBestCost = this->currentBestNode->pathCostToThisNode + -10;
  }
  else {
    currentBestCost = 0;
  }
  maxAllowedCost = (yCoordinate * 0x10000) + xCoordinate;
  for (bucketEntry = this->startOfArray[hashIndex]; (bucketEntry != nullptr && (currentBestCost < bucketEntry->pathCostToThisNode)); bucketEntry = bucketEntry->nextNodeInHashBucket) {
    if (bucketEntry->hashedPositionKey == maxAllowedCost) {
      return 0;
    }
  }
  if (2047 < this->countNodesUsed) {
    if (WrapperRelated == nullptr) {
      newAllocBlock = new PathfindingNodesBlock;
      this->nodeAllocation_1->next = newAllocBlock;
    }
    else {
      this->nodeAllocation_1->next = WrapperRelated;
      WrapperRelated = WrapperRelated->next;
    }
    newAllocBlock = this->nodeAllocation_1->next;
    this->nodeAllocation_1 = newAllocBlock;
    newAllocBlock->next = nullptr;
    this->countNodesUsed = 0;
  }
  newNode = this->nodeAllocation_1->listEyeRelated + this->countNodesUsed;
  this->countNodesUsed = this->countNodesUsed + 1;
  newNode->linkToParentNode = parentNode;
  newNode->usedForPos1 = (int16_t)xCoordinate;
  newNode->usedForPos2 = (int16_t)yCoordinate;
  newNode->hashedPositionKey = maxAllowedCost;
  newNode->pathCostToThisNode = pathCost;
  newNode->directionFromParent = pathDirMod;
  newNode->nextNodeInHashBucket = this->startOfArray[hashIndex];
  this->startOfArray[hashIndex] = newNode;
  this->currentBestNode = newNode;
  if (this->headCircularPathList != nullptr) {
    newNode->nextInOpenList = this->headCircularPathList;
    newNode->previousInOpenList = this->headCircularPathList->previousInOpenList;
    this->headCircularPathList->previousInOpenList->nextInOpenList = newNode;
    this->headCircularPathList->previousInOpenList = newNode;
    return maxAllowedCost;
  }
  this->headCircularPathList = newNode;
  newNode->nextInOpenList = newNode;
  newNode->previousInOpenList = newNode;
  return maxAllowedCost;
}
