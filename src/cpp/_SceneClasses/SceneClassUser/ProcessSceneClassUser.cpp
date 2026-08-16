#include "HazardPatches.hpp"
#include <stdio.h>
#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/EventHandler.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowSpellcast.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/PathfindingState.hpp"
#include "HazardClasses/SceneClassAniBg_RestoreItemAndSpellcasterAura.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneClassItem.hpp"
#include "HazardClasses/SceneClassUser.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardEnums/ItemFlag.hpp"
#include "HazardEnums/MapType.hpp"
#include "HazardEnums/UserFlag.hpp"
#include "HazardExterns/SceneClassUser.hpp"
#include "HazardGlobals.hpp"
#include "HazardInlineFunctions.hpp"
#include "HazardStructs/ActContent.hpp"
#include "HazardStructs/ActiveCharacter.hpp"
#include "HazardStructs/CharacterEquipment.hpp"
#include "HazardStructs/DefaultCharacterStats.hpp"
#include "HazardStructs/DirectionOffsets.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"
#include "HazardStructs/InventoryItemAccessory.hpp"
#include "HazardStructs/InventoryItemArmor.hpp"
#include "HazardStructs/InventoryItemBoots.hpp"
#include "HazardStructs/InventoryItemBracer.hpp"
#include "HazardStructs/InventoryItemSpell.hpp"
#include "HazardStructs/InventoryItemStruct.hpp"
#include "HazardStructs/InventoryItemWeapon.hpp"
#include "HazardStructs/ItemReferenceCollection.hpp"
#include "HazardStructs/ItemReferenceStruct.hpp"
#include "HazardStructs/ItemStatsTemplate.hpp"
#include "HazardStructs/NumericalCharacterStats.hpp"
#include "HazardStructs/ObjectWrapper.hpp"
#include "HazardStructs/PathfindingNode.hpp"
#include "HazardStructs/QueueEventContainer.hpp"
#include "memory.h"

void __fastcall ReturnMemoryPool(PathfindingState* param_1);

__forceinline int32_t __InlineIs2x2AreaNotVisible(GridHandler* gridHandler, int32_t coordX, int32_t coordY) {
  int32_t x;
  int32_t y;

  for (y = 0; y < 2; y++) {
    for (x = 0; x < 2; x++) {
      if (gridHandler->PaddedGridMap_Visibility[(coordY + y) >> 1][(coordX + x) >> 1] == 0) {
        return 1;
      }
    }
  }
  return 0;
}

void inline SceneClassUser::Case_0x7d3b() {
  SceneHandler* sceneHandler;
  GameWindowBase* selectedUnit;
  int16_t spriteLayer;
  int32_t coordX;
  ImageVectorWithHeader* solidSprite;
  int32_t distance;
  GameWindowBase** currentSelectedPtr;
  GameWindowBase** nextSelectedPtr;
  int32_t coordY;
  ActiveCharacter* teamCharacter;
  int32_t isViewportEnabled;
  GameWindowBase* sceneUserPtr;
  longlong floatValue;
  ImageVectorWithHeader* shadowSprite;
  ActiveCharacter** activeCharacter;
  int32_t counter;
  int32_t tempDistance;

  sceneHandler = this->mainSceneHandler;
  counter = 0x2;
  isViewportEnabled = sceneHandler->isViewportEnabled;
  if ((isViewportEnabled != 0) && ((this->userFlags & UserFlag::USERFLAG_IS_UNKNOWN2) != 0)) {
    if (__InlineIs2x2AreaNotVisible(sceneHandler, this->matrixIndexXTimes16, this->matrixIndexYTimes16)) {
      return;
    }
  }
  if (((this->userFlags & UserFlag::USERFLAG_IS_ENEMY) == 0) || (isViewportEnabled == 0)) {
  label_check_action_switch_flag:
    isViewportEnabled = this->voluntaryActionSwitchFlag;
    if ((((isViewportEnabled == 666) || (isViewportEnabled == 0x29b)) || (isViewportEnabled == 1818)) || (counter < 2)) {

      floatValue = (CorpseTimer + this->floatTimesMultiplier2);
      spriteLayer = -(int16_t)floatValue;
    }
    else {

      floatValue = this->floatTimesMultiplier2;
      spriteLayer = (int16_t)floatValue + 0x1f0;
    }
    solidSprite = this->currentSolidSpriteFrame;

    floatValue = this->floatTimesMultiplier2;
    isViewportEnabled = (int32_t)floatValue + 0x10;
    floatValue = this->floatTimesMultiplier1;
    sceneHandler->sceneCamera->DrawSprite((int32_t)floatValue + 0x10, isViewportEnabled, solidSprite, spriteLayer);

    floatValue = this->floatTimesMultiplier2;
    shadowSprite = this->currentShadowSpriteFrame;

    spriteLayer = -0x1e0 - (int16_t)floatValue;
    isViewportEnabled = (int32_t)floatValue + 0x10;
    floatValue = this->floatTimesMultiplier1;
    this->mainSceneHandler->sceneCamera->DrawSprite((int32_t)floatValue + 0x10, isViewportEnabled, shadowSprite, spriteLayer);
  }
  else {
    counter = 0x0;

    if (TeamCharacterList[0] != nullptr) {
      activeCharacter = TeamCharacterList;
      teamCharacter = *TeamCharacterList;
      do {
        if (teamCharacter->shiftedSceneClassUser0x48->mainSceneHandler == sceneHandler) {
          sceneUserPtr = (*activeCharacter)->shiftedSceneClassUser0x48;
          coordY = sceneUserPtr->matrixIndexXTimes16 - this->matrixIndexXTimes16;
          tempDistance = coordY;
          if (coordY < 0) {
            tempDistance = -coordY;
          }
          coordX = sceneUserPtr->matrixIndexYTimes16 - this->matrixIndexYTimes16;
          isViewportEnabled = coordX;
          if (coordX < 0) {
            isViewportEnabled = -coordX;
          }
          distance = ((*activeCharacter)->characterBaseStats->Eye * 30) / 100;
          if ((tempDistance + isViewportEnabled) / 2 < (distance * 70) / 100) {
            counter = (counter + 1);
          }
          if (coordY < 0) {
            coordY = -coordY;
          }
          if (coordX < 0) {
            coordX = -coordX;
          }
          if ((coordX + coordY) / 2 < (distance * 50) / 100) {
            counter = (counter + 1);
          }
        }
        activeCharacter = activeCharacter + 1;
        teamCharacter = (*activeCharacter);
      } while (teamCharacter != nullptr);

      if (counter != 0x0) {
        goto label_check_action_switch_flag;
      }
    }
  }
  sceneHandler = this->mainSceneHandler;
  currentSelectedPtr = sceneHandler->selectedUnits32;
  selectedUnit = *currentSelectedPtr;
  while (selectedUnit != nullptr) {
    if (selectedUnit == this) {

      floatValue = this->floatTimesMultiplier2;

      spriteLayer = -0x100 - (int16_t)floatValue;
      isViewportEnabled = (int32_t)floatValue + 0x10;
      shadowSprite = LoadMark2;
      floatValue = this->floatTimesMultiplier1;
      sceneHandler->sceneCamera->DrawSprite((int32_t)floatValue + 0x10, isViewportEnabled, shadowSprite, spriteLayer);
      return;
    }
    nextSelectedPtr = currentSelectedPtr + 1;
    currentSelectedPtr = currentSelectedPtr + 1;
    selectedUnit = *nextSelectedPtr;
  }
}

__forceinline void SceneClassUser::DispatchAutonomousUpdate_0x7d3c(intptr_t param_2) {
  if (param_2 == 0x0) {
    this->AutonomousSceneClassUserUpdate();
  }
}

__forceinline void SceneClassUser::Case_0x7d40(intptr_t param_2, intptr_t param_3) {

  int32_t currentEvent;
  uint32_t eventMinusOne;
  int32_t eventIndex;
  int32_t* eventPtr;
  int32_t* writePtr;
  int32_t nextEvent;
  int32_t eventStack[106];

  currentEvent = this->eventCounter;
  if (currentEvent <= 0) {
    currentEvent = 0;
  }
  else {
    eventMinusOne = currentEvent - 1;
    this->eventCounter = eventMinusOne;
    currentEvent = this->queuedEventsArray[(int32_t)eventMinusOne >> 8]->queueEvents[eventMinusOne & 0xff];
  }

  eventStack[1] = currentEvent;
  eventIndex = 1;
  eventPtr = eventStack + 2;
  while (((currentEvent == 0x7d04 || (currentEvent == 0x7d00)) && (eventIndex < 100))) {
    nextEvent = this->eventCounter;
    writePtr = eventPtr;
    if (currentEvent != 0x7d04) {
      if (nextEvent <= 0) {
        currentEvent = 0;
      }
      else {
        eventMinusOne = nextEvent - 1;
        this->eventCounter = eventMinusOne;
        currentEvent = this->queuedEventsArray[(int32_t)eventMinusOne >> 8]->queueEvents[eventMinusOne & 0xff];
      }
      *eventPtr = currentEvent;
      nextEvent = this->eventCounter;
      eventIndex = eventIndex + 1;
      writePtr = eventPtr + 1;
    }
    if (nextEvent > 0) {
      currentEvent = 0;
    }
    else {
      eventMinusOne = nextEvent - 1;
      this->eventCounter = eventMinusOne;
      currentEvent = this->queuedEventsArray[(int32_t)eventMinusOne >> 8]->queueEvents[eventMinusOne & 0xff];
    }
    *writePtr = currentEvent;
    currentEvent = this->eventCounter;
    if (currentEvent <= 0) {
      currentEvent = 0;
      eventIndex = eventIndex + 2;
      writePtr[1] = 0;
      eventPtr = writePtr + 2;
    }
    else {
      eventMinusOne = currentEvent - 1;
      this->eventCounter = eventMinusOne;
      eventIndex = eventIndex + 2;
      eventPtr = writePtr + 2;
      currentEvent = this->queuedEventsArray[(int32_t)eventMinusOne >> 8]->queueEvents[eventMinusOne & 0xff];
      writePtr[1] = currentEvent;
    }
  }
  __InlineQueueEvent(currentEvent);

  if (eventIndex < 100) {
    __InlineQueueEvent(param_3);
    QueueEvent(param_2);
    QueueEvent(0x7d00);
  }
  eventIndex = eventIndex + -1;
  if (0 < eventIndex) {
    eventPtr = eventStack + eventIndex;
    do {
      currentEvent = *eventPtr;
      __InlineQueueEvent(currentEvent);
      eventPtr = eventPtr + -1;
      eventIndex = eventIndex + -1;
    } while (eventIndex != 0);
  }
}

