#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/CoreGameClass.hpp"
#include "HazardClasses/EventHandler.hpp"
#include "HazardClasses/GameOverWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowCharacter.hpp"
#include "HazardClasses/GameWindowDialogue.hpp"
#include "HazardClasses/GameWindowInventory.hpp"
#include "HazardClasses/GameWindowMenu.hpp"
#include "HazardClasses/GameWindowWeapon.hpp"
#include "HazardClasses/MusicObjectBase.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardClasses/SceneInstance.hpp"
#include "HazardClasses/SfxObject.hpp"
#include "HazardEnums/ItemGroup.hpp"
#include "HazardExterns/CoreGameClass.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActiveCharacter.hpp"
#include "HazardStructs/InventoryItemStruct.hpp"
#include "HazardStructs/ItemReferenceCollection.hpp"
#include "HazardStructs/ItemReferenceStruct.hpp"
#include "HazardStructs/ItemStatsTemplate.hpp"
#include "HazardStructs/SceneWrapper.hpp"
#include "HazardStructs/WindowReference.hpp"

__forceinline void CoreGameClass::SelectActiveTeamMember_0x7d01(int32_t innerSwitchParam) {
  int32_t slotIndex;
  ActiveCharacter** currentCharSlot;
  ActiveCharacter** currentTeamChar;
  GameWindowBase** selectedUnitPtr;
  GameWindowBase* selectedUnit;

  if (
      ((this->initializedGW0s[5].windowAddress == -1) && (this->initializedGW0s[6].windowAddress == -1)) &&
      (this->initializedGW0s[8].windowAddress == -1)) {
    if (innerSwitchParam < 5) {
      slotIndex = 0;
      currentTeamChar = TeamCharacterList;
      currentCharSlot = ActiveTeamCharacterSlots;
      do {
        if ((innerSwitchParam == slotIndex) && (*currentCharSlot == nullptr) && (*currentTeamChar != nullptr)) {
          (*currentTeamChar)->sceneClassUser->primarySwitchSingleParam_0x7d07((intptr_t)nullptr, 0x0);
        }
        if ((*currentCharSlot == nullptr) && (*currentTeamChar != nullptr)) {
          currentTeamChar = currentTeamChar + 1;
        }
        currentCharSlot = currentCharSlot + 1;
        slotIndex = slotIndex + 1;
      } while (slotIndex < 5);
    }
    else {
      selectedUnitPtr = this->selectedUnits32;
      selectedUnit = *selectedUnitPtr;
      if ((selectedUnit != nullptr) && (selectedUnitPtr[1] == nullptr)) {
        selectedUnit->primarySwitchSingleParam_0x7d1c((innerSwitchParam + -5), 0x0);
      }
    }
  }
}

__forceinline void CoreGameClass::CloseWindowAndSelectUnits_0x7d07(GameWindowBase* gameWindow, GameWindowBase** selectableUnits) {
  GameWindowBase** windowIterator;
  int32_t windowIndex;
  int32_t totalWindows;

  totalWindows = this->gameWindowsCounter;
  windowIndex = 0;
  if (0 < totalWindows) {
    windowIterator = this->gameWindowsArray;
    do {
      if (*windowIterator == gameWindow) {
        this->__InlineQueueEvent(windowIndex);
        this->__InlineQueueEvent(0x7d01);
        this->selectedUnits32 = selectableUnits;
        return;
      }
      windowIndex = windowIndex + 1;
      windowIterator = windowIterator + 1;
    } while (windowIndex < totalWindows);
  }
}

__forceinline void CoreGameClass::PlaySoundEffect_0x7d0a(int32_t innerSwitchParam) {
  if (((0 <= innerSwitchParam) && (innerSwitchParam <= 100)) && (ListOfSfxBuffers[innerSwitchParam] != (LPDIRECTSOUNDBUFFER) nullptr)) {
    PtrSfxObject->RunPlay(ListOfSfxBuffers[innerSwitchParam], 0xff, 0x80);
  }
}

__forceinline void CoreGameClass::PrepareSoundtrack_0x7d0b(int32_t innerSwitchParam) {
  if ((0 <= innerSwitchParam) && (this->currentMusicIndex != innerSwitchParam)) {
    this->currentMusicIndex = innerSwitchParam;
    this->float_600000 = 0.0;
  }
}

