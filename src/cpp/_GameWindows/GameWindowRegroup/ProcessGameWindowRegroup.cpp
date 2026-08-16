#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowDialogue.hpp"
#include "HazardClasses/GameWindowRegroup.hpp"
#include "HazardClasses/MusicObjectBase.hpp"
#include "HazardClasses/SceneClassUser.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardClasses/SfxObject.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActiveCharacter.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

const int32_t GameWindowA_OkButton_LowerX_509 = 509;
const int32_t GameWindowA_OkButton_UpperX_555 = 555;
const int32_t GameWindowA_OkButton_LowerY_18 = 18;
const int32_t GameWindowA_OkButton_UpperY_30 = 30;

const int32_t GameWindowA_CancelButton_LowerX_565 = 565;
const int32_t GameWindowA_CancelButton_UpperX_616 = 616;
const int32_t GameWindowA_CancelButton_LowerY_18 = 18;
const int32_t GameWindowA_CancelButton_UpperY_30 = 30;

const int32_t GameWindowA_Grid_LowerX_164 = 164;
const int32_t GameWindowA_Grid_UpperX_206 = 206;
const int32_t GameWindowA_Grid_LowerY_50 = 50;
const int32_t GameWindowA_Grid_UpperY_101 = 101;
const int32_t GameWindowA_Grid_StepX_237 = 237;
const int32_t GameWindowA_Grid_StepY_84 = 84;

__forceinline void Case_0x7d3b(GameWindowRegroup* thisPtr) {
  ImageVectorWithHeader* spriteToDraw;
  GameWindowBase* currentInventory;
  uint32_t colIndex;
  GameWindowBase** inventoryIter;
  uint32_t inventorySlotIndex;

  spriteToDraw = GameWindowBase::__InlineGetSolidSpriteFrameForAction(thisPtr->frame, thisPtr->winaAct, 0);
  GameWindowRightSide->RenderClippedSprite(-0x91, 0, spriteToDraw, DrawLayer::Layer0xFFF8);
  if (thisPtr->sprite != nullptr) {
    GameWindowRightSide->RenderClippedSprite(-0x91, 0, thisPtr->sprite, DrawLayer::Layer0xFFFB);
  }
  currentInventory = thisPtr->allCharacterInventories[0];
  inventoryIter = thisPtr->allCharacterInventories;
  inventorySlotIndex = 0;
  if (currentInventory == nullptr) {
    return;
  }
  do {
    colIndex = inventorySlotIndex % 2;
    thisPtr->DisplayCharacterValues(colIndex * GameWindowA_Grid_StepX_237, ((int32_t)inventorySlotIndex / 2) * GameWindowA_Grid_StepY_84, currentInventory);
    currentInventory = inventoryIter[1];
    inventoryIter = inventoryIter + 1;
    inventorySlotIndex = inventorySlotIndex + 1;
  } while (currentInventory != nullptr);
}

