#ifndef HAZARD_GAMEWINDOWBUY_HPP
#define HAZARD_GAMEWINDOWBUY_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardEnums/StoreType.hpp"
#include "HazardStructs/InventoryItemStruct.hpp"
#include "HazardTypedef.hpp"

class CoreActClass;
struct ImageVectorWithHeader;
struct InventoryItemStruct;

class GameWindowBuy : public GameWindowBase {
public:
  GameWindowBuy(GameWindowBase* param_1, int32_t* items, int32_t buyFactor, int32_t storeType);
  virtual ~GameWindowBuy();
  virtual void primarySwitchSingleParam(int32_t switchParam, intptr_t param_2, intptr_t param_3) override;

  void Win6Extended(int32_t, InventoryItemStruct*);
  void PrintBuyText(int32_t, int32_t, char*, int32_t);

  GameWindowBase* dialogueWindow;
  CoreActClass* actWin6;
  ImageVectorWithHeader* buttonHighlightSprite;
  int32_t buyFactor;
  int32_t frame;
  int32_t button;
  int32_t select;
  int32_t face;
  int32_t outline;
  int32_t str0;
  int32_t str1;
  int32_t str2;
  int32_t str3;
  int32_t str4;
  int32_t str5;
  int32_t str6;
  int32_t title;
  int32_t unusedActCommands[7];
  int32_t inventoryCounter;
  StoreTypeEnum storeType;
  char currentItemText[3][80];
  InventoryItemStruct twentyInventoryItems[20];

private:
  __forceinline void DrawClickableObjects_0x7d0e();
  __forceinline void DrawText_0x7d35(InventoryItemStruct*);
  __forceinline void DrawPortraitsEtc_0x7d3b();

  __forceinline void Case_0x7d0e();
  __forceinline void Case_0x7d35(InventoryItemStruct* item);
  __forceinline void Case_0x7d3b();
};

#endif
