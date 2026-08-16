#include <memory.h>
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowInventory.hpp"
#include "HazardExterns/GameWindowInventory.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/InventoryItemStruct.hpp"

GameWindowInventory::GameWindowInventory() {

  this->win3actPointer = new CoreActClass(s_win3_act);
  FillMemory(&this->actFrame, 80, 0xff);

  this->actFrame = this->win3actPointer->GetActionIndexByName(s_frame);
  this->actNumber = this->win3actPointer->GetActionIndexByName(s_number);
  this->str0 = this->win3actPointer->GetActionIndexByName(s_str0);
  this->str1 = this->win3actPointer->GetActionIndexByName(s_str1);
  this->str2 = this->win3actPointer->GetActionIndexByName(s_str2);
  this->str3 = this->win3actPointer->GetActionIndexByName(s_str3);
  this->str4 = this->win3actPointer->GetActionIndexByName(s_str4);
  this->str5 = this->win3actPointer->GetActionIndexByName(s_str5);
  this->str6 = this->win3actPointer->GetActionIndexByName(s_str6);
  this->stra = this->win3actPointer->GetActionIndexByName(s_stra);
  this->strb = this->win3actPointer->GetActionIndexByName(s_strb);
  this->strc = this->win3actPointer->GetActionIndexByName(s_strc);
  this->strd = this->win3actPointer->GetActionIndexByName(s_strd);
  this->stre = this->win3actPointer->GetActionIndexByName(s_stre);
  this->strf = this->win3actPointer->GetActionIndexByName(s_strf);
  this->strg = this->win3actPointer->GetActionIndexByName(s_strg);
  this->staticXBoundary = 0;
  this->dynamicYBoundary = 192;
  this->hideOpenCloseFlag = 0;
  this->textLine2[0] = '\0';
  this->textLine1[0] = '\0';
  (this->itemHeldInCursor).quantity = 0;
}
