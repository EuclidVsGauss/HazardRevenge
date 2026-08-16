#ifndef HAZARD_GAMEWINDOWWEAPON_HPP
#define HAZARD_GAMEWINDOWWEAPON_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardEnums/WindowToggle.hpp"
#include "HazardStructs/InventoryItemStruct.hpp"
#include "HazardTypedef.hpp"

class CoreActClass;
struct InventoryItemStruct;

class GameWindowWeapon : public GameWindowBase {

public:
  GameWindowWeapon();
  virtual ~GameWindowWeapon();
  virtual void primarySwitchSingleParam(int32_t switchParam, intptr_t param_2, intptr_t param_3) override;

  CoreActClass* actWin2;
  InventoryItemStruct latestEquipmentItem;
  int32_t actFrame;
  int32_t actSlot;
  int32_t actUndefined[18];
  WindowToggleEnum hideOpenCloseFlag;
  int32_t staticXBoundary;
  int32_t dynamicYBoundary;
  int32_t cursorWidthWhileHolding;
  int32_t cursorHeightWhileHolding;

  __forceinline void Case_0x7d11(intptr_t param_2);
  __forceinline void Case_0x7d3b();
  __forceinline void Case_0x7d3c();
  __forceinline void Case_0x7d0c();
  __forceinline void Case_0x7d0e(intptr_t param_2);
  __forceinline void Case_0x7d2e(intptr_t param_2, intptr_t param_3);
  __forceinline void Case_0x7d16();
  __forceinline void Case_0x7d20();
};

#endif
