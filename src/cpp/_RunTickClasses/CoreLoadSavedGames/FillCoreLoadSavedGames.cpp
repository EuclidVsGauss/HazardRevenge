#include <stdio.h>
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/CoreLoadSavedGames.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardExterns/CoreLoadSavedGames.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/GameState.hpp"

CoreLoadSavedGames::CoreLoadSavedGames() {
  FILE* saveFileObject;
  int32_t loopCounter;
  int32_t* frameEndPtr;

  saveFileObject = fopen(s_hazard_sav, s_rb);
  if (saveFileObject == nullptr) {
    GameState* saveBuffer = &this->SaveSlot1;

    do {
      GameState* dest = saveBuffer;
      int32_t count = 7;

      memset(saveBuffer, 0, 7 * sizeof(GameState));

      do {
        sprintf(dest->description, s_EMPTY);
        --count;
        ++dest;
      } while (count != 0);
      saveFileObject = fopen(s_hazard_sav, s_wb);
      fwrite(saveBuffer, 1, 316176, saveFileObject);
      fclose(saveFileObject);
      saveFileObject = fopen(s_hazard_sav, s_rb);
    } while (saveFileObject == nullptr);
  }
  fread(&this->SaveSlot1, 1, 316176, saveFileObject);
  fclose(saveFileObject);
  this->initiallyMax = 0xffffffff;
  this->windowStruct = new GameWindow(0, 0, 640, 480);
  this->mainMenu_Act = new CoreActClass(s_mainmenu_act);
  this->winB_Act = new CoreActClass(s_winb_act);
  this->cursor_Act = new CoreActClass(s_cursor_act);
  frameEndPtr = &this->frameBegin;
  for (loopCounter = 20; loopCounter != 0; loopCounter = loopCounter + -1) {
    *frameEndPtr = -1;
    frameEndPtr = frameEndPtr + 1;
  }

  this->frameBegin = this->mainMenu_Act->GetActionIndexByName(s_frame);
  this->normal = this->cursor_Act->GetActionIndexByName(s_normal);
  this->str0 = this->winB_Act->GetActionIndexByName(s_str0);
  this->str1 = this->winB_Act->GetActionIndexByName(s_str1);
  this->str2 = this->winB_Act->GetActionIndexByName(s_str2);
  this->str3 = this->winB_Act->GetActionIndexByName(s_str3);
  this->str4 = this->winB_Act->GetActionIndexByName(s_str4);
  this->str5 = this->winB_Act->GetActionIndexByName(s_str5);
  this->str6 = this->winB_Act->GetActionIndexByName(s_str6);
  this->stra = this->winB_Act->GetActionIndexByName(s_stra);
  this->strb = this->winB_Act->GetActionIndexByName(s_strb);
  this->strc = this->winB_Act->GetActionIndexByName(s_strc);
  this->strd = this->winB_Act->GetActionIndexByName(s_strd);
  this->stre = this->winB_Act->GetActionIndexByName(s_stre);
  this->strf = this->winB_Act->GetActionIndexByName(s_strf);
  this->strg = this->winB_Act->GetActionIndexByName(s_strg);
  this->frameEnd = this->winB_Act->GetActionIndexByName(s_frame);
  this->init0_1 = 0;
  this->mouseClick = 0;
  this->init0_3 = 0;
  this->init2 = 2;
}
