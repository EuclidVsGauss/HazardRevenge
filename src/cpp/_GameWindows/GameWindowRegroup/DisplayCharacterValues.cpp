#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowRegroup.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardExterns/GameWindowRegroup.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActiveCharacter.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"
#include "HazardStructs/NumericalCharacterStats.hpp"

void GameWindowRegroup::DisplayCharacterValues(int32_t textCoord1, int32_t textCoord2, GameWindowBase* charInventory) {

  ActiveCharacter* pActiveChar;
  ImageVectorWithHeader* pSpriteFrame;
  int32_t index;
  int32_t levelRemainder;
  int32_t spriteXOffset;
  int32_t isAlreadyInTeam;

  for (index = 0; TeamCharacterList[index] != nullptr; index++) {
    if (TeamCharacterList[index]->shiftedSceneClassUser0x48 == charInventory) {
      break;
    }
  }

  pActiveChar = TeamCharacterList[index];
  if (pActiveChar == nullptr) {
    for (index = 0; BenchedCharacterList[index] != nullptr; index++) {
      if (BenchedCharacterList[index]->shiftedSceneClassUser0x48 == charInventory) {
        break;
      }
    }
    pActiveChar = BenchedCharacterList[index];
    isAlreadyInTeam = 0;
  }
  else {
    isAlreadyInTeam = 1;
  }

  if (pActiveChar == nullptr) {
    WrapperMessageBoxA(s__, s_debug);
  }

  pSpriteFrame = __InlineGetSolidSpriteFrameForAction(this->frame, this->winaAct, 1);
  GameWindowRightSide->RenderClippedSprite(textCoord1 + 0x13, textCoord2 + 0x32, pSpriteFrame, DrawLayer::Layer0xFFFB);

  pSpriteFrame = __InlineGetSolidSpriteFrameForAction(this->face, this->winaAct, (((pActiveChar->characterId << 1) - isAlreadyInTeam) + 1));
  GameWindowRightSide->RenderClippedSprite(textCoord1 + 0x15, textCoord2 + 0x34, pSpriteFrame, DrawLayer::Layer0xFFFB);

  pSpriteFrame = __InlineGetSolidSpriteFrameForAction(this->name, this->winaAct, pActiveChar->characterId);
  GameWindowRightSide->RenderClippedSprite(textCoord1 + -0x21, textCoord2 + 0x42, pSpriteFrame, DrawLayer::Layer0xFFFB);
  levelRemainder = pActiveChar->characterBaseStats->Level;
  if (0 < levelRemainder) {
    spriteXOffset = textCoord1 + -0xf3;
    do {

      pSpriteFrame = __InlineGetSolidSpriteFrameForAction(this->lv, this->winaAct, (levelRemainder % 10));

      GameWindowRightSide->RenderClippedSprite(spriteXOffset, textCoord2 - 0x9b, pSpriteFrame, DrawLayer::Layer0xFFFB);
      levelRemainder = levelRemainder / 10;
      spriteXOffset = spriteXOffset + -6;
    } while (0 < levelRemainder);
  }
  this->DisplayValueInWindow(textCoord1 + 0x152, textCoord2 + 0x43, pActiveChar->characterBaseStats->Experience, this->displayExpRelated);
  levelRemainder = pActiveChar->characterBaseStats->CurrentMp;
  this->DisplayValueInWindow(textCoord1 + 0x124, textCoord2 + 0x5b, pActiveChar->characterBaseStats->CurrentHp, this->displayCurrentHpRelated);
  this->DisplayValueInWindow(textCoord1 + 0x149, textCoord2 + 0x5b, pActiveChar->characterBaseStats->MaxHp, this->displayMaxHpRelated);
  this->DisplayValueInWindow(textCoord1 + 0x124, textCoord2 + 0x6f, levelRemainder, this->displayCurrentMpRelated);
  this->DisplayValueInWindow(textCoord1 + 0x148, textCoord2 + 0x6f, pActiveChar->characterBaseStats->MaxMp, this->displayMaxMpRelated);
}
