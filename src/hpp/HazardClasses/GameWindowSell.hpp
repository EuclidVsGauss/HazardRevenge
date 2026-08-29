#ifndef HAZARD_GAMEWINDOWSELL_HPP
#define HAZARD_GAMEWINDOWSELL_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardTypedef.hpp"

class CoreActClass;
class GameWindow;
class GameWindowDialogue;
struct InventoryItemStruct;

class GameWindowSell : public GameWindowBase {

public:
  GameWindowSell(GameWindowDialogue*, int32_t, int32_t);
  virtual ~GameWindowSell();
  virtual void primarySwitchSingleParam(int32_t switchParam, intptr_t param_2, intptr_t param_3) override;

  void PrintSellWindowText(int32_t param_1, int32_t param_2, char* param_3, int32_t param_4);

  GameWindowDialogue* param1;
  ImageVectorWithHeader* sprite;
  CoreActClass* actWin7;
  InventoryItemStruct* itemStructs[20];
  char informationText[3][80];
  int32_t discountFactor;
  int32_t frame;
  int32_t button_or_itemIndex;
  int32_t select;
  int32_t str0;
  int32_t str1;
  int32_t str2;
  int32_t str3;
  int32_t str4;
  int32_t str5;
  int32_t str6;
  int32_t title;
  int32_t unusedActionIndex12;
  int32_t unusedActionIndex13;
  int32_t unusedActionIndex14;
  int32_t unusedActionIndex15;
  int32_t unusedActionIndex16;
  int32_t unusedActionIndex17;
  int32_t unusedActionIndex18;
  int32_t unusedActionIndex19;
  int32_t unusedActionIndex20;
  int32_t itemIndex;
  int32_t flag1;

  __forceinline void HandleMouseInput_0x7d0e();
  __forceinline void DrawObject_0x7d3b();
  __forceinline void DrawText_0x7d35(InventoryItemStruct* param_2);
  __forceinline void RebuildSellableItems_0x7d2f();
};

#endif
