#include <stdio.h>
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowDialogue.hpp"
#include "HazardClasses/GameWindowSave.hpp"
#include "HazardExterns/GameWindowSave.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/GameState.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

GameWindowSave::GameWindowSave(GameWindowDialogue* parentWindow, char* saveDescription, char* sceneName, int32_t savePointCoordX, int32_t savePointCoordY) {
  GameState* saveBuffer;
  FILE* saveFile;
  CoreActClass* actObject;
  int32_t loopIndex;
  GameState* gameState;

  saveFile = fopen(s_hazard_sav, s_rb);
  if (saveFile == nullptr) {
    saveBuffer = this->gameStateAddr;
    do {
      gameState = saveBuffer;
      memset(gameState, 0, 316176);
      loopIndex = 7;
      gameState = saveBuffer;
      do {
        sprintf(gameState->description, s_EMPTY);
        gameState = gameState + 1;
        loopIndex = loopIndex + -1;
      } while (loopIndex != 0);
      saveFile = fopen(s_hazard_sav, s_wb);
      fwrite(saveBuffer, 1, 316176, saveFile);
      fclose(saveFile);
      saveFile = fopen(s_hazard_sav, s_rb);
    } while (saveFile == nullptr);
  }
  fread(this->gameStateAddr, 1, 0x4d310, saveFile);
  fclose(saveFile);
  this->gameWindow4 = parentWindow;

  actObject = new CoreActClass(s_win9_act);
  this->actWin9 = actObject;
  loopIndex = actObject->GetActionIndexByName(s_frame);
  this->frame = loopIndex;
  loopIndex = this->actWin9->GetActionIndexByName(s_button);
  this->button = loopIndex;
  loopIndex = this->actWin9->GetActionIndexByName(s_str0);
  this->str0 = loopIndex;
  loopIndex = this->actWin9->GetActionIndexByName(s_str1);
  this->str1 = loopIndex;
  loopIndex = this->actWin9->GetActionIndexByName(s_str2);
  this->str2 = loopIndex;
  loopIndex = this->actWin9->GetActionIndexByName(s_str3);
  this->str3 = loopIndex;
  loopIndex = this->actWin9->GetActionIndexByName(s_str4);
  this->str4 = loopIndex;
  loopIndex = this->actWin9->GetActionIndexByName(s_str5);
  this->str5 = loopIndex;
  loopIndex = this->actWin9->GetActionIndexByName(s_str6);
  this->str6 = loopIndex;
  loopIndex = this->actWin9->GetActionIndexByName(s_stra);
  this->stra = loopIndex;
  loopIndex = this->actWin9->GetActionIndexByName(s_strb);
  this->strb = loopIndex;
  loopIndex = this->actWin9->GetActionIndexByName(s_strc);
  this->strc = loopIndex;
  loopIndex = this->actWin9->GetActionIndexByName(s_strd);
  this->strd = loopIndex;
  loopIndex = this->actWin9->GetActionIndexByName(s_stre);
  this->stre = loopIndex;
  loopIndex = this->actWin9->GetActionIndexByName(s_strf);
  this->strf = loopIndex;
  loopIndex = this->actWin9->GetActionIndexByName(s_strg);
  this->strg = loopIndex;

  this->savePointCoordX = savePointCoordX;
  this->savePointCoordY = savePointCoordY;
  this->fillZero = nullptr;

  int32_t len = strlen(saveDescription) + 1;
  memcpy(this->saveDescription, saveDescription, len);
  len = strlen(sceneName) + 1;
  memcpy(this->saveSceneName, sceneName, len);

  this->selectedSaveSlot = -1;
}
