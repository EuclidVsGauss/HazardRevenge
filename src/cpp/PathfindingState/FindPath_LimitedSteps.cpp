#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/PathfindingState.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/PathfindingCollisionOffset.hpp"
#include "HazardStructs/PathfindingDirection.hpp"
#include "HazardStructs/PathfindingNode.hpp"
#include "HazardStructs/PathfindingNodesBlock.hpp"

PathfindingNode* PathfindingState::AStarPathfinding_NavigateAroundObjects(int32_t coord1, int32_t coord2, int32_t modulatedRng) {
  byte direction;
  PathfindingNode* parentNodeReturn;
  PathfindingNodesBlock* newNodeBlock;
  PathfindingNode* parentNode;
  int32_t arrayIndex;
  int32_t costThreshold;
  PathfindingNode** ptr;
  PathfindingDirection* currentDirectionEntry;
  int16_t pathCost;
  PathfindingCollisionOffset* pEntry;

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
  for (arrayIndex = 0x100; arrayIndex != 0; arrayIndex = arrayIndex + -1) {
    *ptr = nullptr;
    ptr = ptr + 1;
  }
  this->currentPathCost = 0;
  this->currentDirection = -1;
  if (0 < modulatedRng) {
    do {
      currentDirectionEntry = PathfindingDirectionLookup;
      do {
        PathfindingLatestDirection = currentDirectionEntry;
        if (currentDirectionEntry->directionIndex != this->currentDirection) {
          arrayIndex = currentDirectionEntry->collisionCheckCount + -1;
          if (-1 < arrayIndex) {

            pEntry = &currentDirectionEntry->collisionOffsets[arrayIndex];
            do {

              if (this->gridHandler->PaddedGridMap_Collision[pEntry->offsetY + coord2][pEntry->offsetX + coord1] == -1) {
                if (-1 < arrayIndex) {
                  goto label_next_direction1;
                }
                break;
              }
              arrayIndex = arrayIndex + -1;

              pEntry--;
            } while (-1 < arrayIndex);
          }
          int32_t newPathCost = this->currentPathCost;
          direction = *(byte*)&currentDirectionEntry->directionIndex;
          int32_t nextY = currentDirectionEntry->direction2 + coord2;
          int32_t nextX = currentDirectionEntry->direction1 + coord1;
          parentNodeReturn = this->currentlyProcessedNode;
          int32_t hashBucketIndex = ((nextY & 0xf) * 0x10) + (nextX & 0xf);
          int32_t hashedPosition = (nextY * 0x10000) + nextX;
          if (this->currentBestNode == nullptr) {
            costThreshold = 0;
          }
          else {
            costThreshold = this->currentBestNode->pathCostToThisNode + -10;
          }
          for (parentNode = this->startOfArray[hashBucketIndex]; (parentNode != nullptr && (costThreshold < parentNode->pathCostToThisNode)); parentNode = parentNode->nextNodeInHashBucket) {
            if (parentNode->hashedPositionKey == hashedPosition) {
              goto label_next_direction1;
            }
          }
          if (0x7ff < this->countNodesUsed) {
            if (WrapperRelated == nullptr) {
              newNodeBlock = new PathfindingNodesBlock;
              this->nodeAllocation_1->next = newNodeBlock;
            }
            else {
              this->nodeAllocation_1->next = WrapperRelated;
              WrapperRelated = WrapperRelated->next;
            }
            newNodeBlock = this->nodeAllocation_1->next;
            this->nodeAllocation_1 = newNodeBlock;
            newNodeBlock->next = nullptr;
            this->countNodesUsed = 0;
          }
          parentNode = this->nodeAllocation_1->listEyeRelated + this->countNodesUsed;
          this->countNodesUsed = this->countNodesUsed + 1;
          parentNode->linkToParentNode = parentNodeReturn;
          parentNode->hashedPositionKey = hashedPosition;
          pathCost = (int16_t)newPathCost;
          parentNode->usedForPos1 = (int16_t)nextX;
          parentNode->usedForPos2 = (int16_t)nextY;
          parentNode->pathCostToThisNode = pathCost;
          parentNode->directionFromParent = direction;
          parentNode->nextNodeInHashBucket = this->startOfArray[hashBucketIndex];
          this->startOfArray[hashBucketIndex] = parentNode;
          this->currentBestNode = parentNode;
          if (this->headCircularPathList == nullptr) {
            this->headCircularPathList = parentNode;
            parentNode->nextInOpenList = parentNode;
            parentNode->previousInOpenList = parentNode;
          }
          else {
            parentNode->nextInOpenList = this->headCircularPathList;
            parentNode->previousInOpenList = this->headCircularPathList->previousInOpenList;
            this->headCircularPathList->previousInOpenList->nextInOpenList = parentNode;
            this->headCircularPathList->previousInOpenList = parentNode;
          }
        }
      label_next_direction1:
        currentDirectionEntry = currentDirectionEntry + 1;

      } while (currentDirectionEntry < PathfindingDirectionLookup + 8);
      parentNodeReturn = this->headCircularPathList;
      if ((parentNodeReturn == nullptr) || (parentNode = parentNodeReturn->nextInOpenList, this->headCircularPathList = parentNode, parentNodeReturn == parentNode)) {
        this->headCircularPathList = nullptr;
      }
      else {
        parentNodeReturn->nextInOpenList->previousInOpenList = parentNodeReturn->previousInOpenList;
        parentNodeReturn->previousInOpenList->nextInOpenList = parentNodeReturn->nextInOpenList;
      }
      this->currentlyProcessedNode = parentNodeReturn;
      if (parentNodeReturn == nullptr) {
        return nullptr;
      }
      coord1 = (int32_t)parentNodeReturn->usedForPos1;
      coord2 = (int32_t)parentNodeReturn->usedForPos2;
      arrayIndex = parentNodeReturn->pathCostToThisNode + 1;
      this->currentPathCost = arrayIndex;
      this->currentDirection = (parentNodeReturn->directionFromParent - 4) & 7;
    } while (arrayIndex < modulatedRng);
  }
  return this->currentlyProcessedNode;
}
