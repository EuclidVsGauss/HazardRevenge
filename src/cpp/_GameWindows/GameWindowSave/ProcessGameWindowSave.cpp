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

__forceinline void GameWindowSave::HandleMouseInput_0x7d0e() {

  ImageVectorWithHeader* sprite;
  int32_t randomSoundEffectIndex;

  this->fillZero = nullptr;
  if ((((SaveWindow_SaveButton_LowerX_336 < CursorXCoord) && (CursorXCoord < SaveWindow_SaveButton_UpperX_387)) && (SaveWindow_SaveButton_LowerY_343 < CursorYCoord)) && (CursorYCoord < SaveWindow_SaveButton_UpperY_355)) {

    sprite = this->actWin9->__InlineGetSolidSpriteFrameForAction(this->button, 0);
    this->fillZero = sprite;
  }
  if (!(((CursorXCoord <= SaveWindow_CancelButton_LowerX_397) || (SaveWindow_CancelButton_UpperX_446 <= CursorXCoord)) || (CursorYCoord <= SaveWindow_CancelButton_LowerY_344 || (SaveWindow_CancelButton_UpperY_354 <= CursorYCoord)))) {
    sprite = this->actWin9->__InlineGetSolidSpriteFrameForAction(this->button, 1);
    this->fillZero = sprite;
  }

  if ((MouseButtonClick & 17) == 1) {
    if (((SaveWindow_SaveButton_LowerX_336 < CursorXCoord) && (CursorXCoord < SaveWindow_SaveButton_UpperX_387)) && (SaveWindow_SaveButton_LowerY_343 < CursorYCoord && (CursorYCoord < SaveWindow_SaveButton_UpperY_355))) {
      if (this->selectedSaveSlot == -1) {
        this->gameWindow4->primarySwitchSingleParam(0x7d0a, 63, 0x0);
      }
      else {
        this->SaveGameToFile(this->selectedSaveSlot);
        this->gameWindow4->primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(this, 0x0);
      }
    }
    if ((((SaveWindow_CancelButton_LowerX_397 < CursorXCoord) && (CursorXCoord < SaveWindow_CancelButton_UpperX_446)) && (SaveWindow_CancelButton_LowerY_344 < CursorYCoord)) && (CursorYCoord < SaveWindow_CancelButton_UpperY_354)) {
      this->gameWindow4->primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(this, 0x0);
    }

    if (((SaveWindow_Grid_LowerX_287 < CursorXCoord) && (CursorXCoord < SaveWindow_Grid_UpperX_517)) && (SaveWindow_Grid_LowerY_143 < CursorYCoord && (CursorYCoord < SaveWindow_Grid_UpperY_336))) {
      SfxObject* sfxObject = PtrSfxObject;
      randomSoundEffectIndex = PseudoRng() % 256;
      LPDIRECTSOUNDBUFFER soundBuffer = ListOfSfxBuffers[66];
      sfxObject->RunPlay(soundBuffer, 255, randomSoundEffectIndex);
      this->selectedSaveSlot = ((CursorYCoord - SaveWindow_Grid_LowerY_143) * 7) / 193;
    }
  }
}

__forceinline void GameWindowSave::DrawObject_0x7d3b() {

  ImageVectorWithHeader* sprite;
  int32_t frameCount;
  GameState* gameState;
  int32_t loopIndex;

  sprite = this->actWin9->__InlineGetSolidSpriteFrameForAction(this->frame, 0);
  GameWindowRightSide->RenderClippedSprite(-0x91, 0, sprite, DrawLayer::Layer0xFFF8);
  if (this->fillZero != nullptr) {
    GameWindowRightSide->RenderClippedSprite(-0x91, 0, this->fillZero, DrawLayer::Layer0xFFF9);
  }
  frameCount = 0;
  loopIndex = 0x9b;
  gameState = this->gameStateAddr;
  do {
    this->PrintSaveWindowText(0xa1, loopIndex, gameState->description, this->selectedSaveSlot == frameCount ? 9 : 2);
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
    this->HandleMouseInput_0x7d0e();
    return;
  case 0x7d3b:
    this->DrawObject_0x7d3b();
    return;
  default:
    return;
  }
}