__forceinline void SceneClassUser::QueueWalkPosition_0x7d00(intptr_t param_2, intptr_t param_3) {
  this->eventCounter = 0;
  __InlineQueueEvent(param_3);
  QueueEvent(param_2);
  QueueEvent(0x7d00);
}

__forceinline void SceneClassUser::Case_0x7d04(intptr_t param_2) {
  this->eventCounter = 0;
  if ((ObjectList[param_2].scriptUserFlags & 0x800U) != 0) {
    __InlineQueueEvent(param_2);
    QueueEvent(0x7d08);
    __InlineQueueEvent(param_2);
    QueueEvent(0x7d0f);
    return;
  }
  __InlineQueueEvent(param_2);
  QueueEvent(0x7d08);
  __InlineQueueEvent(param_2);
  QueueEvent(0x7d07);
}

__forceinline void SceneClassUser::QueueWalkToGate_0x7d15(intptr_t param_2, intptr_t param_3) {

  this->eventCounter = 0;
  __InlineQueueEvent(param_3);
  QueueEvent(0x7d08);
  __InlineQueueEvent(((int32_t*)param_2)[1]);
  QueueEvent(((int32_t*)param_2)[0]);
  QueueEvent(0x7d00);
}

__forceinline void SceneClassUser::QueueWalkToTalker_0x7d18(intptr_t param_2, intptr_t param_3) {

  this->eventCounter = 0;
  if ((ObjectList[param_2].scriptUserFlags & 0x800U) != 0) {
    __InlineQueueEvent(param_3);
    QueueEvent(param_2);
    QueueEvent(0x7d19);
    __InlineQueueEvent(param_2);
    QueueEvent(0x7d0f);
    return;
  }
  QueueEvent(param_3);
  QueueEvent(param_2);
  QueueEvent(0x7d19);
  __InlineQueueEvent(param_2);
  QueueEvent(0x7d07);
}

__forceinline void SceneClassUser::Case_0x7d3f(intptr_t param_2, intptr_t param_3) {

  int32_t eventCode;
  int32_t distanceSquared;
  int32_t directionIndex;
  int32_t closestDistanceSquared;
  DirectionOffsets* directionOffsetPtr;
  GameWindowBase* targetObject;

  if (param_2 == 0x0) {
    if ((this->voluntaryActionSwitchFlag != 0x7d04) && (this->voluntaryActionSwitchFlag != 0x7d21)) {
      return;
    }
    if ((this->mainSceneHandler)->mapType == MapType::Village) {
      return;
    }

    eventCode = this->genericAct->GetFrameCountForAction(this->actGuard1);
    if (eventCode <= 1) {
      return;
    }
    this->eventCounter = 0;
    this->__InlineQueueEvent(0);
    this->QueueEvent(0x7d2a);
    return;
  }
  else {
    if (param_2 == 0x1) {
      if (this->voluntaryActionSwitchFlag == 0x7d2a) {
        this->eventCounter = 0;
        this->__InlineQueueEvent(1);
        this->QueueEvent(0x7d2a);
        return;
      }
      else {
        return;
      }
    }
    else {
      if (param_2 < 2) {
        return;
      }
      if (this->voluntaryActionSwitchFlag != 0x7d2a) {
        return;
      }
      directionIndex = 0x0;
      closestDistanceSquared = 0x10000;
      directionOffsetPtr = CollisionHelper_ARRAY;
      do {
        eventCode = (int32_t)(this->mainSceneHandler->PaddedGridMap_Collision[directionOffsetPtr->DeltaY1 + this->floatMultiplier2_pos2][this->floatMultiplier1_pos1 + directionOffsetPtr->DeltaX1]);
        if (((-1 < eventCode) || (eventCode = (int32_t)this->mainSceneHandler->PaddedGridMap_Collision[directionOffsetPtr->DeltaY2 + this->floatMultiplier2_pos2][(directionOffsetPtr->DeltaX2 + this->floatMultiplier1_pos1)], -1 < eventCode)) && ((*(byte*)&ObjectList[eventCode].scriptUserFlags & 1) != 0 && (targetObject = ObjectList[eventCode].sceneClassObjectPointer, distanceSquared = param_3 - targetObject->matrixIndexYTimes16, eventCode = param_2 + (-2 - targetObject->matrixIndexXTimes16), eventCode = (distanceSquared * distanceSquared) + (eventCode * eventCode), eventCode < closestDistanceSquared))) {
          this->orientation = directionIndex;
          closestDistanceSquared = eventCode;
        }
        directionOffsetPtr = directionOffsetPtr + 1;
        directionIndex = (directionIndex + 1);
      } while (directionOffsetPtr < 8 + CollisionHelper_ARRAY);
      return;
    }
  }
}

__forceinline void SceneClassUser::Case_0x7d02(intptr_t param_2) {
  int32_t eventValue;
  int32_t orientation;

  if (this->eventCounter > 0) {
    this->eventCounter--;
    eventValue = this->queuedEventsArray[this->eventCounter >> 8]->queueEvents[this->eventCounter & 0xff];
    if ((((eventValue == 0x7d0b) || (eventValue == 0x7d0c)) || (eventValue == 0x7d26)) || (eventValue == 0x7d27 || (eventValue == 0x7d0d))) {
      orientation = this->orientation;
      if (((this->mainSceneHandler->PaddedGridMap_Collision[CollisionHelper_ARRAY[orientation].DeltaY1 + this->floatMultiplier2_pos2][(CollisionHelper_ARRAY[orientation].DeltaX1 + this->floatMultiplier1_pos1)]) == param_2) || ((this->mainSceneHandler->PaddedGridMap_Collision[CollisionHelper_ARRAY[orientation].DeltaY2 + this->floatMultiplier2_pos2][(CollisionHelper_ARRAY[orientation].DeltaX2 + this->floatMultiplier1_pos1)]) == param_2)) {
        this->__InlineableQueueEvent(eventValue);
        return;
      }
    }
  }
  this->eventCounter = 0;
  __InlineQueueEvent(param_2);
  QueueEvent(0x7d0a);
  __InlineQueueEvent(param_2);
  __InlineQueueEvent(0x7d0f);
}

__forceinline void SceneClassUser::Case_0x7d33(intptr_t param_2, intptr_t param_3) {
  CoreActClass* actObject;
  int32_t actionId;

  if ((this->userFlags & UserFlag::USERFLAG_IS_ENEMY_OR_PLAYER) != 1) {
    return;
  }
  actObject = this->genericAct;

  actionId = actObject->GetActionIndexByName(ListOfResistances[param_3]);
  if ((actionId == -1) || (actionId = *actObject->txtContent[actionId].ptrFrameStart, actionId < 1)) {
    actionId = 0;
  }
  this->__InlineableQueueEvent(-1);
  this->__InlineableQueueEvent(((100 - actionId) * param_2) / 100);
  this->__InlineableQueueEvent(0x7d15);
}

__forceinline void SceneClassUser::QueueTalkTrigger_0x7d19(intptr_t param_2, intptr_t param_3) {

  if ((this->voluntaryActionSwitchFlag != 0x7d19) && (this->triggerScriptIdOnTalk != 0)) {

    this->__InlineableQueueEvent(param_3);
    this->__InlineableQueueEvent(param_2);
    this->__InlineableQueueEvent(0x7d1a);
  }
}

__forceinline void SceneClassUser::Case_0x7d2a(intptr_t param_2) {

  this->eventCounter = 0;
  this->voluntaryActionSwitchFlag = 0x7d19;
  this->__InlineableQueueEvent(param_2);
  this->__InlineableQueueEvent(0x7d1b);
}

__forceinline void SceneClassUser::UseItem_0x7d05(intptr_t param_2) {
  if ((ItemStruct12k->itemArray[param_2].equipFlags & 1) == 0) {
    this->primarySwitchSingleParam(0x7d1b, param_2, 0x0);
  }
  else {
    this->mainSceneHandler->primarySwitchSingleParam(0x7d2b, param_2, 0x0);
  }
}

