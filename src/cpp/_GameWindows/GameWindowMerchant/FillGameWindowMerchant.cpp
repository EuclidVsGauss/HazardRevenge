#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowDialogue.hpp"
#include "HazardClasses/GameWindowMerchant.hpp"
#include "HazardExterns/GameWindowMerchant.hpp"
#include "HazardGlobals.hpp"

GameWindowMerchant::GameWindowMerchant(GameWindowDialogue* param_1) {
  int32_t loopIndex;
  int32_t* framePtr;

  this->dialogueWindow = param_1;
  this->actWin5 = new CoreActClass(s_win5_act);
  framePtr = &this->frame;
  for (loopIndex = 20; loopIndex != 0; loopIndex = loopIndex + -1) {
    *framePtr = -1;
    framePtr = framePtr + 1;
  }
  this->frame = this->actWin5->GetActionIndexByName(s_frame);
  this->button = this->actWin5->GetActionIndexByName(s_button);
  this->selectedButtonIndex = -1;
}
