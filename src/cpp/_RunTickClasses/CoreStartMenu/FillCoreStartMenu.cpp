#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/CoreStartMenu.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardExterns/CoreStartMenu.hpp"
#include "HazardGlobals.hpp"

CoreStartMenu::CoreStartMenu() {
  int32_t* frameBase = &this->mainmenuFrame;
  for (int32_t i = 0; i < 3; i++) {
    frameBase[i] = -1;
  }

  this->windowPtr = new GameWindow(0, 0, 640, 480);

  this->mainmenuAct = new CoreActClass(s_mainmenu_act);
  this->cursorAct = new CoreActClass(s_cursor_act);

  this->mainmenuFrame = this->mainmenuAct->GetActionIndexByName(s_frame);
  this->mainmenuStringIndex = this->mainmenuAct->GetActionIndexByName(s_string);
  this->cursorNormal = this->cursorAct->GetActionIndexByName(s_normal);

  this->menuSnd_psblyLPDIRECTSOUNDBUF = RunMenuSound(s_menu_snd, 11025);

  this->timeResolutionRelated = 0;
  this->mouseInput = 0;
  this->selectedMainMenuOption = 0;
}
