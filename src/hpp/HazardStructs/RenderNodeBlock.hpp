#ifndef HAZARD_RENDERNODES_HPP
#define HAZARD_RENDERNODES_HPP

#include "HazardStructs/RenderListEntry.hpp"
#include "HazardTypedef.hpp"

struct RenderNodeBlock {
  RenderListEntry entries[65536];
  RenderNodeBlock* nextBlock;
};
typedef struct RenderNodeBlock RenderNodeBlock, *PRenderNodeBlock;

#endif
