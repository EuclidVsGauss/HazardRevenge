#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowSidebar.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardEnums/InternalKey.hpp"
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
#include "HazardPatches.hpp"
#ifndef _MSC_VER
#include <SDL3/SDL_platform.h>
#endif

const int32_t Sidebar_LowerX_12 = 12;
const int32_t Sidebar_UpperX_55 = 55;
const int32_t Sidebar_LowerY_40 = 40;
const int32_t Sidebar_UpperY_92 = 92;
const int32_t Sidebar_Loop_Limit_387 = 387;
const int32_t Sidebar_LowerX_114 = 114;
const int32_t Sidebar_UpperX_130 = 130;
const int32_t Sidebar_LowerY_59 = 59;
const int32_t Sidebar_UpperY_70 = 70;
const int32_t Sidebar_Width_145 = 145;
const int32_t Sidebar_Height_480 = 480;

#if (defined(SDL_PLATFORM_IOS) || defined(__IPHONEOS__)) == 0
const int32_t PauseVirtualKey = 0x50;
#else
const int32_t PauseVirtualKey = 0x1b;
#endif
const int32_t EscapeVirtualKey = 0x1b;

__forceinline void GameWindowSidebar::InitializeObject_0x7d11(intptr_t param_2) {
  WindowReference windowReference;
  windowReference.coords[2] = Sidebar_Width_145;
  windowReference.coords[0] = 0;
  windowReference.coords[1] = 0;
  windowReference.coords[3] = Sidebar_Height_480;
  this->mainSceneHandler = (SceneHandler*)param_2;
  windowReference.windowAddress = (intptr_t)this;
  this->mainSceneHandler->primarySwitchSingleParam_SetWindow_0x7d16(1, &windowReference);
}

