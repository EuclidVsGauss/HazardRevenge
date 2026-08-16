#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/PathfindingState.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/PathfindingCollisionOffset.hpp"
#include "HazardStructs/PathfindingDirection.hpp"
#include "HazardStructs/PathfindingNode.hpp"
#include "HazardStructs/PathfindingNodesBlock.hpp"

PathfindingNode* PathfindingState::FindPath_AvoidWallsAndUnits() {
  int32_t initialPathCost;
  byte directionInfo;
  PathfindingNode* parentNode;
  PathfindingNodesBlock* newNodeWrapper;
  PathfindingNodesBlock* backupPointer;
  PathfindingNode* hashBucketNode;

  int32_t bucketIndex;

  int32_t minCost;
  uint32_t newCoordY;
  uint32_t newCoordX;
  int32_t packedCoord;
  PathfindingDirection* directionEntry;
  int16_t pathCost;

  initialPathCost = this->currentPathCost;
  int32_t baseCost = initialPathCost + 5;
  do {
    if (baseCost <= initialPathCost) {
      return nullptr;
    }
    directionEntry = PathfindingDirectionLookup;
    do {
      PathfindingLatestDirection = directionEntry;
      if (directionEntry->directionIndex != this->currentDirection) {

        int32_t subIndex = directionEntry->collisionCheckCount - 1;
        if (-1 < subIndex) {
          PathfindingCollisionOffset* pEntry = &directionEntry->collisionOffsets[subIndex];
          do {
            if (this->gridHandler->PaddedGridMap_Collision
                    [pEntry->offsetY + this->currentCoord2]
                    [pEntry->offsetX + this->currentCoord1] != -2) {
              if (-1 < subIndex) {
                goto label_skip_blocked_direction2;
              }
              break;
            }
            subIndex--;
            pEntry--;
          } while (-1 < subIndex);
        }
        initialPathCost = this->currentPathCost;
        directionInfo = *(byte*)&directionEntry->directionIndex;
        newCoordY = directionEntry->direction2 + this->currentCoord2;
        newCoordX = this->currentCoord1 + directionEntry->direction1;
        parentNode = this->currentlyProcessedNode;
        bucketIndex = ((newCoordY & 0xf) * 0x10) + (newCoordX & 0xf);
        packedCoord = (newCoordY * 0x10000) + newCoordX;
        if (this->currentBestNode == nullptr) {
          minCost = 0;
        }
        else {
          minCost = this->currentBestNode->pathCostToThisNode + -10;
        }
        for (hashBucketNode = this->startOfArray[bucketIndex]; (hashBucketNode != nullptr && (minCost < hashBucketNode->pathCostToThisNode)); hashBucketNode = hashBucketNode->nextNodeInHashBucket) {
          if (hashBucketNode->hashedPositionKey == packedCoord) {
            packedCoord = 0;
            goto label_skip_visited_node1;
          }
        }
        if (0x7ff < this->countNodesUsed) {
          if (WrapperRelated == nullptr) {
            backupPointer = new PathfindingNodesBlock;
            this->nodeAllocation_1->next = backupPointer;
          }
          else {
            this->nodeAllocation_1->next = WrapperRelated;
            WrapperRelated = WrapperRelated->next;
          }
          newNodeWrapper = this->nodeAllocation_1->next;
          this->nodeAllocation_1 = newNodeWrapper;
          newNodeWrapper->next = nullptr;
          this->countNodesUsed = 0;
        }
        hashBucketNode = this->nodeAllocation_1->listEyeRelated + this->countNodesUsed;
        this->countNodesUsed = this->countNodesUsed + 1;
        hashBucketNode->linkToParentNode = parentNode;
        pathCost = (int16_t)initialPathCost;
        hashBucketNode->pathCostToThisNode = pathCost;
        hashBucketNode->usedForPos1 = (int16_t)newCoordX;
        hashBucketNode->usedForPos2 = (int16_t)newCoordY;
        hashBucketNode->hashedPositionKey = packedCoord;
        hashBucketNode->directionFromParent = directionInfo;
        hashBucketNode->nextNodeInHashBucket = this->startOfArray[bucketIndex];
        this->startOfArray[bucketIndex] = hashBucketNode;
        this->currentBestNode = hashBucketNode;
        if (this->headCircularPathList == nullptr) {
          this->headCircularPathList = hashBucketNode;
          hashBucketNode->nextInOpenList = hashBucketNode;
          hashBucketNode->previousInOpenList = hashBucketNode;
        }
        else {
          hashBucketNode->nextInOpenList = this->headCircularPathList;
          hashBucketNode->previousInOpenList = this->headCircularPathList->previousInOpenList;
          this->headCircularPathList->previousInOpenList->nextInOpenList = hashBucketNode;
          this->headCircularPathList->previousInOpenList = hashBucketNode;
        }
      label_skip_visited_node1:
        if (packedCoord == this->targetPackedCoordinate) {
          return this->currentBestNode;
        }
      }
    label_skip_blocked_direction2:
      directionEntry = directionEntry + 1;
    } while ((intptr_t)directionEntry < 320 + (intptr_t)PathfindingDirectionLookup);
    parentNode = this->headCircularPathList;
    if ((parentNode == nullptr) || (hashBucketNode = parentNode->nextInOpenList, this->headCircularPathList = hashBucketNode, parentNode == hashBucketNode)) {
      this->headCircularPathList = nullptr;
    }
    else {
      parentNode->nextInOpenList->previousInOpenList = parentNode->previousInOpenList;
      parentNode->previousInOpenList->nextInOpenList = parentNode->nextInOpenList;
    }
    this->currentlyProcessedNode = parentNode;
    if (parentNode == nullptr) {
      return nullptr;
    }
    this->currentCoord1 = (int32_t)parentNode->usedForPos1;
    this->currentCoord2 = (int32_t)parentNode->usedForPos2;
    initialPathCost = parentNode->pathCostToThisNode + 1;
    this->currentPathCost = initialPathCost;
    this->currentDirection = (parentNode->directionFromParent - 4) & 7;
  } while (true);
}