__forceinline void CoreGameClass::CancelOrCloseWindow_0x7d0c(GameWindowBase* param_2) {

  int32_t windowIndex;
  int32_t totalWindows;
  SceneWrapper* sceneWrapperIterator;
  int32_t sceneIndex;

  totalWindows = this->gameWindowsCounter;
  for (windowIndex = 0; windowIndex < totalWindows; windowIndex++) {
    if (this->gameWindowsArray[windowIndex] == param_2) {
      this->__InlineQueueEvent(windowIndex);
      this->__InlineQueueEvent(0x7d00);
      break;
    }
  }
  sceneWrapperIterator = this->activeAndCachedScenes;
  for (sceneIndex = 0; sceneIndex < 12; ++sceneIndex) {
    SceneHandler* sceneHandlerPtr = sceneWrapperIterator->sceneInstance;
    if (sceneHandlerPtr != nullptr) {

      if (sceneHandlerPtr == param_2) {
        sceneWrapperIterator->sceneInstance = nullptr;
      }
    }
    sceneWrapperIterator++;
  }
}

__forceinline void CoreGameClass::RemoveGameWindow_0x7d10(GameWindowBase* param_2) {
  GameWindowBase** windowSlots;
  int32_t windowIndex;

  windowIndex = 0;
  if (0 < this->gameWindowsCounter) {
    do {
      windowSlots = &this->gameWindowsArray[windowIndex];
      if (*windowSlots == param_2) {
        *windowSlots = nullptr;
      }
      windowIndex = windowIndex + 1;
    } while (windowIndex < this->gameWindowsCounter);
  }
}

__forceinline void CoreGameClass::ToggleGameWindow_0x7d14(intptr_t param_2, intptr_t param_3) {
  GameWindowCharacter* characterWindow;
  GameWindowWeapon* weaponWindow;
  GameWindowInventory* inventoryWindow;
  GameWindowMenu* menuWindow;
  GameWindowBase* targetWindow;
  int32_t savedWindowIndex;
  GameWindowBase* windowBase;
  int32_t totalWindows;
  int32_t storedWindowRef;
  int32_t* refMacroIterator;
  int32_t innerSwitchParam = (int32_t)param_2;

  if (param_2 == 0) {
    this->toggleableWindows[param_3] = -1;
    return;
  }
  storedWindowRef = this->toggleableWindows[innerSwitchParam];
  if (storedWindowRef == -1) {
    switch (innerSwitchParam) {
    case 1:
      if (((this->initializedGW0s[5].windowAddress == -1) && (this->initializedGW0s[6].windowAddress == -1)) && (this->initializedGW0s[8].windowAddress == -1 && (this->initializedGW0s[7].windowAddress == -1))) {
        characterWindow = new GameWindowCharacter();
        storedWindowRef = this->StoreAndInitializeObject(characterWindow);
        this->toggleableWindows[1] = storedWindowRef;
      }
      break;
    case 2:
      if (((this->initializedGW0s[5].windowAddress == -1) && (this->initializedGW0s[6].windowAddress == -1)) && (this->initializedGW0s[8].windowAddress == -1 && (this->initializedGW0s[7].windowAddress == -1))) {
        weaponWindow = new GameWindowWeapon();
        storedWindowRef = this->StoreAndInitializeObject(weaponWindow);
        this->toggleableWindows[2] = storedWindowRef;
      }
      break;
    case 3:
      if (((this->initializedGW0s[6].windowAddress == -1) && (this->initializedGW0s[8].windowAddress == -1)) && (this->initializedGW0s[7].windowAddress == -1)) {
        inventoryWindow = new GameWindowInventory();
        storedWindowRef = this->StoreAndInitializeObject(inventoryWindow);
        this->toggleableWindows[3] = storedWindowRef;
      }
      break;
    case 4:
      refMacroIterator = this->toggleableWindows;
      totalWindows = 3;
      do {
        if (*refMacroIterator != -1) {
          targetWindow = this->gameWindowsArray[*refMacroIterator];
          targetWindow->primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(nullptr, 0x0);
        }
        refMacroIterator = refMacroIterator + 1;
        totalWindows = totalWindows + -1;
      } while (totalWindows != 0);
      break;
    case 6:
      savedWindowIndex = this->initializedGW0s[8].windowAddress;
      if (savedWindowIndex != -1) {
        totalWindows = 0x7d0c;
        targetWindow = this->gameWindowsArray[savedWindowIndex];
        windowBase = targetWindow;
        windowBase->primarySwitchSingleParam(totalWindows, 0x0, 0x0);
        this->primarySwitchSingleParam_PlaySoundEffect_0x7d0a(0x1d, nullptr);
        return;
      }
      refMacroIterator = this->toggleableWindows;
      totalWindows = 3;
      do {
        if (*refMacroIterator != -1) {
          targetWindow = this->gameWindowsArray[*refMacroIterator];
          targetWindow->primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(nullptr, 0x0);
        }
        refMacroIterator = refMacroIterator + 1;
        totalWindows = totalWindows + -1;
      } while (totalWindows != 0);
      menuWindow = new GameWindowMenu();

      targetWindow = menuWindow;
      this->StoreAndInitializeObject(targetWindow);
    }
  }
  else {
    if (this->initializedGW0s[5].windowAddress != -1) {
      return;
    }
    if (this->initializedGW0s[6].windowAddress != -1) {
      return;
    }
    if (this->initializedGW0s[8].windowAddress != -1) {
      return;
    }
    totalWindows = 0x7d20;
    targetWindow = this->gameWindowsArray[storedWindowRef];
    windowBase = targetWindow;

    windowBase->primarySwitchSingleParam(totalWindows, 0x0, 0x0);
  }
  this->primarySwitchSingleParam_PlaySoundEffect_0x7d0a(0x1d, nullptr);
}