__forceinline void Case_0x7d0e(GameWindowRegroup* thisPtr) {
  GameWindowBase* currentInventory;
  int32_t colIndex;
  ActiveCharacter* currentCharInLoop;
  ActiveCharacter** activeChar1;
  ActiveCharacter** activeChar2;
  int32_t charIndexInTeam;
  int32_t charIndexInBench;
  GameWindowBase** inventoryIter;
  uint32_t inventorySlotIndex;
  SceneHandler* sceneHandler;
  ActiveCharacter* nestedActiveChar;
  int32_t i;

  thisPtr->sprite = nullptr;
  if ((((GameWindowA_OkButton_LowerX_509 < CursorXCoord) && (CursorXCoord < GameWindowA_OkButton_UpperX_555)) && (GameWindowA_OkButton_LowerY_18 < CursorYCoord)) && (CursorYCoord < GameWindowA_OkButton_UpperY_30)) {
    thisPtr->sprite = GameWindowRegroup::__InlineGetSolidSpriteFrameForAction(thisPtr->button, thisPtr->winaAct, 0);
    if (((MouseButtonClick & 0x11) == 1) && (TeamCharacterList[0] != nullptr)) {
      inventoryIter = thisPtr->allCharacterInventories;
      currentInventory = thisPtr->allCharacterInventories[0];
      currentCharInLoop = TeamCharacterList[0];
      while (TeamCharacterList[0] = currentCharInLoop, currentInventory != nullptr) {
        currentInventory = *inventoryIter;
        sceneHandler = currentInventory->mainSceneHandler;
        currentInventory->primarySwitchSingleParam_PrepareMapForUnit_0x7d12(0, 0);
        if ((sceneHandler != thisPtr->mainSceneHandlerCopy) && (sceneHandler != nullptr)) {
          sceneHandler->primarySwitchSingleParam(0x7d0d, 0, 0x0);
        }
        inventoryIter = inventoryIter + 1;
        currentCharInLoop = TeamCharacterList[0];
        currentInventory = *inventoryIter;
      }
      if (currentCharInLoop != nullptr) {
        activeChar1 = TeamCharacterList;
        do {
          currentCharInLoop->shiftedSceneClassUser0x48->primarySwitchSingleParam_SetUserLocationOnScene_0x7d13(thisPtr->partyCoord1, thisPtr->partyCoord2);
          thisPtr->mainSceneHandlerCopy->primarySwitchSingleParam_TriggerObjectInitialization_0x7d27((*activeChar1)->shiftedSceneClassUser0x48, 0x0);
          thisPtr->mainSceneHandlerCopy->primarySwitchSingleParam_UpdateSelectedUnits_0x7d1a((*activeChar1)->shiftedSceneClassUser0x48, 0x0);
          (*activeChar1)->shiftedSceneClassUser0x48->primarySwitchSingleParam(0x7d06, 0x0, 0x0);
          currentCharInLoop = activeChar1[1];
          activeChar1 = activeChar1 + 1;
        } while (currentCharInLoop != nullptr);
      }
      thisPtr->gameWindow4->primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(thisPtr, 0x0);
    }
  }
  if ((((GameWindowA_CancelButton_LowerX_565 < CursorXCoord) && (CursorXCoord < GameWindowA_CancelButton_UpperX_616)) && (GameWindowA_CancelButton_LowerY_18 < CursorYCoord)) && (CursorYCoord < GameWindowA_CancelButton_UpperY_30)) {
    thisPtr->sprite = GameWindowRegroup::__InlineGetSolidSpriteFrameForAction(thisPtr->button, thisPtr->winaAct, 1);
    ;
    if ((MouseButtonClick & 0x11) == 1) {

      charIndexInTeam = 0;
      while (BenchedCharacterList[charIndexInTeam] != nullptr) {
        charIndexInTeam++;
      }

      for (i = 0; TeamCharacterList[i] != nullptr; i++) {
        BenchedCharacterList[charIndexInTeam + i] = TeamCharacterList[i];
      }
      BenchedCharacterList[charIndexInTeam + i] = nullptr;

      charIndexInTeam = thisPtr->counter;
      for (i = 0; i < thisPtr->counter; i++) {
        TeamCharacterList[i] = thisPtr->teamCharacterInventories[i];
      }
      TeamCharacterList[charIndexInTeam] = nullptr;

      currentCharInLoop = TeamCharacterList[0];
      if (BenchedCharacterList[0] != nullptr) {
        activeChar1 = BenchedCharacterList;
        do {
          charIndexInTeam = 0;
          if (currentCharInLoop != nullptr) {
            activeChar2 = TeamCharacterList;
            nestedActiveChar = currentCharInLoop;
            do {
              if (nestedActiveChar == *activeChar1) {
                break;
              }
              nestedActiveChar = activeChar2[1];
              activeChar2 = activeChar2 + 1;
              charIndexInTeam = charIndexInTeam + 1;
            } while (nestedActiveChar != nullptr);
          }
          if (TeamCharacterList[charIndexInTeam] == *activeChar1) {
            nestedActiveChar = activeChar1[1];
            *activeChar1 = nestedActiveChar;
            activeChar2 = activeChar1;
            while (nestedActiveChar != nullptr) {
              nestedActiveChar = activeChar2[2];
              activeChar2 = activeChar2 + 1;
              *activeChar2 = nestedActiveChar;
            }
          }
          else {
            activeChar1 = activeChar1 + 1;
          }
        } while (*activeChar1 != nullptr);
      }
      thisPtr->gameWindow4->primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(thisPtr, 0x0);
    }
  }
  if ((MouseButtonClick & 0x11) != 1) {
    return;
  }
  inventoryIter = thisPtr->allCharacterInventories;
  inventorySlotIndex = 0;
  if (thisPtr->allCharacterInventories[0] == nullptr) {
    return;
  }
  while (true) {
    colIndex = inventorySlotIndex % 2;
    if ((((int32_t)((colIndex * GameWindowA_Grid_StepX_237) + GameWindowA_Grid_LowerX_164) <= CursorXCoord) && (CursorXCoord <= (int32_t)((colIndex * GameWindowA_Grid_StepX_237) + GameWindowA_Grid_UpperX_206))) && (charIndexInTeam = ((int32_t)inventorySlotIndex / 2) * GameWindowA_Grid_StepY_84, charIndexInTeam + GameWindowA_Grid_LowerY_50 <= CursorYCoord && (CursorYCoord <= charIndexInTeam + GameWindowA_Grid_UpperY_101))) {
      break;
    }
    inventoryIter = inventoryIter + 1;
    inventorySlotIndex = inventorySlotIndex + 1;
    if (*inventoryIter == nullptr) {
      return;
    }
  }

  charIndexInTeam = 0;
  if (TeamCharacterList[0] != nullptr) {
    activeChar1 = TeamCharacterList;
    currentCharInLoop = TeamCharacterList[0];
    do {
      if (currentCharInLoop->shiftedSceneClassUser0x48 == thisPtr->allCharacterInventories[inventorySlotIndex]) {
        break;
      }
      currentCharInLoop = activeChar1[1];
      activeChar1 = activeChar1 + 1;
      charIndexInTeam = charIndexInTeam + 1;
    } while (currentCharInLoop != nullptr);
  }

  if (TeamCharacterList[charIndexInTeam] == nullptr) {
    charIndexInTeam = 0;
    if ((SceneClassUser*)BenchedCharacterList[0]->shiftedSceneClassUser0x48 != thisPtr->allCharacterInventories[inventorySlotIndex]) {
      activeChar1 = BenchedCharacterList;
      do {
        activeChar2 = activeChar1 + 1;
        activeChar1 = activeChar1 + 1;
        charIndexInTeam = charIndexInTeam + 1;
      } while ((SceneClassUser*)(*activeChar2)->shiftedSceneClassUser0x48 != thisPtr->allCharacterInventories[inventorySlotIndex]);
    }
    charIndexInBench = 0;
    if (TeamCharacterList[0] != nullptr) {
      activeChar1 = TeamCharacterList;
      do {
        activeChar2 = activeChar1 + 1;
        activeChar1 = activeChar1 + 1;
        charIndexInBench = charIndexInBench + 1;
      } while (*activeChar2 != nullptr);
      if (4 < charIndexInBench) {
        PtrSfxObject->RunPlay(ListOfSfxBuffers[66], 0xff, PseudoRng() & 0xff);
        return;
      }
    }
    activeChar1 = BenchedCharacterList + charIndexInTeam;
    TeamCharacterList[charIndexInBench] = BenchedCharacterList[charIndexInTeam];
    TeamCharacterList[charIndexInBench + 1] = nullptr;
    currentCharInLoop = BenchedCharacterList[charIndexInTeam + 1];
    *activeChar1 = currentCharInLoop;
    while (currentCharInLoop != nullptr) {
      currentCharInLoop = activeChar1[2];
      activeChar1 = activeChar1 + 1;
      charIndexInTeam = charIndexInTeam + 1;
      *activeChar1 = currentCharInLoop;
    }
    BenchedCharacterList[charIndexInTeam] = nullptr;
  }
  else {
    int32_t benchLength = 0;
    while (BenchedCharacterList[benchLength] != nullptr) {
      benchLength++;
    }
    BenchedCharacterList[benchLength] = TeamCharacterList[charIndexInTeam];
    BenchedCharacterList[benchLength + 1] = nullptr;

    while (TeamCharacterList[charIndexInTeam + 1] != nullptr) {
      TeamCharacterList[charIndexInTeam] = TeamCharacterList[charIndexInTeam + 1];
      charIndexInTeam++;
    }
    TeamCharacterList[charIndexInTeam] = nullptr;
  }
  PtrSfxObject->RunPlay(ListOfSfxBuffers[66], 0xff, PseudoRng() & 0xff);
}

void GameWindowRegroup::primarySwitchSingleParam(int32_t param_1, intptr_t param2, intptr_t param_3) {
  (void)param2;
  (void)param_3;

  switch (param_1) {
  case 0x7d3b:
    Case_0x7d3b(this);
    return;

  case 0x7d0e:
    Case_0x7d0e(this);
    return;

  default:
    return;
  }
}
