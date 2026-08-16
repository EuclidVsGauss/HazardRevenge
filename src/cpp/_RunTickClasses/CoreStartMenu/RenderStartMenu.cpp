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

  sprite = GameWindowBase::__InlineGetSolidSpriteFrameForAction(this->mainmenuFrame, this->mainmenuAct, 0);
  this->windowPtr->RenderClippedSprite(0, 0, sprite, DrawLayer::Layer0x0);

  sprite = GameWindowBase::__InlineGetSolidSpriteFrameForAction(this->mainmenuFrame, this->mainmenuAct, 1);
  this->windowPtr->RenderClippedSprite(0, 0, sprite, DrawLayer::Layer0x2);

  sprite = GameWindowBase::__InlineGetSolidSpriteFrameForAction(this->cursorNormal, this->cursorAct, this->timeResolutionRelated);
  this->windowPtr->RenderClippedSprite(this->cursorX, this->cursorY, sprite, DrawLayer::Layer0x1);

  for (menuFrame = 0; menuFrame < 4; menuFrame++) {
    sprite = GameWindowBase::__InlineGetSolidSpriteFrameForAction(this->mainmenuStringIndex, this->mainmenuAct, menuFrame * 2);
    this->windowPtr->RenderClippedSprite(0, 0, sprite, DrawLayer::Layer0x0);
  }

  if (this->counter != nullptr) {
    this->windowPtr->RenderClippedSprite(0, 0, this->counter, DrawLayer::Layer0x0);
  }
  this->windowPtr->RenderWithDirectDrawSurface();
}
