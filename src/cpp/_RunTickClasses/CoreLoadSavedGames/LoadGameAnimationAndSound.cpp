#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/CoreLoadSavedGames.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SfxObject.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/GameState.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

void __fastcall CoreLoadSavedGames::LoadGameAnimationAndSound() {

  int32_t random1;
  int32_t hoveredSlotIndex;
  uint32_t checksum;
  GameState* pDestState;
  int32_t loopCounter;
  GameState* pSrcState;
  SfxObject* sfxObject;

  checksum = 0;
  hoveredSlotIndex = this->xCoord;
  this->init0_1 = this->init0_1 + 1;
  this->init0_3 = this->init0_3 + 1;
  if ((((hoveredSlotIndex < 454) || (587 < hoveredSlotIndex)) || (this->yCoord < 223)) || (375 < this->yCoord)) {
    if (((hoveredSlotIndex < 58) || (118 < hoveredSlotIndex)) || (this->yCoord < 257 || (407 < this->yCoord))) {
      this->frameEndSprite = nullptr;
      goto label_check_save_slot_click;
    }
    if (this->frameEndSprite == nullptr) {

      sfxObject = PtrSfxObject;
      random1 = PseudoRng();
      random1 = random1 % 128;
      sfxObject->RunPlay(ListOfSfxBuffers[66], 255, random1 + 64);
    }

    this->frameEndSprite = GameWindowBase::__InlineGetSolidSpriteFrameForAction(this->frameEnd, this->winB_Act, 2);
    if (((this->mouseClick & 17) == 1) && (this->initiallyMax != -1)) {
      pDestState = &this->SaveSlot1 + this->initiallyMax;
      pSrcState = &GlobalHazGameState;

      memcpy(pSrcState, pDestState, sizeof(GameState));
      this->init2 = 0;
    }
    goto label_check_save_slot_click;
  }
  if (this->frameEndSprite == nullptr) {

    random1 = PseudoRng();
    random1 = random1 % 128;
    PtrSfxObject->RunPlay(ListOfSfxBuffers[66], 0xff, random1 + 64);
  }

  this->frameEndSprite = GameWindowBase::__InlineGetSolidSpriteFrameForAction(this->frameEnd, this->winB_Act, 1);
  if ((this->mouseClick & 0x11) == 1) {
    this->init2 = 1;
  }
label_check_save_slot_click:
  if (((((this->mouseClick & 0x11) == 1) && (214 <= this->xCoord)) && (this->xCoord <= 444)) && (hoveredSlotIndex = this->yCoord, 232 <= hoveredSlotIndex && (hoveredSlotIndex <= 428))) {
    hoveredSlotIndex = ((hoveredSlotIndex + -232) * 7) / 196;
    if ((&this->SaveSlot1)[hoveredSlotIndex].sceneLocationName[0] != '\0') {
      pDestState = &this->SaveSlot1 + hoveredSlotIndex;
      loopCounter = 45136;
      do {
        checksum = ((byte)pDestState->description[0] + checksum) & 0x3ff;
        pDestState = (GameState*)(pDestState->description + 1);
        loopCounter = loopCounter + -1;
      } while (loopCounter != 0);
      if ((checksum & 0x3ff) == (&this->SaveSlot2)[hoveredSlotIndex + -1].gameFlags[0x7ff]) {
        if ((this->init0_3 < TimeResolution_45or15 / 2) && (this->initiallyMax == hoveredSlotIndex)) {
          pDestState = &this->SaveSlot1 + this->initiallyMax;
          pSrcState = &GlobalHazGameState;

          memcpy(pSrcState, pDestState, sizeof(GameState));
          this->init2 = 0;
        }
        else {
          this->initiallyMax = hoveredSlotIndex;
          random1 = PseudoRng();
          random1 = random1 % 128;
          PtrSfxObject->RunPlay(ListOfSfxBuffers[66], 255, random1 + 64);
          this->init0_3 = 0;
        }
      }
    }
  }
  if (InputStates128[1] != '\0') {
    this->init2 = 1;
  }
}
