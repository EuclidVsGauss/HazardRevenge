#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowCharacter.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActContent.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

void GameWindowCharacter::DisplayNumericalValue(int32_t coordX, int32_t coordY, int32_t displayValue, int32_t actionIndex) {
  ImageVectorWithHeader* sprite;

  if (displayValue == 0) {
    sprite = this->win1Act->__InlineGetSolidSpriteFrameForAction(actionIndex, displayValue);
    GameWindowRightSide->RenderClippedSprite(
        this->staticXBoundary + coordX - 465,
        this->dynamicYBoundary + coordY - 240,
        sprite,
        DrawLayer::Layer0xFFF7);
    return;
  }

  while (displayValue > 0) {
    sprite = this->win1Act->__InlineGetSolidSpriteFrameForAction(actionIndex, displayValue % 10);
    GameWindowRightSide->RenderClippedSprite(
        coordX + this->staticXBoundary - 465,
        this->dynamicYBoundary + coordY - 240,
        sprite,
        DrawLayer::Layer0xFFF7);
    coordX -= 8;
    displayValue = displayValue / 10;
  }
}
