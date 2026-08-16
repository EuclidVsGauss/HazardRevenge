#include "HazardClasses/PathfindingState.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/PathfindingNodesBlock.hpp"

void __fastcall PathfindingState::ReturnMemoryPool() {
  this->nodeAllocation_1->next = WrapperRelated;
  WrapperRelated = this->nodeAllocation_2;
}