__forceinline void CoreGameClass::SetWindow_0x7d16(int32_t windowRelatedIndex, WindowReference* windowReference) {

  int32_t maxWindows;
  int32_t windowScanIndex;

  this->initializedGW0s[windowRelatedIndex].windowAddress = -1;
  if (windowReference != nullptr) {
    this->initializedGW0s[windowRelatedIndex].coords[0] = windowReference->coords[0];
    this->initializedGW0s[windowRelatedIndex].coords[1] = windowReference->coords[1];
    this->initializedGW0s[windowRelatedIndex].coords[2] = windowReference->coords[2];
    this->initializedGW0s[windowRelatedIndex].coords[3] = windowReference->coords[3];

    maxWindows = this->gameWindowsCounter;

    for (windowScanIndex = 0; windowScanIndex < maxWindows; windowScanIndex++) {
      if ((intptr_t)this->gameWindowsArray[windowScanIndex] == windowReference->windowAddress) {
        this->initializedGW0s[windowRelatedIndex].windowAddress = windowScanIndex;
        return;
      }
    }
  }
}

__forceinline void CoreGameClass::SetCursorSprite_0x7d17(intptr_t param_2, intptr_t param_3) {
  int32_t* sceneCounterPtr;
  int32_t innerSwitchParam = (int32_t)param_2;

  if ((innerSwitchParam < 20) && (&this->frameNormal)[innerSwitchParam] != -1) {
    if (param_3 != 0x0) {
      sceneCounterPtr = &this->callSceneCounter;
      *sceneCounterPtr = *sceneCounterPtr + -1;
    }

    this->cursorSprite = this->actCursor->__InlineGetSolidSpriteFrameForAction((&this->frameNormal)[innerSwitchParam], this->callSceneCounter);
  }
}

__forceinline void CoreGameClass::OpenDialogueWindow_0x7d18(int32_t innerSwitchParam, GameWindowBase* param_3) {
  GameWindowDialogue* dialogueWindow;
  GameWindowBase* targetWindow;
  int32_t counter;
  int32_t* refMacroIterator;

  refMacroIterator = this->toggleableWindows;
  counter = 3;
  do {
    if (*refMacroIterator != -1) {
      targetWindow = this->gameWindowsArray[*refMacroIterator];
      targetWindow->primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(nullptr, 0x0);
    }
    refMacroIterator = refMacroIterator + 1;
    counter = counter + -1;
  } while (counter != 0);
  dialogueWindow = new GameWindowDialogue(innerSwitchParam, param_3);
  this->StoreAndInitializeObject(dialogueWindow);
}

__forceinline void CoreGameClass::SetRunTickSwitchResult_0x7d1d(int32_t innerSwitchParam) {
  this->RunTickSwitchIntegerResult = innerSwitchParam + 1;
}

