#include "HazardClasses/CoreStartMenu.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

void __fastcall CoreStartMenu::RenderStartMenu() {

  ImageVectorWithHeader* sprite;
  int32_t menuFrame;

  this->windowPtr->PrepareRenderArrays();

  sprite = this->mainmenuAct->__InlineGetSolidSpriteFrameForAction(this->mainmenuFrame, 0);
  this->windowPtr->RenderClippedSprite(0, 0, sprite, DrawLayer::Layer0x0);

  sprite = this->mainmenuAct->__InlineGetSolidSpriteFrameForAction(this->mainmenuFrame, 1);
  this->windowPtr->RenderClippedSprite(0, 0, sprite, DrawLayer::Layer0x2);

  sprite = this->cursorAct->__InlineGetSolidSpriteFrameForAction(this->cursorNormal, this->timeResolutionRelated);
  this->windowPtr->RenderClippedSprite(this->cursorX, this->cursorY, sprite, DrawLayer::Layer0x1);

  for (menuFrame = 0; menuFrame < 4; menuFrame++) {
    sprite = this->mainmenuAct->__InlineGetSolidSpriteFrameForAction(this->mainmenuStringIndex, menuFrame * 2);
    this->windowPtr->RenderClippedSprite(0, 0, sprite, DrawLayer::Layer0x0);
  }

  if (this->counter != nullptr) {
    this->windowPtr->RenderClippedSprite(0, 0, this->counter, DrawLayer::Layer0x0);
  }
  this->windowPtr->RenderWithDirectDrawSurface();
}
