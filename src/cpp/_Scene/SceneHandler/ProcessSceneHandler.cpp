#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/EventHandler.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneClassCamera.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneClassCommand.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardClasses/SfxObject.hpp"
#include "HazardEnums/ItemFlag.hpp"
#include "HazardEnums/MapType.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActiveCharacter.hpp"
#include "HazardStructs/InventoryItemStruct.hpp"
#include "HazardStructs/ItemReferenceCollection.hpp"
#include "HazardStructs/ItemReferenceStruct.hpp"
#include "HazardStructs/QueueEventContainer.hpp"

__forceinline void SceneHandler::Case_0x7d11(intptr_t param_1) {
  this->mainSceneHandler = (SceneHandler*)param_1;
}

__forceinline void SceneHandler::Case_0x7d3b() {

  SceneClassCameraBase* cameraBase;
  int32_t cameraOffsetY;
  int32_t loopIndexY;
  int32_t cameraOffsetX;
  int32_t loopIndexX;
  GameWindowBase* sceneObject;

  cameraBase = this->sceneCamera;
  if (cameraBase != nullptr) {
    cameraOffsetY = cameraBase->cameraCoordX - 0x80;
    cameraOffsetX = cameraOffsetY > 0 ? cameraOffsetY : 0;

    cameraOffsetY = cameraBase->cameraCoordY - 0x80;
    loopIndexX = cameraOffsetY > 0 ? cameraOffsetY : 0;

    for (sceneObject = this->currentObject; sceneObject != nullptr; sceneObject = sceneObject->previousObject) {
      sceneObject->primarySwitchSingleParam(0x7d3b, 0x0, 0x0);
    }

    cameraBase = this->sceneCamera;

    for (; loopIndexX <= cameraBase->cameraCoordY + 0x360; loopIndexX = loopIndexX + 0x100) {

      loopIndexY = cameraOffsetX;
      for (loopIndexY = cameraOffsetX; loopIndexY <= this->sceneCamera->cameraCoordX + 0x36f; loopIndexY = loopIndexY + 0x100) {

        for (sceneObject = this->matrix_128x128[(loopIndexX >> 8 & 0x7fU)][(loopIndexY >> 8 & 0x7fU)]; sceneObject != nullptr; sceneObject = sceneObject->previousObject) {
          sceneObject->primarySwitchSingleParam(0x7d3b, 0x0, 0x0);
        }
      }

      cameraBase = this->sceneCamera;
    }
    return;
  }
}

__forceinline void SceneHandler::Case_0x7d3c(intptr_t param_1) {
  SceneHandler* sceneHandler;
  int32_t localCounter;
  int32_t eventType;
  intptr_t eventValue2;
  GameWindowBase* gameWindow;
  intptr_t eventValue1;
  ActiveCharacter** character;
  GameWindowBase* sceneClassUser;

  while (eventType = this->eventCounter, 0 < eventType) {
    localCounter = eventType - 1;
    this->eventCounter = localCounter;
    eventType = this->queuedEventsArray[localCounter >> 8]->queueEvents[localCounter & 0xff];

    switch (eventType) {
    case 0:
      goto label_exit;

    case 0x7d00: {
      eventType = this->eventCounter;
      if (eventType > 0) {
        localCounter = eventType - 1;
        this->eventCounter = localCounter;
        eventType = this->queuedEventsArray[localCounter >> 8]->queueEvents[localCounter & 0xff];
      }
      else {
        eventType = 0;
      }
      gameWindow = this->gameWindowsArray[eventType];
      if (gameWindow != nullptr) {
        delete gameWindow;
      }
    } break;

    case 0x7d02: {
      eventType = this->eventCounter;
      if (eventType > 0) {
        localCounter = eventType - 1;
        this->eventCounter = localCounter;
        eventValue1 = this->queuedEventsArray[localCounter >> 8]->queueEvents[localCounter & 0xff];
      }
      else {
        eventValue1 = 0x0;
      }
      eventType = this->eventCounter;
      if (eventType > 0) {
        localCounter = eventType - 1;
        this->eventCounter = localCounter;
        eventValue2 = this->queuedEventsArray[localCounter >> 8]->queueEvents[localCounter & 0xff];
      }
      else {
        eventValue2 = 0x0;
      }
      this->mainSceneHandler->primarySwitchSingleParam(0x7d18, eventValue1, (intptr_t)(GameWindowBase*)eventValue2);
    } break;

    case 0x7d03:
      if ((this->mapType == MapType::World) && (TeamCharacterList[0] != nullptr)) {
        character = TeamCharacterList;
        while (*character != nullptr) {
          sceneClassUser = (*character)->shiftedSceneClassUser0x48;
          sceneHandler = sceneClassUser->mainSceneHandler;
          sceneClassUser->primarySwitchSingleParam_PrepareMapForUnit_0x7d12(0x0, 0x0);
          if (sceneHandler != this) {
            sceneHandler->primarySwitchSingleParam(0x7d0d, 0x0, 0x0);
          }
          character = character + 1;
        }
      }
      break;
    }
  }
label_exit:

  eventType = 0;
  while (eventType < this->gameWindowsCounter) {
    gameWindow = this->gameWindowsArray[eventType];
    if (gameWindow != nullptr) {
      gameWindow->primarySwitchSingleParam(0x7d3c, param_1, 0x0);
    }
    eventType = eventType + 1;
  }
}

