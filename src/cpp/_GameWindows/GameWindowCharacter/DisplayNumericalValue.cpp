#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowCharacter.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActContent.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

void GameWindowCharacter::DisplayNumericalValue(int32_t coordX, int32_t coordY, int32_t displayValue, int32_t mostlyField33) {

  ImageVectorWithHeader* sprite;
  ActContent* txtContent;
  GameWindow* gw;

  int32_t frameCount;
  int32_t hash;
  int32_t* frameStartTable;
  int32_t index;

  int32_t temp;

  ActContent* entryPtr;

  if (displayValue == 0) {

    sprite = __InlineGetSolidSpriteFrameForAction(mostlyField33, this->win1Act, displayValue);

    gw = GameWindowRightSide;
    gw->RenderClippedSprite(
        this->staticXBoundary + coordX - 465,
        this->dynamicYBoundary + coordY - 240,
        sprite,
        DrawLayer::Layer0xFFF7);
  }
  else if (displayValue > 0) {

    do {
      sprite = nullptr;

      if (coordY >= 0) {
        txtContent = this->win1Act->txtContent;

        entryPtr = &txtContent[mostlyField33];

        frameCount = entryPtr->numberFrames;

        if (frameCount > 0) {
          temp = (displayValue % 10) & 0xffff;
          hash = temp % frameCount;

          frameStartTable = entryPtr->ptrFrameStart;
          index = frameStartTable[hash];
          sprite = this->win1Act->solidSpriteMap[index];
        }
      }

      gw = GameWindowRightSide;
      gw->RenderClippedSprite(
          this->staticXBoundary + coordX - 465,
          this->dynamicYBoundary + coordY - 240,
          sprite,
          DrawLayer::Layer0xFFF7);

      coordX -= 8;
      displayValue = displayValue / 10;

    } while (displayValue > 0);
  }
}
