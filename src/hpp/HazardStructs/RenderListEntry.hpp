#ifndef HAZARD_WIDTHLINKEDLIST_HPP
#define HAZARD_WIDTHLINKEDLIST_HPP
#include "HazardTypedef.hpp"

struct RenderListEntry {
  int16_t rightBound;
  int16_t leftBound;
  int16_t* pixelTable;
  uint16_t layerIndex;
  int16_t padding;
  RenderListEntry* next;
};
typedef struct RenderListEntry RenderListEntry, *PRenderListEntry;

#endif
