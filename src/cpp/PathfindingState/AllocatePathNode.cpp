#include "HazardClasses/PathfindingState.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/PathfindingNode.hpp"
#include "HazardStructs/PathfindingNodesBlock.hpp"

PathfindingNode* __fastcall PathfindingState::AllocatePathNode() {

  PathfindingNodesBlock* recycledBlock;
  int32_t index;
  PathfindingNodesBlock* newBlock;

  if (2048 <= this->countNodesUsed) {
    if (WrapperRelated != nullptr) {
      this->nodeAllocation_1->next = WrapperRelated;
      WrapperRelated = WrapperRelated->next;
    }
    else {
      newBlock = new PathfindingNodesBlock;
      this->nodeAllocation_1->next = newBlock;
    }
    recycledBlock = this->nodeAllocation_1->next;
    this->nodeAllocation_1 = recycledBlock;
    recycledBlock->next = nullptr;
    this->countNodesUsed = 0;
  }
  index = this->countNodesUsed;
  PathfindingNode* out = (this->nodeAllocation_1->listEyeRelated + index);
  this->countNodesUsed++;
  return out;
}