__forceinline void SceneHandler::Case_0x7d0e(int32_t switchConstant, intptr_t param_1, intptr_t param_2) {
  GameWindowBase* sceneClassCommand;

  sceneClassCommand = this->sceneClassCommand;
  if (sceneClassCommand != nullptr) {
    sceneClassCommand->primarySwitchSingleParam(switchConstant, param_1, param_2);
    return;
  }
}

__forceinline void SceneHandler::Case_0x7d2b(intptr_t param_1) {
  int32_t itemFlags;
  int32_t inventoryIndex;
  GameWindowBase* sceneObject;

  itemFlags = ItemStruct12k->itemArray[param_1].equipFlags;
  if ((itemFlags & ItemFlag::Unknown_2) != 0) {
    for (inventoryIndex = 0; inventoryIndex < 32; inventoryIndex++) {
      if (((ItemInventory[inventoryIndex].typeId == param_1) && (0 < ItemInventory[inventoryIndex].quantity)) && (ItemInventory[inventoryIndex].quantity < 9)) {
        ItemInventory[inventoryIndex].quantity = ItemInventory[inventoryIndex].quantity + 1;
        return;
      }
    }
  }

  if ((itemFlags & 0x20) == 0x20) {
    for (inventoryIndex = 20; inventoryIndex < 32; inventoryIndex++) {
      if (ItemInventory[inventoryIndex].quantity == 0) {
        break;
      }
    }
  }
  else {
    for (inventoryIndex = 0; inventoryIndex < 19; inventoryIndex++) {
      if (ItemInventory[inventoryIndex].quantity == 0) {
        break;
      }
    }
  }

  if ((inventoryIndex != 0x13) && (inventoryIndex != 0x20)) {

    this->mainSceneHandler->primarySwitchSingleParam(0x7d37, param_1, (intptr_t)(ItemInventory + inventoryIndex));
    return;
  }
  sceneObject = *this->selectedUnits32;
  if (sceneObject != nullptr) {
    sceneObject->primarySwitchSingleParam_0x7d2e((InventoryItemStruct*)param_1, 0x0);
    return;
  }
}

__forceinline void SceneHandler::Case_0x7d2c(intptr_t param_1) {
  int32_t equipFlags;
  int32_t inventoryIndex;
  InventoryItemStruct* itemStruct;

  itemStruct = (InventoryItemStruct*)param_1;
  equipFlags = itemStruct->equipFlags;

  if ((equipFlags & ItemFlag::Scene_0x20) == 0) {

    for (inventoryIndex = 0; inventoryIndex < 20; inventoryIndex++) {
      if (
          (ItemInventory[inventoryIndex].quantity == 0) ||
          ((ItemInventory[inventoryIndex].typeId == itemStruct->typeId && ((equipFlags & ItemFlag::Unknown_2) != 0)) && (itemStruct->quantity + ItemInventory[inventoryIndex].quantity) <= 9)) {
        if (ItemInventory[inventoryIndex].quantity == 0) {
          memcpy(ItemInventory + inventoryIndex, (void*)param_1, sizeof(InventoryItemStruct));
        }
        else {
          ItemInventory[inventoryIndex].quantity = itemStruct->quantity + ItemInventory[inventoryIndex].quantity;
        }
        itemStruct->quantity = 0x0;
        break;
      }
    }

    if (inventoryIndex < 20) {
      return;
    }

    if (*this->selectedUnits32 == nullptr) {
      return;
    }

    (*this->selectedUnits32)->primarySwitchSingleParam(0x7d2e, (intptr_t)itemStruct->typeId, 0x0);
    itemStruct->quantity = 0x0;
    return;
  }

  for (inventoryIndex = 20; inventoryIndex < 32; inventoryIndex++) {
    if ((ItemInventory[inventoryIndex].quantity == 0 || ((ItemInventory[inventoryIndex].typeId == itemStruct->typeId && ((equipFlags & 2) != 0)) && (itemStruct->quantity + ItemInventory[inventoryIndex].quantity) < 9))) {
      if (ItemInventory[inventoryIndex].quantity == 0) {
        memcpy(ItemInventory + inventoryIndex, itemStruct, sizeof(InventoryItemStruct));
      }
      else {
        ItemInventory[inventoryIndex].quantity = itemStruct->quantity + ItemInventory[inventoryIndex].quantity;
      }
      itemStruct->quantity = 0x0;
      break;
    }
  }

  if (inventoryIndex < 32) {
    return;
  }

  if (*this->selectedUnits32 == nullptr) {
    return;
  }

  (*this->selectedUnits32)->primarySwitchSingleParam(0x7d2e, (intptr_t)itemStruct->typeId, 0x0);
  itemStruct->quantity = 0x0;
}

