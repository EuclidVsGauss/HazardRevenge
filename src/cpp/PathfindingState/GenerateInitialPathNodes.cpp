#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/PathfindingState.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/PathfindingDirection.hpp"
#include "HazardStructs/PathfindingNode.hpp"
#include "HazardStructs/PathfindingNodesBlock.hpp"

void PathfindingState::GenerateInitialPathNodes(int32_t param_1, int32_t param_2, int32_t eyeRelated) {
  uint32_t posX;
  int32_t isVisited;
  PathfindingNode* entry;
  PathfindingNode* currentNode;
  byte* visibilityByte;
  int32_t bucketIndex;
  int16_t startX;
  uint32_t shiftedPosX;
  PathfindingNode** currentBucket;
  int16_t startY;
  uint32_t shiftedPosY;
  int32_t positionHash;
  PathfindingDirection* neighborSrc;
  int32_t loopCounter;

  loopCounter = 0x100;
  currentBucket = this->startOfArray;
  do {
    for (currentNode = *currentBucket; currentNode != nullptr; currentNode = currentNode->nextNodeInHashBucket) {
      visibilityByte = (this->gridHandler->PaddedGridMap_Visibility[currentNode->usedForPos2]) + currentNode->usedForPos1;
      *visibilityByte = *visibilityByte + -1;
    }
    currentBucket = currentBucket + 1;
    loopCounter = loopCounter + -1;
  } while (loopCounter != 0);
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
  currentBucket = this->startOfArray;
  for (bucketIndex = 0x100; bucketIndex != 0; bucketIndex = bucketIndex + -1) {
    *currentBucket = nullptr;
    currentBucket = currentBucket + 1;
  }
  this->currentPathCost = 0;
  this->currentDirection = -1;
  if (-1 < eyeRelated) {
    posX = param_1 >> 1;
    shiftedPosY = param_2 >> 1;
    startY = (int16_t)posX;
    startX = (int16_t)shiftedPosY;
    if ((0 < (int32_t)posX) && (0 < (int32_t)shiftedPosY)) {
      currentNode = this->currentlyProcessedNode;
      bucketIndex = ((shiftedPosY & 0xf) * 0x10) + (posX & 0xf);
      positionHash = (shiftedPosY * 0x10000) + posX;
      isVisited = IsCoordinateVisited(positionHash, bucketIndex);
      if (isVisited == 0) {
        entry = this->AllocatePathNode();
        entry->linkToParentNode = currentNode;
        entry->usedForPos1 = startY;
        entry->usedForPos2 = startX;
        entry->hashedPositionKey = positionHash;
        entry->pathCostToThisNode = 0;
        entry->directionFromParent = 0xff;
        entry->nextNodeInHashBucket = this->startOfArray[bucketIndex];
        this->startOfArray[bucketIndex] = entry;
        this->currentBestNode = entry;
        if (this->headCircularPathList == nullptr) {
          this->headCircularPathList = entry;
          entry->nextInOpenList = entry;
          entry->previousInOpenList = entry;
        }
        else {
          entry->nextInOpenList = this->headCircularPathList;
          entry->previousInOpenList = this->headCircularPathList->previousInOpenList;
          this->headCircularPathList->previousInOpenList->nextInOpenList = entry;
          this->headCircularPathList->previousInOpenList = entry;
        }
      }
    }
    shiftedPosX = posX - 1;
    if ((0 < (int32_t)shiftedPosX) && (0 < (int32_t)shiftedPosY)) {
      currentNode = this->currentlyProcessedNode;
      bucketIndex = ((shiftedPosY & 0xf) * 0x10) + (shiftedPosX & 0xf);
      positionHash = (shiftedPosY * 0x10000) + shiftedPosX;
      isVisited = IsCoordinateVisited(positionHash, bucketIndex);
      if (isVisited == 0) {
        entry = this->AllocatePathNode();
        entry->linkToParentNode = currentNode;
        entry->usedForPos1 = startY + -1;
        entry->usedForPos2 = startX;
        entry->hashedPositionKey = positionHash;
        entry->pathCostToThisNode = 0;
        entry->directionFromParent = 0;
        entry->nextNodeInHashBucket = this->startOfArray[bucketIndex];
        this->startOfArray[bucketIndex] = entry;
        this->currentBestNode = entry;
        if (this->headCircularPathList == nullptr) {
          this->headCircularPathList = entry;
          entry->nextInOpenList = entry;
          entry->previousInOpenList = entry;
        }
        else {
          entry->nextInOpenList = this->headCircularPathList;
          entry->previousInOpenList = this->headCircularPathList->previousInOpenList;
          this->headCircularPathList->previousInOpenList->nextInOpenList = entry;
          this->headCircularPathList->previousInOpenList = entry;
        }
      }
    }
    shiftedPosX = posX + 1;
    if ((0 < (int32_t)shiftedPosX) && (0 < (int32_t)shiftedPosY)) {
      currentNode = this->currentlyProcessedNode;
      bucketIndex = ((shiftedPosY & 0xf) * 0x10) + (shiftedPosX & 0xf);
      positionHash = (shiftedPosY * 0x10000) + shiftedPosX;
      isVisited = IsCoordinateVisited(positionHash, bucketIndex);
      if (isVisited == 0) {
        entry = this->AllocatePathNode();
        entry->linkToParentNode = currentNode;
        entry->usedForPos1 = startY + 1;
        entry->usedForPos2 = startX;
        entry->hashedPositionKey = positionHash;
        entry->pathCostToThisNode = 0;
        entry->directionFromParent = 0;
        entry->nextNodeInHashBucket = this->startOfArray[bucketIndex];
        this->startOfArray[bucketIndex] = entry;
        this->currentBestNode = entry;
        if (this->headCircularPathList == nullptr) {
          this->headCircularPathList = entry;
          entry->nextInOpenList = entry;
          entry->previousInOpenList = entry;
        }
        else {
          entry->nextInOpenList = this->headCircularPathList;
          entry->previousInOpenList = this->headCircularPathList->previousInOpenList;
          this->headCircularPathList->previousInOpenList->nextInOpenList = entry;
          this->headCircularPathList->previousInOpenList = entry;
        }
      }
    }
    if (0 < (int32_t)posX) {
      shiftedPosX = shiftedPosY - 1;
      if (0 < (int32_t)shiftedPosX) {
        currentNode = this->currentlyProcessedNode;
        bucketIndex = ((shiftedPosX & 0xf) * 0x10) + (posX & 0xf);
        positionHash = (shiftedPosX * 0x10000) + posX;
        isVisited = IsCoordinateVisited(positionHash, bucketIndex);
        if (isVisited == 0) {
          entry = this->AllocatePathNode();
          entry->linkToParentNode = currentNode;
          entry->usedForPos1 = startY;
          entry->usedForPos2 = startX + -1;
          entry->hashedPositionKey = positionHash;
          entry->pathCostToThisNode = 0;
          entry->directionFromParent = 0;
          entry->nextNodeInHashBucket = this->startOfArray[bucketIndex];
          this->startOfArray[bucketIndex] = entry;
          this->currentBestNode = entry;
          if (this->headCircularPathList == nullptr) {
            this->headCircularPathList = entry;
            entry->nextInOpenList = entry;
            entry->previousInOpenList = entry;
          }
          else {
            entry->nextInOpenList = this->headCircularPathList;
            entry->previousInOpenList = this->headCircularPathList->previousInOpenList;
            this->headCircularPathList->previousInOpenList->nextInOpenList = entry;
            this->headCircularPathList->previousInOpenList = entry;
          }
        }
      }
      if (0 < (int32_t)(shiftedPosY + 1)) {
        PushOpenNode(this->currentlyProcessedNode, posX, shiftedPosY + 1, 0, 0);
      }
    }
    positionHash = this->currentPathCost;
    while (positionHash <= (eyeRelated + 1) >> 1) {
      if (this->gridHandler->PaddedGridMap_LineOfSight[shiftedPosY][posX] == 0) {
        param_1 = 0;
        neighborSrc = PathfindingDirectionLookup;
        do {
          PathfindingLatestDirection = neighborSrc;
          if (param_1 != this->currentDirection) {
            PushOpenNode(this->currentlyProcessedNode, neighborSrc->direction1 + posX, neighborSrc->direction2 + shiftedPosY, *(byte*)&neighborSrc->directionIndex, (int16_t)this->currentPathCost);
          }
          neighborSrc = neighborSrc + 1;
          param_1 = param_1 + 1;
        } while (neighborSrc < PathfindingDirectionLookup + 8);
      }
      currentNode = this->PopHighestPriorityNodeFromOpenList();
      this->currentlyProcessedNode = currentNode;
      if (currentNode == nullptr) {
        break;
      }
      posX = (uint32_t)currentNode->usedForPos1;
      shiftedPosY = (uint32_t)currentNode->usedForPos2;
      positionHash = currentNode->pathCostToThisNode + 1;
      this->currentPathCost = positionHash;
      this->currentDirection = (currentNode->directionFromParent - 4) & 7;
    }
    currentBucket = this->startOfArray;
    bucketIndex = 0x100;
    do {
      for (currentNode = *currentBucket; currentNode != nullptr; currentNode = currentNode->nextNodeInHashBucket) {
        this->gridHandler->SetVisibilityAtPosition((int32_t)currentNode->usedForPos1, (int32_t)currentNode->usedForPos2, 1);
      }
      currentBucket = currentBucket + 1;
      bucketIndex = bucketIndex + -1;
    } while (bucketIndex != 0);
  }
}
