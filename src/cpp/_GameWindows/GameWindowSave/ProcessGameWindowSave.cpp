#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowDialogue.hpp"
#include "HazardClasses/GameWindowSave.hpp"
#include "HazardClasses/MusicObjectBase.hpp"
#include "HazardClasses/SfxObject.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/GameState.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

const int32_t SaveWindow_SaveButton_LowerX_336 = 336;
const int32_t SaveWindow_SaveButton_UpperX_387 = 387;
const int32_t SaveWindow_SaveButton_LowerY_343 = 343;
const int32_t SaveWindow_SaveButton_UpperY_355 = 355;

const int32_t SaveWindow_CancelButton_LowerX_397 = 396;
const int32_t SaveWindow_CancelButton_UpperX_446 = 447;
const int32_t SaveWindow_CancelButton_LowerY_344 = 343;
const int32_t SaveWindow_CancelButton_UpperY_354 = 355;

const int32_t SaveWindow_Grid_LowerX_287 = 287;
const int32_t SaveWindow_Grid_UpperX_517 = 517;
const int32_t SaveWindow_Grid_LowerY_143 = 143;
const int32_t SaveWindow_Grid_UpperY_336 = 336;

__forceinline void Case_0x7d0e(GameWindowSave* saveWindow) {

  ImageVectorWithHeader* sprite;
  int32_t randomSoundEffectIndex;

  saveWindow->fillZero = nullptr;
  if ((((SaveWindow_SaveButton_LowerX_336 < CursorXCoord) && (CursorXCoord < SaveWindow_SaveButton_UpperX_387)) && (SaveWindow_SaveButton_LowerY_343 < CursorYCoord)) && (CursorYCoord < SaveWindow_SaveButton_UpperY_355)) {

    sprite = GameWindowBase::__InlineGetSolidSpriteFrameForAction(saveWindow->button, saveWindow->actWin9, 0);
    saveWindow->fillZero = sprite;
  }
  if (!(((CursorXCoord <= SaveWindow_CancelButton_LowerX_397) || (SaveWindow_CancelButton_UpperX_446 <= CursorXCoord)) || (CursorYCoord <= SaveWindow_CancelButton_LowerY_344 || (SaveWindow_CancelButton_UpperY_354 <= CursorYCoord)))) {
    sprite = GameWindowBase::__InlineGetSolidSpriteFrameForAction(saveWindow->button, saveWindow->actWin9, 1);
    saveWindow->fillZero = sprite;
  }

  if ((MouseButtonClick & 17) == 1) {
    if (((SaveWindow_SaveButton_LowerX_336 < CursorXCoord) && (CursorXCoord < SaveWindow_SaveButton_UpperX_387)) && (SaveWindow_SaveButton_LowerY_343 < CursorYCoord && (CursorYCoord < SaveWindow_SaveButton_UpperY_355))) {
      if (saveWindow->selectedSaveSlot == -1) {
        saveWindow->gameWindow4->primarySwitchSingleParam(0x7d0a, 63, 0x0);
      }
      else {
        saveWindow->SaveGameToFile(saveWindow->selectedSaveSlot);
        saveWindow->gameWindow4->primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(saveWindow, 0x0);
      }
    }
    if ((((SaveWindow_CancelButton_LowerX_397 < CursorXCoord) && (CursorXCoord < SaveWindow_CancelButton_UpperX_446)) && (SaveWindow_CancelButton_LowerY_344 < CursorYCoord)) && (CursorYCoord < SaveWindow_CancelButton_UpperY_354)) {
      saveWindow->gameWindow4->primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(saveWindow, 0x0);
    }

    if (((SaveWindow_Grid_LowerX_287 < CursorXCoord) && (CursorXCoord < SaveWindow_Grid_UpperX_517)) && (SaveWindow_Grid_LowerY_143 < CursorYCoord && (CursorYCoord < SaveWindow_Grid_UpperY_336))) {
      randomSoundEffectIndex = (PseudoRng() % 256);
      PtrSfxObject->RunPlay(ListOfSfxBuffers[66], 255, randomSoundEffectIndex);
      saveWindow->selectedSaveSlot = ((CursorYCoord - SaveWindow_Grid_LowerY_143) * 7) / 193;
    }
  }
}

__forceinline void Case_0x7d3b(GameWindowSave* saveWindow) {

  ImageVectorWithHeader* sprite;
  int32_t frameCount;
  GameState* gameState;
  int32_t loopIndex;

  sprite = GameWindowBase::__InlineGetSolidSpriteFrameForAction(saveWindow->frame, saveWindow->actWin9, 0);
  GameWindowRightSide->RenderClippedSprite(-0x91, 0, sprite, DrawLayer::Layer0xFFF8);
  if (saveWindow->fillZero != nullptr) {
    GameWindowRightSide->RenderClippedSprite(-0x91, 0, saveWindow->fillZero, DrawLayer::Layer0xFFF9);
  }
  frameCount = 0;
  loopIndex = 0x9b;
  gameState = saveWindow->gameStateAddr;
  do {
    saveWindow->DrawText(0xa1, loopIndex, gameState->description, saveWindow->selectedSaveSlot == frameCount ? 9 : 2);
    loopIndex = loopIndex + 0x1c;
    frameCount = frameCount + 1;
    gameState = gameState + 1;
  } while (loopIndex < 0x15f);
}

void GameWindowSave::primarySwitchSingleParam(int32_t switchParam, intptr_t param_2, intptr_t param_3) {

  (void)param_2;
  (void)param_3;

  switch (switchParam) {
  case 0x7d0e:
    Case_0x7d0e(this);
    return;
  case 0x7d3b:
    Case_0x7d3b(this);
    return;
  default:
    return;
  }
}
