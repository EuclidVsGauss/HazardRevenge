#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowSidebar.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardEnums/MapType.hpp"
#include "HazardExterns/GameWindowSidebar.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActContent.hpp"
#include "HazardStructs/ActiveCharacter.hpp"
#include "HazardStructs/CharacterEquipment.hpp"
#include "HazardStructs/ClickableRectangle2.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"
#include "HazardStructs/InventoryItemAccessory.hpp"
#include "HazardStructs/InventoryItemArmor.hpp"
#include "HazardStructs/InventoryItemStruct.hpp"
#include "HazardStructs/InventoryItemWeapon.hpp"
#include "HazardStructs/NumericalCharacterStats.hpp"
#include "HazardStructs/WindowReference.hpp"

const int32_t Sidebar_LowerX_12 = 12;
const int32_t Sidebar_UpperX_55 = 55;
const int32_t Sidebar_LowerY_40 = 40;
const int32_t Sidebar_UpperY_92 = 92;
const int32_t Sidebar_Loop_Limit_387 = 387;
const int32_t Sidebar_LowerX_113 = 113;
const int32_t Sidebar_UpperX_131 = 131;
const int32_t Sidebar_LowerY_59 = 59;
const int32_t Sidebar_UpperY_70 = 70;
const int32_t Sidebar_Width_145 = 145;
const int32_t Sidebar_Height_480 = 480;

__forceinline void GameWindowSidebar::Case_0x7d11(intptr_t param_2) {
  WindowReference windowReference;
  windowReference.coords[2] = Sidebar_Width_145;
  windowReference.coords[0] = 0;
  windowReference.coords[1] = 0;
  windowReference.coords[3] = Sidebar_Height_480;
  this->mainSceneHandler = (SceneHandler*)param_2;
  windowReference.windowAddress = (intptr_t)this;
  this->mainSceneHandler->primarySwitchSingleParam_SetWindow_0x7d16(1, &windowReference);
}