__forceinline void SceneHandler::Case_0x7d08_0x7d17_0x7d18_0x7d25_0x7d35_0x7d37_0x7d39(int32_t switchConstant, intptr_t param_1, intptr_t param_2) {
  this->mainSceneHandler->primarySwitchSingleParam(switchConstant, param_1, param_2);
}

__forceinline void SceneHandler::Case_0x7d21(intptr_t param_1, intptr_t param_2) {
  this->sceneCamera->primarySwitchSingleParam(0x7d21, param_1, param_2);
}

__forceinline void SceneHandler::Case_0x7d26() {
  int32_t windowIndex;
  GameWindowBase* gameWindow;

  windowIndex = 0;
  if (0 < this->gameWindowsCounter) {
    do {
      gameWindow = this->gameWindowsArray[windowIndex];
      if (gameWindow != nullptr) {
        gameWindow->primarySwitchSingleParam(0x7d26, 0x0, 0x0);
      }
      windowIndex = windowIndex + 1;
    } while (windowIndex < this->gameWindowsCounter);
    return;
  }
}

__forceinline void SceneHandler::Case_0x7d07(intptr_t param_1) {
  GameWindowBase* sfxIndex;

  sfxIndex = (GameWindowBase*)param_1;
  this->mainSceneHandler->primarySwitchSingleParam(0x7d0b, this->sceneMusicIndex, 0x0);
  if (param_1 != 0x0) {
    if (sfxIndex->mainSceneHandler == this) {
      sfxIndex->primarySwitchSingleParam(0x7d06, 0, 0);
      return;
    }
    return;
  }
  this->mainSceneHandler->primarySwitchSingleParam(0x7d07, (intptr_t)(GameWindowBase*)this, (intptr_t)this->selectedUnits32);
}

__forceinline void SceneHandler::Case_0x7d1a(intptr_t param_1) {

  if (param_1 == 0x0) {
    *this->selectedUnits32 = nullptr;
    return;
  }
  ((GameWindowBase*)param_1)->primarySwitchSingleParam_UpdateSelectedUnits_0x7d1a(this, 0x0);
}

__forceinline void SceneHandler::Case_0x7d29(intptr_t param_1, intptr_t param_2) {

  switch (param_1) {
  case 0x0:
    this->sceneMusicIndex = param_2;
    return;
  case 0x1:
    this->sceneClassCommand = (SceneClassCommand*)param_2;
    return;
  case 0x2:
    this->sceneCamera = (SceneClassCamera*)param_2;
    return;
  }
}

__forceinline void SceneHandler::Case_0x7d0f(intptr_t param_1, intptr_t param_2) {
  int32_t matrixIndexY;
  int32_t matrixIndexX;
  GameWindowBase* sceneObject;
  GameWindowBase* sfxIndex;

  sfxIndex = (GameWindowBase*)param_1;
  ((GameWindowBase*)param_1)->previousObject = nullptr;
  ((GameWindowBase*)param_1)->nextObject = nullptr;
  if (param_2 == 0x0) {
    matrixIndexY = sfxIndex->matrixIndexYTimes16 >> 4 & 127;
    sfxIndex->matrixIndexY = matrixIndexY;
    matrixIndexX = sfxIndex->matrixIndexXTimes16 >> 4 & 127;
    sfxIndex->matrixIndexX = matrixIndexX;
    sceneObject = this->matrix_128x128[matrixIndexY][matrixIndexX];
    if (param_1 != 0x0) {
      sfxIndex->previousObject = sceneObject;
    }
    if (sceneObject != nullptr) {
      sceneObject->nextObject = sfxIndex;
    }
    this->matrix_128x128[sfxIndex->matrixIndexY][sfxIndex->matrixIndexX] = (GameWindowBase*)param_1;
    return;
  }
  sceneObject = this->currentObject;
  if (param_1 != 0x0) {
    sfxIndex->previousObject = sceneObject;
  }
  if (sceneObject != nullptr) {
    sceneObject->nextObject = (GameWindowBase*)param_1;
  }
  this->currentObject = (GameWindowBase*)param_1;
}

