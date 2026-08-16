#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/PathfindingState.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ObjectWrapper.hpp"
#include "HazardStructs/PathfindingCollisionOffset.hpp"
#include "HazardStructs/PathfindingDirection.hpp"
#include "HazardStructs/PathfindingNode.hpp"
#include "HazardStructs/PathfindingNodesBlock.hpp"

PathfindingNode* PathfindingState::VisionTargetSearch(int32_t startPos1, int32_t startPos2, int32_t scaledEyeValue, uint32_t userFlag) {
  byte invalidDirectionModFlag;
  PathfindingNode* bestCandidateNode;
  PathfindingNode* currentNodeInBucket;
  PathfindingCollisionOffset* currentSubEntry;
  int32_t collisionCheckValue;
  PathfindingNode* newlyAllocatedNode;
  int32_t subEntryIndex;
  uint32_t targetCoord1;
  uint32_t targetCoord2;
  PathfindingNode** hashBucketPointer;
  int32_t hashIndex;
  PathfindingDirection* currentEyeArray;
  int32_t costThreshold;
  int16_t defaultPathCost;

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
  hashBucketPointer = this->startOfArray;
  for (subEntryIndex = 0x100; subEntryIndex != 0; subEntryIndex = subEntryIndex + -1) {
    *hashBucketPointer = nullptr;
    hashBucketPointer = hashBucketPointer + 1;
  }
  this->currentPathCost = 0;
  this->currentDirection = -1;
  if (0 < scaledEyeValue) {
    do {
      currentEyeArray = PathfindingDirectionLookup;
      do {
        PathfindingLatestDirection = currentEyeArray;
        if (currentEyeArray->directionIndex != this->currentDirection) {
          subEntryIndex = currentEyeArray->collisionCheckCount + -1;
          if (-1 < subEntryIndex) {

            currentSubEntry = ((PathfindingCollisionOffset*)(&currentEyeArray->directionIndex)) + currentEyeArray->collisionCheckCount;
            do {
              if (this->gridHandler->PaddedGridMap_Collision[currentSubEntry->offsetY + startPos2][currentSubEntry->offsetX + startPos1] == -1) {
                if (-1 < subEntryIndex) {
                  goto label_next_direction4;
                }
                break;
              }
              subEntryIndex = subEntryIndex + -1;
              currentSubEntry = currentSubEntry - 1;
            } while (-1 < subEntryIndex);
          }
          collisionCheckValue = this->currentPathCost;
          invalidDirectionModFlag = *(byte*)&currentEyeArray->directionIndex;
          bestCandidateNode = this->currentlyProcessedNode;
          targetCoord2 = currentEyeArray->direction2 + startPos2;
          targetCoord1 = startPos1 + currentEyeArray->direction1;
          hashIndex = ((targetCoord2 & 0xf) * 0x10) + (targetCoord1 & 0xf);
          collisionCheckValue = (targetCoord2 * 0x10000) + targetCoord1;
          if (this->currentBestNode == nullptr) {
            costThreshold = 0;
          }
          else {
            costThreshold = this->currentBestNode->pathCostToThisNode + -10;
          }
          for (currentNodeInBucket = this->startOfArray[hashIndex]; (currentNodeInBucket != nullptr && (costThreshold < currentNodeInBucket->pathCostToThisNode)); currentNodeInBucket = currentNodeInBucket->nextNodeInHashBucket) {
            if (currentNodeInBucket->hashedPositionKey == collisionCheckValue) {
              goto label_next_direction4;
            }
          }
          newlyAllocatedNode = this->AllocatePathNode();
          newlyAllocatedNode->linkToParentNode = bestCandidateNode;
          defaultPathCost = (int16_t)collisionCheckValue;
          newlyAllocatedNode->hashedPositionKey = collisionCheckValue;
          newlyAllocatedNode->usedForPos1 = (int16_t)targetCoord1;
          newlyAllocatedNode->usedForPos2 = (int16_t)targetCoord2;
          newlyAllocatedNode->pathCostToThisNode = defaultPathCost;
          newlyAllocatedNode->directionFromParent = invalidDirectionModFlag;
          newlyAllocatedNode->nextNodeInHashBucket = this->startOfArray[hashIndex];
          this->startOfArray[hashIndex] = newlyAllocatedNode;
          this->currentBestNode = newlyAllocatedNode;
          if (this->headCircularPathList == nullptr) {
            this->headCircularPathList = newlyAllocatedNode;
            newlyAllocatedNode->nextInOpenList = newlyAllocatedNode;
            newlyAllocatedNode->previousInOpenList = newlyAllocatedNode;
          }
          else {
            newlyAllocatedNode->nextInOpenList = this->headCircularPathList;
            newlyAllocatedNode->previousInOpenList = this->headCircularPathList->previousInOpenList;
            this->headCircularPathList->previousInOpenList->nextInOpenList = newlyAllocatedNode;
            this->headCircularPathList->previousInOpenList = newlyAllocatedNode;
          }
        }
      label_next_direction4:
        currentEyeArray = currentEyeArray + 1;
      } while (currentEyeArray < PathfindingDirectionLookup + 8);
      bestCandidateNode = this->headCircularPathList;
      if ((bestCandidateNode == nullptr) || (currentNodeInBucket = bestCandidateNode->nextInOpenList, this->headCircularPathList = currentNodeInBucket, bestCandidateNode == currentNodeInBucket)) {
        this->headCircularPathList = nullptr;
      }
      else {
        bestCandidateNode->nextInOpenList->previousInOpenList = bestCandidateNode->previousInOpenList;
        bestCandidateNode->previousInOpenList->nextInOpenList = bestCandidateNode->nextInOpenList;
      }
      this->currentlyProcessedNode = bestCandidateNode;
      if (bestCandidateNode == nullptr) {
        return nullptr;
      }
      startPos1 = (int32_t)bestCandidateNode->usedForPos1;
      startPos2 = (int32_t)bestCandidateNode->usedForPos2;
      this->currentPathCost = bestCandidateNode->pathCostToThisNode + 1;
      this->currentDirection = (bestCandidateNode->directionFromParent - 4) & 7;
      if (-1 < this->gridHandler->PaddedGridMap_Collision[startPos2][startPos1]) {
        if (((userFlag & 3) == 2) && ((ObjectList[8].scriptUserFlags & 3) == 1)) {
          return bestCandidateNode;
        }
        if (((userFlag & 3) == 1) && ((ObjectList[8].scriptUserFlags & 3) == 2)) {
          return bestCandidateNode;
        }
      }
    } while (this->currentPathCost < scaledEyeValue);
  }
  return this->currentlyProcessedNode;
}