__forceinline void SceneClassUser::EquipItemFromInventory_0x7d2b(intptr_t param_2, intptr_t param_3) {
  int32_t counter;
  ActiveCharacter* activeCharacter;
  InventoryItemStruct* item;

  int32_t param4AsInt = param_3;
  counter = __InlineGetActiveCharacterIndex(this);

  activeCharacter = TeamCharacterList[counter];
  if (activeCharacter != nullptr) {
    item = (InventoryItemStruct*)(&(activeCharacter->charEquip).equipmentWeapon + param4AsInt);
    if ((&(activeCharacter->charEquip).equipmentWeapon)[param4AsInt].quantity != 0) {
      this->mainSceneHandler->primarySwitchSingleParam(0x7d2c, (intptr_t)item, 0x0);
    }
    this->primarySwitchSingleParam(0x7d37, (intptr_t)(InventoryItemStruct*)param_2, (intptr_t)item);
  }
  else {
    for (counter = 0; BenchedCharacterList[counter] != nullptr; counter++) {
      if (BenchedCharacterList[counter]->shiftedSceneClassUser0x48 == this) {
        break;
      }
    }
    activeCharacter = BenchedCharacterList[counter];
    if (activeCharacter != nullptr) {
      if ((&(activeCharacter->charEquip).equipmentWeapon)[param4AsInt].quantity != 0) {
        this->mainSceneHandler->primarySwitchSingleParam(0x7d2c, (intptr_t)(&(activeCharacter->charEquip).equipmentWeapon + param4AsInt), 0x0);
      }
      this->primarySwitchSingleParam(0x7d37, (intptr_t)(InventoryItemStruct*)param_2, (intptr_t)(InventoryItemStruct*)&((&(BenchedCharacterList[counter]->charEquip).equipmentWeapon)[param4AsInt]));
    }
  }
}

__forceinline void SceneClassUser::InitializeStarterEquipment_0x7d37(intptr_t param_2, intptr_t param_3) {
  ItemStatsTemplate* itemStats;
  uint32_t equipFlag;
  uint32_t rng;
  int32_t counter;
  int32_t attributeValue;
  int32_t* itemTemplateAttribute1;
  int32_t attributrPtr;
  int32_t* itemInstanceAttributePtr1;
  int32_t* itemInstanceAttributePtr2;
  int32_t* itemTemplateAttribute2;
  InventoryItemStruct* itemInstance;
  int32_t param3AsInt = param_2;

  itemInstance = (InventoryItemStruct*)param_3;

  itemStats = ItemStruct12k->itemArray[param3AsInt].stats;
  equipFlag = ItemStruct12k->itemArray[param3AsInt].equipFlags;

  itemInstance->quantity = 1;
  itemInstance->typeId = param3AsInt;
  itemInstance->equipFlags = ItemStruct12k->itemArray[param3AsInt].equipFlags;
  itemInstance->actOffset = ItemStruct12k->itemArray[param3AsInt].actOffset;

  memset(&itemInstance->itemGroup, 0x0, 30);

  counter = 1;
  if (itemStats->itemGroup == 5) {
    itemInstanceAttributePtr1 = &itemInstance->aParameter;
    itemInstanceAttributePtr2 = &itemInstance->bParameter;

    equipFlag = equipFlag & ItemFlag::SellAndWindowRelated_0x700;
    itemTemplateAttribute1 = &itemStats->aParameter;
    itemTemplateAttribute2 = &itemStats->bParameter;

    do {

      attributeValue = 1;
      if (
          (

              (
                  (equipFlag == ItemFlag::Value_0x100 && (counter == 1 || (counter == 3))) ||
                  (equipFlag == ItemFlag::Value_0x200 && ((counter == 1 || (counter == 3)) || (counter == 5 || (counter == 7))))) ||
              (equipFlag == ItemFlag::Value_0x300 && (counter == 1 || (counter == 3)))) ||
          (equipFlag == ItemFlag::Value_0x500 && (counter == 8 || (counter == 10))) &&
              (param3AsInt < 0xae)) {
        attributrPtr = *itemTemplateAttribute1;
        rng = PseudoRng();
        attributeValue = (int32_t)rng % (*itemTemplateAttribute2 + (1 - attributrPtr));
        *itemInstanceAttributePtr2 = (attributrPtr + attributeValue) * 100;
        if (attributeValue == 0) {
          attributeValue = 0;
        }
        else {
          rng = PseudoRng();
          attributeValue = (int32_t)rng % attributeValue;
        }
        *itemInstanceAttributePtr1 = (attributrPtr + attributeValue) * 100;
        counter = counter + 2;

        attributeValue = 2;
      }
      else {
        counter = counter + 1;
        *itemInstanceAttributePtr1 = *itemTemplateAttribute1;
      }

      itemTemplateAttribute2 = itemTemplateAttribute2 + attributeValue;
      itemInstanceAttributePtr2 = itemInstanceAttributePtr2 + attributeValue;
      itemTemplateAttribute1 = itemTemplateAttribute1 + attributeValue;
      itemInstanceAttributePtr1 = itemInstanceAttributePtr1 + attributeValue;
    } while (counter < 15);
  }
}

__forceinline void SceneClassUser::Case_0x7d41() {
  int32_t eventCounter;
  uint32_t rng;
  char orientation;
  PathfindingNode* pathfindinNode;

  eventCounter = this->eventCounter;
  if (eventCounter < 1) {
    eventCounter = 0;

  label_navigate_around_objects:
    if ((this->voluntaryActionSwitchFlag == 0x7d21) && ((this->userFlags & UserFlag::RELATES_TO_PUSHED) == 0)) {
      rng = PseudoRng();
      for (pathfindinNode = this->pathfindingInputObj->AStarPathfinding_NavigateAroundObjects(this->matrixIndexXTimes16, this->matrixIndexYTimes16, ((int32_t)rng % 3) + 3); pathfindinNode != nullptr; pathfindinNode = pathfindinNode->linkToParentNode) {
        orientation = pathfindinNode->directionFromParent;
        this->__InlineableQueueEvent((int32_t)orientation);
        this->__InlineableQueueEvent(0x7d04);
      }
      return;
    }
  }
  else {
    this->eventCounter = eventCounter - 1;
    eventCounter = this->queuedEventsArray[this->eventCounter >> 8]->queueEvents[this->eventCounter & 0xff];
    if (eventCounter == 0) {
      goto label_navigate_around_objects;
    }
  }
  this->__InlineableQueueEvent(eventCounter);
}

__forceinline void SceneClassUser::SearchNearbyTarget_0x7d23() {
  GameWindowBase** selectableUnits;
  int32_t eventCounter;
  int32_t foundObject;

  selectableUnits = this->mainSceneHandler->selectedUnits32;
  if ((*selectableUnits == this) && (selectableUnits[1] == nullptr)) {
    return;
  }

  if (this->voluntaryActionSwitchFlag == 0x29b) {
    return;
  }

  eventCounter = this->eventCounter;
  if (eventCounter > 0) {
    this->eventCounter = eventCounter - 1;
    eventCounter = this->queuedEventsArray[this->eventCounter >> 8]->queueEvents[this->eventCounter & 0xff];
    if ((eventCounter == 0) || (eventCounter == 0x7d18)) {
      goto label_search_nearby_object;
    }
    this->__InlineableQueueEvent(eventCounter);
    return;
  }
  eventCounter = 0;
label_search_nearby_object:
  foundObject = this->pathfindingInputObj->FindObjectByFlags(this->floatMultiplier1_pos1, this->floatMultiplier2_pos2, ((int32_t)((this->numericalCharacterStats).Eye * 20) / 100) + 2, this->userFlags);
  if (foundObject != -1) {
    this->eventCounter = 0;
    this->__InlineableQueueEvent(0x7d09);
    this->__InlineableQueueEvent(foundObject);
    this->__InlineQueueEvent(0x7d0f);
    this->__InlineQueueEvent(0x7d09);
    return;
  }
  this->__InlineableQueueEvent(eventCounter);
}

__forceinline void SceneClassUser::Case_0x7d06() {
  SceneHandler* sceneHandler;
  int32_t coord2;
  int32_t coord1;

  sceneHandler = this->mainSceneHandler;
  if (sceneHandler != nullptr) {
    coord2 = this->floatTimesMultiplier2;
    coord1 = this->floatTimesMultiplier1;
    sceneHandler->primarySwitchSingleParam(0x7d21, coord1, coord2);
    sceneHandler = this->mainSceneHandler;
    sceneHandler->primarySwitchSingleParam(0x7d07, (intptr_t)nullptr, 0);
  }
}

__forceinline void SceneClassUser::Case_0x7d07() {
  SceneHandler* sceneHandler;

  sceneHandler = this->mainSceneHandler;
  if (sceneHandler != nullptr) {
    sceneHandler->primarySwitchSingleParam_UpdateSelectedUnits_0x7d1a((GameWindowBase*)nullptr, 0x0);
    this->mainSceneHandler->primarySwitchSingleParam_UpdateSelectedUnits_0x7d1a((GameWindowBase*)this, 0x0);
    this->primarySwitchSingleParam(0x7d06, 0x0, 0x0);
  }
}