__forceinline void SceneHandler::Case_0x7d10(intptr_t param1) {
  GameWindowBase** ppNextArrayEntry;
  GameWindowBase** ppCurrentArrayEntry;
  int32_t arrayIndex;
  GameWindowBase** ppUnitArray;
  int32_t selectedUnitIndex;
  GameWindowBase* previousObject;
  GameWindowBase** ppSearchArray;
  GameWindowBase* nextObject;
  GameWindowBase* removedObject;

  removedObject = (GameWindowBase*)param1;
  nextObject = removedObject->nextObject;
  previousObject = removedObject->previousObject;
  if (nextObject != nullptr) {
    nextObject->previousObject = previousObject;
  }
  if (previousObject != nullptr) {
    previousObject->nextObject = nextObject;
  }
  previousObject = this->currentObject;
  if (previousObject == removedObject) {
    this->currentObject = previousObject->previousObject;
  }

  previousObject = this->matrix_128x128[removedObject->matrixIndexY][removedObject->matrixIndexX];
  if (previousObject == removedObject) {

    this->matrix_128x128[removedObject->matrixIndexY][removedObject->matrixIndexX] = previousObject->previousObject;
  }
  removedObject->previousObject = nullptr;
  removedObject->nextObject = nullptr;
  arrayIndex = 0;
  if (0 < this->gameWindowsCounter) {
    do {
      ppCurrentArrayEntry = this->gameWindowsArray;
      if (ppCurrentArrayEntry[arrayIndex] == removedObject) {
        ppCurrentArrayEntry[arrayIndex] = nullptr;
      }
      arrayIndex = arrayIndex + 1;
    } while (arrayIndex < this->gameWindowsCounter);
  }

  if (this->mainSceneHandler != nullptr) {
    ppUnitArray = this->selectedUnits32;
    arrayIndex = 0;
    previousObject = *ppUnitArray;
    ppSearchArray = ppUnitArray;
    while ((previousObject != nullptr && (previousObject != removedObject))) {
      ppNextArrayEntry = ppSearchArray + 1;
      ppSearchArray = ppSearchArray + 1;
      arrayIndex = arrayIndex + 1;
      previousObject = *ppNextArrayEntry;
    }
    selectedUnitIndex = arrayIndex;
    if (ppUnitArray[arrayIndex] != nullptr) {
      ppUnitArray[arrayIndex] = ppUnitArray[arrayIndex + 1];
      ppUnitArray = this->selectedUnits32;
      if (ppUnitArray[arrayIndex] != nullptr) {
        do {
          arrayIndex = selectedUnitIndex + 2;
          selectedUnitIndex = selectedUnitIndex + 1;
          ppUnitArray[selectedUnitIndex] = ppUnitArray[arrayIndex];
          ppUnitArray = this->selectedUnits32;
        } while (ppUnitArray[selectedUnitIndex] != nullptr);
        return;
      }
    }
  }
}

__forceinline void SceneHandler::Case_0x7d0a(intptr_t param_1, intptr_t param_2) {

  SceneClassCameraBase* cameraBase;
  int32_t randomAngle;
  int32_t deltaX;
  int32_t absDeltaX;
  int32_t absDeltaY;
  SfxObject* localSoundObject;

  if (0 < param_1) {

    if (param_2 == 0x0) {
      localSoundObject = PtrSfxObject;
      randomAngle = PseudoRng();
      localSoundObject->RunPlay(ListOfSfxBuffers[param_1], 255, (randomAngle % 40) + 108);
      return;
    }
    localSoundObject = PtrSfxObject;
    cameraBase = (SceneClassCamera*)this->sceneCamera;
    if (cameraBase != nullptr) {
      deltaX = ((((GameWindowBase*)param_2)->matrixIndexXTimes16 * 16) - cameraBase->cameraCoordX) + -247;
      absDeltaY = ((((GameWindowBase*)param_2)->matrixIndexYTimes16 + -15) * 16) - cameraBase->cameraCoordY;
      absDeltaX = deltaX;
      if (deltaX < 0) {
        absDeltaX = -deltaX;
      }
      if (absDeltaX < 495) {
        if (absDeltaY < 0) {
          absDeltaY = -absDeltaY;
        }
        if (absDeltaY < 480) {
          localSoundObject->RunPlay(ListOfSfxBuffers[param_1], 255, ((deltaX * 100) / 495) + 128);
          return;
        }
      }
    }
  }
}