__forceinline void CoreGameClass::SetCameraPosition_0x7d21(int32_t coord1, int32_t coord2) {
  int32_t windowIndex;
  CoreGameClass* mapController;

  windowIndex = this->initializedGW0s[0].windowAddress;
  if (windowIndex != -1) {
    mapController = (CoreGameClass*)this->gameWindowsArray[windowIndex];
    mapController->sceneCamera->primarySwitchSingleParam_SetCameraPosition_0x7d21((coord1 % (mapController->mapWidth + -0x20)) + 0x10, ((coord2 % (mapController->mapHeight + -0x20)) + 0x10));
  }
}

__forceinline void CoreGameClass::ResetRngAndAsyncKeys_0x7d25() {
  ResetRngAndAsyncKeys();
}

__forceinline void CoreGameClass::TriggerObjectInitialization_0x7d27(GameWindowBase* param_2) {
  this->StoreAndInitializeObject(param_2);
}

__forceinline void CoreGameClass::RegisterSceneInstance_0x7d28(SceneHandler* param_2, char* param3AsSceneName) {
  int32_t nextFreeSlot;
  int32_t sceneIndex;

  for (sceneIndex = 0; sceneIndex < 12; ++sceneIndex) {
    if (strcmp(this->activeAndCachedScenes[sceneIndex].sceneName, param3AsSceneName) == 0) {
      this->activeAndCachedScenes[sceneIndex].sceneInstance = nullptr;
    }
  }

  nextFreeSlot = 0;
  while (this->activeAndCachedScenes[nextFreeSlot].sceneInstance != nullptr) {
    nextFreeSlot = nextFreeSlot + 1;
  }

  strcpy(this->activeAndCachedScenes[nextFreeSlot].sceneName, param3AsSceneName);
  this->activeAndCachedScenes[nextFreeSlot].sceneInstance = param_2;
}

__forceinline void CoreGameClass::ResolveItemConflict_0x7d2c(int32_t switchParameter, intptr_t param_2, intptr_t param_3) {
  SceneHandler::primarySwitchSingleParam(switchParameter, param_2, param_3);
}

__forceinline void CoreGameClass::PlaceInEitherWindow_0x7d2e(InventoryItemStruct* param_2) {
  WindowReference* currentWindowRef;
  GameWindowBase* targetWindow;
  int32_t windowIndex;

  windowIndex = 4;
  currentWindowRef = this->initializedGW0s + 4;
  do {
    if ((currentWindowRef->windowAddress != -1) && (currentWindowRef->coords[0] <= CursorXCoord) && (CursorXCoord <= currentWindowRef->coords[2]) && (currentWindowRef->coords[1] <= CursorYCoord) && (CursorYCoord <= currentWindowRef->coords[3])) {
      targetWindow = this->gameWindowsArray[this->initializedGW0s[windowIndex].windowAddress];
      targetWindow->primarySwitchSingleParam_0x7d2e(param_2, 0x0);
      return;
    }
    windowIndex = windowIndex + -1;
    currentWindowRef = currentWindowRef + -1;
  } while (windowIndex >= 0);
}

__forceinline void CoreGameClass::SetLoadingMarkerCount_0x7d31(int32_t innerSwitchParam) {
  this->counterDrawObjects = innerSwitchParam;
}

__forceinline void CoreGameClass::DrawText_0x7d35(int32_t switchParameter, intptr_t param_2, intptr_t param_3) {
  GameWindowBase* targetWindow;
  int32_t windowAddress;

  if (param_3 == 0x1) {
    windowAddress = this->initializedGW0s[1].windowAddress;
    if (windowAddress != -1) {
      targetWindow = this->gameWindowsArray[windowAddress];
      targetWindow->primarySwitchSingleParam(switchParameter, param_2, 0x1);
    }
  }
  else if ((param_3 == 2) && (windowAddress = this->initializedGW0s[4].windowAddress, windowAddress != -1)) {
    targetWindow = this->gameWindowsArray[windowAddress];
    targetWindow->primarySwitchSingleParam(switchParameter, param_2, 0x2);
  }
}

