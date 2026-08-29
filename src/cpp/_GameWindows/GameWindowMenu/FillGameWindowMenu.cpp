#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowMenu.hpp"
#include "HazardExterns/GameWindowMenu.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

GameWindowMenu::GameWindowMenu() {
  CoreActClass* menuActObject;
  int32_t frameIndex;
  int32_t* frameArrayPtr;

  menuActObject = new CoreActClass(s_menu_act);
  this->menuAct = menuActObject;
  frameArrayPtr = &this->actFrame;
  for (frameIndex = 20; frameIndex != 0; frameIndex = frameIndex + -1) {
    *frameArrayPtr = -1;
    frameArrayPtr = frameArrayPtr + 1;
  }

  this->actFrame = this->menuAct->GetActionIndexByName(s_frame);
  this->actString = this->menuAct->GetActionIndexByName(s_string);
  this->actFrame2 = this->menuAct->GetActionIndexByName(s_frame2);
  this->actString2 = this->menuAct->GetActionIndexByName(s_string2);
  this->highlightedTextSprite = nullptr;
  this->sliderIsHeld = 0;
  this->showQuitGameMenu = 0;
}
