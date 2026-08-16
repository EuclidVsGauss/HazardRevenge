#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/PathfindingState.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/PathfindingCollisionOffset.hpp"
#include "HazardStructs/PathfindingDirection.hpp"
#include "HazardStructs/PathfindingNode.hpp"
#include "HazardStructs/PathfindingNodesBlock.hpp"

PathfindingNode* PathfindingState::FindPath_AvoidWallsOnly() {
  int32_t traversalCostOffset;
  byte nextDirectionByte;
  PathfindingNode* currentNodeFromHash;
  PathfindingNode* iterNode;
  PathfindingNode* headNodePtr;
  PathfindingNodesBlock* newNodePtr;
  PathfindingNode* nextNodePtr;
  PathfindingCollisionOffset* subEntryPtr;
  int32_t subEntryIndex;
  int32_t packedCoord;
  int32_t bestPathCostThreshold;
  uint32_t newCoord2;
  uint32_t newCoord1;
  int32_t bucketIndex;
  PathfindingDirection* currentDirectionEntry;
  int16_t currentNodePathCost;
  PathfindingNode* processedNode;

  subEntryIndex = this->currentPathCost;
  traversalCostOffset = subEntryIndex + 5;
  do {
    if (traversalCostOffset <= subEntryIndex) {
      return nullptr;
    }
    currentDirectionEntry = PathfindingDirectionLookup;
    do {
      PathfindingLatestDirection = currentDirectionEntry;
      if (currentDirectionEntry->directionIndex != this->currentDirection) {
        subEntryIndex = currentDirectionEntry->collisionCheckCount + -1;
        if (-1 < subEntryIndex) {
          subEntryPtr = currentDirectionEntry->collisionOffsets + (currentDirectionEntry->collisionCheckCount - 1);
          do {
            if ((this->gridHandler->PaddedGridMap_Collision[subEntryPtr->offsetY + this->currentCoord2][subEntryPtr->offsetX + this->currentCoord1]) == -1) {
              if (-1 < subEntryIndex) {
                goto label_skip_blocked_direction1;
              }
              break;
            }
            subEntryIndex = subEntryIndex + -1;

            subEntryPtr = subEntryPtr - 1;
          } while (-1 < subEntryIndex);
        }
        subEntryIndex = this->currentPathCost;
        nextDirectionByte = *(byte*)&currentDirectionEntry->directionIndex;
        newCoord2 = currentDirectionEntry->direction2 + this->currentCoord2;
        newCoord1 = this->currentCoord1 + currentDirectionEntry->direction1;
        currentNodeFromHash = this->currentlyProcessedNode;
        bucketIndex = ((newCoord2 & 0xf) * 0x10) + (newCoord1 & 0xf);
        packedCoord = (newCoord2 * 0x10000) + newCoord1;
        if (this->currentBestNode == nullptr) {
          bestPathCostThreshold = 0;
        }
        else {
          bestPathCostThreshold = this->currentBestNode->pathCostToThisNode + -10;
        }
        for (iterNode = this->startOfArray[bucketIndex]; (iterNode != nullptr && (bestPathCostThreshold < iterNode->pathCostToThisNode)); iterNode = iterNode->nextNodeInHashBucket) {
          if (iterNode->hashedPositionKey == packedCoord) {
            packedCoord = 0;
            goto label_skip_visited_node2;
          }
        }
        if (0x7ff < this->countNodesUsed) {
          if (WrapperRelated == nullptr) {
            newNodePtr = new PathfindingNodesBlock;
            this->nodeAllocation_1->next = newNodePtr;
          }
          else {
            this->nodeAllocation_1->next = WrapperRelated;
            WrapperRelated = WrapperRelated->next;
          }
          newNodePtr = this->nodeAllocation_1->next;
          this->nodeAllocation_1 = newNodePtr;
          newNodePtr->next = nullptr;
          this->countNodesUsed = 0;
        }
        nextNodePtr = (PathfindingNode*)(this->nodeAllocation_1->listEyeRelated + this->countNodesUsed);
        this->countNodesUsed = this->countNodesUsed + 1;
        nextNodePtr->linkToParentNode = currentNodeFromHash;
        currentNodePathCost = (int16_t)subEntryIndex;
        nextNodePtr->pathCostToThisNode = currentNodePathCost;
        nextNodePtr->usedForPos1 = (int16_t)newCoord1;
        nextNodePtr->usedForPos2 = (int16_t)newCoord2;
        nextNodePtr->hashedPositionKey = packedCoord;
        nextNodePtr->directionFromParent = nextDirectionByte;
        nextNodePtr->nextNodeInHashBucket = this->startOfArray[bucketIndex];
        this->startOfArray[bucketIndex] = nextNodePtr;
        this->currentBestNode = nextNodePtr;
        if (this->headCircularPathList == nullptr) {
          this->headCircularPathList = nextNodePtr;
          nextNodePtr->nextInOpenList = nextNodePtr;
          nextNodePtr->previousInOpenList = nextNodePtr;
        }
        else {
          nextNodePtr->nextInOpenList = this->headCircularPathList;
          nextNodePtr->previousInOpenList = this->headCircularPathList->previousInOpenList;
          this->headCircularPathList->previousInOpenList->nextInOpenList = nextNodePtr;
          this->headCircularPathList->previousInOpenList = nextNodePtr;
        }
      label_skip_visited_node2:
        if (packedCoord == this->targetPackedCoordinate) {
          return this->currentBestNode;
        }
      }
    label_skip_blocked_direction1:
      currentDirectionEntry = currentDirectionEntry + 1;
    } while (currentDirectionEntry < PathfindingDirectionLookup + 8);
    processedNode = this->headCircularPathList;
    if ((processedNode == nullptr) || (headNodePtr = processedNode->nextInOpenList, this->headCircularPathList = headNodePtr, processedNode == headNodePtr)) {
      this->headCircularPathList = nullptr;
    }
    else {
      processedNode->nextInOpenList->previousInOpenList = processedNode->previousInOpenList;
      processedNode->previousInOpenList->nextInOpenList = processedNode->nextInOpenList;
    }
    this->currentlyProcessedNode = processedNode;
    if (processedNode == nullptr) {
      return nullptr;
    }
    this->currentCoord1 = (int32_t)processedNode->usedForPos1;
    this->currentCoord2 = (int32_t)processedNode->usedForPos2;
    subEntryIndex = processedNode->pathCostToThisNode + 1;
    this->currentPathCost = subEntryIndex;
    this->currentDirection = (processedNode->directionFromParent - 4) & 7;
  } while (true);
}
