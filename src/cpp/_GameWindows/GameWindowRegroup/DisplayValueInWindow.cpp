#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowRegroup.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

void GameWindowRegroup::DisplayValueInWindow(int32_t position1, int32_t position2, int32_t displayValue, int32_t valueIndex) {
  ImageVectorWithHeader* pImageVector;
  int32_t spriteY;
  int32_t spriteX;

  if (displayValue <= 0) {
    pImageVector = __InlineGetSolidSpriteFrameForAction(valueIndex, this->winaAct, 0);
    GameWindowRightSide->RenderClippedSprite(
        position1 - 465,
        position2 - 240,
        pImageVector,
        DrawLayer::Layer0xFFFB);
  }
  else {
    spriteY = position2 - 240;
    spriteX = position1 - 465;

    while (displayValue > 0) {
      pImageVector = __InlineGetSolidSpriteFrameForAction(valueIndex, this->winaAct, displayValue % 10);
      GameWindowRightSide->RenderClippedSprite(
          spriteX,
          spriteY,
          pImageVector,
          DrawLayer::Layer0xFFFB);
      displayValue = displayValue / 10;
      spriteX -= 8;
    }
  }
}