__forceinline void GameWindowSidebar::Case_0x7d3b() {

  ImageVectorWithHeader* spritePointer;
  GameWindowBase* unitWindowBase;
  GameWindowBase** unitWindowList;
  int32_t loopCounter;
  int32_t actIndex;
  char* stringCursor;
  int32_t totalMpBonus;
  int32_t totalHpBonus;
  int32_t digitXPos;
  ActiveCharacter** activeCharCheckSlot;
  ActiveCharacter* partyMember;
  CoreActClass* coreAct;
  ActiveCharacter* currentCharPtr;
  GameWindowBase** selectedUnitList;
  ActiveCharacter** activeCharList;
  int32_t digitRenderPos;

  spritePointer = __InlineGetSolidSpriteFrameForAction(this->actMain, this->win0act, 0);
  GameWindowLeftSidebar->RenderClippedSprite(0, 0, spritePointer, DrawLayer::Layer0xFFF6);

  if (GoldAmount == 0) {
    spritePointer = __InlineGetSolidSpriteFrameForAction(this->actNumber, this->win0act, 0);
    GameWindowLeftSidebar->RenderClippedSprite(-0xca, 0x6d, spritePointer, DrawLayer::Layer0xFFF6);
  }
  else if (0 < (int32_t)GoldAmount) {
    digitRenderPos = -202;
    loopCounter = GoldAmount;
    do {
      spritePointer = __InlineGetSolidSpriteFrameForAction(this->actNumber, this->win0act, loopCounter % 10);
      GameWindowLeftSidebar->RenderClippedSprite(digitRenderPos, 0x6d, spritePointer, DrawLayer::Layer0xFFF6);
      digitRenderPos = digitRenderPos - 8;
      loopCounter = loopCounter / 10;
    } while (0 < loopCounter);
  }

  intptr_t switchParam = 0;
  activeCharList = (ActiveCharacter**)TeamCharacterList;
  activeCharCheckSlot = ActiveTeamCharacterSlots;
  do {
    if (*activeCharCheckSlot != nullptr) {
      spritePointer = __InlineGetSolidSpriteFrameForAction(this->actFrame, this->win0act, 0);
      GameWindowLeftSidebar->RenderClippedSprite(0, switchParam, spritePointer, DrawLayer::Layer0xFFF6);

      spritePointer = __InlineGetSolidSpriteFrameForAction(this->actFace, this->win0act, (((*activeCharCheckSlot)->characterId * 3) + 1));
      GameWindowLeftSidebar->RenderClippedSprite(0xd, switchParam + 0x29, spritePointer, DrawLayer::Layer0xFFF6);
    }
    else {
      partyMember = *activeCharList;
      if (partyMember != nullptr) {
        totalMpBonus = 0;
        totalHpBonus = 0;
        if (0 < (partyMember->charEquip).equipmentWeapon.quantity) {
          totalMpBonus = (partyMember->charEquip).equipmentWeapon.mp;
        }
        if (0 < (partyMember->charEquip).equipmentArmor.quantity) {
          totalMpBonus = totalMpBonus + (partyMember->charEquip).equipmentArmor.mp;
        }
        if (0 < (partyMember->charEquip).equipmentAccessory1.quantity) {
          totalHpBonus = (partyMember->charEquip).equipmentAccessory1.hp;
          totalMpBonus = totalMpBonus + (partyMember->charEquip).equipmentAccessory1.mp;
        }
        if (0 < (partyMember->charEquip).equipmentAccessory2.quantity) {
          totalHpBonus = totalHpBonus + (partyMember->charEquip).equipmentAccessory2.hp;
          totalMpBonus = totalMpBonus + (partyMember->charEquip).equipmentAccessory2.mp;
        }

        spritePointer = __InlineGetSolidSpriteFrameForAction(this->actFrame, this->win0act, 0);
        GameWindowLeftSidebar->RenderClippedSprite(0, switchParam, spritePointer, DrawLayer::Layer0xFFF6);

        spritePointer = __InlineGetSolidSpriteFrameForAction(this->actName, this->win0act, (*activeCharList)->characterId);
        GameWindowLeftSidebar->RenderClippedSprite(0, switchParam, spritePointer, DrawLayer::Layer0xFFF6);

        spritePointer = __InlineGetSolidSpriteFrameForAction(this->actLv, this->win0act, 0);
        GameWindowLeftSidebar->RenderClippedSprite(0, switchParam, spritePointer, DrawLayer::Layer0xFFF6);

        actIndex = (*activeCharList)->characterBaseStats->Level;
        if (0 < actIndex) {
          digitXPos = -0xde;
          do {
            spritePointer = __InlineGetSolidSpriteFrameForAction(this->actLvNum, this->win0act, actIndex % 10);
            GameWindowLeftSidebar->RenderClippedSprite(digitXPos, switchParam - 0xb1, spritePointer, DrawLayer::Layer0xFFF6);
            digitXPos = digitXPos + -6;
            actIndex = actIndex / 10;
          } while (0 < actIndex);
        }

        if (((*activeCharList)->charEquip).ActiveSlot1.typeId != 0) {
          spritePointer = __InlineGetSolidSpriteFrameForAction(((*activeCharList)->charEquip).ActiveSlot1.actOffset, Item00Act, 2);
          GameWindowLeftSidebar->RenderClippedSprite(0x7b, switchParam + 0x3f, spritePointer, DrawLayer::Layer0xFFF6);
        }

        if (((*activeCharList)->charEquip).ActiveSlot2.typeId != 0) {
          spritePointer = __InlineGetSolidSpriteFrameForAction(((*activeCharList)->charEquip).ActiveSlot2.actOffset, Item00Act, 2);
          GameWindowLeftSidebar->RenderClippedSprite(0x7b, switchParam + 0x54, spritePointer, DrawLayer::Layer0xFFF6);
        }

        actIndex = (*activeCharList)->characterBaseStats->CurrentHp + totalHpBonus;
        if (0 < actIndex) {
          loopCounter = actIndex * 0x10;
          spritePointer = __InlineGetSolidSpriteFrameForAction(this->actHp, this->win0act, (0x10U - ((loopCounter & ((loopCounter < 1) - 1)) / ((*activeCharList)->characterBaseStats->MaxHp + totalHpBonus))));
          GameWindowLeftSidebar->RenderClippedSprite(0, switchParam, spritePointer, DrawLayer::Layer0xFFF6);
        }

        actIndex = (*activeCharList)->characterBaseStats->CurrentMp + totalMpBonus;
        if (0 < actIndex) {
          loopCounter = actIndex * 0x10;
          spritePointer = __InlineGetSolidSpriteFrameForAction(this->actMp, this->win0act, (0x10U - ((loopCounter & ((loopCounter < 1) - 1)) / ((*activeCharList)->characterBaseStats->MaxMp + totalMpBonus))));
          GameWindowLeftSidebar->RenderClippedSprite(0, switchParam, spritePointer, DrawLayer::Layer0xFFF6);
        }

        loopCounter = (*activeCharList)->characterBaseStats->TimeGauge << 4;
        spritePointer = __InlineGetSolidSpriteFrameForAction(this->actTime, this->win0act, (((loopCounter < 1) - 1) & loopCounter) / 0x140);
        GameWindowLeftSidebar->RenderClippedSprite(0, switchParam, spritePointer, DrawLayer::Layer0xFFF6);

        coreAct = this->win0act;
        currentCharPtr = *activeCharList;
        actIndex = this->actFace;
        if (currentCharPtr->shiftedSceneClassUser0x48->mainSceneHandler == this->currentlyActiveScene) {
          spritePointer = __InlineGetSolidSpriteFrameForAction(actIndex, coreAct, (currentCharPtr->characterId * 3));
        }
        else {
          spritePointer = __InlineGetSolidSpriteFrameForAction(actIndex, coreAct, (currentCharPtr->characterId * 3) + 2);
        }
        GameWindowLeftSidebar->RenderClippedSprite(0xd, switchParam + 0x29, spritePointer, DrawLayer::Layer0xFFF6);

        actIndex = 0;
        selectedUnitList = this->mainSceneHandler->selectedUnits32;
        unitWindowBase = *selectedUnitList;
        if (unitWindowBase != nullptr) {
          unitWindowList = selectedUnitList;
          do {
            if (unitWindowBase == (*activeCharList)->shiftedSceneClassUser0x48) {
              break;
            }
            unitWindowBase = unitWindowList[1];
            unitWindowList = unitWindowList + 1;
            actIndex = actIndex + 1;
          } while (unitWindowBase != nullptr);
        }
        if (selectedUnitList[actIndex] != nullptr) {
          spritePointer = __InlineGetSolidSpriteFrameForAction(this->actSelect, this->win0act, 0);
          GameWindowLeftSidebar->RenderClippedSprite(0xb, switchParam + 0x27, spritePointer, DrawLayer::Layer0xFFF6);
        }
        activeCharList = activeCharList + 1;
      }
    }
    activeCharCheckSlot = activeCharCheckSlot + 1;
    switchParam = switchParam + 0x3b;
  } while (activeCharCheckSlot < ActiveTeamCharacterSlots + 5);

  actIndex = 0x1ab;
  stringCursor = &this->sidebarTextLine1[0];
  do {
    if (*stringCursor != 0) {
      loopCounter = strlen(stringCursor);
      this->DrawStringForImage(0x4c - ((loopCounter - 1) * 0xb >> 1), actIndex, stringCursor);
    }
    actIndex = actIndex + 0xc;
    stringCursor = stringCursor + 0xb;
  } while (actIndex < 0x1cf);

  if (this->sidebarHighlight != nullptr) {
    GameWindowLeftSidebar->RenderClippedSprite(0, 0, this->sidebarHighlight, DrawLayer::Layer0xFFF6);
    return;
  }
}

