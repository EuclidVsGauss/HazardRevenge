#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowDialogue.hpp"
#include "HazardClasses/GameWindowSell.hpp"
#include "HazardExterns/GameWindowSell.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

GameWindowSell::GameWindowSell(GameWindowDialogue* parentWindow, int32_t sellOption, int32_t sellParam) {
  CoreActClass* actObject;
  int32_t loopIndex;
  int32_t* framePtr;

  framePtr = &this->frame;
  for (loopIndex = 20; loopIndex != 0; loopIndex = loopIndex + -1) {
    *framePtr = -1;
    framePtr = framePtr + 1;
  }
  this->param1 = parentWindow;
  actObject = new CoreActClass(s_win7_act);
  this->param3 = sellParam;
  this->actWin7 = actObject;
  this->frame = actObject->GetActionIndexByName(s_frame);
  this->button_or_itemIndex = this->actWin7->GetActionIndexByName(s_button);
  this->select = this->actWin7->GetActionIndexByName(s_select);
  this->str0 = this->actWin7->GetActionIndexByName(s_str0);
  this->str1 = this->actWin7->GetActionIndexByName(s_str1);
  this->str2 = this->actWin7->GetActionIndexByName(s_str2);
  this->str3 = this->actWin7->GetActionIndexByName(s_str3);
  this->str4 = this->actWin7->GetActionIndexByName(s_str4);
  this->str5 = this->actWin7->GetActionIndexByName(s_str5);
  this->str6 = this->actWin7->GetActionIndexByName(s_str6);
  this->title = this->actWin7->GetActionIndexByName(s_title);
  this->itemIndex = -1;
  this->flag1 = sellOption;
  this->sprite = nullptr;
  this->loadTrackGoldStringInterpolation[0] = '\0';
  this->char2[0] = '\0';
  this->char3[0] = '\0';

  this->primarySwitchSingleParam(0x7d2f, 0, 0);
}
