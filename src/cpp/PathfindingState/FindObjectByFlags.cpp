#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/PathfindingState.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ObjectWrapper.hpp"
#include "HazardStructs/PathfindingDirection.hpp"
#include "HazardStructs/PathfindingNode.hpp"
#include "HazardStructs/PathfindingNodesBlock.hpp"

int32_t PathfindingState::FindObjectByFlags(int32_t posX, int32_t posY, int32_t maxSearchDepth, uint32_t searchFlags) {
  byte directionIndex;
  PathfindingNode* currentNode;
  int32_t nextPosX;
  PathfindingNode* hashEntry;
  int32_t collisionIndex;
  int32_t nextPosY;
  int32_t hashedPosition;
  PathfindingNode** hashTable;
  int32_t hashBucketIndex;
  PathfindingDirection* directionEntry;
  int32_t minPathCost;
  int16_t posXShort;
  int16_t pathCostShort;

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
  hashTable = this->startOfArray;
  for (collisionIndex = 0x100; collisionIndex != 0; collisionIndex = collisionIndex + -1) {
    *hashTable = nullptr;
    hashTable = hashTable + 1;
  }
  this->currentPathCost = 0;
  this->currentDirection = -1;
  if (0 < maxSearchDepth) {
    do {
      directionEntry = PathfindingDirectionLookup;
      do {
        PathfindingLatestDirection = directionEntry;
        if (((1 < posX) && (1 < posY)) && (directionEntry->directionIndex != this->currentDirection)) {
          nextPosX = PathfindingLatestDirection->direction1 + posX;
          nextPosY = directionEntry->direction2 + posY;
          if (this->gridHandler->PaddedGridMap_Collision[nextPosY][nextPosX] != -1) {
            collisionIndex = this->currentPathCost;
            directionIndex = directionEntry->directionIndex;
            currentNode = this->currentlyProcessedNode;
            hashedPosition = (nextPosY * 0x10000) + nextPosX;
            hashBucketIndex = ((nextPosY & 0xf) * 0x10) + (nextPosX & 0xf);
            if (this->currentBestNode == nullptr) {
              minPathCost = 0;
            }
            else {
              minPathCost = this->currentBestNode->pathCostToThisNode + -10;
            }
            for (hashEntry = this->startOfArray[hashBucketIndex]; (hashEntry != nullptr && (minPathCost < hashEntry->pathCostToThisNode)); hashEntry = hashEntry->nextNodeInHashBucket) {
              if (hashEntry->hashedPositionKey == hashedPosition) {
                goto label_next_direction2;
              }
            }
            hashEntry = this->AllocatePathNode();
            posXShort = (int16_t)nextPosX;
            hashEntry->linkToParentNode = currentNode;
            pathCostShort = (int16_t)collisionIndex;
            hashEntry->usedForPos1 = posXShort;
            hashEntry->usedForPos2 = (int16_t)nextPosY;
            hashEntry->hashedPositionKey = hashedPosition;
            hashEntry->pathCostToThisNode = pathCostShort;
            hashEntry->directionFromParent = directionIndex;
            hashEntry->nextNodeInHashBucket = this->startOfArray[hashBucketIndex];
            this->startOfArray[hashBucketIndex] = hashEntry;
            this->currentBestNode = hashEntry;
            if (this->headCircularPathList == nullptr) {
              this->headCircularPathList = hashEntry;
              hashEntry->nextInOpenList = hashEntry;
              hashEntry->previousInOpenList = hashEntry;
            }
            else {
              hashEntry->nextInOpenList = this->headCircularPathList;
              hashEntry->previousInOpenList = this->headCircularPathList->previousInOpenList;
              this->headCircularPathList->previousInOpenList->nextInOpenList = hashEntry;
              this->headCircularPathList->previousInOpenList = hashEntry;
            }
          }
        }
      label_next_direction2:
        directionEntry = directionEntry + 1;
      } while (directionEntry < PathfindingDirectionLookup + 8);
      currentNode = this->headCircularPathList;
      if ((currentNode == nullptr) || (hashEntry = currentNode->nextInOpenList, this->headCircularPathList = hashEntry, currentNode == hashEntry)) {
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
      posX = (int32_t)currentNode->usedForPos1;
      posY = (int32_t)currentNode->usedForPos2;
      this->currentPathCost = currentNode->pathCostToThisNode + 1;
      this->currentDirection = (currentNode->directionFromParent - 4) & 7;
      collisionIndex = (int32_t)this->gridHandler->PaddedGridMap_Collision[posY][posX];
      if (-1 < collisionIndex) {
        if (((searchFlags & 3) == 2) && ((ObjectList[collisionIndex].scriptUserFlags & 3) == 1)) {
          return collisionIndex;
        }
        if (((searchFlags & 3) == 1) && ((ObjectList[collisionIndex].scriptUserFlags & 3) == 2)) {
          return collisionIndex;
        }
      }
    } while (this->currentPathCost < maxSearchDepth);
  }
  return -1;
}