__forceinline void GameWindowSidebar::Case_0x7d07(intptr_t param_2) {
  this->currentlyActiveScene = (SceneHandler*)param_2;
}

__forceinline void GameWindowSidebar::Case_0x7d35(intptr_t param_2) {
  int32_t lineCount;
  int32_t charIndex;
  int32_t baseYPos;
  int32_t adjustedPos;
  byte currentChar;

  this->sidebarTextLine3[0] = 0;
  this->sidebarTextLine2[0] = 0;
  this->sidebarTextLine1[0] = 0;
  if (param_2 != 0x0) {
    lineCount = 0;
    charIndex = 0;
    if (param_2 != 0) {
      baseYPos = 0x2c;
      do {
        if (0x57 < baseYPos) {
          break;
        }
        adjustedPos = baseYPos + charIndex;
        currentChar = *((char*)param_2);
        this->sidebarTextLine2[adjustedPos + -0x37] = currentChar;
        if (currentChar == 0x7c) {
          lineCount = lineCount + 1;
          baseYPos = baseYPos + 0xb;
          this->sidebarTextLine2[adjustedPos + -0x37] = 0;
          charIndex = 0;
        }
        else {
          charIndex = charIndex + 1;
        }
        param_2 = param_2 + 1;
      } while (*((char*)param_2) != '\0');
    }
    this->sidebarTextLine2[charIndex + (lineCount * 0xb) + -0xb] = 0;
    return;
  }
}