__forceinline void SceneHandler::Case_0x7d0d() {
  ActiveCharacter** characterArray;

  this->primarySwitchSingleParam_UpdateSelectedUnits_0x7d1a((GameWindowBase*)nullptr, 0x0);

  characterArray = TeamCharacterList;
  while (*characterArray != nullptr) {
    if ((*characterArray)->shiftedSceneClassUser0x48->mainSceneHandler == this) {
      return;
    }
    characterArray++;
  }
  this->mainSceneHandler->primarySwitchSingleParam(0x7d0c, (intptr_t)(GameWindowBase*)this, 0x0);
}

__forceinline void SceneHandler::Case_0x7d27(intptr_t param_1) {
  GameWindowBase* sfxIndex;

  sfxIndex = (GameWindowBase*)param_1;
  this->StoreAndInitializeObject(sfxIndex);
}

__forceinline void SceneHandler::Case_0x7d0c(intptr_t param_1) {
  int32_t counter;
  int32_t windowIndex;
  int32_t eventCounterNew;
  GameWindowBase* sfxIndex;

  sfxIndex = (GameWindowBase*)param_1;
  for (windowIndex = 0; windowIndex < this->gameWindowsCounter; windowIndex++) {
    if (this->gameWindowsArray[windowIndex] == sfxIndex) {
      if (this->queuedEventsArray[this->eventCounter >> 8] == nullptr) {
        this->queuedEventsArray[this->eventCounter >> 8] = new QueueEventContainer;
      }
      counter = this->eventCounter;
      this->queuedEventsArray[counter >> 8]->queueEvents[counter & 0xff] = windowIndex;
      eventCounterNew = this->eventCounter + 1;
      this->eventCounter = eventCounterNew;
      if (this->queuedEventsArray[eventCounterNew >> 8] == nullptr) {
        this->queuedEventsArray[this->eventCounter >> 8] = new QueueEventContainer;
      }
      counter = this->eventCounter;
      this->queuedEventsArray[counter >> 8]->queueEvents[counter & 0xff] = 0x7d00;
      this->eventCounter = this->eventCounter + 1;
    }
  }
}

void SceneHandler::primarySwitchSingleParam(int32_t switchConstant, intptr_t param_1, intptr_t param_2) {

  switch (switchConstant) {

  case 0x7d11:
    this->Case_0x7d11(param_1);
    return;

  case 0x7d3b:
    this->Case_0x7d3b();
    return;

  case 0x7d3c:
    this->Case_0x7d3c(param_1);
    return;

  case 0x7d0e:
    this->Case_0x7d0e(switchConstant, param_1, param_2);
    return;

  case 0x7d2b:
    this->Case_0x7d2b(param_1);
    return;

  case 0x7d2c:
    this->Case_0x7d2c(param_1);
    return;

  case 0x7d08:
  case 0x7d17:
  case 0x7d18:
  case 0x7d25:
  case 0x7d35:
  case 0x7d37:
  case 0x7d39:
    this->Case_0x7d08_0x7d17_0x7d18_0x7d25_0x7d35_0x7d37_0x7d39(switchConstant, param_1, param_2);
    return;

  case 0x7d21:
    this->Case_0x7d21(param_1, param_2);
    return;

  case 0x7d26:
    this->Case_0x7d26();
    return;

  case 0x7d07:
    this->Case_0x7d07(param_1);
    return;

  case 0x7d1a:
    this->Case_0x7d1a(param_1);
    return;

  case 0x7d29:
    this->Case_0x7d29(param_1, param_2);
    return;

  case 0x7d0f:
    this->Case_0x7d0f(param_1, param_2);
    return;

  case 0x7d10:
    this->Case_0x7d10(param_1);
    return;

  case 0x7d0a:
    this->Case_0x7d0a(param_1, param_2);
    return;

  case 0x7d0d:
    this->Case_0x7d0d();
    return;

  case 0x7d27:
    this->Case_0x7d27(param_1);
    return;

  case 0x7d0c:
    this->Case_0x7d0c(param_1);
    return;

  default:
    return;
  }
}