__forceinline void GameWindowSidebar::DrawObject_0x7d3b() {

  ImageVectorWithHeader* spritePointer;
  GameWindowBase* unitWindowBase;
  GameWindowBase** unitWindowList;
  int32_t loopCounter;
  int32_t actIndex;
  int32_t textLineY;
  char* stringCursor;
  int32_t totalMpBonus;
  int32_t totalHpBonus;
  int32_t digitXPos;
  ActiveCharacter* partyMember;
  ActiveCharacter** activeTeamCharacterSlots;
  CoreActClass* coreAct;
  ActiveCharacter* currentCharPtr;
  GameWindowBase** selectedUnitList;
  ActiveCharacter** activeCharList;
  int32_t digitRenderPos;

  spritePointer = this->win0act->__InlineGetSolidSpriteFrameForAction(this->actMain, 0);
  GameWindowLeftSidebar->RenderClippedSprite(0, 0, spritePointer, DrawLayer::Layer0xFFF6);

  if (GoldAmount == 0) {
    spritePointer = this->win0act->__InlineGetSolidSpriteFrameForAction(this->actNumber, 0);
    GameWindowLeftSidebar->RenderClippedSprite(-0xca, 0x6d, spritePointer, DrawLayer::Layer0xFFF6);
  }
  else if (0 < (int32_t)GoldAmount) {
    digitRenderPos = -202;
    loopCounter = GoldAmount;
    do {
      spritePointer = this->win0act->__InlineGetSolidSpriteFrameForAction(this->actNumber, loopCounter % 10);
      GameWindowLeftSidebar->RenderClippedSprite(digitRenderPos, 0x6d, spritePointer, DrawLayer::Layer0xFFF6);
      digitRenderPos = digitRenderPos - 8;
      loopCounter = loopCounter / 10;
    } while (0 < loopCounter);
  }

  int32_t spritePositionY = 0;
  activeCharList = (ActiveCharacter**)TeamCharacterList;
  for (activeTeamCharacterSlots = ActiveTeamCharacterSlots; activeTeamCharacterSlots < ActiveTeamCharacterSlots + 5; activeTeamCharacterSlots++) {
    if (*activeTeamCharacterSlots != nullptr) {
      spritePointer = this->win0act->__InlineGetSolidSpriteFrameForAction(this->actFrame, 0);
      GameWindowLeftSidebar->RenderClippedSprite(0, spritePositionY, spritePointer, DrawLayer::Layer0xFFF6);

      spritePointer = this->win0act->__InlineGetSolidSpriteFrameForAction(this->actFace, (((*activeTeamCharacterSlots)->characterId * 3) + 1));
      GameWindowLeftSidebar->RenderClippedSprite(0xd, spritePositionY + 0x29, spritePointer, DrawLayer::Layer0xFFF6);
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
        if (0 < (partyMember->charEquip).equipmentAccessories[0].quantity) {
          totalHpBonus = (partyMember->charEquip).equipmentAccessories[0].hp;
          totalMpBonus = totalMpBonus + (partyMember->charEquip).equipmentAccessories[0].mp;
        }
        if (0 < (partyMember->charEquip).equipmentAccessories[1].quantity) {
          totalHpBonus = totalHpBonus + (partyMember->charEquip).equipmentAccessories[1].hp;
          totalMpBonus = totalMpBonus + (partyMember->charEquip).equipmentAccessories[1].mp;
        }

        spritePointer = this->win0act->__InlineGetSolidSpriteFrameForAction(this->actFrame, 0);
        GameWindowLeftSidebar->RenderClippedSprite(0, spritePositionY, spritePointer, DrawLayer::Layer0xFFF6);

        spritePointer = this->win0act->__InlineGetSolidSpriteFrameForAction(this->actName, (*activeCharList)->characterId);
        GameWindowLeftSidebar->RenderClippedSprite(0, spritePositionY, spritePointer, DrawLayer::Layer0xFFF6);

        spritePointer = this->win0act->__InlineGetSolidSpriteFrameForAction(this->actLv, 0);
        GameWindowLeftSidebar->RenderClippedSprite(0, spritePositionY, spritePointer, DrawLayer::Layer0xFFF6);

        actIndex = (*activeCharList)->characterBaseStats->Level;
        if (0 < actIndex) {
          digitXPos = -0xde;
          do {
            spritePointer = this->win0act->__InlineGetSolidSpriteFrameForAction(this->actLvNum, actIndex % 10);
            GameWindowLeftSidebar->RenderClippedSprite(digitXPos, spritePositionY - 0xb1, spritePointer, DrawLayer::Layer0xFFF6);
            digitXPos = digitXPos + -6;
            actIndex = actIndex / 10;
          } while (0 < actIndex);
        }

        if (((*activeCharList)->charEquip).ActiveSlots[0].typeId != 0) {
          spritePointer = Item00Act->__InlineGetSolidSpriteFrameForAction(((*activeCharList)->charEquip).ActiveSlots[0].actOffset, 2);
          GameWindowLeftSidebar->RenderClippedSprite(0x7b, spritePositionY + 0x3f, spritePointer, DrawLayer::Layer0xFFF6);
        }

        if (((*activeCharList)->charEquip).ActiveSlots[1].typeId != 0) {
          spritePointer = Item00Act->__InlineGetSolidSpriteFrameForAction(((*activeCharList)->charEquip).ActiveSlots[1].actOffset, 2);
          GameWindowLeftSidebar->RenderClippedSprite(0x7b, spritePositionY + 0x54, spritePointer, DrawLayer::Layer0xFFF6);
        }

        actIndex = (*activeCharList)->characterBaseStats->CurrentHp + totalHpBonus;
        if (0 < actIndex) {
          loopCounter = actIndex * 0x10;
          spritePointer = this->win0act->__InlineGetSolidSpriteFrameForAction(this->actHp, (0x10U - ((loopCounter & ((loopCounter < 1) - 1)) / ((*activeCharList)->characterBaseStats->MaxHp + totalHpBonus))));
          GameWindowLeftSidebar->RenderClippedSprite(0, spritePositionY, spritePointer, DrawLayer::Layer0xFFF6);
        }

        actIndex = (*activeCharList)->characterBaseStats->CurrentMp + totalMpBonus;
        if (0 < actIndex) {
          loopCounter = actIndex * 0x10;
          spritePointer = this->win0act->__InlineGetSolidSpriteFrameForAction(this->actMp, (0x10U - ((loopCounter & ((loopCounter < 1) - 1)) / ((*activeCharList)->characterBaseStats->MaxMp + totalMpBonus))));
          GameWindowLeftSidebar->RenderClippedSprite(0, spritePositionY, spritePointer, DrawLayer::Layer0xFFF6);
        }

        loopCounter = (*activeCharList)->characterBaseStats->TimeGauge << 4;
        spritePointer = this->win0act->__InlineGetSolidSpriteFrameForAction(this->actTime, (((loopCounter < 1) - 1) & loopCounter) / 0x140);
        GameWindowLeftSidebar->RenderClippedSprite(0, spritePositionY, spritePointer, DrawLayer::Layer0xFFF6);

        coreAct = this->win0act;
        currentCharPtr = *activeCharList;
        actIndex = this->actFace;
        if (currentCharPtr->sceneClassUser->mainSceneHandler == this->currentlyActiveScene) {
          spritePointer = coreAct->__InlineGetSolidSpriteFrameForAction(actIndex, (currentCharPtr->characterId * 3));
        }
        else {
          spritePointer = coreAct->__InlineGetSolidSpriteFrameForAction(actIndex, (currentCharPtr->characterId * 3) + 2);
        }
        GameWindowLeftSidebar->RenderClippedSprite(0xd, spritePositionY + 0x29, spritePointer, DrawLayer::Layer0xFFF6);

        actIndex = 0;
        selectedUnitList = this->mainSceneHandler->selectedUnits32;
        unitWindowBase = *selectedUnitList;
        if (unitWindowBase != nullptr) {
          unitWindowList = selectedUnitList;
          do {
            if (unitWindowBase == (*activeCharList)->sceneClassUser) {
              break;
            }
            unitWindowBase = unitWindowList[1];
            unitWindowList = unitWindowList + 1;
            actIndex = actIndex + 1;
          } while (unitWindowBase != nullptr);
        }
        if (selectedUnitList[actIndex] != nullptr) {
          spritePointer = this->win0act->__InlineGetSolidSpriteFrameForAction(this->actSelect, 0);
          GameWindowLeftSidebar->RenderClippedSprite(0xb, spritePositionY + 0x27, spritePointer, DrawLayer::Layer0xFFF6);
        }
        activeCharList = activeCharList + 1;
      }
    }
    spritePositionY = spritePositionY + 0x3b;
  }

  textLineY = 0x1ab;
  stringCursor = &this->sidebarTextLine1[0];
  while (textLineY < 0x1cf) {
    if (*stringCursor != 0) {
      uint32_t textLength = strlen(stringCursor);
      this->PrintSidebarWindowText(0x4c - ((textLength - 1) * 0xb >> 1), textLineY, stringCursor);
    }
    textLineY = textLineY + 0xc;
    stringCursor = stringCursor + 0xb;
  }

  if (this->sidebarHighlight != nullptr) {
    GameWindowLeftSidebar->RenderClippedSprite(0, 0, this->sidebarHighlight, DrawLayer::Layer0xFFF6);
    return;
  }
}

