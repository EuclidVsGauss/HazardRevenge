#ifndef HAZARD_GAMEWINDOWSPELLCAST_HPP
#define HAZARD_GAMEWINDOWSPELLCAST_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardTypedef.hpp"

struct ActiveCharacter;
struct InventoryItemSpell;

class GameWindowSpellcast : public GameWindowBase {

public:
  GameWindowSpellcast(GameWindowBase* sceneClassUserIdentifier, InventoryItemSpell* param_2);
  virtual ~GameWindowSpellcast();
  virtual void primarySwitchSingleParam(int32_t switchParam, intptr_t param_1, intptr_t param_2) override;

  void NestedHeapAnimationBaseClass(GameWindowBase*);
  void __fastcall CreateSpellAnimationObject();

  GameWindowBase* sceneClassUser;
  ActiveCharacter* characterInventory;
  InventoryItemSpell* spellItem;
  int32_t init0_1;
  int32_t init0_2;
  int32_t isActiveFlag;
  int32_t coord1;
  int32_t coord2;
  int32_t incrementIndex;
  int32_t loopMax_spellRange;
  uint32_t orientationRelated;
  char spellAnimationAct[32];
};

#endif
