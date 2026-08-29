#ifndef HAZARD_HAZARDGAMESTATE_HPP
#define HAZARD_HAZARDGAMESTATE_HPP

#include "CharacterDetails.hpp"
#include "HazardTypedef.hpp"
#include "InventoryItemStruct.hpp"

struct CharacterDetails;
struct InventoryItemStruct;

struct GameState {
  char description[30];
  char sceneLocationName[22];
  int32_t coordX;
  int32_t coordY;
  CharacterDetails characterDetails[10];
  uint32_t goldAmount;
  InventoryItemStruct inventoryItems[32];
  int32_t gameFlags[2048];
};
typedef struct GameState GameState, *PGameState;

#endif