__forceinline void GameWindowSidebar::Case_0x7d0e(intptr_t param_2) {
  SHORT asyncKeyStateP;
  int16_t tempKeyState;
  ImageVectorWithHeader* highlightSprite;
  int32_t inputIndex;
  int32_t clickPosY;
  uint32_t* inputBuffer;
  int32_t* clickableInputs;
  int32_t clickPosX;
  ClickableRectangle2* currentClickBox;
  ClickableRectangle2* clickBoxIter;
  int32_t slotCheckIndex;
  ActiveCharacter** characterSlotPtr;

  int32_t baseYCoord;
  uint32_t actionInputs[9];
  ActContent* frameContent;
  int32_t clickInputs[4];

  ActiveCharacter* activeSlotChar;

  actionInputs[0] = (uint32_t)InputStates128[2];
  actionInputs[1] = (uint32_t)InputStates128[3];
  actionInputs[2] = (uint32_t)InputStates128[4];
  actionInputs[3] = (uint32_t)InputStates128[5];
  actionInputs[4] = (uint32_t)InputStates128[6];
  actionInputs[5] = (uint32_t)InputStates128[59];
  actionInputs[6] = (uint32_t)InputStates128[60];
  actionInputs[7] = (uint32_t)InputStates128[61];
  actionInputs[8] = (uint32_t)InputStates128[62];

  clickInputs[0] = (int32_t)InputStates128[46];
  clickInputs[1] = (int32_t)InputStates128[23];
  clickInputs[2] = (int32_t)InputStates128[68];
  clickInputs[3] = (int32_t)InputStates128[17];

  asyncKeyStateP = GetAsyncKeyState(0x50);
  if (asyncKeyStateP != 0) {
    PixelCalculations_DirectDrawSurface(0x2e, 0x18);
    tempKeyState = GetAsyncKeyState(0x50);
    while (tempKeyState != 0) {
      tempKeyState = GetAsyncKeyState(0x50);
    }
    tempKeyState = GetAsyncKeyState(0x50);
    while ((tempKeyState == 0 && (asyncKeyStateP = GetAsyncKeyState(0x1b), asyncKeyStateP == 0))) {
      tempKeyState = GetAsyncKeyState(0x50);
    }
    tempKeyState = GetAsyncKeyState(0x50);
    while (tempKeyState != 0) {
      tempKeyState = GetAsyncKeyState(0x50);
    }
    tempKeyState = GetAsyncKeyState(0x1b);
    while (tempKeyState != 0) {
      tempKeyState = GetAsyncKeyState(0x1b);
    }
    PauseState = 2;
  }

  inputIndex = 0;
  inputBuffer = actionInputs;
  do {
    if (((*inputBuffer & 1) == 1) && (((inputIndex < 5 || ((*inputBuffer & 0x10) == 0)) && (this->currentlyActiveScene != nullptr)) && (this->currentlyActiveScene->mapType != MapType::World))) {
      this->mainSceneHandler->primarySwitchSingleParam(0x7d01, inputIndex, 0x0);
    }
    inputIndex = inputIndex + 1;
    inputBuffer = inputBuffer + 1;
  } while (inputIndex < 9);

  currentClickBox = SidebarWindowClickBoxes;
  clickableInputs = clickInputs;
  do {
    if (((*clickableInputs & 0x11) == 1) && ((currentClickBox == &SidebarWindowClickBoxes[2] || (this->currentlyActiveScene == nullptr)) || (this->currentlyActiveScene->mapType != MapType::World))) {
      this->mainSceneHandler->primarySwitchSingleParam_0x7d14(currentClickBox->WindowRelatedOuter_0x14, 0x0);
    }
    currentClickBox = currentClickBox + 1;
    clickableInputs = clickableInputs + 1;
  } while (currentClickBox < 4 + SidebarWindowClickBoxes);

  this->sidebarHighlight = nullptr;
  if (param_2 != 0) {
    clickBoxIter = &SidebarWindowClickBoxes[0];
    clickPosY = CursorYCoord;
    clickPosX = CursorXCoord;
    do {
      if (((clickBoxIter->lowerX == clickPosX || clickBoxIter->lowerX < clickPosX) && (clickPosX <= clickBoxIter->upperX)) && (clickBoxIter->lowerY == clickPosY || (clickBoxIter->lowerY < clickPosY && (clickPosY <= clickBoxIter->upperY)))) {
        clickPosY = this->actButton;
        highlightSprite = nullptr;
        if (clickPosY >= 0) {
          frameContent = this->win0act->txtContent;
          clickPosX = frameContent[clickPosY].numberFrames;
          if (clickPosX > 0) {
            highlightSprite = this->win0act->solidSpriteMap[frameContent[clickPosY].ptrFrameStart[clickBoxIter->short1 % clickPosX]];
          }
        }
        this->sidebarHighlight = highlightSprite;
        clickPosY = CursorYCoord;
        clickPosX = CursorXCoord;
        if (((MouseButtonClick & 0x11) == 1) && ((clickBoxIter == &SidebarWindowClickBoxes[2] || (this->currentlyActiveScene == nullptr)) || (this->currentlyActiveScene->mapType != MapType::World))) {
          this->mainSceneHandler->primarySwitchSingleParam_0x7d14(clickBoxIter->WindowRelatedOuter_0x14, 0x0);
          clickPosY = CursorYCoord;
          clickPosX = CursorXCoord;
        }
      }
      clickBoxIter = clickBoxIter + 1;
    } while ((intptr_t)clickBoxIter < 96 + (intptr_t)&SidebarWindowClickBoxes[0]);

    if ((MouseButtonClick & 0x11) == 1) {
      slotCheckIndex = 0;
      baseYCoord = Sidebar_UpperY_92;
      do {
        if (((Sidebar_LowerX_12 < clickPosX) && (clickPosX < Sidebar_UpperX_55)) && ((baseYCoord - (Sidebar_UpperY_92 - Sidebar_LowerY_40) < clickPosY && (clickPosY < baseYCoord && (this->currentlyActiveScene != nullptr))) && (this->currentlyActiveScene->mapType != MapType::World))) {
          this->mainSceneHandler->primarySwitchSingleParam(0x7d01, slotCheckIndex, 0x0);
          clickPosY = CursorYCoord;
          clickPosX = CursorXCoord;
        }
        baseYCoord = baseYCoord + 0x3b;
        slotCheckIndex = slotCheckIndex + 1;
      } while (baseYCoord < Sidebar_Loop_Limit_387);
    }

    if (((MouseButtonClick & 0x22) == 2) && (baseYCoord = 0, TeamCharacterList[0] != nullptr)) {
      characterSlotPtr = TeamCharacterList;
      slotCheckIndex = 0x46;
      activeSlotChar = (ActiveCharacter*)ActiveTeamCharacterSlots;
      do {
        if (activeSlotChar->characterId == 0x0) {
          if ((Sidebar_LowerX_113 < clickPosX) && (clickPosX < Sidebar_UpperX_131)) {
            if ((slotCheckIndex - (Sidebar_UpperY_70 - Sidebar_LowerY_59) <= clickPosY) && (clickPosY <= slotCheckIndex)) {
              this->mainSceneHandler->primarySwitchSingleParam(0x7d01, baseYCoord, 0x0);
              (*characterSlotPtr)->shiftedSceneClassUser0x48->primarySwitchSingleParam(0x7d1c, 0x0, 0x0);
              clickPosY = CursorYCoord;
              clickPosX = CursorXCoord;
            }
            if ((slotCheckIndex + 8 <= clickPosY) && (clickPosY <= slotCheckIndex + 0x14)) {
              this->mainSceneHandler->primarySwitchSingleParam(0x7d01, baseYCoord, 0x0);
              (*characterSlotPtr)->shiftedSceneClassUser0x48->primarySwitchSingleParam(0x7d1c, 0x1, 0x0);
              clickPosY = CursorYCoord;
              clickPosX = CursorXCoord;
            }
          }
          characterSlotPtr = characterSlotPtr + 1;
        }
        baseYCoord = baseYCoord + 1;
        activeSlotChar = activeSlotChar + 1;
        slotCheckIndex = slotCheckIndex + 0x3b;
      } while (*characterSlotPtr != nullptr);
    }
    this->mainSceneHandler->primarySwitchSingleParam_0x7d17(0, 0x0);
  }
}

void GameWindowSidebar::primarySwitchSingleParam(int32_t switchParam, intptr_t param_2, intptr_t param_3) {

  (void)param_3;

  switch (switchParam) {
  case 0x7d11:
    Case_0x7d11(param_2);
    return;

  case 0x7d3b:
    Case_0x7d3b();
    return;

  case 0x7d07:
    Case_0x7d07(param_2);
    return;

  case 0x7d35:
    Case_0x7d35(param_2);
    return;

  case 0x7d0e:
    Case_0x7d0e(param_2);
    break;
  }
}