__forceinline void GameWindowSidebar::SetActiveScene_0x7d07(intptr_t param_2) {
  this->currentlyActiveScene = (SceneHandler*)param_2;
}

__forceinline void GameWindowSidebar::DrawText_0x7d35(char* param_2) {
  int32_t lineCount;
  int32_t charIndex;
  int32_t baseYPos;
  int32_t adjustedPos;
  byte currentChar;

  this->sidebarTextLine3[0] = 0;
  this->sidebarTextLine2[0] = 0;
  this->sidebarTextLine1[0] = 0;
  if (param_2 != nullptr) {
    lineCount = 0;
    charIndex = 0;
    if (param_2 != nullptr) {
      baseYPos = 0;
      while (*param_2 != '\0' && baseYPos < 0x2c) {
        adjustedPos = baseYPos + charIndex;
        currentChar = *param_2;
        this->sidebarTextLine1[adjustedPos] = currentChar;
        if (currentChar == '|') {
          lineCount = lineCount + 1;
          baseYPos = baseYPos + 0xb;
          this->sidebarTextLine1[adjustedPos] = 0;
          charIndex = 0;
        }
        else {
          charIndex = charIndex + 1;
        }
        param_2 = param_2 + 1;
      }
    }
    this->sidebarTextLine1[charIndex + (lineCount * 0xb)] = 0;
    return;
  }
}