__forceinline void SceneClassUser::AddToSelectedUnits_0x7d1a(intptr_t param_2) {
  SceneHandler* sceneHandler;
  GameWindowBase** selectableUnits;
  GameWindowBase* nextWindow;
  GameWindowBase** currentWindow;
  int32_t counter;

  sceneHandler = (SceneHandler*)param_2;

  if (sceneHandler == nullptr) {
    sceneHandler = this->mainSceneHandler;
  }
  if (ObjectList[this->objectListId].scriptUserFlags & UserFlag::USERFLAG_IS_ALIVE && sceneHandler != nullptr) {
    selectableUnits = sceneHandler->selectedUnits32;
    nextWindow = *selectableUnits;
    currentWindow = selectableUnits;
    for (counter = 0; (nextWindow != nullptr && (counter < 30)); counter = counter + 1) {
      if (*currentWindow == this) {
        return;
      }
      nextWindow = currentWindow[1];
      currentWindow = currentWindow + 1;
    }
    selectableUnits[counter] = this;
    sceneHandler->selectedUnits32[counter + 1] = nullptr;
  }
}

__forceinline void SceneClassUser::Case_0x7d0c() {
  this->primarySwitchSingleParam_PrepareMapForUnit_0x7d12(0x0, 0x0);
  this->voluntaryActionSwitchFlag = 666;
  this->statusInternalTimer = 0;
}

__forceinline void SceneClassUser::Case_0x7d12() {
  SceneHandler* sceneHandler;
  PathfindingState* allyPathfindingState;
  PathfindingState* pathfindingState;

  sceneHandler = this->mainSceneHandler;
  if (sceneHandler != nullptr) {

    sceneHandler->SetCollisionValueInRectangularRegion(this->floatMultiplier1_pos1, this->floatMultiplier2_pos2, 2, 2, -2);
    if (this->allySupportPathfinding != nullptr) {
      this->allySupportPathfinding->GenerateInitialPathNodes(this->floatMultiplier1_pos1, this->floatMultiplier2_pos2, -1);
      allyPathfindingState = this->allySupportPathfinding;
      if (allyPathfindingState != nullptr) {
        allyPathfindingState->ReturnMemoryPool();

        delete allyPathfindingState;
      }
      this->allySupportPathfinding = nullptr;
    }
    pathfindingState = this->pathfindingInputObj;
    if (pathfindingState != nullptr) {
      pathfindingState->ReturnMemoryPool();

      delete pathfindingState;
      this->pathfindingInputObj = nullptr;
    }
    this->mainSceneHandler->primarySwitchSingleParam_0x7d10((GameWindowBase*)this, 0x0);
    this->mainSceneHandler = nullptr;
    this->voluntaryActionSwitchFlag = 0x7d21;
    this->eventCounter = 0;
  }
}

__forceinline void SceneClassUser::CalculateSpellImpact_0x7d22(intptr_t spellPower, intptr_t spellEffect) {
  int32_t teamIndex;
  int32_t totalFireResistance;
  int32_t totalIceResistance;
  int32_t totalWindResistance;
  int32_t totalLandResistance;
  int32_t resistedDamage;
  int32_t rng;
  ActiveCharacter* activeChar;
  NumericalCharacterStats* numericalStats;
  CoreActClass* actObject;
  bool isCondition;

  teamIndex = __InlineGetActiveCharacterIndex(this);
  activeChar = TeamCharacterList[teamIndex];
  if (activeChar != nullptr) {
    numericalStats = activeChar->characterBaseStats;
    totalFireResistance = numericalStats->FireResistance;
    totalIceResistance = numericalStats->IceResistance;
    totalWindResistance = numericalStats->WindResistance;
    totalLandResistance = numericalStats->LandResistance;
#if PATCH_FIX_RESISTANCES != 0
    int32_t totalLightningResistance = numericalStats->LightningResistance;
#endif
    if (0 < (activeChar->charEquip).equipmentWeapon.quantity) {
      totalFireResistance = totalFireResistance + (activeChar->charEquip).equipmentWeapon.resFire;
      totalIceResistance = totalIceResistance + (activeChar->charEquip).equipmentWeapon.resIce;
      totalWindResistance = totalWindResistance + (activeChar->charEquip).equipmentWeapon.resWind;
      totalLandResistance = totalLandResistance + (activeChar->charEquip).equipmentWeapon.resLand;
#if PATCH_FIX_RESISTANCES != 0
      totalLightningResistance = totalLightningResistance + (activeChar->charEquip).equipmentWeapon.resLightning;
#endif
    }
    if (0 < (activeChar->charEquip).equipmentArmor.quantity) {
      totalFireResistance = totalFireResistance + (activeChar->charEquip).equipmentArmor.resFire;
      totalIceResistance = totalIceResistance + (activeChar->charEquip).equipmentArmor.resIce;
      totalWindResistance = totalWindResistance + (activeChar->charEquip).equipmentArmor.resWind;
      totalLandResistance = totalLandResistance + (activeChar->charEquip).equipmentArmor.resLand;
#if PATCH_FIX_RESISTANCES != 0
      totalLightningResistance = totalLightningResistance + (activeChar->charEquip).equipmentArmor.resLightning;
#endif
    }
    if (0 < (activeChar->charEquip).equipmentBracer.quantity) {
      totalLandResistance = totalLandResistance + (activeChar->charEquip).equipmentBracer.resLand;
    }
    if (0 < (activeChar->charEquip).equipmentBoots.quantity) {
      totalFireResistance = totalFireResistance + (activeChar->charEquip).equipmentBoots.resFire;
      totalIceResistance = totalIceResistance + (activeChar->charEquip).equipmentBoots.resIce;
      totalWindResistance = totalWindResistance + (activeChar->charEquip).equipmentBoots.resWind;
      totalLandResistance = totalLandResistance + (activeChar->charEquip).equipmentBoots.resLand;
#if PATCH_FIX_RESISTANCES != 0
      totalLightningResistance = totalLightningResistance + (activeChar->charEquip).equipmentBoots.resLightning;
#endif
    }
    if (0 < (activeChar->charEquip).equipmentAccessory1.quantity) {
      totalLandResistance = totalLandResistance + (activeChar->charEquip).equipmentAccessory1.resLand;
      totalFireResistance = totalFireResistance + (activeChar->charEquip).equipmentAccessory1.resFire;
      totalWindResistance = totalWindResistance + (activeChar->charEquip).equipmentAccessory1.resWind;
      totalIceResistance = totalIceResistance + (activeChar->charEquip).equipmentAccessory1.resIce;
#if PATCH_FIX_RESISTANCES != 0
      totalLightningResistance = totalLightningResistance + (activeChar->charEquip).equipmentAccessory1.resLightning;
#endif
    }

    if (0 < (activeChar->charEquip).equipmentAccessory2.quantity) {
      totalLandResistance = totalLandResistance + (activeChar->charEquip).equipmentAccessory2.resLand;
      totalFireResistance = totalFireResistance + (activeChar->charEquip).equipmentAccessory2.resFire;
      totalWindResistance = totalWindResistance + (activeChar->charEquip).equipmentAccessory2.resWind;
      totalIceResistance = totalIceResistance + (activeChar->charEquip).equipmentAccessory2.resIce;
#if PATCH_FIX_RESISTANCES != 0
      totalLightningResistance = totalLightningResistance + (activeChar->charEquip).equipmentAccessory2.resLightning;
#endif
    }
  }
  else {
    actObject = this->genericAct;
    teamIndex = actObject->GetActionIndexByName(s__res_f);
    if ((teamIndex == -1) || (totalFireResistance = *actObject->txtContent[teamIndex].ptrFrameStart, totalFireResistance <= 0)) {
      totalFireResistance = 0;
    }
    actObject = this->genericAct;
    teamIndex = actObject->GetActionIndexByName(s__res_i);
    if ((teamIndex == -1) || (totalIceResistance = *actObject->txtContent[teamIndex].ptrFrameStart, totalIceResistance <= 0)) {
      totalIceResistance = 0;
    }
    this->genericAct->GetActionIndexByName(s__res_li);
    actObject = this->genericAct;
    teamIndex = actObject->GetActionIndexByName(s__res_w);
    if ((teamIndex == -1) || (totalWindResistance = *actObject->txtContent[teamIndex].ptrFrameStart, totalWindResistance <= 0)) {
      totalWindResistance = 0;
    }
    actObject = this->genericAct;
    teamIndex = actObject->GetActionIndexByName(s__res_la);
    if ((teamIndex == -1) || (totalLandResistance = *actObject->txtContent[teamIndex].ptrFrameStart, totalLandResistance <= 0)) {
      totalLandResistance = 0;
    }
  }

  switch (spellEffect) {
  case 0x1:
    resistedDamage = spellPower - ((totalFireResistance * spellPower) / 100);
    resistedDamage = resistedDamage > 0 ? resistedDamage : 0;
    this->__InlineableQueueEvent(-1);
    this->__InlineableQueueEvent(resistedDamage);
    this->__InlineQueueEvent(0x7d15);
    break;
  case 0x3:
#if PATCH_FIX_RESISTANCES == 0
    resistedDamage = spellPower - ((int32_t)(totalIceResistance * spellPower) / 100);
#else
    resistedDamage = spellPower - ((int32_t)(totalLightningResistance * spellPower) / 100);
#endif

    resistedDamage = resistedDamage > 0 ? resistedDamage : 0;
    this->__InlineableQueueEvent(-1);
    this->__InlineableQueueEvent(resistedDamage);
    this->__InlineableQueueEvent(0x7d15);
    break;
  case 0x4:
    resistedDamage = spellPower - ((totalWindResistance * spellPower) / 100);
    resistedDamage = resistedDamage > 0 ? resistedDamage : 0;
    this->__InlineableQueueEvent(-1);
    this->__InlineableQueueEvent(resistedDamage);
    this->__InlineableQueueEvent(0x7d15);
    break;
  case 0x5:
    resistedDamage = spellPower - ((int32_t)(totalLandResistance * spellPower) / 100);
    resistedDamage = resistedDamage > 0 ? resistedDamage : 0;
    this->__InlineableQueueEvent(-1);
    this->__InlineableQueueEvent(resistedDamage);
    this->__InlineableQueueEvent(0x7d15);
    break;
  case 0x6: {
    if (spellPower < 0) {
      spellPower = this->numericalCharacterStats.CurrentHp * spellPower / 100;
    }
    int32_t maxHp = (this->numericalCharacterStats).MaxHp;
    int32_t newHp = spellPower + this->numericalCharacterStats.CurrentHp;
    if (maxHp < newHp) {
      newHp = maxHp;
    }
    (this->numericalCharacterStats).CurrentHp = newHp;
    break;
  }
  case 0x2:
    actObject = this->genericAct;
    teamIndex = actObject->GetActionIndexByName(s__res_i);
    if ((teamIndex == -1) || (*actObject->txtContent[teamIndex].ptrFrameStart < 100)) {
      this->statusCondition = UnitStatusCondition::Frozen_Stopped;
#if PATCH_FIX_RESISTANCES == 0
      this->statusConditionTimeLeft = spellPower << 5;
#else
      this->statusConditionTimeLeft = (spellPower - ((int32_t)(totalIceResistance * spellPower) / 100)) << 5;
      resistedDamage = spellPower - ((int32_t)(totalLightningResistance * spellPower) / 100);
#endif
    }
    break;
  case 0x7:
    if ((this->userFlags & UserFlag::WANDER_GLOOMY_RELATED) == 0) {
      this->statusCondition = UnitStatusCondition::Gloomy_Stopped;
      this->statusConditionTimeLeft = spellPower << 5;
    }
    break;
  case 0x8:
    if ((this->userFlags & UserFlag::WANDER_GLOOMY_RELATED) == 0) {
      this->statusCondition = UnitStatusCondition::Wander_Confused;
      this->statusConditionTimeLeft = spellPower << 5;
    }
    break;
  case 0x9:
    isCondition = this->statusCondition == UnitStatusCondition::Gloomy_Stopped;
    if (isCondition) {
      this->eventCounter = 0;
      this->statusCondition = UnitStatusCondition::Normal;
    }
    break;
  case 0xa:
    isCondition = this->statusCondition == UnitStatusCondition::Wander_Confused;
    if (isCondition) {
      this->eventCounter = 0;
      this->statusCondition = UnitStatusCondition::Normal;
    }
    break;
  case 0xc:
    this->eventCounter = 0;
    this->statusCondition = UnitStatusCondition::Normal;
    break;
  case 0xb: {
    int32_t currentHp = (this->numericalCharacterStats).CurrentHp;
    (this->numericalCharacterStats).CurrentHp = currentHp - (currentHp / 2);
    break;
  }
  default:
    if ((this->userFlags & UserFlag::USERFLAG_IS_ENEMY_OR_PLAYER) == 1) {
      __InlineQueueEvent(-1);
      __InlineQueueEvent(spellPower);
      __InlineQueueEvent(0x7d15);
    }
    WrapperMessageBoxA(s_magic, s_debug);
  }
  rng = PseudoRng() & 7;
  __InlineQueueEvent(rng);
  __InlineQueueEvent(0);
  __InlineQueueEvent(0x7d18);
}