__forceinline void CoreGameClass::GenerateItemStats_0x7d37(int32_t itemTypeId, InventoryItemStruct* itemStruct) {
  uint32_t filteredEquipFlags;
  uint32_t randomValue;
  int32_t statVariation;
  int32_t statIndex;
  ItemStatsTemplate* itemStats;
  int32_t* primaryStatPtr;
  int32_t* sourcePrimaryStatPtr;
  int32_t* secondaryStatPtr;
  int32_t* sourceSecondaryStatPtr;
  int32_t basePrimaryStat;
  int32_t statStep;

  if (0 < itemTypeId) {
    itemStats = ItemStruct12k->itemArray[itemTypeId].stats;
    filteredEquipFlags = ItemStruct12k->itemArray[itemTypeId].equipFlags;
    itemStruct->quantity = 0x1;
    itemStruct->typeId = itemTypeId;
    itemStruct->equipFlags = ItemStruct12k->itemArray[itemTypeId].equipFlags;
    itemStruct->actOffset = ItemStruct12k->itemArray[itemTypeId].actOffset;
    for (statIndex = 0; statIndex < 0xf; statIndex++) {
      (&itemStruct->itemGroup)[statIndex] = 0;
    }

    if (itemStats->itemGroup == ItemGroup::HoldableItem) {
      filteredEquipFlags = filteredEquipFlags & 0x700;
      primaryStatPtr = &itemStruct->aParameter;
      secondaryStatPtr = &itemStruct->bParameter;
      sourcePrimaryStatPtr = &itemStats->aParameter;
      sourceSecondaryStatPtr = &itemStats->bParameter;
      statIndex = 1;
      do {
        statStep = 1;
        if (
            (((
                  (filteredEquipFlags == 0x100 && (statIndex == 1 || (statIndex == 3))) ||
                  (filteredEquipFlags == 0x200 && (((statIndex == 1 || (statIndex == 3)) || (statIndex == 5)) || (statIndex == 7)))) ||
              (filteredEquipFlags == 0x300 && (statIndex == 1 || (statIndex == 3)))) ||
             (filteredEquipFlags == 0x500 && (statIndex == 8 || (statIndex == 10)))) &&
            (itemTypeId < 174)) {
          basePrimaryStat = *sourcePrimaryStatPtr;
          randomValue = PseudoRng();
          statVariation = (int32_t)randomValue % (*sourceSecondaryStatPtr - basePrimaryStat + 1);
          *secondaryStatPtr = (basePrimaryStat + statVariation) * 100;
          if (statVariation != 0) {
            randomValue = PseudoRng();
            statVariation = (int32_t)randomValue % statVariation;
          }
          else {
            statVariation = 0;
          }
          *primaryStatPtr = ((basePrimaryStat + statVariation) * 100);
          statIndex = statIndex + 2;
          statStep = 2;
        }
        else {
          statIndex = statIndex + 1;
          *primaryStatPtr = *sourcePrimaryStatPtr;
        }

        sourceSecondaryStatPtr = sourceSecondaryStatPtr + statStep;
        secondaryStatPtr = secondaryStatPtr + statStep;
        sourcePrimaryStatPtr = sourcePrimaryStatPtr + statStep;
        primaryStatPtr = primaryStatPtr + statStep;
      } while (statIndex <= 0xe);
    }
  }
}