__forceinline void GameWindowSidebar::HandleMouseInput_0x7d0e(intptr_t param_2) {
  SHORT asyncKeyStateP;
  int16_t tempKeyState;
  int32_t clickPosY;
  int32_t clickPosX;
  int32_t slotCheckIndex;
  ActiveCharacter** characterSlotPtr;
  int32_t baseYCoord;
  uint32_t actionInputs[9];
  int32_t clickInputs[4];
  ActiveCharacter* activeSlotChar;

  actionInputs[0] = (uint32_t)InputStates128[InternalKey::InternalKey_1];
  actionInputs[1] = (uint32_t)InputStates128[InternalKey::InternalKey_2];
  actionInputs[2] = (uint32_t)InputStates128[InternalKey::InternalKey_3];
  actionInputs[3] = (uint32_t)InputStates128[InternalKey::InternalKey_4];
  actionInputs[4] = (uint32_t)InputStates128[InternalKey::InternalKey_5];
  actionInputs[5] = (uint32_t)InputStates128[InternalKey::InternalKey_F1];
  actionInputs[6] = (uint32_t)InputStates128[InternalKey::InternalKey_F2];
  actionInputs[7] = (uint32_t)InputStates128[InternalKey::InternalKey_F3];
  actionInputs[8] = (uint32_t)InputStates128[InternalKey::InternalKey_F4];

  clickInputs[0] = (int32_t)InputStates128[InternalKey::InternalKey_C];
  clickInputs[1] = (int32_t)InputStates128[InternalKey::InternalKey_I];
  clickInputs[2] = (int32_t)InputStates128[InternalKey::InternalKey_M];
  clickInputs[3] = (int32_t)InputStates128[InternalKey::InternalKey_W];

  asyncKeyStateP = GetAsyncKeyState(PauseVirtualKey);
  if (asyncKeyStateP != 0) {
    PixelCalculations_DirectDrawSurface(0x2e, 0x18);
    tempKeyState = GetAsyncKeyState(PauseVirtualKey);
    while (tempKeyState != 0) {
      tempKeyState = GetAsyncKeyState(PauseVirtualKey);
    }
    tempKeyState = GetAsyncKeyState(PauseVirtualKey);
    while ((tempKeyState == 0 && (asyncKeyStateP = GetAsyncKeyState(EscapeVirtualKey), asyncKeyStateP == 0))) {
      tempKeyState = GetAsyncKeyState(PauseVirtualKey);
    }
    tempKeyState = GetAsyncKeyState(PauseVirtualKey);
    while (tempKeyState != 0) {
      tempKeyState = GetAsyncKeyState(PauseVirtualKey);
    }
    tempKeyState = GetAsyncKeyState(EscapeVirtualKey);
    while (tempKeyState != 0) {
      tempKeyState = GetAsyncKeyState(EscapeVirtualKey);
    }
    PauseState = 2;
  }

  for (int32_t k = 0; k < 9; k++) {
    if (((actionInputs[k] & 1) == 1) && (((k < 5 || ((actionInputs[k] & 0x10) == 0)) && (this->currentlyActiveScene != nullptr)) && (this->currentlyActiveScene->mapType != MapType::World))) {
      this->mainSceneHandler->primarySwitchSingleParam_0x7d01(k, 0x0);
    }
  }

  for (int32_t j = 0; j < 4; j++) {
    if (((clickInputs[j] & 0x11) == 1) && ((&SidebarWindowClickBoxes[j] == &SidebarWindowClickBoxes[2] || (this->currentlyActiveScene == nullptr)) || (this->currentlyActiveScene->mapType != MapType::World))) {
      this->mainSceneHandler->primarySwitchSingleParam_0x7d14(SidebarWindowClickBoxes[j].switchCommand, 0x0);
    }
  }

  this->sidebarHighlight = nullptr;
  if (param_2 != 0) {
    clickPosX = CursorXCoord;
    clickPosY = CursorYCoord;
    for (int32_t i = 0; i < 4; i++) {
      if (((SidebarWindowClickBoxes[i].lowerX <= clickPosX) && (clickPosX <= SidebarWindowClickBoxes[i].upperX)) && (SidebarWindowClickBoxes[i].lowerY <= clickPosY && clickPosY <= SidebarWindowClickBoxes[i].upperY)) {
        this->sidebarHighlight = this->win0act->__InlineGetSolidSpriteFrameForAction(this->actButton, SidebarWindowClickBoxes[i].actionFrame);
        if (((MouseButtonClick & 0x11) == 1) && (&SidebarWindowClickBoxes[i] == &SidebarWindowClickBoxes[2] || (this->currentlyActiveScene == nullptr) || (this->currentlyActiveScene->mapType != MapType::World))) {
          this->mainSceneHandler->primarySwitchSingleParam_0x7d14(SidebarWindowClickBoxes[i].switchCommand, 0x0);
          clickPosX = CursorXCoord;
          clickPosY = CursorYCoord;
        }
      }
    }

    if ((MouseButtonClick & 0x11) == 1) {
      slotCheckIndex = 0;
      baseYCoord = Sidebar_UpperY_92;
      do {
        if (((Sidebar_LowerX_12 < clickPosX) && (clickPosX < Sidebar_UpperX_55)) && ((baseYCoord - (Sidebar_UpperY_92 - Sidebar_LowerY_40) < clickPosY && (clickPosY < baseYCoord && (this->currentlyActiveScene != nullptr))) && (this->currentlyActiveScene->mapType != MapType::World))) {
          this->mainSceneHandler->primarySwitchSingleParam_0x7d01(slotCheckIndex, 0x0);
          clickPosX = CursorXCoord;
          clickPosY = CursorYCoord;
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
          if ((Sidebar_LowerX_114 <= clickPosX) && (clickPosX <= Sidebar_UpperX_130)) {
            if ((slotCheckIndex - (Sidebar_UpperY_70 - Sidebar_LowerY_59) <= clickPosY) && (clickPosY <= slotCheckIndex)) {
              this->mainSceneHandler->primarySwitchSingleParam_0x7d01(baseYCoord, 0x0);
              (*characterSlotPtr)->sceneClassUser->primarySwitchSingleParam_0x7d1c(0x0, 0x0);
              clickPosX = CursorXCoord;
              clickPosY = CursorYCoord;
            }
            if ((slotCheckIndex + 8 <= clickPosY) && (clickPosY <= slotCheckIndex + 0x14)) {
              this->mainSceneHandler->primarySwitchSingleParam_0x7d01(baseYCoord, 0x0);
              (*characterSlotPtr)->sceneClassUser->primarySwitchSingleParam_0x7d1c(0x1, 0x0);
              clickPosX = CursorXCoord;
              clickPosY = CursorYCoord;
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
    this->InitializeObject_0x7d11(param_2);
    return;

  case 0x7d3b:
    this->DrawObject_0x7d3b();
    return;

  case 0x7d07:
    this->SetActiveScene_0x7d07(param_2);
    return;

  case 0x7d35:
    this->DrawText_0x7d35((char*)param_2);
    return;

  case 0x7d0e:
    this->HandleMouseInput_0x7d0e(param_2);
    break;
  }
}
