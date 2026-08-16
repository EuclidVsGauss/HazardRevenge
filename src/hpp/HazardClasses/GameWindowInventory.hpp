#ifndef HAZARD_GAMEWINDOWINVENTORY_HPP
#define HAZARD_GAMEWINDOWINVENTORY_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardEnums/WindowToggle.hpp"
#include "HazardStructs/InventoryItemStruct.hpp"
#include "HazardTypedef.hpp"

class CoreActClass;
struct InventoryItemStruct;

class GameWindowInventory : public GameWindowBase {

public:
  GameWindowInventory();
  virtual ~GameWindowInventory();
  virtual void primarySwitchSingleParam(int32_t switchParam, intptr_t param_2, intptr_t param_3) override;

  void PresumablyDisplayMultiLineText(int32_t param_1, int32_t param_2, char* param_3, int32_t param_4);

  CoreActClass* win3actPointer;
  int32_t actFrame;
  int32_t actNumber;
  int32_t str0;
  int32_t str1;
  int32_t str2;
  int32_t str3;
  int32_t str4;
  int32_t str5;
  int32_t str6;
  int32_t stra;
  int32_t strb;
  int32_t strc;
  int32_t strd;
  int32_t stre;
  int32_t strf;
  int32_t strg;
  int32_t actUndefined[4];
  WindowToggleEnum hideOpenCloseFlag;
  char textLine1[80];
  char textLine2[80];
  char textLine3[80];
  int32_t staticXBoundary;
  int32_t dynamicYBoundary;
  int32_t cursorWidthWhileHolding;
  int32_t cursorHeightWhileHolding;
  InventoryItemStruct itemHeldInCursor;

  __forceinline void Case_0x7d11(intptr_t param_2);
  __forceinline void Case_0x7d3b();
  __forceinline void Case_0x7d3c();
  __forceinline void Case_0x7d16();
  __forceinline void Case_0x7d20();
  __forceinline void Case_0x7d0c();
  __forceinline void Case_0x7d0e(intptr_t param_2, intptr_t param_3);
  __forceinline void Case_0x7d2e(InventoryItemStruct* param2AsItem);
  __forceinline void Case_0x7d35(intptr_t param_2);
};

#endif