__forceinline void SceneClassUser::SetPosition_0x7d13(intptr_t param_2, intptr_t param_3) {

  this->eventCounter = 0;
  this->floatMultiplier2_pos2 = param_3;
  this->floatMultiplier1_pos1 = param_2;
  this->__InlineableQueueEvent(param_3);
  this->__InlineableQueueEvent(param_2);
  this->__InlineableQueueEvent(0x7d1f);

  this->floatTimesMultiplier1 = (float)this->floatMultiplier1_pos1 * GridMultiplier_16;
  this->floatTimesMultiplier2 = (float)this->floatMultiplier2_pos2 * GridMultiplier_16;
}

__forceinline void SceneClassUser::UpdateOrientation_0x7d38(intptr_t param_2) {
  this->orientation = (uint32_t)param_2;
  this->__InlineableQueueEvent(0x7d28);
}

__forceinline void SceneClassUser::Case_0x7d3a(intptr_t param_2) {
  int32_t actionIndex;
  int32_t counter;
  int32_t frameCount;

  actionIndex = this->genericAct->GetActionIndexByName((char*)param_2);
  if (-1 < actionIndex) {
    counter = 0;
    frameCount = this->genericAct->GetFrameCountForAction(actionIndex);
    if (0 < frameCount) {
      do {
        this->__InlineableQueueEvent(actionIndex);
        this->__InlineableQueueEvent(0x7d27);
        counter = counter + 1;
        frameCount = this->genericAct->GetFrameCountForAction(actionIndex);
      } while (counter < frameCount);
    }
  }
  this->statusInternalTimer = 0;
}

__forceinline void SceneClassUser::Case_0x7d3d(intptr_t param_2) {
  ActiveCharacter** benchedCharacters;
  ActiveCharacter** teamCharacters;
  uint32_t stringLength;
  char* sourceString;

  memcpy(&this->numericalCharacterStats, (void*)param_2, sizeof(uint32_t) * 24);
  if (TeamCharacterList[0] != nullptr) {
    teamCharacters = TeamCharacterList;
    do {
      if ((*teamCharacters)->shiftedSceneClassUser0x48 == this) {
        stringLength = strlen((&ListOfDefaultCharacterStats[(*teamCharacters)->characterId].Battle1)[(this->numericalCharacterStats).SpriteOutfitLevel * 2]);
        sourceString = (&ListOfDefaultCharacterStats[(*teamCharacters)->characterId].Battle1)[(this->numericalCharacterStats).SpriteOutfitLevel * 2];
        memcpy(this->names, sourceString, stringLength);
        stringLength = strlen((&ListOfDefaultCharacterStats[(*teamCharacters)->characterId].Town1)[(this->numericalCharacterStats).SpriteOutfitLevel * 2]);
        sourceString = (&ListOfDefaultCharacterStats[(*teamCharacters)->characterId].Town1)[(this->numericalCharacterStats).SpriteOutfitLevel * 2];
        memcpy(this->townSpriteRelated, sourceString, stringLength);
      }
      benchedCharacters = teamCharacters + 1;
      teamCharacters = teamCharacters + 1;
    } while (*benchedCharacters != nullptr);
  }
  if (BenchedCharacterList[0] != nullptr) {
    teamCharacters = BenchedCharacterList;
    do {
      if ((*teamCharacters)->shiftedSceneClassUser0x48 == this) {
        stringLength = strlen((&ListOfDefaultCharacterStats[(*teamCharacters)->characterId].Battle1)[(this->numericalCharacterStats).SpriteOutfitLevel * 2]);
        sourceString = (&ListOfDefaultCharacterStats[(*teamCharacters)->characterId].Battle1)[(this->numericalCharacterStats).SpriteOutfitLevel * 2];
        memcpy(this->names, sourceString, stringLength);
        stringLength = strlen((&ListOfDefaultCharacterStats[(*teamCharacters)->characterId].Town1)[(this->numericalCharacterStats).SpriteOutfitLevel * 2]);
        sourceString = (&ListOfDefaultCharacterStats[(*teamCharacters)->characterId].Town1)[(this->numericalCharacterStats).SpriteOutfitLevel * 2];
        memcpy(this->townSpriteRelated, sourceString, stringLength);
      }
      benchedCharacters = teamCharacters + 1;
      teamCharacters = teamCharacters + 1;
    } while (*benchedCharacters != nullptr);
  }
}

__forceinline void SceneClassUser::RestoreFullHealth_0x7d34() {
  (this->numericalCharacterStats).CurrentHp = (this->numericalCharacterStats).MaxHp;
}

__forceinline void SceneClassUser::UpdateAllyPathfinding_0x7d26() {
  if (this->allySupportPathfinding != nullptr) {
    this->allySupportPathfinding->GenerateInitialPathNodes(this->floatMultiplier1_pos1, this->floatMultiplier2_pos2, (((this->numericalCharacterStats).Eye * 20) / 100) + 2);
  }
}

__forceinline void SceneClassUser::ResetEventCounter_0x7d32() {
  this->eventCounter = 0;
}