void CoreGameClass::primarySwitchSingleParam(int32_t switchParameter, intptr_t param_2, intptr_t param_3) {

  GameOverWindow* gameOverWindow;
  GameWindowBase* targetWindow;
  int32_t counter;
  int32_t windowSwitchParam;
  int32_t* refMacroIterator;
  GameWindowCharacter* characterWindow;
  GameWindowWeapon* weaponWindow;
  GameWindowInventory* inventoryWindow;
  GameWindowMenu* menuWindow;
  int32_t savedWindowIndex;
  GameWindowBase* windowBase;
  int32_t storedWindowRef;
  int32_t innerSwitchParam = (int32_t)param_2;
  int32_t sceneIndex;
  SceneHandler* foundSceneHandler;
  GameWindowDialogue* dialogueWindow;

  while (true) {
    switch (switchParameter) {
    case 0x7d07:
      this->CloseWindowAndSelectUnits_0x7d07((GameWindowBase*)param_2, (GameWindowBase**)param_3);
      break;

    case 0x7d21:
      this->SetCameraPosition_0x7d21(param_2, param_3);
      break;

    case 0x7d01:
      this->SelectActiveTeamMember_0x7d01(param_2);
      break;

    case 0x7d37:
      this->GenerateItemStats_0x7d37(param_2, (InventoryItemStruct*)param_3);
      break;

    case 0x7d31:
      this->SetLoadingMarkerCount_0x7d31(param_2);
      break;

    case 0x7d17:
      this->SetCursorSprite_0x7d17(param_2, param_3);
      break;

    case 0x7d14: {
      if (param_2 == 0) {
        this->toggleableWindows[param_3] = -1;
        return;
      }
      storedWindowRef = this->toggleableWindows[innerSwitchParam];
      if (storedWindowRef == -1) {
        switch (innerSwitchParam) {
        case 1:
          if (((this->initializedGW0s[5].windowAddress == -1) && (this->initializedGW0s[6].windowAddress == -1)) && (this->initializedGW0s[8].windowAddress == -1 && (this->initializedGW0s[7].windowAddress == -1))) {
            characterWindow = new GameWindowCharacter();
            storedWindowRef = SceneHandler::StoreAndInitializeObject(characterWindow);
            this->toggleableWindows[1] = storedWindowRef;
          }
          break;
        case 2:
          if (((this->initializedGW0s[5].windowAddress == -1) && (this->initializedGW0s[6].windowAddress == -1)) && (this->initializedGW0s[8].windowAddress == -1 && (this->initializedGW0s[7].windowAddress == -1))) {
            weaponWindow = new GameWindowWeapon();
            storedWindowRef = SceneHandler::StoreAndInitializeObject(weaponWindow);
            this->toggleableWindows[2] = storedWindowRef;
          }
          break;
        case 3:
          if (((this->initializedGW0s[6].windowAddress == -1) && (this->initializedGW0s[8].windowAddress == -1)) && (this->initializedGW0s[7].windowAddress == -1)) {
            inventoryWindow = new GameWindowInventory();
            storedWindowRef = SceneHandler::StoreAndInitializeObject(inventoryWindow);
            this->toggleableWindows[3] = storedWindowRef;
          }
          break;
        case 4:
          refMacroIterator = this->toggleableWindows + 1;
          counter = 3;
          do {
            if (*refMacroIterator != -1) {
              targetWindow = this->gameWindowsArray[*refMacroIterator];
              targetWindow->primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(nullptr, 0x0);
            }
            refMacroIterator = refMacroIterator + 1;
            counter = counter + -1;
          } while (counter != 0);
          break;
        case 6:
          savedWindowIndex = this->initializedGW0s[8].windowAddress;
          if (savedWindowIndex != -1) {
            windowSwitchParam = 0x7d0c;
            targetWindow = this->gameWindowsArray[savedWindowIndex];
            windowBase = targetWindow;
            windowBase->primarySwitchSingleParam(windowSwitchParam, 0x0, 0x0);
            this->primarySwitchSingleParam_PlaySoundEffect_0x7d0a(0x1d, nullptr);
            return;
          }
          refMacroIterator = this->toggleableWindows + 1;
          counter = 3;
          do {
            if (*refMacroIterator != -1) {
              targetWindow = this->gameWindowsArray[*refMacroIterator];
              targetWindow->primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(nullptr, 0x0);
            }
            refMacroIterator = refMacroIterator + 1;
            counter = counter + -1;
          } while (counter != 0);
          menuWindow = new GameWindowMenu();

          targetWindow = menuWindow;
          this->StoreAndInitializeObject(targetWindow);
        }
      }
      else {
        if (this->initializedGW0s[5].windowAddress != -1) {
          return;
        }
        if (this->initializedGW0s[6].windowAddress != -1) {
          return;
        }
        if (this->initializedGW0s[8].windowAddress != -1) {
          return;
        }
        windowSwitchParam = 0x7d20;
        targetWindow = this->gameWindowsArray[storedWindowRef];
        windowBase = targetWindow;

        windowBase->primarySwitchSingleParam(windowSwitchParam, 0x0, 0x0);
      }
      this->primarySwitchSingleParam_PlaySoundEffect_0x7d0a(0x1d, nullptr);
      break;
    }

    case 0x7d16:
      this->initializedGW0s[innerSwitchParam].windowAddress = -1;
      if ((WindowReference*)param_3 != nullptr) {
        this->initializedGW0s[innerSwitchParam].coords[0] = ((WindowReference*)param_3)->coords[0];
        this->initializedGW0s[innerSwitchParam].coords[1] = ((WindowReference*)param_3)->coords[1];
        this->initializedGW0s[innerSwitchParam].coords[2] = ((WindowReference*)param_3)->coords[2];
        this->initializedGW0s[innerSwitchParam].coords[3] = ((WindowReference*)param_3)->coords[3];
        counter = this->gameWindowsCounter;
        for (sceneIndex = 0; sceneIndex < counter; sceneIndex++) {
          if ((intptr_t)this->gameWindowsArray[sceneIndex] == ((WindowReference*)param_3)->windowAddress) {
            this->initializedGW0s[innerSwitchParam].windowAddress = sceneIndex;
            break;
          }
        }
      }
      break;

    case 0x7d18:

      refMacroIterator = this->toggleableWindows + 1;
      counter = 3;
      do {
        if (*refMacroIterator != -1) {
          targetWindow = this->gameWindowsArray[*refMacroIterator];
          targetWindow->primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(nullptr, 0x0);
        }
        refMacroIterator = refMacroIterator + 1;
        counter = counter + -1;
      } while (counter != 0);
      dialogueWindow = new GameWindowDialogue((int32_t)param_2, (GameWindowBase*)param_3);
      this->StoreAndInitializeObject(dialogueWindow);
      break;

    case 0x7d0b:
      this->PrepareSoundtrack_0x7d0b((int32_t)param_2);
      break;

    case 0x7d10:
      this->RemoveGameWindow_0x7d10((GameWindowBase*)param_2);
      break;

    case 0x7d2c:
      this->ResolveItemConflict_0x7d2c(switchParameter, param_2, param_3);
      break;

    case 0x7d0c:
      this->CancelOrCloseWindow_0x7d0c((GameWindowBase*)param_2);
      break;

    case 0x7d0a:
      this->PlaySoundEffect_0x7d0a((int32_t)param_2);
      break;

    case 0x7d39:

      refMacroIterator = this->toggleableWindows + 1;
      counter = 3;
      do {
        if (*refMacroIterator != -1) {
          targetWindow = this->gameWindowsArray[*refMacroIterator];
          targetWindow->primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(nullptr, 0x0);
        }
        refMacroIterator = refMacroIterator + 1;
        counter = counter + -1;
      } while (counter != 0);
      gameOverWindow = new GameOverWindow();
      this->StoreAndInitializeObject(gameOverWindow);

      break;

    case 0x7d28:
      for (sceneIndex = 0; sceneIndex < 12; ++sceneIndex) {
        if ((this->activeAndCachedScenes[sceneIndex].sceneInstance != nullptr) && (strcmp(this->activeAndCachedScenes[sceneIndex].sceneName, (char*)param_3) == 0)) {
          this->activeAndCachedScenes[sceneIndex].sceneInstance = nullptr;
        }
      }
      sceneIndex = 0;
      while (this->activeAndCachedScenes[sceneIndex].sceneInstance != nullptr) {
        sceneIndex = sceneIndex + 1;
      }
      strcpy(this->activeAndCachedScenes[sceneIndex].sceneName, (char*)param_3);
      this->activeAndCachedScenes[sceneIndex].sceneInstance = (SceneHandler*)param_2;
      break;

    case 0x7d2e:
      this->PlaceInEitherWindow_0x7d2e((InventoryItemStruct*)param_2);
      break;

    case 0x7d08:

      foundSceneHandler = nullptr;
      for (sceneIndex = 0; sceneIndex < 12; ++sceneIndex) {
        if (this->activeAndCachedScenes[sceneIndex].sceneInstance != nullptr) {
          if (strcmp(this->activeAndCachedScenes[sceneIndex].sceneName, (char*)param_2) == 0) {
            foundSceneHandler = this->activeAndCachedScenes[sceneIndex].sceneInstance;
          }
        }
      }

      if (foundSceneHandler == nullptr) {
        foundSceneHandler = new SceneInstance((char*)param_2);
        this->StoreAndInitializeObject(foundSceneHandler);
      }

      if (param_3 != 0x0) {
        *(SceneHandler**)param_3 = foundSceneHandler;
      }
      break;

    case 0x7d27:
      this->TriggerObjectInitialization_0x7d27((GameWindowBase*)param_2);
      break;

    case 0x7d25:
      this->ResetRngAndAsyncKeys_0x7d25();
      break;

    case 0x7d35:
      this->DrawText_0x7d35(switchParameter, param_2, param_3);
      break;

    case 0x7d1d:
      this->SetRunTickSwitchResult_0x7d1d((int32_t)param_2);
      break;

    default:
      WrapperMessageBoxA(s_Wrong_Command, s_Error_in_cFRAME);
      break;
    }
    break;
  }
}
