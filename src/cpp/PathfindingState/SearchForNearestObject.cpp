#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/PathfindingState.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/PathfindingDirection.hpp"
#include "HazardStructs/PathfindingNode.hpp"
#include "HazardStructs/PathfindingNodesBlock.hpp"

int32_t PathfindingState::SearchForNearestObject(int32_t startX, int32_t startY, int32_t maxSteps, int32_t unused, int32_t excludeId) {
  byte direction;
  PathfindingNode* currentNode;
  int32_t newX;
  PathfindingNode* newNode;
  int32_t objectIdAtPosition;
  int32_t newY;
  int32_t hashedPositionKey;
  PathfindingNode** bucketStart;
  int32_t hashBucketIndex;
  PathfindingDirection* directionEntry;
  int32_t limitPathCost;
  int16_t posXShort;
  int16_t pathCostShort;
  PathfindingNode* existingNode;

  (void)unused;

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
  bucketStart = this->startOfArray;
  for (objectIdAtPosition = 0x100; objectIdAtPosition != 0; objectIdAtPosition = objectIdAtPosition + -1) {
    *bucketStart = nullptr;
    bucketStart = bucketStart + 1;
  }
  this->currentPathCost = 0;
  this->currentDirection = -1;
  if (0 < maxSteps) {
    do {
      directionEntry = PathfindingDirectionLookup;
      do {
        PathfindingLatestDirection = directionEntry;
        if (((2 <= startX) && (2 <= startY)) && (directionEntry->directionIndex != this->currentDirection)) {
          newX = PathfindingLatestDirection->direction1 + startX;
          newY = startY + directionEntry->direction2;
          if (this->gridHandler->PaddedGridMap_Collision[newY][newX] != -1) {
            objectIdAtPosition = this->currentPathCost;
            direction = *(byte*)&directionEntry->directionIndex;
            currentNode = this->currentlyProcessedNode;
            hashedPositionKey = (newY * 0x10000) + newX;
            hashBucketIndex = ((newY & 0xf) * 0x10) + (newX & 0xf);
            if (this->currentBestNode == nullptr) {
              limitPathCost = 0;
            }
            else {
              limitPathCost = this->currentBestNode->pathCostToThisNode + -10;
            }
            for (existingNode = this->startOfArray[hashBucketIndex]; (existingNode != nullptr && (limitPathCost < existingNode->pathCostToThisNode)); existingNode = existingNode->nextNodeInHashBucket) {
              if (existingNode->hashedPositionKey == hashedPositionKey) {
                goto label_next_direction3;
              }
            }
            newNode = this->AllocatePathNode();
            posXShort = (int16_t)newX;
            newNode->linkToParentNode = currentNode;
            pathCostShort = (int16_t)objectIdAtPosition;
            newNode->usedForPos1 = posXShort;
            newNode->usedForPos2 = (int16_t)newY;
            newNode->hashedPositionKey = hashedPositionKey;
            newNode->pathCostToThisNode = pathCostShort;
            newNode->directionFromParent = direction;
            newNode->nextNodeInHashBucket = this->startOfArray[hashBucketIndex];
            this->startOfArray[hashBucketIndex] = newNode;
            this->currentBestNode = newNode;
            if (this->headCircularPathList != nullptr) {
              this->headCircularPathList = newNode;
              newNode->nextInOpenList = newNode;
              newNode->previousInOpenList = newNode;
            }
            else {
              newNode->nextInOpenList = this->headCircularPathList;
              newNode->previousInOpenList = this->headCircularPathList->previousInOpenList;
              this->headCircularPathList->previousInOpenList->nextInOpenList = newNode;
              this->headCircularPathList->previousInOpenList = newNode;
            }
          }
        }
      label_next_direction3:
        directionEntry = directionEntry + 1;
      } while (directionEntry < 8 + PathfindingDirectionLookup);
      currentNode = this->headCircularPathList;
      if ((currentNode == nullptr) || (newNode = currentNode->nextInOpenList, this->headCircularPathList = newNode, currentNode == newNode)) {
        this->headCircularPathList = nullptr;
      }
      else {
        currentNode->nextInOpenList->previousInOpenList = currentNode->previousInOpenList;
        currentNode->previousInOpenList->nextInOpenList = currentNode->nextInOpenList;
      }
      this->currentlyProcessedNode = currentNode;
      if (currentNode == nullptr) {
        return -1;
      }
      startX = (int32_t)currentNode->usedForPos1;
      startY = (int32_t)currentNode->usedForPos2;
      this->currentPathCost = currentNode->pathCostToThisNode + 1;
      this->currentDirection = (currentNode->directionFromParent - 4) & 7;
      objectIdAtPosition = this->gridHandler->PaddedGridMap_Collision[startY][startX];
      if ((0 <= objectIdAtPosition) && (objectIdAtPosition != excludeId)) {
        return objectIdAtPosition;
      }
    } while (this->currentPathCost < maxSteps);
  }
  return -1;
}
