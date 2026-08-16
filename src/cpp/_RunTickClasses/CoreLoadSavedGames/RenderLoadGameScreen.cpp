#include "HazardClasses/CoreLoadSavedGames.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardInlineFunctions.hpp"
#include "HazardStructs/GameState.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

void __fastcall CoreLoadSavedGames::RenderLoadGameScreen() {

  ImageVectorWithHeader* sprite;
  int32_t currentFrame;
  GameState* currentSlot;
  int32_t slotIndex;

  this->windowStruct->PrepareRenderArrays();

  sprite = GameWindowBase::__InlineGetSolidSpriteFrameForAction(this->frameBegin, this->mainMenu_Act, 0);
  this->windowStruct->RenderClippedSprite(0, 0, sprite, DrawLayer::Layer0x0);

  sprite = GameWindowBase::__InlineGetSolidSpriteFrameForAction(this->frameBegin, this->mainMenu_Act, 1);
  this->windowStruct->RenderClippedSprite(0, 0, sprite, DrawLayer::Layer0x2);

  sprite = GameWindowBase::__InlineGetSolidSpriteFrameForAction(this->frameEnd, this->winB_Act, 0);
  this->windowStruct->RenderClippedSprite(0, 0, sprite, DrawLayer::Layer0x0);
  if (this->frameEndSprite != nullptr) {
    this->windowStruct->RenderClippedSprite(0, 0, this->frameEndSprite, DrawLayer::Layer0x0);
  }

  sprite = GameWindowBase::__InlineGetSolidSpriteFrameForAction(this->normal, this->cursor_Act, this->init0_1);
  this->windowStruct->RenderClippedSprite(this->xCoord, this->yCoord, sprite, DrawLayer::Layer0x2);
  currentFrame = 0;
  slotIndex = 0xf6;
  currentSlot = &this->SaveSlot1;
  do {
    this->PrintSaveFileText(0xea, slotIndex, currentSlot->description, this->initiallyMax == currentFrame ? 9 : 2);
    slotIndex = slotIndex + 0x1c;
    currentFrame = currentFrame + 1;
    currentSlot = currentSlot + 1;
  } while (slotIndex < 0x1ba);
  this->windowStruct->RenderWithDirectDrawSurface();
}