void SceneClassUser::primarySwitchSingleParam(int32_t switchParam, intptr_t param_2, intptr_t param_3) {
  int32_t param3AsInt = param_2;

  switch (switchParam) {

  case 0x7d11: {
    this->mainSceneHandler = (SceneHandler*)param_2;
    this->mainSceneHandler->primarySwitchSingleParam(0x7d0f, (intptr_t)(GameWindowBase*)this, 0x0);
    this->pathfindingInputObj = new PathfindingState(this->mainSceneHandler);

    PathfindingState* allyPathfindingState;
    if ((this->userFlags & UserFlag::USERFLAG_IS_UNKNOWN1) != 0) {
      allyPathfindingState = new PathfindingState(this->mainSceneHandler);
    }
    else {
      allyPathfindingState = nullptr;
    }
    this->allySupportPathfinding = allyPathfindingState;

    this->primarySwitchSingleParam(0x7d24, MapTypeEnum(param_3), 0x0);
    int32_t rngMod100 = PseudoRng() % 100;
    this->statusInternalTimer = rngMod100;
    this->currentSolidSpriteFrame = __InlineGetSolidSpriteFrameForActionWithOrientation(this->actWalk, this->genericAct, this->orientation - 1, rngMod100);
    this->currentShadowSpriteFrame = this->genericAct->GetShadowSpriteForAction(this->actWalk, rngMod100, (this->orientation - 1) & 7);
  } break;

  case 0x7d3b:
    Case_0x7d3b();
    break;

  case 0x7d3c:
    DispatchAutonomousUpdate_0x7d3c(param_2);
    break;

  case 0x7d40:
    Case_0x7d40(param_2, param_3);
    break;

  case 0x7d00:
    QueueWalkPosition_0x7d00(param_2, param_3);
    break;

  case 0x7d04:
    Case_0x7d04(param_2);
    break;

  case 0x7d15:
    QueueWalkToGate_0x7d15(param_2, param_3);
    break;

  case 0x7d18:
    QueueWalkToTalker_0x7d18(param_2, param_3);
    break;

  case 0x7d3f:
    Case_0x7d3f(param_2, param_3);
    break;

  case 0x7d02:
    Case_0x7d02(param_2);
    break;

  case 0x7d03: {
    ActiveCharacter** teamCharNextPtr;
    int32_t guardValue;
    int32_t totalSpeed;
    int32_t rng;
    GameWindowBase** selectedUnitPtr;
    ActiveCharacter** teamCharPtr;
    int32_t tempValue;
    ActiveCharacter* activeCharacter;
    int32_t tempStat;
    int32_t armorGuardBonus;
    GameWindowBase* sceneUser;
    int32_t minimumDamage;

    int32_t param4AsInt = param_3;
    int32_t param_4 = param_3;
    NumericalCharacterStats* param3AsNumericalCharacterStats = (NumericalCharacterStats*)param_2;

    totalSpeed = (this->numericalCharacterStats).Speed;
    activeCharacter = nullptr;

    if (((byte)this->userFlags & UserFlag::USERFLAG_IS_ENEMY_OR_PLAYER) == 2) {

      tempStat = __InlineGetActiveCharacterIndex(this);
      activeCharacter = TeamCharacterList[tempStat];

      if (activeCharacter != nullptr) {
        if ((activeCharacter->charEquip).equipmentArmor.quantity < 0) {
          tempStat = 0;
        }
        else {
          tempStat = (activeCharacter->charEquip).equipmentArmor.maxSpeed;
          tempValue = (activeCharacter->charEquip).equipmentArmor.currentSpeed + 1;
          if (tempValue <= tempStat) {
            tempStat = tempValue;
          }

          (activeCharacter->charEquip).equipmentArmor.currentSpeed = tempStat;
          tempStat = tempStat / 100;
        }
        totalSpeed = totalSpeed + (activeCharacter->charEquip).equipmentBoots.speed + tempStat;
        if (TeamCharacterList[0] != nullptr) {
          teamCharPtr = TeamCharacterList;
          do {
            if ((*teamCharPtr != activeCharacter) && (sceneUser = (*teamCharPtr)->shiftedSceneClassUser0x48, sceneUser->mainSceneHandler == this->mainSceneHandler)) {
              sceneUser->primarySwitchSingleParam(0x7d23, this->objectListId, 0x0);
            }
            teamCharNextPtr = teamCharPtr + 1;
            teamCharPtr = teamCharPtr + 1;
          } while (*teamCharNextPtr != nullptr);
        }
      }
    }
    if ((((this->userFlags & UserFlag::USERFLAG_IS_TARGETABLE) != 0) && (param4AsInt != (int32_t)0xffffffff)) && (selectedUnitPtr = this->mainSceneHandler->selectedUnits32, *selectedUnitPtr != this || (selectedUnitPtr[1] != nullptr))) {
      this->primarySwitchSingleParam(0x7d02, param_4, 0x0);
    }
    if ((this->userFlags & UserFlag::USERFLAG_IS_ENEMY_OR_PLAYER) == 1) {
      rng = PseudoRng();
      if (rng % 600 >= (param3AsNumericalCharacterStats->ToHit + totalSpeed)) {
        return;
      }
      tempStat = param3AsNumericalCharacterStats->Power / 10;
      tempValue = param3AsNumericalCharacterStats->Power - (this->numericalCharacterStats).Guard;
      if (tempValue <= tempStat) {
        tempValue = tempStat;
      }
      this->__InlineableQueueEvent(param_4);
      this->__InlineableQueueEvent(tempValue);
    }
    else {
      rng = PseudoRng();
      if (rng % 600 <= (param3AsNumericalCharacterStats->ToHit + totalSpeed)) {
        return;
      }
      if ((activeCharacter == nullptr) || ((activeCharacter->charEquip).equipmentArmor.quantity < 0)) {
        armorGuardBonus = 0;
      }
      else {
        armorGuardBonus = (activeCharacter->charEquip).equipmentArmor.maxGuard;
        tempStat = (activeCharacter->charEquip).equipmentArmor.currentGuard + 1;
        if (tempStat <= armorGuardBonus) {
          armorGuardBonus = tempStat;
        }
        (activeCharacter->charEquip).equipmentArmor.currentGuard = armorGuardBonus;
        armorGuardBonus = armorGuardBonus / 100;
      }
      if ((activeCharacter == nullptr) || ((activeCharacter->charEquip).equipmentBracer.quantity < 0)) {
        tempStat = 0;
      }
      else {
        tempStat = (activeCharacter->charEquip).equipmentBracer.maxGuard;
        tempValue = (activeCharacter->charEquip).equipmentBracer.currentGuard + 1;
        if (tempValue <= tempStat) {
          tempStat = tempValue;
        }
        (activeCharacter->charEquip).equipmentBracer.currentGuard = tempStat;
        tempStat = tempStat / 100;
      }
      if ((activeCharacter == nullptr) || ((activeCharacter->charEquip).equipmentAccessory1.quantity < 0)) {
        tempValue = 0;
      }
      else {
        tempValue = (activeCharacter->charEquip).equipmentAccessory1.maxGuard;
        guardValue = (activeCharacter->charEquip).equipmentAccessory1.guard + 1;
        if (guardValue <= tempValue) {
          tempValue = guardValue;
        }
        (activeCharacter->charEquip).equipmentAccessory1.guard = tempValue;
        tempValue = tempValue / 100;
      }
      if ((activeCharacter == nullptr) || ((activeCharacter->charEquip).equipmentAccessory2.quantity < 0)) {
        guardValue = 0;
      }
      else {
        guardValue = (activeCharacter->charEquip).equipmentAccessory2.maxGuard;
        minimumDamage = (activeCharacter->charEquip).equipmentAccessory2.guard + 1;
        if (minimumDamage <= guardValue) {
          guardValue = minimumDamage;
        }
        (activeCharacter->charEquip).equipmentAccessory2.guard = guardValue;
        guardValue = guardValue / 100;
      }
      minimumDamage = param3AsNumericalCharacterStats->Power / 10;
      tempStat = param3AsNumericalCharacterStats->Power + ((((-guardValue - (this->numericalCharacterStats).Guard) - tempValue) - tempStat) - armorGuardBonus);
      if (tempStat <= minimumDamage) {
        tempStat = minimumDamage;
      }
      this->__InlineableQueueEvent(param_4);
      this->__InlineableQueueEvent(tempStat);
    }
    this->__InlineableQueueEvent(0x7d15);
  } break;

  case 0x7d33:
    Case_0x7d33(param_2, param_3);
    break;

  case 0x7d19:
    QueueTalkTrigger_0x7d19(param_2, param_3);
    break;

  case 0x7d2a:
    Case_0x7d2a(param_2);
    break;

  case 0x7d1b: {
    int32_t itemValue;
    int32_t statCounter;
    uint32_t maxValue;
    uint32_t currentValue;
    SceneClassAniBg_RestoreItemAndSpellcasterAura* particleEffect;
    ItemReferenceCollection* itemCollection;
    char* caption;
    char errorMessage[16];
    int32_t param3AsInt = param_2;

    itemValue = (ItemStruct12k->itemArray[param3AsInt].stats)->itemGroup;
    if (itemValue != 0) {
      itemCollection = ItemStruct12k;
      statCounter = 1;

      do {
        switch (itemValue) {
        case 1:
          GoldAmount = GoldAmount + (&(itemCollection->itemArray[param3AsInt].stats)->itemGroup)[statCounter];
          break;
        case 2:
          itemValue = (&(itemCollection->itemArray[param3AsInt].stats)->itemGroup)[statCounter];
          if (this->voluntaryActionSwitchFlag != 667) {
            if (itemValue < 0) {

              itemValue = (this->numericalCharacterStats).MaxHp * itemValue / 100;
            }
            maxValue = (this->numericalCharacterStats).MaxHp;
            currentValue = (this->numericalCharacterStats).CurrentHp + itemValue;
            if ((int32_t)maxValue < (int32_t)currentValue) {
              currentValue = maxValue;
            }
            (this->numericalCharacterStats).CurrentHp = currentValue;
          }
          this->mainSceneHandler->primarySwitchSingleParam_PlaySoundEffect_0x7d0a(0x1e, nullptr);
          particleEffect = new SceneClassAniBg_RestoreItemAndSpellcasterAura(s_re_hp_act, this->floatMultiplier1_pos1, this->floatMultiplier2_pos2);
          this->mainSceneHandler->primarySwitchSingleParam_TriggerObjectInitialization_0x7d27(particleEffect, 0x0);
          itemCollection = ItemStruct12k;
          break;
        case 3:
          itemValue = (&(itemCollection->itemArray[param3AsInt].stats)->itemGroup)[statCounter];
          if (this->voluntaryActionSwitchFlag != 0x29b) {
            if (itemValue < 0) {
              itemValue = (this->numericalCharacterStats.MaxMp * itemValue) / 100;
            }
            maxValue = (this->numericalCharacterStats).MaxMp;
            currentValue = itemValue + (this->numericalCharacterStats).CurrentMp;
            if ((int32_t)currentValue <= (int32_t)maxValue) {
              maxValue = currentValue;
            }
            (this->numericalCharacterStats).CurrentMp = maxValue;
          }
          this->mainSceneHandler->primarySwitchSingleParam_PlaySoundEffect_0x7d0a(0x1e, nullptr);

          particleEffect = new SceneClassAniBg_RestoreItemAndSpellcasterAura(s_re_mp_act, this->floatMultiplier1_pos1, this->floatMultiplier2_pos2);
          this->mainSceneHandler->primarySwitchSingleParam_TriggerObjectInitialization_0x7d27(particleEffect, 0x0);
          itemCollection = ItemStruct12k;
          break;
        case 4:
          itemValue = (&(itemCollection->itemArray[param3AsInt].stats)->itemGroup)[statCounter];
          if (itemValue == 1) {
            if (this->statusCondition == UnitStatusCondition::DarkenedEye) {
              goto label_cure_status_condition;
            }
          }
          else if (itemValue == 2) {
            if (this->statusCondition == UnitStatusCondition::Wander_Confused) {
              goto label_cure_status_condition;
            }
          }
          else if (itemValue == 3) {
            if (this->statusCondition == UnitStatusCondition::Gloomy_Stopped) {
            label_cure_status_condition:
              this->statusCondition = UnitStatusCondition::Normal;
              this->eventCounter = 0;
              particleEffect = new SceneClassAniBg_RestoreItemAndSpellcasterAura(s_re_dark_act, this->floatMultiplier1_pos1, this->floatMultiplier2_pos2);
              this->mainSceneHandler->primarySwitchSingleParam_TriggerObjectInitialization_0x7d27(particleEffect, 0x0);
              itemCollection = ItemStruct12k;
              break;
            }
          }
          else if ((itemValue == 4) && (this->statusCondition == UnitStatusCondition::DyingRelatesToFlag0x400)) {
            goto label_cure_status_condition;
          }
          break;
        case 5:
          return;
        default:
          sprintf(errorMessage, s_Item__d___d, param3AsInt, itemValue);
          caption = s_item_error;
          WrapperMessageBoxA(errorMessage, caption);
          return;
        }
        itemValue = (&(itemCollection->itemArray[param3AsInt].stats)->aParameter)[statCounter];
        statCounter = statCounter + 2;
      } while (itemValue != 0);
    }
  } break;

  case 0x7d1c: {
    int32_t characterId;
    int32_t itemTypeId;
    int32_t counter;
    ActiveCharacter* activeCharacter;
    InventoryItemSpell* itemSpell;
    GameWindowSpellcast* spellcastWindow;

    characterId = __InlineGetActiveCharacterIndex(this);
    activeCharacter = TeamCharacterList[characterId];
    if ((activeCharacter != nullptr) && (itemTypeId = (&(activeCharacter->charEquip).ActiveSlot1)[param_2].typeId, itemTypeId != 0)) {
      itemSpell = (InventoryItemSpell*)(&(activeCharacter->charEquip).ActiveSlot1 + param_2);
      if ((*itemSpell).quantity > 0) {
        spellcastWindow = new GameWindowSpellcast(this, itemSpell);
        this->mainSceneHandler->mainSceneHandler->primarySwitchSingleParam_TriggerObjectInitialization_0x7d27(spellcastWindow, 0x0);
      }
      else {
        for (counter = 0; counter < 19; counter++) {
          if ((((ItemInventory[counter].equipFlags & 0x700U) == 0) && (ItemInventory[counter].typeId == itemTypeId)) && (0 < ItemInventory[counter].quantity)) {
            this->primarySwitchSingleParam(0x7d1b, ItemInventory[counter].typeId, 0x0);
            ItemInventory[counter].quantity = ItemInventory[counter].quantity + -1;
            return;
          }
        }
        itemSpell->quantity = 0;
        (&(activeCharacter->charEquip).ActiveSlot1)[param_2].typeId = 0;
      }
    }
  } break;

  case 0x7d05:
    UseItem_0x7d05(param_2);
    break;

  case 0x7d2b:
    EquipItemFromInventory_0x7d2b(param_2, param_3);
    break;

  case 0x7d37:
    InitializeStarterEquipment_0x7d37(param_2, param_3);
    break;

  case 0x7d41:
    Case_0x7d41();
    break;

  case 0x7d23:
    SearchNearbyTarget_0x7d23();
    break;

  case 0x7d06:
    Case_0x7d06();
    break;

  case 0x7d07:
    Case_0x7d07();
    break;

  case 0x7d1a:
    AddToSelectedUnits_0x7d1a(param_2);
    break;

  case 0x7d2e: {
    SceneClassItem* item;

    if (this->mainSceneHandler != nullptr) {
      item = new SceneClassItem(this->floatMultiplier1_pos1, this->floatMultiplier2_pos2, param_2, 0x7700);
      this->mainSceneHandler->primarySwitchSingleParam_TriggerObjectInitialization_0x7d27(item, 0x0);
      this->mainSceneHandler->primarySwitchSingleParam(0x7d18, 0x9, 0x0);
    }
  } break;

  case 0x7d0c:
    Case_0x7d0c();
    break;

  case 0x7d12:
    Case_0x7d12();
    break;

  case 0x7d22:
    CalculateSpellImpact_0x7d22(param_2, param_3);
    break;

  case 0x7d1e: {
    uint32_t level;
    SceneClassAniBg_RestoreItemAndSpellcasterAura* levelUpParticleEffect;
    int32_t itemValue;
    int32_t* itemStat;
    ActiveCharacter* activeCharacter;
    char* sceneSpriteName;
    int32_t itemLoopCounter;

    SceneClassUser* this00 = this;
    if (ExperienceTable_Leveling[4] == 666) {
      float previousLevel = ExpRequirementLevel4;
      for (int32_t tmp = 3; tmp < 72; tmp++) {
        ExperienceTable_Leveling[tmp] = previousLevel;
        previousLevel = ExpIncreasePerLevel * previousLevel;
      }
    }

    (this00->numericalCharacterStats).Experience = param3AsInt + (this00->numericalCharacterStats).Experience;

    level = (this00->numericalCharacterStats).Level;
    while (((int32_t)level < 72 && (ExperienceTable_Leveling[level] < (this00->numericalCharacterStats).Experience))) {
      (this00->numericalCharacterStats).Level = level + 1;
      (this00->numericalCharacterStats).Power = (this00->numericalCharacterStats).Power + (((this00->numericalCharacterStats).PowerGrowth * 20) / 100);
      (this00->numericalCharacterStats).ToHit = (this00->numericalCharacterStats).ToHit + (((this00->numericalCharacterStats).ToHitGrowth * 20) / 100);
      (this00->numericalCharacterStats).Guard = (this00->numericalCharacterStats).Guard + (((this00->numericalCharacterStats).GuardGrowth * 20) / 100);
      (this00->numericalCharacterStats).Speed = (this00->numericalCharacterStats).Speed + (((this00->numericalCharacterStats).SpeedGrowth * 20) / 100);
      (this00->numericalCharacterStats).MaxHp = ((this00->numericalCharacterStats).MaxHp * 108) / 100;
      (this00->numericalCharacterStats).MaxMp = ((this00->numericalCharacterStats).MaxMp * 108) / 100;
      (this00->numericalCharacterStats).CurrentHp = (this00->numericalCharacterStats).MaxHp;
      (this00->numericalCharacterStats).CurrentMp = (this00->numericalCharacterStats).MaxMp;
      this00->mainSceneHandler->primarySwitchSingleParam_PlaySoundEffect_0x7d0a(0x49, nullptr);
      levelUpParticleEffect = new SceneClassAniBg_RestoreItemAndSpellcasterAura(s_levelup_act, this00->floatMultiplier1_pos1, this00->floatMultiplier2_pos2);
      this00->mainSceneHandler->primarySwitchSingleParam_TriggerObjectInitialization_0x7d27(levelUpParticleEffect, 0x0);
      level = (this00->numericalCharacterStats).Level;
      if ((level == 20) || (level == 40)) {
        (this00->numericalCharacterStats).SpriteOutfitLevel = (this00->numericalCharacterStats).SpriteOutfitLevel + 1;
        (this00->numericalCharacterStats).Eye = (this00->numericalCharacterStats).Eye + 20;

        for (itemLoopCounter = 0; TeamCharacterList[itemLoopCounter] != nullptr; itemLoopCounter++) {
          if (TeamCharacterList[itemLoopCounter]->shiftedSceneClassUser0x48 == this00) {
            break;
          }
        }

        activeCharacter = TeamCharacterList[itemLoopCounter];
        if (activeCharacter != nullptr) {
          sceneSpriteName = (&ListOfDefaultCharacterStats[activeCharacter->characterId].Battle1)[(this00->numericalCharacterStats).SpriteOutfitLevel * 2];
          strcpy(this00->names, sceneSpriteName);
          sceneSpriteName = (&ListOfDefaultCharacterStats[activeCharacter->characterId].Town1)[(this00->numericalCharacterStats).SpriteOutfitLevel * 2];
          strcpy(this00->townSpriteRelated, sceneSpriteName);

          this00->nameAsAct = nullptr;
          this00->primarySwitchSingleParam_CreateControllableUnit_0x7d24(this00->mainSceneHandler->mapType, 0x0);
          itemStat = &(activeCharacter->charEquip).equipmentWeapon.currentPower;
          itemLoopCounter = 0x2c;
          do {
            if (((((uint32_t)itemStat[-3] & 0x700) == 0x700) && (*itemStat == 2)) && (itemStat[2] < 3)) {
              itemValue = itemStat[-4];
              itemStat[-4] = itemValue + 1;
              itemStat[-2] = ItemStruct12k->itemArray[itemValue + 1].actOffset;
            }
            itemStat = itemStat + 0x13;
            itemLoopCounter = itemLoopCounter + -1;
          } while (itemLoopCounter != 0);
        }
      }
      level = (this00->numericalCharacterStats).Level;
    }
  } break;

  case 0x7d13:
    SetPosition_0x7d13(param_2, param_3);
    break;

  case 0x7d38:
    UpdateOrientation_0x7d38(param_2);
    break;

  case 0x7d3a:
    Case_0x7d3a(param_2);
    break;

  case 0x7d3d:
    Case_0x7d3d(param_2);
    break;

  case 0x7d36: {
    int32_t characterIndex;
    ActiveCharacter* activeCharacter;
    SceneClassAniBg_RestoreItemAndSpellcasterAura* particleEffect;

    this->__InlineableQueueEvent(0x7d1c);
    characterIndex = __InlineGetActiveCharacterIndex(this);
    activeCharacter = TeamCharacterList[characterIndex];
    if (activeCharacter == nullptr) {
      return;
    }
    if (PointersMagicAnimation[activeCharacter->characterId] == nullptr) {
      return;
    }
    particleEffect = new SceneClassAniBg_RestoreItemAndSpellcasterAura(PointersMagicAnimation[activeCharacter->characterId], this->floatMultiplier1_pos1, this->floatMultiplier2_pos2);
    this->mainSceneHandler->primarySwitchSingleParam_TriggerObjectInitialization_0x7d27(particleEffect, 0x0);
  } break;

  case 0x7d34:
    RestoreFullHealth_0x7d34();
    break;

  case 0x7d26:
    UpdateAllyPathfinding_0x7d26();
    break;

  case 0x7d32:
    ResetEventCounter_0x7d32();
    break;

  case 0x7d24: {
    int32_t counter;
    int32_t actionId;
    byte* namePtr;
    CoreActClass* actObject;
    SceneClassUser* worldMapSceneClassUser;
    ObjectWrapper* sceneObjectPtr;
    int32_t* actionPtr;
    int32_t param3AsInt = param_2;

    if (param3AsInt == (int32_t)MapType::World) {
      if ((this->userFlags & UserFlag::USERFLAG_WORLDMAP_CHARACTER) == 0) {
        counter = 0;
        sceneObjectPtr = ObjectList;
        do {
          if ((sceneObjectPtr->sceneClassObjectPointer != nullptr) && ((sceneObjectPtr->scriptUserFlags & 0x200000U) != 0)) {
            return;
          }
          counter = counter + 1;
          sceneObjectPtr = sceneObjectPtr + 1;
        } while (counter < 0x8000);

        worldMapSceneClassUser = new SceneClassUser(this->floatMultiplier1_pos1, this->floatMultiplier2_pos2, s_wtoby_act, 0x200996, 0, 0);
        if (worldMapSceneClassUser != nullptr) {
          this->mainSceneHandler->primarySwitchSingleParam_TriggerObjectInitialization_0x7d27(worldMapSceneClassUser, 0x0);
          return;
        }
      }
      param3AsInt = 0x1;
    }
    actObject = this->genericAct;
    if (actObject != nullptr) {
      namePtr = (byte*)this->nameAsAct;
      if (namePtr != nullptr) {
        counter = strcmp(this->names + (param3AsInt * 0x10), (char*)namePtr);
        if (counter == 0) {
          return;
        }
      }
      if (actObject != nullptr) {

        delete actObject;
        this->genericAct = nullptr;
      }
    }
    this->nameAsAct = this->names + (param3AsInt * 0x10);
    actObject = new CoreActClass(this->nameAsAct);

    this->genericAct = actObject;
    if (param_3 != 0x0) {
      FillMemory(&this->numericalCharacterStats, sizeof(NumericalCharacterStats), 0);
      int32_t hp = this->genericAct->__InlineGetActionIndexFromName(s__hp);
      (this->numericalCharacterStats).MaxHp = hp;
      (this->numericalCharacterStats).CurrentHp = hp;
      int32_t mp = this->genericAct->__InlineGetActionIndexFromName(s__mp);
      (this->numericalCharacterStats).MaxMp = mp;
      (this->numericalCharacterStats).CurrentMp = mp;
      (this->numericalCharacterStats).Power = this->genericAct->__InlineGetActionIndexFromName(s__power);
#if PATCH_FIX_MONSTER_TOHIT_SPEED == 0
      (this->numericalCharacterStats).ToHit = this->genericAct->__InlineGetActionIndexFromName(s__speed);
      (this->numericalCharacterStats).Speed = this->genericAct->__InlineGetActionIndexFromName(s__tohit);
#else
      (this->numericalCharacterStats).ToHit = this->genericAct->__InlineGetActionIndexFromName(s__tohit);
      (this->numericalCharacterStats).Speed = this->genericAct->__InlineGetActionIndexFromName(s__speed);
#endif
      (this->numericalCharacterStats).Guard = this->genericAct->__InlineGetActionIndexFromName(s__guard);
      (this->numericalCharacterStats).Eye = this->genericAct->__InlineGetActionIndexFromName(s__eye);
      (this->numericalCharacterStats).ExpPerKill = this->genericAct->__InlineGetActionIndexFromName(s__addexp);
      (this->numericalCharacterStats).Experience = 0;
    }
    this->actStand = this->genericAct->GetActionIndexByName(s_stand);
    this->actWalk = this->genericAct->GetActionIndexByName(s_walk);
    this->act1Natt1 = this->genericAct->GetActionIndexByName(s_1natt1);
    this->act2Natt1 = this->genericAct->GetActionIndexByName(s_2natt1);
    this->act3Natt1 = this->genericAct->GetActionIndexByName(s_3natt1);
    actionPtr = &this->act1Natt2;
    *actionPtr = this->genericAct->GetActionIndexByName(s_1natt2);
    this->act2Natt2 = this->genericAct->GetActionIndexByName(s_2natt2);
    this->act3Natt2 = this->genericAct->GetActionIndexByName(s_3natt2);
    counter = 3;
    do {
      if (actionPtr[-3] < 0) {
        actionId = this->genericAct->GetActionIndexByName(s_natt1);
        actionPtr[-3] = actionId;
      }
      if (*actionPtr < 0) {
        actionId = this->genericAct->GetActionIndexByName(s_natt2);
        *actionPtr = actionId;
      }
      actionPtr = actionPtr + 1;
      counter = counter + -1;
    } while (counter != 0);
    this->actGuard1 = this->genericAct->GetActionIndexByName(s_guard1);
    this->actGuard2 = this->genericAct->GetActionIndexByName(s_guard2);
    this->actDamage = this->genericAct->GetActionIndexByName(s_damage);
    this->actDead = this->genericAct->GetActionIndexByName(s_dead);
    this->actMagic = this->genericAct->GetActionIndexByName(s_magic);
    this->actSpecialAtt = this->genericAct->GetActionIndexByName(s_satt);
    this->halfIndex = this->genericAct->GetFrameCountForAction(this->actWalk) / 2;
    this->currentSolidSpriteFrame = __InlineGetSolidSpriteFrameForActionWithOrientation(this->actStand, this->genericAct, this->orientation - 1, 0);
    this->currentShadowSpriteFrame = __InlineGetSolidSpriteFrameForActionWithOrientation(this->actStand, this->genericAct, this->orientation - 1, 0);
  } break;

  default:
    WrapperMessageBoxA(s_object, s___);
    break;
  }
}
