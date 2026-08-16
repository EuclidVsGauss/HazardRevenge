#include <stdio.h>
#include "HazardClasses/AnimationSpell.hpp"
#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/BloodObject.hpp"
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/EventHandler.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/PathfindingState.hpp"
#include "HazardClasses/SceneClassItem.hpp"
#include "HazardClasses/SceneClassUser.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardEnums/MapType.hpp"
#include "HazardEnums/SpriteFrameSceneClass.hpp"
#include "HazardEnums/UserFlag.hpp"
#include "HazardExterns/SceneClassUser.hpp"
#include "HazardGlobals.hpp"
#include "HazardInlineFunctions.hpp"
#include "HazardStructs/ActContent.hpp"
#include "HazardStructs/ActiveCharacter.hpp"
#include "HazardStructs/CharacterEquipment.hpp"
#include "HazardStructs/DirectionOffsets.hpp"
#include "HazardStructs/DirectionalTuple.hpp"
#include "HazardStructs/InventoryItemAccessory.hpp"
#include "HazardStructs/InventoryItemArmor.hpp"
#include "HazardStructs/InventoryItemBracer.hpp"
#include "HazardStructs/InventoryItemSharant.hpp"
#include "HazardStructs/InventoryItemStruct.hpp"
#include "HazardStructs/InventoryItemWeapon.hpp"
#include "HazardStructs/ItemReferenceCollection.hpp"
#include "HazardStructs/ItemReferenceStruct.hpp"
#include "HazardStructs/ItemStatsTemplate.hpp"
#include "HazardStructs/NumericalCharacterStats.hpp"
#include "HazardStructs/ObjectWrapper.hpp"
#include "HazardStructs/PathfindingNode.hpp"
#include "HazardStructs/QueueEventContainer.hpp"

typedef int32_t ItemSlotEnum;

struct ItemSlot {
  enum Value {
    Weapon = 0,
    Armor = 1,
    Bracer = 2,
    Boots = 3,
    Accessory1 = 4,
    Accessory2 = 5,
  };
};

typedef int32_t ItemAttributeEnum;

struct ItemAttribute {
  enum Value {
    CurrentPower = 5,
    MaxPower = 6,
    CurrentToHit = 7,
    MaxToHit = 8,
    AccessoryCurrentPower = 12,
    AccessoryMaxPower = 13,
  };
};

__forceinline int32_t __InlineItemAttribute(ActiveCharacter* character, ItemSlotEnum itemSlot, ItemAttributeEnum currentItemAttribute, ItemAttributeEnum maxItemAttribute) {
  int32_t maxPower;
  int32_t latestPower;
  int32_t outPower;
  InventoryItemStruct item;

  if ((character == nullptr) || (item = ((InventoryItemStruct*)&character->charEquip)[itemSlot], item.quantity < 0)) {
    outPower = 0x0;
  }
  else {
    maxPower = ((ItemAttributeEnum*)&item)[maxItemAttribute];
    latestPower = ((ItemAttributeEnum*)&item)[currentItemAttribute] + 1;
    if (latestPower <= maxPower) {
      maxPower = latestPower;
    }
    ((ItemAttributeEnum*)&item)[currentItemAttribute] = maxPower;
    outPower = (maxPower / 100);
  }
  return outPower;
}

__forceinline int32_t __InlineAccessoryPower(ActiveCharacter* character, ItemSlotEnum itemSlot) {
  int32_t maxPower;
  int32_t latestPower;
  int32_t outPower;
  InventoryItemAccessory item;

  if ((character == nullptr) || (item = ((InventoryItemAccessory*)&character->charEquip)[itemSlot], item.quantity < 0)) {
    outPower = 0x0;
  }
  else {
    maxPower = item.maxPower;
    latestPower = item.power;
    if (latestPower <= maxPower) {
      maxPower = latestPower;
    }
    item.power = maxPower;
    outPower = (maxPower / 100);
  }
  return outPower;
}

__forceinline int32_t __InlineWeaponItemPower(ActiveCharacter* character) {
  int32_t maxPower;
  int32_t latestPower;
  int32_t outPower;

  if ((character == nullptr) || ((character->charEquip).equipmentWeapon.quantity < 0)) {
    outPower = 0x0;
  }
  else {
    maxPower = (character->charEquip).equipmentWeapon.maxPower;
    latestPower = (character->charEquip).equipmentWeapon.currentPower + 1;
    if (latestPower <= maxPower) {
      maxPower = latestPower;
    }
    (character->charEquip).equipmentWeapon.currentPower = maxPower;
    outPower = (maxPower / 100);
  }
  return outPower;
}

__forceinline int32_t __InlineArmorItemPower(ActiveCharacter* character) {
  int32_t maxPower;
  int32_t latestPower;
  int32_t outPower;

  if ((character == nullptr) || ((character->charEquip).equipmentArmor.quantity < 0)) {
    outPower = 0x0;
  }
  else {
    maxPower = (character->charEquip).equipmentArmor.maxPower;
    latestPower = (character->charEquip).equipmentArmor.currentPower + 1;
    if (latestPower <= maxPower) {
      maxPower = latestPower;
    }
    (character->charEquip).equipmentArmor.currentPower = maxPower;
    outPower = (maxPower / 100);
  }
  return outPower;
}

__forceinline int32_t __InlineBracerItemPower(ActiveCharacter* character) {
  int32_t maxPower;
  int32_t latestPower;
  int32_t outPower;

  if ((character == nullptr) || ((character->charEquip).equipmentBracer.quantity < 0)) {
    outPower = 0x0;
  }
  else {
    maxPower = (character->charEquip).equipmentBracer.maxPower;
    latestPower = (character->charEquip).equipmentBracer.currentPower + 1;
    if (latestPower <= maxPower) {
      maxPower = latestPower;
    }
    (character->charEquip).equipmentBracer.currentPower = maxPower;
    outPower = (maxPower / 100);
  }
  return outPower;
}

__forceinline int32_t __InlineSignDifference(int32_t a, int32_t b) {

  if (a == b) {
    return 0;
  }
  else {
    return (((a <= b) - 1) & 2) - 1;
  }
}

__forceinline int32_t __InlineIs2x2AreaBlocked(SceneClassUser* sceneClassUser, int32_t coordX, int32_t coordY) {
  int32_t x;
  int32_t y;

  for (y = 0; y < 2; y++) {
    for (x = 0; x < 2; x++) {
      if (sceneClassUser->mainSceneHandler->PaddedGridMap_Collision[coordY + y][coordX + x] == -1) {
        return 1;
      }
    }
  }
  return 0;
}

__forceinline int32_t __InlineFirstNonBlockedCharacterIdIn2x2Area(SceneClassUser* sceneClassUser, int32_t coordX, int32_t coordY) {
  int32_t x;
  int32_t y;
  int32_t value;

  for (y = 0; y < 2; y++) {
    for (x = 0; x < 2; x++) {
      value = sceneClassUser->mainSceneHandler->PaddedGridMap_Collision[coordY + y][coordX + x];
      if ((-1 < value) && (value != sceneClassUser->objectListId)) {
        return 1;
      }
    }
  }
  return 0;
}

__forceinline int32_t __InlinePopEventQueueDecrement2(SceneClassUser* sceneClassUser, int32_t currentCounter, int32_t previousCounter) {
  int32_t value;
  if (currentCounter < 1) {
    value = 0;
  }
  else {
    currentCounter = previousCounter - 2;
    sceneClassUser->eventCounter = currentCounter;
    value = sceneClassUser->queuedEventsArray[currentCounter >> 8]->queueEvents[currentCounter & 0xff];
  }
  return value;
}

__forceinline int32_t __InlinePopEventQueueDecrement(SceneClassUser* sceneClassUser) {
  if (sceneClassUser->eventCounter < 1) {
    return 0;
  }
  else {
    sceneClassUser->eventCounter--;
    return sceneClassUser->queuedEventsArray[sceneClassUser->eventCounter >> 8]->queueEvents[sceneClassUser->eventCounter & 0xff];
  }
}

__forceinline int32_t __InlineCappedPopEventQueueDecrement(SceneClassUser* sceneClassUser, int32_t cappedValue) {
  if (sceneClassUser->eventCounter < 1) {
    return 0;
  }
  else {
    sceneClassUser->eventCounter--;
    int32_t value = sceneClassUser->queuedEventsArray[sceneClassUser->eventCounter >> 8]->queueEvents[sceneClassUser->eventCounter & 0xff];
    if (value >= cappedValue) {
      return cappedValue;
    }
    return value;
  }
}

__forceinline void __InlineUpdateSpriteFrames(SceneClassUser* sceneClassUser, int32_t actionIndex, int32_t index) {
  CoreActClass* coreAct = sceneClassUser->genericAct;
  sceneClassUser->currentSolidSpriteFrame = GameWindowBase::__InlineGetSolidSpriteFrameForActionWithOrientation(actionIndex, sceneClassUser->genericAct, sceneClassUser->orientation - 1, index);
  sceneClassUser->currentShadowSpriteFrame = coreAct->GetShadowSpriteForAction(actionIndex, index, (sceneClassUser->orientation - 1) & 7);
}

__forceinline ActiveCharacter* __InlineGetTeamCharacterForSceneUser(SceneClassUser* sceneClassUser) {
  SceneClassUser* sceneClassUserOrNull = (sceneClassUser != nullptr) ? sceneClassUser : nullptr;
  int32_t counter = 0;

  if (TeamCharacterList[0] != nullptr) {
    ActiveCharacter** activeCharacterList = TeamCharacterList;
    ActiveCharacter* activeCharacter = TeamCharacterList[0];
    do {
      if (activeCharacter->shiftedSceneClassUser0x48 == sceneClassUserOrNull) {
        break;
      }
      activeCharacter = activeCharacterList[1];
      activeCharacterList = activeCharacterList + 1;
      counter = counter + 1;
    } while (activeCharacter != nullptr);
  }
  return TeamCharacterList[counter];
}

__forceinline void __InlineMoveDeadCharacterToBenchedList(SceneClassUser* sceneClassUser) {
  ActiveCharacter** slotIterator;
  ActiveCharacter** activeListIterator;
  int32_t teamListIndex;
  ActiveCharacter* currentCharacter;
  ActiveCharacter** teamListIterator;
  int32_t activeSlotCounter;
  SceneClassUser* targetSceneUser;
  int32_t benchedListIndex;

  teamListIndex = 0;
  if (TeamCharacterList[0] != nullptr) {
    teamListIterator = TeamCharacterList;
    currentCharacter = TeamCharacterList[0];
    do {
      if (sceneClassUser == nullptr) {
        targetSceneUser = nullptr;
      }
      else {
        targetSceneUser = sceneClassUser;
      }
      if (currentCharacter->shiftedSceneClassUser0x48 == targetSceneUser) {
        break;
      }
      currentCharacter = teamListIterator[1];
      teamListIterator = teamListIterator + 1;
      teamListIndex = teamListIndex + 1;
    } while (currentCharacter != nullptr);
  }
  currentCharacter = TeamCharacterList[teamListIndex];
  teamListIterator = TeamCharacterList + teamListIndex;
  if (currentCharacter == nullptr) {
    return;
  }
  benchedListIndex = 0;
  activeSlotCounter = 0;
  activeListIterator = ActiveTeamCharacterSlots;
  do {
    if (*activeListIterator == nullptr) {
      if (activeSlotCounter == teamListIndex) {
        ActiveTeamCharacterSlots[benchedListIndex] = currentCharacter;
        break;
      }
      activeSlotCounter = activeSlotCounter + 1;
    }
    activeListIterator = activeListIterator + 1;
    benchedListIndex = benchedListIndex + 1;
  } while (activeListIterator < ActiveTeamCharacterSlots + 5);
  benchedListIndex = 0;
  if (BenchedCharacterList[0] != nullptr) {
    activeListIterator = BenchedCharacterList;
    do {
      slotIterator = activeListIterator + 1;
      activeListIterator = activeListIterator + 1;
      benchedListIndex = benchedListIndex + 1;
    } while (*slotIterator != nullptr);
  }
  BenchedCharacterList[benchedListIndex] = currentCharacter;
  BenchedCharacterList[benchedListIndex + 1] = nullptr;
  currentCharacter = TeamCharacterList[teamListIndex + 1];
  *teamListIterator = currentCharacter;
  while (currentCharacter != nullptr) {
    currentCharacter = teamListIterator[2];
    teamListIterator = teamListIterator + 1;
    *teamListIterator = currentCharacter;
  }
  sceneClassUser->numericalCharacterStats.CurrentHp = 1;
  sceneClassUser->numericalCharacterStats.CurrentMp = 1;
  if (TeamCharacterList[0] == nullptr) {
    sceneClassUser->mainSceneHandler->primarySwitchSingleParam(0x7d39, 0x0, 0x0);
  }
  sceneClassUser->primarySwitchSingleParam_PrepareMapForUnit_0x7d12(0x0, 0x0);
}

inline void AutonomousUpdate_0x7d00_Pathfinding(SceneClassUser* sceneClassUser) {
  int32_t directionCounter;
  int32_t targetCoord1;
  int32_t targetCoord2;

  targetCoord1 = __InlinePopEventQueueDecrement(sceneClassUser);
  targetCoord2 = __InlinePopEventQueueDecrement(sceneClassUser);
  if ((targetCoord1 == sceneClassUser->floatMultiplier1_pos1) && (targetCoord2 == sceneClassUser->floatMultiplier2_pos2)) {
    return;
  }

  if (__InlineIs2x2AreaBlocked(sceneClassUser, targetCoord1, targetCoord2)) {
    for (directionCounter = 0x0; directionCounter < 8; directionCounter = directionCounter + 1) {
      if (!__InlineIs2x2AreaBlocked(sceneClassUser, DirectionalTuples[directionCounter].rng1 - 4 + targetCoord1, DirectionalTuples[directionCounter].rng2 + targetCoord2)) {
        targetCoord1 = targetCoord1 + DirectionalTuples[directionCounter].rng1;
        targetCoord2 = targetCoord2 + DirectionalTuples[directionCounter].rng2;
        break;
      }
    }
  }

  sceneClassUser->pathfindingInputObj->SetStartAndTargetCoordinates(sceneClassUser->floatMultiplier1_pos1, sceneClassUser->floatMultiplier2_pos2, targetCoord1, targetCoord2);
  sceneClassUser->__InlineQueueEvent(0);
  sceneClassUser->QueueEvent(0x7d01);
}

inline void AutonomousUpdate_0x7d01_Pathfinding(SceneClassUser* sceneClassUser) {
  char orientation;
  PathfindingNode* pathfindingNode;
  int32_t eventValue;

  if (sceneClassUser->eventCounter > 0) {
    sceneClassUser->eventCounter--;
    eventValue = sceneClassUser->queuedEventsArray[sceneClassUser->eventCounter >> 8]->queueEvents[sceneClassUser->eventCounter & 0xff];
    if (eventValue >= 0x40) {
      goto label_update_stand_sprite;
    }
  }
  else {
    eventValue = 0;
  }

  pathfindingNode = sceneClassUser->pathfindingInputObj->FindPath_AvoidWallsOnly();
  if (pathfindingNode != nullptr) {
    do {
      orientation = pathfindingNode->directionFromParent;
      sceneClassUser->__InlineQueueEvent(orientation);
      sceneClassUser->QueueEvent(0x7d04);
      pathfindingNode = pathfindingNode->linkToParentNode;
    } while (pathfindingNode != nullptr);
  }
  else {
    sceneClassUser->QueueEvent(eventValue + 1);
    sceneClassUser->QueueEvent(0x7d01);
  }
label_update_stand_sprite:
  if (eventValue < 0x18) {
    return;
  }
  __InlineUpdateSpriteFrames(sceneClassUser, sceneClassUser->actStand, eventValue - 0x18);
}

inline void AutonomousUpdate_0x7d04_Pathfinding(SceneClassUser* sceneClassUser) {

  GameWindowBase* sceneObject;
  int32_t localEventCounter;
  int32_t secondEventCounter;
  int32_t actionIndexRelated;
  int32_t* localCounter;
  int32_t userFlags;
  int32_t coordY;
  UnitStatusConditionEnum statusCondition;
  int32_t collisionStatus;
  int32_t coordY_2;
  int32_t value;
  int32_t loopCounter;
  int32_t* loopPtr;
  int32_t localArray[100];

  value = __InlinePopEventQueueDecrement(sceneClassUser);
  statusCondition = sceneClassUser->statusCondition;
  sceneClassUser->orientation = value;
  if (statusCondition == UnitStatusCondition::Frozen_Stopped) {
    return;
  }
  if (statusCondition == UnitStatusCondition::Gloomy_Stopped) {
    return;
  }

  coordY = sceneClassUser->floatMultiplier2_pos2;
  collisionStatus = __InlineHasUnoccupiedTileExcludingTypeInRectangularRegion(sceneClassUser->mainSceneHandler, DirectionalTuples[value].rng1 + sceneClassUser->floatMultiplier1_pos1, DirectionalTuples[value].rng2 + sceneClassUser->floatMultiplier2_pos2, 2, 2, sceneClassUser->objectListId);
  if (collisionStatus != -1) {
    userFlags = sceneClassUser->userFlags;
    if (((userFlags & 8) == 1) && ((userFlags = userFlags & 3, userFlags == 1 && ((ObjectList[collisionStatus].scriptUserFlags & 3) == 2)) || (userFlags == 2 && ((ObjectList[collisionStatus].scriptUserFlags & 3) == 1)))) {
      sceneClassUser->eventCounter = 0;
      sceneClassUser->QueueEvent(collisionStatus);
      sceneClassUser->QueueEvent(0x7d0a);
      return;
    }

    sceneClassUser->QueueEvent(value);
    sceneClassUser->QueueEvent(0x7d04);
    coordY_2 = sceneClassUser->floatMultiplier2_pos2;
    value = sceneClassUser->floatMultiplier1_pos1;
    loopPtr = localArray;
    loopCounter = 0;
  label_process_queued_path_events:
    coordY = sceneClassUser->eventCounter;
    if (coordY > 0) {
      localEventCounter = coordY + -1;
      sceneClassUser->eventCounter = localEventCounter;
      actionIndexRelated = sceneClassUser->queuedEventsArray[localEventCounter >> 8]->queueEvents[localEventCounter & 0xff];
      if (actionIndexRelated == 0x7d04) {
        if (localEventCounter > 0) {
          secondEventCounter = coordY + -2;
          sceneClassUser->eventCounter = secondEventCounter;
          coordY = sceneClassUser->queuedEventsArray[secondEventCounter >> 8]->queueEvents[secondEventCounter & 0xff];
        }
        else {
          coordY = 0;
        }
        value = value + DirectionalTuples[coordY].rng1;
        *loopPtr = coordY;
        coordY_2 = coordY_2 + DirectionalTuples[coordY].rng2;
        userFlags = __InlineHasUnoccupiedTileExcludingTypeInRectangularRegion(sceneClassUser->mainSceneHandler, value, coordY_2, 2, 2, sceneClassUser->objectListId);
        if (userFlags == -1) {
          value = loopCounter + 1;
          if ((sceneClassUser->userFlags & UserFlag::USERFLAG_IS_ENEMY_OR_PLAYER) != 1) {
            sceneObject = ObjectList[collisionStatus].sceneClassObjectPointer;
            coordY = sceneClassUser->orientation;
            sceneObject->primarySwitchSingleParam(0x7d41, (DirectionalTuples[coordY].rng1 + sceneClassUser->floatMultiplier1_pos1), (DirectionalTuples[coordY].rng2 + sceneClassUser->floatMultiplier2_pos2));
          }

          for (localCounter = localArray + loopCounter; value > 0; value--, localCounter--) {
            sceneClassUser->QueueEvent(*localCounter);
            sceneClassUser->QueueEvent(0x7d04);
          }

          sceneClassUser->QueueEvent(0);
          sceneClassUser->QueueEvent(0x7d05);
          sceneClassUser->QueueEvent((PseudoRng() & 7) + 4);
          sceneClassUser->QueueEvent(0);
          sceneClassUser->QueueEvent(0x7d18);
          return;
        }
        loopCounter = loopCounter + 1;
        loopPtr = loopPtr + 1;
        goto label_process_queued_path_events;
      }
    }
    else {
      actionIndexRelated = 0;
    }
    sceneClassUser->__InlineQueueEvent(actionIndexRelated);
    return;
  }

  if (__InlineIs2x2AreaBlocked(sceneClassUser, DirectionalTuples[value].rng1 + sceneClassUser->floatMultiplier1_pos1, DirectionalTuples[value].rng2 + sceneClassUser->floatMultiplier2_pos2)) {
    sceneClassUser->eventCounter = 0;
    sceneClassUser->QueueEvent((PseudoRng() & 0xf) + 4);
    sceneClassUser->QueueEvent(0);
    sceneClassUser->QueueEvent(0x7d18);
    return;
  }
  actionIndexRelated = sceneClassUser->halfIndex;
  sceneClassUser->statusInternalTimer = actionIndexRelated;
  sceneClassUser->frameIndexRelated = actionIndexRelated - sceneClassUser->frameIndexRelated;
  sceneClassUser->voluntaryActionSwitchFlag = 0x7d04;
  sceneClassUser->float1 = ((float)DirectionalTuples[value].rng1 * GridMultiplier_16) / (float)actionIndexRelated;
  sceneClassUser->float2 = ((float)DirectionalTuples[value].rng2 * GridMultiplier_16) / (float)actionIndexRelated;
  sceneClassUser->mainSceneHandler->SetCollisionValueInRectangularRegion(sceneClassUser->floatMultiplier1_pos1, coordY, 2, 2, -2);

  int32_t orientation = sceneClassUser->orientation;
  int32_t newCoordY = sceneClassUser->floatMultiplier2_pos2 + DirectionalTuples[orientation].rng2;
  sceneClassUser->floatMultiplier2_pos2 = newCoordY;
  int32_t newCoordX = sceneClassUser->floatMultiplier1_pos1 + DirectionalTuples[orientation].rng1;
  sceneClassUser->floatMultiplier1_pos1 = newCoordX;
  sceneClassUser->mainSceneHandler->SetCollisionValueInRectangularRegion(newCoordX, newCoordY, 2, 2, (int16_t)sceneClassUser->objectListId);
  sceneClassUser->UpdateObjectOnGrid(sceneClassUser->floatMultiplier1_pos1 << 4, sceneClassUser->floatMultiplier2_pos2 << 4);
  sceneClassUser->primarySwitchSingleParam(0x7d26, NULL, NULL);
}

inline void AutonomousUpdate_BarrageCheck_0x7d0a(SceneClassUser* sceneClassUser) {
  SceneHandler* sceneHandler;
  GameWindowBase* sceneObject;
  GameWindowBase** selectableUnits;
  int32_t coordX;
  GameWindowBase* sceneClassUserCopy;
  int32_t coordY;
  int32_t counter;
  ActiveCharacter* activeCharacter;
  int32_t orientation;
  int32_t objectIndex;

  objectIndex = __InlinePopEventQueueDecrement(sceneClassUser);
  if (sceneClassUser->statusCondition == UnitStatusCondition::Frozen_Stopped) {

    return;
  }
  if (objectIndex < 0) {

    return;
  }
  sceneObject = ObjectList[objectIndex].sceneClassObjectPointer;
  if (sceneObject == nullptr) {

    return;
  }
  sceneHandler = sceneClassUser->mainSceneHandler;
  if (sceneObject->mainSceneHandler != sceneHandler) {

    return;
  }
  coordY = sceneClassUser->floatMultiplier2_pos2;

  for (counter = 0x0; counter < 8; counter++) {
    orientation = sceneClassUser->orientation;
    coordX = sceneClassUser->floatMultiplier1_pos1;
    if (((sceneHandler->PaddedGridMap_Collision[HitRngRelated1[orientation].DeltaY1 + coordY][(HitRngRelated1[orientation].DeltaX1 + coordX)]) == objectIndex) || ((sceneHandler->PaddedGridMap_Collision[HitRngRelated1[orientation].DeltaY2 + coordY][(HitRngRelated1[orientation].DeltaX2 + coordX)]) == objectIndex)) {
      goto label_check_selected_unit;
    }
    sceneClassUser->orientation = (orientation + 1) & 7;
  }
  return;

label_check_selected_unit:
  if (sceneClassUser == nullptr) {
    sceneClassUserCopy = nullptr;
  }
  else {
    sceneClassUserCopy = (GameWindowBase*)sceneClassUser;
  }
  selectableUnits = sceneHandler->selectedUnits32;
  if ((*selectableUnits != sceneClassUserCopy) || (selectableUnits[1] != nullptr)) {
    sceneClassUser->__InlineableQueueEvent(objectIndex);
    sceneClassUser->__InlineableQueueEvent(0x7d0a);
  }
  sceneObject = ObjectList[objectIndex].sceneClassObjectPointer;
  orientation = (((sceneClassUser->floatMultiplier2_pos2 - sceneObject->matrixIndexYTimes16) * 5) - sceneObject->matrixIndexXTimes16) + 0xc + sceneClassUser->floatMultiplier1_pos1;
  if (orientation < 0) {

    return;
  }
  if (0x19 <= orientation) {
    return;
  }

  if ((orientation & 1) == 0) {
    sceneClassUser->orientation = MovementLookupTable2[orientation];

    activeCharacter = __InlineGetTeamCharacterForSceneUser(sceneClassUser);

    if (((activeCharacter != nullptr) && (coordY = (uint32_t)(0 < (activeCharacter->charEquip).SharantSlot1.quantity) + (uint32_t)(0 < (activeCharacter->charEquip).SharantSlot2.quantity) + (uint32_t)(0 < (activeCharacter->charEquip).SharantSlot3.quantity) + (uint32_t)(0 < (activeCharacter->charEquip).SharantSlot4.quantity) + (uint32_t)(0 < (activeCharacter->charEquip).SharantSlot5.quantity) + (uint32_t)(0 < (activeCharacter->charEquip).SharantSlot6.quantity) + activeCharacter->characterBaseStats->Barrage, 4 <= coordY)) && (orientation = PseudoRng(), orientation % 20 <= coordY)) {
      sceneClassUser->__InlineQueueEvent(coordY / 2);
      sceneClassUser->__InlineableQueueEvent(1);
      sceneClassUser->__InlineableQueueEvent(0x7d26);
      return;
    }

    if ((0xc0000 <= (sceneClassUser->userFlags & UserFlag::USERFLAG_MULTILEVELPROBABILITY)) && (orientation = PseudoRng(), orientation % 5 <= (int32_t)((sceneClassUser->userFlags & 0x1c0000) - 0x80001) >> 0x12)) {
      sceneClassUser->__InlineQueueEvent(objectIndex);
      sceneClassUser->__InlineableQueueEvent(0x7d14);
      return;
    }

    sceneClassUser->__InlineQueueEvent(PseudoRng() % 3);
    sceneClassUser->QueueEvent(coordY);
    sceneClassUser->QueueEvent(0x7d0b);
  }
  else {
    if ((sceneClassUser->userFlags & UserFlag::USERFLAG_IS_ENEMY_OR_PLAYER) == 1) {
      sceneClassUser->__InlineQueueEvent((PseudoRng() & 7) + 8);
      sceneClassUser->QueueEvent(0);
      sceneClassUser->QueueEvent(0x7d18);
    }
    sceneClassUser->__InlineableQueueEvent(MovementLookupTable1[orientation]);
    sceneClassUser->__InlineableQueueEvent(0x7d04);
    return;
  }
}

inline void AutonomousUpdate_ApplyItemStats_0x7d0d(SceneClassUser* sceneClassUser) {

  GameWindowBase* sceneObject;
  uint32_t userFlag;
  int32_t powerArmor;
  int32_t powerAccessory2;
  int32_t powerAccessory1;
  int32_t totalPower;
  SceneClassUser* sceneClassUserCopy;
  int32_t powerBracer;
  int32_t orientation;
  int32_t powerWeapon;
  int32_t collisionValue;
  ActiveCharacter* activeCharacter;

  orientation = sceneClassUser->orientation;
  int32_t coordY = sceneClassUser->floatMultiplier2_pos2;
  int32_t coordX = sceneClassUser->floatMultiplier1_pos1;

  collisionValue = sceneClassUser->mainSceneHandler->PaddedGridMap_Collision[HitRngRelated1[orientation].DeltaY1 + coordY][HitRngRelated1[orientation].DeltaX1 + coordX];
  if ((collisionValue < 0) && (collisionValue = (sceneClassUser->mainSceneHandler->PaddedGridMap_Collision[HitRngRelated1[orientation].DeltaY2 + coordY][(HitRngRelated1[orientation].DeltaX2 + coordX)]), collisionValue < 0)) {
    return;
  }

  activeCharacter = __InlineGetTeamCharacterForSceneUser(sceneClassUser);
  powerWeapon = __InlineWeaponItemPower(activeCharacter);
  powerArmor = __InlineArmorItemPower(activeCharacter);
  powerBracer = __InlineBracerItemPower(activeCharacter);
  powerAccessory1 = __InlineItemAttribute(activeCharacter, ItemSlot::Accessory1, ItemAttribute::AccessoryCurrentPower, ItemAttribute::AccessoryMaxPower);
  powerAccessory2 = __InlineItemAttribute(activeCharacter, ItemSlot::Accessory2, ItemAttribute::AccessoryCurrentPower, ItemAttribute::AccessoryMaxPower);
  totalPower = powerBracer + powerWeapon + powerArmor + powerAccessory2 + powerAccessory1;

  powerArmor = __InlineItemAttribute(activeCharacter, ItemSlot::Weapon, ItemAttribute::CurrentToHit, ItemAttribute::MaxToHit);
  powerBracer = __InlineItemAttribute(activeCharacter, ItemSlot::Armor, ItemAttribute::CurrentToHit, ItemAttribute::MaxToHit);

  sceneClassUser->numericalCharacterStats.Power = sceneClassUser->numericalCharacterStats.Power + totalPower;
  sceneClassUser->numericalCharacterStats.ToHit = sceneClassUser->numericalCharacterStats.ToHit + powerArmor + powerBracer;

  sceneObject = ObjectList[collisionValue].sceneClassObjectPointer;
  sceneObject->primarySwitchSingleParam(0x7d03, (intptr_t)&sceneClassUser->numericalCharacterStats, sceneClassUser->objectListId);
  userFlag = sceneClassUser->userFlags;
  sceneClassUser->numericalCharacterStats.Power = sceneClassUser->numericalCharacterStats.Power - totalPower;
  sceneClassUser->numericalCharacterStats.ToHit = sceneClassUser->numericalCharacterStats.ToHit - (powerArmor + powerBracer);
  if ((userFlag & 3) != 2) {
    return;
  }
  if (sceneClassUser == nullptr) {
    sceneClassUserCopy = nullptr;
  }
  else {
    sceneClassUserCopy = sceneClassUser;
  }
  int32_t soundEffectId = __InlineGetSoundEffectIndex(sceneClassUser->genericAct, (PseudoRng() & 1) + 2);
  sceneClassUser->mainSceneHandler->primarySwitchSingleParam_PlaySoundEffect_0x7d0a(soundEffectId, sceneClassUserCopy);
}

inline void AutonomousUpdate_0x7d10_EngagementMove(SceneClassUser* sceneClassUser) {
  PathfindingNode* pathfindingNode;
  int32_t objectIndex;
  int32_t actionState;

  actionState = __InlinePopEventQueueDecrement(sceneClassUser);
  objectIndex = __InlinePopEventQueueDecrement(sceneClassUser);

  if (0x1f < actionState) {
    if (sceneClassUser->eventCounter < 1) {
      return;
    }
    sceneClassUser->eventCounter--;
    actionState = sceneClassUser->queuedEventsArray[sceneClassUser->eventCounter >> 8]->queueEvents[sceneClassUser->eventCounter & 0xff];

    if (actionState == 0x7d07) {
      if ((sceneClassUser->userFlags & UserFlag::USERFLAG_IS_ENEMY_OR_PLAYER) == 1) {
        return;
      }
      if (ObjectList[objectIndex].sceneClassObjectPointer == nullptr) {
        return;
      }
      if ((ObjectList[objectIndex].scriptUserFlags & 3) == 1) {
        return;
      }
      sceneClassUser->__InlineQueueEvent(objectIndex);
      sceneClassUser->__InlineableQueueEvent(0x7d07);
      sceneClassUser->__InlineableQueueEvent(PseudoRng() & 7);
      sceneClassUser->__InlineableQueueEvent(0);
      sceneClassUser->__InlineableQueueEvent(0x7d18);

      return;
    }
    if (actionState == 0) {

      return;
    }
    sceneClassUser->__InlineableQueueEvent(actionState);
    return;
  }
  pathfindingNode = sceneClassUser->pathfindingInputObj->FindPath_AvoidWallsAndUnits();
  if (pathfindingNode != nullptr) {
    actionState = (int32_t)pathfindingNode->pathCostToThisNode / 3;
    if (actionState < 3) {
      actionState = 3;
    }
    actionState = pathfindingNode->pathCostToThisNode - actionState;
    do {
      if (actionState < 0) {
        for (; pathfindingNode != nullptr; pathfindingNode = pathfindingNode->linkToParentNode) {
          sceneClassUser->__InlineableQueueEvent(*(char*)(&pathfindingNode->directionFromParent));
          sceneClassUser->__InlineableQueueEvent(0x7d04);
        }

        return;
      }
      pathfindingNode = pathfindingNode->linkToParentNode;
      actionState = actionState + -1;
    } while (pathfindingNode != nullptr);

    return;
  }
  if (actionState < 8) {
    sceneClassUser->__InlineableQueueEvent(objectIndex);
    sceneClassUser->__InlineableQueueEvent(actionState + 1);
    sceneClassUser->__InlineableQueueEvent(0x7d10);
    return;
  }

  __InlineUpdateSpriteFrames(sceneClassUser, sceneClassUser->actStand, actionState - 8);
  sceneClassUser->__InlineableQueueEvent(objectIndex);
  sceneClassUser->__InlineableQueueEvent(actionState + 1);
  sceneClassUser->__InlineableQueueEvent(0x7d10);
}

inline void AutonomousUpdate_0x7d16_ReceiveNonFatalDamage(int32_t eventValue, int32_t actionId, SceneClassUser* sceneClassUser) {
  int32_t localCounter;

  eventValue = __InlinePopEventQueueDecrement(sceneClassUser);
  if (sceneClassUser->statusCondition == UnitStatusCondition::Frozen_Stopped) {
    return;
  }

  __InlineUpdateSpriteFrames(sceneClassUser, sceneClassUser->actDamage, eventValue);
  actionId = sceneClassUser->genericAct->GetFrameCountForAction(sceneClassUser->actDamage);
  if ((eventValue + 1) < actionId) {
    sceneClassUser->QueueTwoEvents(0x7d16, eventValue + 1);
    return;
  }
  localCounter = sceneClassUser->eventCounter;
  if (localCounter < 1) {
    return;
  }
  eventValue = localCounter - 1;
  sceneClassUser->eventCounter = eventValue;
  actionId = sceneClassUser->queuedEventsArray[eventValue >> 8]->queueEvents[eventValue & 0xff];
  if (actionId != 0x7d0c) {
    if (actionId == 0) {

      return;
    }
    sceneClassUser->__InlineableQueueEvent(actionId);
    return;
  }
  if (0 < eventValue) {
    sceneClassUser->eventCounter = localCounter + -2;
  }
  actionId = sceneClassUser->eventCounter;
  if (0 < actionId) {
    sceneClassUser->eventCounter = actionId + -1;
  }
  eventValue = PseudoRng();
  sceneClassUser->__InlineableQueueEvent(eventValue % 3);
  sceneClassUser->__InlineableQueueEvent(localCounter);
  sceneClassUser->__InlineableQueueEvent(0x7d0b);
}

inline void AutonomousUpdate_0x7d17_ReceiveFatalDamage(SceneClassUser* sceneClassUser) {
  int32_t actionIndex;
  SceneClassItem* sceneItem;
  int32_t itemActionIndex;
  uint32_t timer;
  CoreActClass* coreAct;

  timer = sceneClassUser->statusInternalTimer;
  sceneClassUser->statusInternalTimer = timer + 1;
  __InlineUpdateSpriteFrames(sceneClassUser, sceneClassUser->actDead, timer);

  actionIndex = sceneClassUser->genericAct->GetFrameCountForAction(sceneClassUser->actDead);
  if (sceneClassUser->statusInternalTimer < actionIndex) {
    return;
  }

  sceneClassUser->mainSceneHandler->SetCollisionValueInRectangularRegion(sceneClassUser->floatMultiplier1_pos1, sceneClassUser->floatMultiplier2_pos2, 2, 2, -2);
  if (((sceneClassUser->userFlags & UserFlag::USERFLAG_IS_UNKNOWN3) != 0) && (actionIndex = sceneClassUser->genericAct->GetActionIndexByName(s__item), 0 <= actionIndex)) {
    coreAct = sceneClassUser->genericAct;
    actionIndex = coreAct->GetActionIndexByName(s__item);
    actionIndex = coreAct->GetFrameCountForAction(actionIndex);
    if (0 < actionIndex) {
      coreAct = sceneClassUser->genericAct;
      actionIndex = coreAct->GetActionIndexByName(s__item);
      actionIndex = coreAct->GetFrameCountForAction(actionIndex);
      timer = PseudoRng();
      coreAct = sceneClassUser->genericAct;
      itemActionIndex = coreAct->GetActionIndexByName(s__item);

      if ((itemActionIndex != -1) && (actionIndex = coreAct->txtContent[itemActionIndex].ptrFrameStart[(int32_t)timer % actionIndex], 0 < actionIndex)) {
        sceneItem = new SceneClassItem(sceneClassUser->floatMultiplier1_pos1, sceneClassUser->floatMultiplier2_pos2, actionIndex, 0x8c0);
        sceneClassUser->mainSceneHandler->primarySwitchSingleParam_TriggerObjectInitialization_0x7d27(sceneItem, 0x0);
      }
    }
  }
  sceneClassUser->statusInternalTimer = 0;
  sceneClassUser->voluntaryActionSwitchFlag = ((~sceneClassUser->userFlags & UserFlag::USERFLAG_IS_UNKNOWN3) | 0xa6800) >> 10;
  if (sceneClassUser->triggerScriptIdOnDeath != 0) {
    sceneClassUser->primarySwitchSingleParam(0x7d06, 0x0, 0x0);
    (sceneClassUser->mainSceneHandler->mainSceneHandler->primarySwitchSingleParam(0x7d18, sceneClassUser->triggerScriptIdOnDeath, (intptr_t)(GameWindowBase*)sceneClassUser));
    sceneClassUser->voluntaryActionSwitchFlag = 0x71a;
  }
  __InlineMoveDeadCharacterToBenchedList(sceneClassUser);
}

inline void AutonomousUpdate_0x29a_0x29b(SceneClassUser* sceneClassUser) {
  int32_t internalTimer;

  internalTimer = sceneClassUser->statusInternalTimer;
  sceneClassUser->statusInternalTimer = internalTimer + 1;
  if (internalTimer < 0x141) {
    return;
  }
  if (sceneClassUser != nullptr) {
    sceneClassUser->mainSceneHandler->primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(sceneClassUser, 0x0);
    return;
  }
  sceneClassUser->mainSceneHandler->primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(nullptr, 0x0);
}

inline void AutonomousUpdate_Case_0(SceneClassUser* sceneClassUser) {
  SceneClassUser* sceneClassUserCopy;
  int32_t userFlag;
  ActiveCharacter* activeCharacter;
  int32_t isVisible;

  if (sceneClassUser->statusCondition != UnitStatusCondition::Frozen_Stopped) {
    userFlag = sceneClassUser->statusInternalTimer;
    sceneClassUser->statusInternalTimer = userFlag + 1;
    sceneClassUser->SetSpriteFrames(SpriteFrameSceneClassUser::Stand, userFlag);
  }
  userFlag = sceneClassUser->userFlags;
  if (((userFlag & UserFlag::USERFLAG_CHARACTER_UNKNOWN) != 0) &&
      (((userFlag & UserFlag::USERFLAG_CHARACTER_UNKNOWN_ENEMY_SPELLCASTER) == 0 && ((userFlag & 3) == 1 || (0x140 <= sceneClassUser->statusInternalTimer))) ||
       ((userFlag & UserFlag::USERFLAG_CHARACTER_UNKNOWN_ENEMY_SPELLCASTER) != 0 &&
        (isVisible = sceneClassUser->mainSceneHandler->HasVisibileTileInRectangularRegion(sceneClassUser->floatMultiplier1_pos1, sceneClassUser->floatMultiplier2_pos2, 2, 2), isVisible != 0)))) {
    sceneClassUser->statusInternalTimer = 0;
    sceneClassUser->QueueEvent(0x7d11);
  }
  if ((sceneClassUser->userFlags & UserFlag::USERFLAG_IS_ENEMY_OR_PLAYER) != 2) {

    return;
  }
  if ((*(byte*)&sceneClassUser->statusInternalTimer & 3) != 0) {

    return;
  }
  if (sceneClassUser == nullptr) {
    sceneClassUserCopy = nullptr;
  }
  else {
    sceneClassUserCopy = sceneClassUser;
  }
  activeCharacter = sceneClassUserCopy->GetCharacterObject();
  if (activeCharacter == nullptr) {

    return;
  }
  userFlag = Maximum(0, activeCharacter->characterBaseStats->TimeGauge - 1);
  activeCharacter->characterBaseStats->TimeGauge = userFlag;
}

inline void AutonomousUpdate_0x71a(SceneClassUser* sceneClassUser) {
  int32_t statusCounter;

  statusCounter = sceneClassUser->statusInternalTimer;
  sceneClassUser->statusInternalTimer = statusCounter + 1;
  if (statusCounter < 321) {
    return;
  }

  if (sceneClassUser != nullptr) {
    sceneClassUser->mainSceneHandler->primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(sceneClassUser, 0x0);
    return;
  }
  sceneClassUser->mainSceneHandler->primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(nullptr, 0x0);
}

inline void AutonomousUpdate_0x7d03(SceneClassUser* sceneClassUser, int32_t eventCounter, int32_t previousEventCounter) {
  PathfindingNode* pathfindingNode;

  if (previousEventCounter < 1) {
    eventCounter = 0;
  label_find_path_avoid_walls_and_units:
    pathfindingNode = sceneClassUser->pathfindingInputObj->FindPath_AvoidWallsAndUnits();
    if (pathfindingNode == nullptr) {
      sceneClassUser->__InlineQueueEvent(eventCounter + 1);
      sceneClassUser->QueueEvent(0x7d03);
    }
    else {
      do {
        sceneClassUser->QueueEvent(pathfindingNode->directionFromParent);
        sceneClassUser->QueueEvent(0x7d04);
        pathfindingNode = pathfindingNode->linkToParentNode;
      } while (pathfindingNode != nullptr);
    }
  }
  else {
    previousEventCounter = eventCounter - 2;
    sceneClassUser->eventCounter = previousEventCounter;
    eventCounter = sceneClassUser->queuedEventsArray[previousEventCounter >> 8]->queueEvents[previousEventCounter & 0xff];
    if (eventCounter < 0x20) {
      goto label_find_path_avoid_walls_and_units;
    }
  }
  if (eventCounter < 0x18) {

    return;
  }
  __InlineUpdateSpriteFrames(sceneClassUser, sceneClassUser->actStand, previousEventCounter);
}

inline void AutonomousUpdate_0x7d0f(SceneClassUser* sceneClassUser) {
  GameWindowBase* targetUser;
  int32_t coordX;
  int32_t coordY;
  int32_t coord1;
  int32_t deltaCoord2;
  int32_t counter;
  int32_t objectIndex;
  int32_t rng;

  objectIndex = __InlinePopEventQueueDecrement(sceneClassUser);

  if ((sceneClassUser->statusCondition == UnitStatusCondition::Wander_Confused) && (rng = PseudoRng(), (rng & 1) == 0)) {
    return;
  }
  if (objectIndex < 0) {
    return;
  }

  targetUser = ObjectList[objectIndex].sceneClassObjectPointer;
  if (targetUser == nullptr) {
    return;
  }
  if (targetUser->mainSceneHandler != sceneClassUser->mainSceneHandler) {
    return;
  }
  coordX = targetUser->matrixIndexXTimes16;
  coordY = targetUser->matrixIndexYTimes16;
  int32_t diffX = __InlineSignDifference(sceneClassUser->floatMultiplier1_pos1, targetUser->matrixIndexXTimes16);
  int32_t diffY = __InlineSignDifference(sceneClassUser->floatMultiplier2_pos2, targetUser->matrixIndexYTimes16);
  while (
      (diffX != DirectionalTuples[OrientationRelated].rng1 || diffY != DirectionalTuples[OrientationRelated].rng2) &&
      (sceneClassUser->floatMultiplier1_pos1 != coordX + (DirectionalTuples[OrientationRelated].rng1 * 2) || (sceneClassUser->floatMultiplier2_pos2 != coordY + (DirectionalTuples[OrientationRelated].rng2 * 2)))) {
    OrientationRelated = (OrientationRelated + 1) & 7;
  }

  for (counter = 0; counter < 8; counter++) {
    coord1 = coordX + (DirectionalTuples[OrientationRelated].rng1 * 2);
    deltaCoord2 = DirectionalTuples[OrientationRelated].rng2 * 2;
    if ((sceneClassUser->floatMultiplier1_pos1 != coord1) || (sceneClassUser->floatMultiplier2_pos2 != coordY + deltaCoord2)) {
      rng = __InlineHasUnoccupiedTileExcludingTypeInRectangularRegion(sceneClassUser->mainSceneHandler, coord1, coordY + deltaCoord2, 2, 2, sceneClassUser->objectListId);
      if (rng != -1) {
        goto label_rotate_orientation;
      }
      if (__InlineIs2x2AreaBlocked(sceneClassUser, coord1, coordY + deltaCoord2)) {
        goto label_rotate_orientation;
      }

      sceneClassUser->pathfindingInputObj->SetStartAndTargetCoordinates(sceneClassUser->floatMultiplier1_pos1, sceneClassUser->floatMultiplier2_pos2, coordX + (DirectionalTuples[OrientationRelated].rng1 * 2), coordY + deltaCoord2);
      if (sceneClassUser->voluntaryActionSwitchFlag != 0x7d23) {
        sceneClassUser->__InlineableQueueEvent(objectIndex);
        sceneClassUser->__InlineableQueueEvent(0x7d0f);
      }
      sceneClassUser->__InlineQueueEvent(objectIndex);
      sceneClassUser->QueueEvent(0);
      sceneClassUser->QueueEvent(0x7d10);
    }
    if (counter < 8) {

      return;
    }
    sceneClassUser->__InlineQueueEvent(coordY);
    sceneClassUser->__InlineableQueueEvent(coordX);
    sceneClassUser->__InlineableQueueEvent(0x7d00);
    return;

  label_rotate_orientation:
    OrientationRelated = (OrientationRelated - 1) & 7;
  }
  sceneClassUser->__InlineableQueueEvent(coordY);
  sceneClassUser->QueueEvent(coordX);
  sceneClassUser->QueueEvent(0x7d00);
}

inline void AutonomousUpdate_0x7d02(SceneClassUser* sceneClassUser) {
  int32_t targetX;
  int32_t targetY;
  int32_t counter;
  int32_t cellCollisionStatus;

  targetX = __InlinePopEventQueueDecrement(sceneClassUser);
  targetY = __InlinePopEventQueueDecrement(sceneClassUser);
  if ((targetX == sceneClassUser->floatMultiplier1_pos1) && (targetY == sceneClassUser->floatMultiplier2_pos2)) {
    return;
  }

  if (
      __InlineIs2x2AreaBlocked(sceneClassUser, targetX, targetY) ||
      (__InlineHasUnoccupiedTileExcludingTypeInRectangularRegion(sceneClassUser->mainSceneHandler, targetX, targetY, 2, 2, sceneClassUser->objectListId) != -1)) {
    for (counter = 0; counter < 8; counter++) {
      if (!__InlineIs2x2AreaBlocked(sceneClassUser, DirectionalTuples[counter].rng1 + targetX, DirectionalTuples[counter].rng2 + targetY) &&
          (cellCollisionStatus = __InlineHasUnoccupiedTileExcludingTypeInRectangularRegion(sceneClassUser->mainSceneHandler, DirectionalTuples[counter].rng1 + targetX - 2, DirectionalTuples[counter].rng2 + targetY, 2, 2, sceneClassUser->objectListId), cellCollisionStatus == -1)) {
        targetX = targetX + DirectionalTuples[counter].rng1;
        targetY = targetY + DirectionalTuples[counter].rng2;
        goto label_set_pathfinding_target;
      }
    }
    return;
  }
label_set_pathfinding_target:
  sceneClassUser->pathfindingInputObj->SetStartAndTargetCoordinates(sceneClassUser->floatMultiplier1_pos1, sceneClassUser->floatMultiplier2_pos2, targetX, targetY);
  sceneClassUser->QueueEvent(0);
  sceneClassUser->QueueEvent(0x7d03);
}

inline void Autonomous_ApplyDynamicallyLoadedSprite_0x7d27(SceneClassUser* sceneClassUser) {
  int32_t frameIndex;
  int32_t actionType;

  frameIndex = __InlinePopEventQueueDecrement(sceneClassUser);
  actionType = __InlinePopEventQueueDecrement(sceneClassUser);
  sceneClassUser->actDynamicallyLoadedFrameFromIndex = actionType;
  __InlineUpdateSpriteFrames(sceneClassUser, sceneClassUser->actDynamicallyLoadedFrameFromIndex, frameIndex);
}

inline void Autonomous_ApplyAttackFrame_LastFrame(SceneClassUser* sceneClassUser) {
  int32_t frameIndex;
  int32_t nextFrameIndex;
  int32_t maxFrameIndex;
  int32_t actionType;

  frameIndex = __InlinePopEventQueueDecrement(sceneClassUser);
  actionType = __InlinePopEventQueueDecrement(sceneClassUser);
  __InlineUpdateSpriteFrames(sceneClassUser, (&sceneClassUser->act1Natt1)[actionType], frameIndex);

  nextFrameIndex = frameIndex + 1;
  maxFrameIndex = sceneClassUser->genericAct->GetFrameCountForAction((&sceneClassUser->act1Natt1)[actionType]);
  if (maxFrameIndex <= nextFrameIndex) {
    sceneClassUser->__InlineableQueueEvent(actionType);
    sceneClassUser->__InlineableQueueEvent(0);
    sceneClassUser->__InlineableQueueEvent(0x7d0c);
    sceneClassUser->__InlineableQueueEvent(0x7d0d);
    return;
  }
  sceneClassUser->__InlineableQueueEvent(actionType);
  sceneClassUser->__InlineableQueueEvent(nextFrameIndex);
  sceneClassUser->__InlineableQueueEvent(0x7d0b);
}

inline void AutonomousUpdate_0x7d05(SceneClassUser* sceneClassUser) {
  int32_t coord1;
  int32_t eventValue;
  int32_t direction;
  int32_t cellValueRange;
  int32_t targetCellValue;
  int32_t coord2;
  int32_t currentOrientation;

  targetCellValue = __InlinePopEventQueueDecrement(sceneClassUser);
  __InlineUpdateSpriteFrames(sceneClassUser, sceneClassUser->actStand, targetCellValue);

  if (targetCellValue < 0x10) {
    currentOrientation = sceneClassUser->orientation;
    if (__InlineFirstNonBlockedCharacterIdIn2x2Area(sceneClassUser, DirectionalTuples[currentOrientation].rng1 + sceneClassUser->floatMultiplier1_pos1, DirectionalTuples[currentOrientation].rng2 + sceneClassUser->floatMultiplier2_pos2)) {
      sceneClassUser->QueueEvent(targetCellValue + 1);
      sceneClassUser->QueueEvent(0x7d05);
    }
    return;
  }
  coord1 = sceneClassUser->floatMultiplier1_pos1;
  coord2 = sceneClassUser->floatMultiplier2_pos2;

  while (0 < sceneClassUser->eventCounter) {
    sceneClassUser->eventCounter--;
    eventValue = sceneClassUser->queuedEventsArray[sceneClassUser->eventCounter >> 8]->queueEvents[sceneClassUser->eventCounter & 0xff];
    if (eventValue == 0x7d04) {
      direction = __InlinePopEventQueueDecrement(sceneClassUser);
      coord2 = coord2 + DirectionalTuples[direction].rng2;
      coord1 = coord1 + DirectionalTuples[direction].rng1;

      if (!__InlineFirstNonBlockedCharacterIdIn2x2Area(sceneClassUser, coord1, coord2)) {
        sceneClassUser->__InlineableQueueEvent(coord2);
        sceneClassUser->__InlineableQueueEvent(coord1);
        sceneClassUser->__InlineableQueueEvent(0x7d02);
        return;
      }
    }
    else if (eventValue != 0) {
      sceneClassUser->__InlineQueueEvent(eventValue);
      break;
    }
  }

  targetCellValue = __InlineHasUnoccupiedTileExcludingTypeInRectangularRegion(sceneClassUser->mainSceneHandler, coord1, coord2, 2, 2, sceneClassUser->objectListId);
  if (targetCellValue != -1) {
    currentOrientation = sceneClassUser->orientation;
    cellValueRange = __InlineHasUnoccupiedTileExcludingTypeInRectangularRegion(sceneClassUser->mainSceneHandler, HitRngRelated1[currentOrientation].DeltaX2 + sceneClassUser->floatMultiplier1_pos1, HitRngRelated1[currentOrientation].DeltaY1 + sceneClassUser->floatMultiplier2_pos2, 2, 2, sceneClassUser->objectListId);
    if (cellValueRange == targetCellValue) {
      return;
    }

    cellValueRange = __InlineHasUnoccupiedTileExcludingTypeInRectangularRegion(sceneClassUser->mainSceneHandler, HitRngRelated1[currentOrientation].DeltaX2 + sceneClassUser->floatMultiplier1_pos1, HitRngRelated1[currentOrientation].DeltaY2 + sceneClassUser->floatMultiplier2_pos2, 2, 2, sceneClassUser->objectListId);
    if (cellValueRange == targetCellValue) {
      return;
    }
    if ((ObjectList[targetCellValue].scriptUserFlags & 0x70) == 0x50) {
      sceneClassUser->QueueEvent(coord2);
      sceneClassUser->QueueEvent(coord1);
      sceneClassUser->QueueEvent(0x7d00);
      sceneClassUser->__InlineQueueEvent(0x20);
      sceneClassUser->QueueEvent(0);
      sceneClassUser->QueueEvent(0x7d18);
      return;
    }
    sceneClassUser->QueueEvent(targetCellValue);
    sceneClassUser->QueueEvent(0x7d07);
    targetCellValue = (PseudoRng() & 7) + 7;
    sceneClassUser->__InlineQueueEvent(targetCellValue);
    sceneClassUser->QueueEvent(0);
    sceneClassUser->QueueEvent(0x7d18);
  }
}

inline void AutonomousUpdate_State_0x7d19(SceneClassUser* sceneClassUser) {
  int32_t counter;
  int32_t orientation;
  int32_t collisionValue;

  int32_t objectIndex = sceneClassUser->PopQueuedElement();
  int32_t value = sceneClassUser->PopQueuedElement();
  if (objectIndex < 0) {
    return;
  }
  if (ObjectList[objectIndex].sceneClassObjectPointer == nullptr) {
    return;
  }
  counter = 0;
  while ((orientation = sceneClassUser->orientation, collisionValue = sceneClassUser->mainSceneHandler->GetCollisionMapValueAtCoordindate(HitRngRelated1[orientation].DeltaX1 + sceneClassUser->floatMultiplier1_pos1, HitRngRelated1[orientation].DeltaY1 + sceneClassUser->floatMultiplier2_pos2), collisionValue != objectIndex && (orientation = sceneClassUser->orientation, collisionValue = sceneClassUser->mainSceneHandler->GetCollisionMapValueAtCoordindate(HitRngRelated1[orientation].DeltaX2 + sceneClassUser->floatMultiplier1_pos1, HitRngRelated1[orientation].DeltaY2 + sceneClassUser->floatMultiplier2_pos2), collisionValue != objectIndex))) {
    counter = counter + 1;
    sceneClassUser->orientation = (sceneClassUser->orientation + 1) & 7;
    if (7 < counter) {
      if (counter != 8) {
        return;
      }
      sceneClassUser->QueueThreeEvents(0x7d19, objectIndex, value);
      sceneClassUser->QueueTwoEvents(0x7d07, objectIndex);
      return;
    }
  }
  ObjectList[objectIndex].sceneClassObjectPointer->primarySwitchSingleParam(0x7d19, sceneClassUser->objectListId, value);
  if (counter != 8) {
    return;
  }
  sceneClassUser->QueueThreeEvents(0x7d19, objectIndex, value);
  sceneClassUser->QueueTwoEvents(0x7d07, objectIndex);
}

inline void AutonomousUpdate_SetStandAnimation_0x7d18(SceneClassUser* sceneClassUser) {
  int32_t currentFrame = sceneClassUser->PopQueuedElement();
  int32_t maxFrame = sceneClassUser->PopQueuedElement();
  if (currentFrame < maxFrame) {
    sceneClassUser->QueueThreeEvents(0x7d18, currentFrame + 1, maxFrame);
  }
  if (sceneClassUser->statusCondition == UnitStatusCondition::Frozen_Stopped) {
    return;
  }
  sceneClassUser->SetSpriteFrames(SpriteFrameSceneClassUser::Stand, currentFrame);
}

inline void AutonomousUpdate_State_0x7d13(SceneClassUser* sceneClassUser) {
  int32_t rng;
  PathfindingNode* pathfindingNode;

  rng = PseudoRng();
  if ((rng & 7) == 0) {
    sceneClassUser->__InlineableQueueEvent(10);
    sceneClassUser->__InlineableQueueEvent(0);
    sceneClassUser->__InlineableQueueEvent(0x7d18);
  }
  pathfindingNode = sceneClassUser->pathfindingInputObj->VisionTargetSearch(sceneClassUser->floatMultiplier1_pos1, sceneClassUser->floatMultiplier2_pos2, (int32_t)(sceneClassUser->numericalCharacterStats.Eye << 4) / 100, sceneClassUser->userFlags);
  rng = PseudoRng();
  int32_t scaledEye = ((sceneClassUser->numericalCharacterStats.Eye * 10) / 100) + (rng % 3);
  while (true) {
    if (pathfindingNode == nullptr) {
      return;
    }
    if (scaledEye < 1) {
      break;
    }
    sceneClassUser->__InlineableQueueEvent(pathfindingNode->directionFromParent);
    sceneClassUser->__InlineableQueueEvent(0x7d04);
    pathfindingNode = pathfindingNode->linkToParentNode;
    scaledEye = scaledEye + -1;
  }
}

void SceneClassUser::AutonomousSceneClassUserUpdate() {
  SceneHandler* mainSceneHandler;
  int32_t mainSwitchValue;
  int32_t mainValue2;
  UserFlagEnum mainValue3;
  CoreActClass* coreAct;

  SceneClassUser* sceneClassUser = this;

  if ((sceneClassUser->statusCondition != UnitStatusCondition::Normal) && (mainSwitchValue = sceneClassUser->statusConditionTimeLeft, sceneClassUser->statusConditionTimeLeft = mainSwitchValue + -1, mainSwitchValue <= 0)) {
    sceneClassUser->eventCounter = 0;
    sceneClassUser->statusCondition = UnitStatusCondition::Normal;
  }

  mainSwitchValue = sceneClassUser->voluntaryActionSwitchFlag;

  switch (mainSwitchValue) {

  case 0x7d17: {
    mainValue3 = sceneClassUser->statusInternalTimer;
    sceneClassUser->statusInternalTimer++;
    __InlineUpdateSpriteFrames(sceneClassUser, sceneClassUser->actDead, mainValue3);
    mainSwitchValue = sceneClassUser->genericAct->GetFrameCountForAction(sceneClassUser->actDead);
    if (sceneClassUser->statusInternalTimer < mainSwitchValue) {
      return;
    }

    sceneClassUser->mainSceneHandler->SetCollisionValueInRectangularRegion(sceneClassUser->floatMultiplier1_pos1, sceneClassUser->floatMultiplier2_pos2, 2, 2, -2);
    if (((sceneClassUser->userFlags & UserFlag::USERFLAG_IS_UNKNOWN3) != 0) && (mainSwitchValue = sceneClassUser->genericAct->GetActionIndexByName(s__item), 0 <= mainSwitchValue)) {
      coreAct = sceneClassUser->genericAct;
      mainSwitchValue = coreAct->GetActionIndexByName(s__item);
      mainSwitchValue = coreAct->GetFrameCountForAction(mainSwitchValue);
      if (0 < mainSwitchValue) {
        coreAct = sceneClassUser->genericAct;
        mainSwitchValue = coreAct->GetActionIndexByName(s__item);
        mainSwitchValue = coreAct->GetFrameCountForAction(mainSwitchValue);
        mainValue3 = PseudoRng() % mainSwitchValue;
        coreAct = sceneClassUser->genericAct;
        mainValue2 = coreAct->GetActionIndexByName(s__item);

        if ((mainValue2 != -1) && (mainSwitchValue = coreAct->txtContent[mainValue2].ptrFrameStart[mainValue3], 0 < mainSwitchValue)) {
          SceneClassItem* sceneItem = new SceneClassItem(sceneClassUser->floatMultiplier1_pos1, sceneClassUser->floatMultiplier2_pos2, mainSwitchValue, 0x8c0);
          sceneClassUser->mainSceneHandler->primarySwitchSingleParam_TriggerObjectInitialization_0x7d27(sceneItem, 0x0);
        }
      }
    }
    sceneClassUser->statusInternalTimer = 0;
    sceneClassUser->voluntaryActionSwitchFlag = ((~sceneClassUser->userFlags & UserFlag::USERFLAG_IS_UNKNOWN3) | 0xa6800) >> 10;
    if (sceneClassUser->triggerScriptIdOnDeath != 0) {
      sceneClassUser->primarySwitchSingleParam(0x7d06, 0x0, 0x0);
      sceneClassUser->mainSceneHandler->mainSceneHandler->primarySwitchSingleParam(0x7d18, sceneClassUser->triggerScriptIdOnDeath, (intptr_t)(GameWindowBase*)sceneClassUser);
      sceneClassUser->voluntaryActionSwitchFlag = 0x71a;
    }
    __InlineMoveDeadCharacterToBenchedList(sceneClassUser);
    return;
  }

  case 0x7d04:
    mainSwitchValue = sceneClassUser->statusInternalTimer;
    mainValue3 = (sceneClassUser->halfIndex + sceneClassUser->frameIndexRelated) - mainSwitchValue;
    sceneClassUser->statusInternalTimer = mainSwitchValue + -1;

    __InlineUpdateSpriteFrames(sceneClassUser, sceneClassUser->actWalk, mainValue3);
    if (0 < sceneClassUser->statusInternalTimer) {
      sceneClassUser->floatTimesMultiplier1 = sceneClassUser->float1 + sceneClassUser->floatTimesMultiplier1;
      sceneClassUser->floatTimesMultiplier2 = sceneClassUser->float2 + sceneClassUser->floatTimesMultiplier2;

      return;
    }
    sceneClassUser->statusInternalTimer = 0;
    sceneClassUser->voluntaryActionSwitchFlag = 0x7d21;
    sceneClassUser->floatTimesMultiplier1 = (float)sceneClassUser->floatMultiplier1_pos1 * GridMultiplier_16;
    sceneClassUser->floatTimesMultiplier2 = (float)sceneClassUser->floatMultiplier2_pos2 * GridMultiplier_16;
    break;

  case 0x71a:
    AutonomousUpdate_0x71a(sceneClassUser);
    return;

  case 0x29a:
  case 0x29b:
    AutonomousUpdate_0x29a_0x29b(sceneClassUser);
    return;

  case 0x7d21:
    break;

  case 0x7d2a:
    if ((MouseButtonClick & 34) == 0) {
      sceneClassUser->eventCounter = 0;
      sceneClassUser->QueueEvent(1);
      sceneClassUser->QueueEvent(0x7d2a);
    }
    break;

  default: {
    char* messageBox1 = s_debug;
    char* messageBox2 = s___;
    WrapperMessageBoxA(messageBox2, messageBox1);
    return;
  }
  }

  mainSwitchValue = sceneClassUser->eventCounter;
  if (mainSwitchValue < 1) {
  label_handle_combat_case_0:
    AutonomousUpdate_Case_0(sceneClassUser);
    return;
  }

  mainValue3 = mainSwitchValue - 1;
  sceneClassUser->eventCounter = mainValue3;
  mainValue2 = sceneClassUser->queuedEventsArray[mainValue3 >> 8]->queueEvents[mainValue3 & 0xff];

  switch (mainValue2) {
  case 0x7d12: {
    if (sceneClassUser->statusCondition == UnitStatusCondition::Wander_Confused) {
      mainValue3 = sceneClassUser->userFlags;
    }
    else {
      mainValue3 = sceneClassUser->userFlags;
    }
    mainSwitchValue = sceneClassUser->pathfindingInputObj->FindObjectByFlags(sceneClassUser->floatMultiplier1_pos1, sceneClassUser->floatMultiplier2_pos2, ((int32_t)(sceneClassUser->numericalCharacterStats.Eye * 20) / 100) + 2, mainValue3);
    if (mainSwitchValue >= 0) {
      sceneClassUser->__InlineQueueEvent(0x7d09);
      sceneClassUser->__InlineableQueueEvent(mainSwitchValue);
      sceneClassUser->QueueEvent(0x7d0f);
      sceneClassUser->__InlineQueueEvent(0x7d09);
      return;
    }

    sceneClassUser->__InlineableQueueEvent(0x7d11);
    int32_t rng = PseudoRng() % 16;
    sceneClassUser->QueueEvent(rng + 0x20);
    sceneClassUser->QueueEvent(0);
    sceneClassUser->QueueEvent(0x7d18);

    return;
  }
  case 0x7d08: {
    GameWindowBase* sceneObject;
    int16_t** collisionMap;
    int32_t counter;
    int32_t objectIndex;

    if (mainValue3 < 1) {
      objectIndex = 0x0;
    }
    else {
      mainValue3 = mainSwitchValue - 2;
      sceneClassUser->eventCounter = mainValue3;
      objectIndex = sceneClassUser->queuedEventsArray[mainValue3 >> 8]->queueEvents[mainValue3 & 0xff];
      if (objectIndex < 0) {

        return;
      }
    }
    sceneObject = ObjectList[objectIndex].sceneClassObjectPointer;
    if (sceneObject == nullptr) {

      return;
    }
    mainSceneHandler = sceneClassUser->mainSceneHandler;
    if (sceneObject->mainSceneHandler != mainSceneHandler) {

      return;
    }
    mainSwitchValue = sceneClassUser->floatMultiplier2_pos2;
    for (counter = 0; counter < 8; counter++) {
      mainValue3 = sceneClassUser->orientation;
      collisionMap = mainSceneHandler->PaddedGridMap_Collision;
      mainValue2 = sceneClassUser->floatMultiplier1_pos1;
      if ((collisionMap[HitRngRelated1[mainValue3].DeltaY1 + mainSwitchValue][(HitRngRelated1[mainValue3].DeltaX1 + mainValue2)] == objectIndex) || (collisionMap[HitRngRelated1[mainValue3].DeltaY2 + mainSwitchValue][(HitRngRelated1[mainValue3].DeltaX2 + mainValue2)] == objectIndex)) {
        sceneObject = ObjectList[objectIndex].sceneClassObjectPointer;
        sceneObject->primarySwitchSingleParam(0x7d04, sceneClassUser->objectListId, 0);
        break;
      }
      sceneClassUser->orientation = (mainValue3 + 1) & 7;
    }
    return;
  }

  case 0x7d09: {
    DirectionOffsets* directionOffsets;
    int32_t objectIndex;

    mainSwitchValue = sceneClassUser->floatMultiplier2_pos2;
    mainValue2 = sceneClassUser->floatMultiplier1_pos1;
    directionOffsets = (DirectionOffsets*)HitRngRelated1;
    while ((
        (objectIndex = (int32_t)sceneClassUser->mainSceneHandler->PaddedGridMap_Collision[directionOffsets->DeltaY1 + mainSwitchValue][(directionOffsets->DeltaX1 + mainValue2)], objectIndex < 0 &&
                                                                                                                                                                                      (objectIndex = (int32_t)sceneClassUser->mainSceneHandler->PaddedGridMap_Collision[directionOffsets->DeltaY2 + mainSwitchValue][(directionOffsets->DeltaX2 + mainValue2)], objectIndex < 0)) ||
        ((mainValue3 = sceneClassUser->userFlags & UserFlag::USERFLAG_IS_ENEMY_OR_PLAYER, mainValue3 != 1 ||
                                                                                              ((ObjectList[objectIndex].scriptUserFlags & 3) != 2)) &&
         ((mainValue3 != 2 || ((ObjectList[objectIndex].scriptUserFlags & 3) != 1)) && (sceneClassUser->statusCondition != UnitStatusCondition::Wander_Confused))))) {
      directionOffsets = directionOffsets + 1;
      if (HitRngRelated1 + 8 <= directionOffsets) {

        return;
      }
    }
    sceneClassUser->__InlineQueueEvent(objectIndex);
    sceneClassUser->QueueEvent(0x7d0a);
    return;
  }

  case 0x7d0a: {
    AutonomousUpdate_BarrageCheck_0x7d0a(sceneClassUser);
    return;
  }

  case 0x7d0b: {
    Autonomous_ApplyAttackFrame_LastFrame(sceneClassUser);
    return;
  }

  case 0x7d0c: {
    int32_t attackFrameCount = __InlinePopEventQueueDecrement(sceneClassUser);
    int32_t attackFrameIndex = __InlinePopEventQueueDecrement(sceneClassUser);
    __InlineUpdateSpriteFrames(sceneClassUser, (&sceneClassUser->act1Natt2)[attackFrameIndex], attackFrameCount);
    mainValue2 = sceneClassUser->genericAct->GetFrameCountForAction((&sceneClassUser->act1Natt2)[attackFrameIndex]);
    if (mainValue2 <= (attackFrameCount + 1)) {
      return;
    }
    sceneClassUser->__InlineableQueueEvent(attackFrameIndex);
    sceneClassUser->__InlineableQueueEvent(attackFrameCount + 1);
    sceneClassUser->__InlineableQueueEvent(0x7d0c);
    return;
  }

  case 0x7d0d: {
    AutonomousUpdate_ApplyItemStats_0x7d0d(sceneClassUser);
    return;
  }

  case 0x7d0f: {
    AutonomousUpdate_0x7d0f(sceneClassUser);
    return;
  }

  case 0x7d10: {
    AutonomousUpdate_0x7d10_EngagementMove(sceneClassUser);
    return;
  }

  case 0x7d11: {
    int32_t filteredFlag;

    if (sceneClassUser->statusCondition == UnitStatusCondition::Frozen_Stopped) {
      return;
    }
    mainValue3 = sceneClassUser->userFlags;
    filteredFlag = mainValue3 & UserFlag::USERFLAG_MULTILEVELPROBABILITY;
    if (filteredFlag < UserFlag::USERFLAG_MORE_MONSTER_RELATED_EXTRA_FLAG) {
      if (filteredFlag != UserFlag::USERFLAG_MORE_MONSTER_RELATED) {
        if (filteredFlag != 0) {
          if (filteredFlag == UserFlag::USERFLAG_SPELLCASTER_MONSTER_RELATED) {
            sceneClassUser->__InlineableQueueEvent(0x7d13);
            return;
          }
          if (filteredFlag != UserFlag::USERFLAG_NORMAL_ENEMY_RELATED_2) {
            return;
          }
          sceneClassUser->__InlineableQueueEvent(0x7d12);
          return;
        }
        if (sceneClassUser->voluntaryActionSwitchFlag == 0x7d23) {
          mainSwitchValue = sceneClassUser->pathfindingInputObj->SearchForNearestObject(sceneClassUser->floatMultiplier1_pos1, sceneClassUser->floatMultiplier2_pos2, ((int32_t)(sceneClassUser->numericalCharacterStats.Eye * 0x14) / 100) + 2, mainValue3, sceneClassUser->objectListId);
        }
        else {
          mainSwitchValue = sceneClassUser->pathfindingInputObj->FindObjectByFlags(sceneClassUser->floatMultiplier1_pos1, sceneClassUser->floatMultiplier2_pos2, ((int32_t)(sceneClassUser->numericalCharacterStats.Eye * 0x14) / 100) + 2, mainValue3);
        }

        if (mainSwitchValue != -1) {
          sceneClassUser->__InlineableQueueEvent(0x7d09);
          sceneClassUser->__InlineableQueueEvent(mainSwitchValue);
          sceneClassUser->__InlineableQueueEvent(0x7d0f);
          sceneClassUser->__InlineableQueueEvent(0x7d09);
          return;
        }
        else {
          sceneClassUser->__InlineableQueueEvent(0x7d13);
          return;
        }
      }
    }
    else if ((filteredFlag != UserFlag::USERFLAG_ENDBOSSES_RELATED) && (filteredFlag != UserFlag::USERFLAG_SPELLCASTER_ENDBOSSES_RELATED)) {

      return;
    }
    if (sceneClassUser->voluntaryActionSwitchFlag == 0x7d23) {
      mainSwitchValue = sceneClassUser->pathfindingInputObj->SearchForNearestObject(sceneClassUser->floatMultiplier1_pos1, sceneClassUser->floatMultiplier2_pos2, ((int32_t)(sceneClassUser->numericalCharacterStats.Eye * 0x14) / 100) + 2, mainValue3, sceneClassUser->objectListId);
    }
    else {
      mainSwitchValue = sceneClassUser->pathfindingInputObj->FindObjectByFlags(sceneClassUser->floatMultiplier1_pos1, sceneClassUser->floatMultiplier2_pos2, ((int32_t)(sceneClassUser->numericalCharacterStats.Eye * 0x14) / 100) + 2, mainValue3);
    }
    if (mainSwitchValue != -1) {
      int32_t rng = PseudoRng();
      if ((rng % 5) <= ((sceneClassUser->userFlags & UserFlag::USERFLAG_MULTILEVELPROBABILITY) - 0x80001) >> 0x12) {
        sceneClassUser->__InlineQueueEvent(0x7d09);
        sceneClassUser->__InlineQueueEvent(mainSwitchValue);
        sceneClassUser->QueueEvent(0x7d0f);
        sceneClassUser->__InlineQueueEvent(0x7d09);
        sceneClassUser->__InlineQueueEvent(0x20);
        sceneClassUser->QueueEvent(0);
        sceneClassUser->QueueEvent(0x7d18);
        return;
      }
      sceneClassUser->__InlineableQueueEvent(mainSwitchValue);
      sceneClassUser->QueueEvent(0x7d14);
      return;
    }
    sceneClassUser->__InlineQueueEvent(0x60);
    sceneClassUser->QueueEvent(0);
    sceneClassUser->QueueEvent(0x7d18);

    return;
  }

  case 0x7d04:
    AutonomousUpdate_0x7d04_Pathfinding(sceneClassUser);
    return;

  case 0x7d05:
    AutonomousUpdate_0x7d05(sceneClassUser);
    return;

  case 0x7d06: {
    int32_t coordY;
    int32_t coordX;
    int32_t counter;

    mainSwitchValue = __InlinePopEventQueueDecrement(sceneClassUser);
    mainValue2 = __InlinePopEventQueueDecrement(sceneClassUser);
    coordX = __InlineSignDifference(sceneClassUser->floatMultiplier1_pos1, mainSwitchValue);
    coordY = __InlineSignDifference(sceneClassUser->floatMultiplier2_pos2, mainValue2);

    for (mainValue3 = 0; mainValue3 < 8; mainValue3 = mainValue3 + 1) {
      if ((coordX == DirectionalTuples[mainValue3].rng1) && (coordY == DirectionalTuples[mainValue3].rng2)) {
        break;
      }
    }

    for (counter = 0; counter < 8; counter = counter + 1) {
      coordX = mainSwitchValue + (DirectionalTuples[mainValue3].rng1 * 2);
      coordY = mainValue2 + (DirectionalTuples[mainValue3].rng2 * 2);
      if ((-1 < coordX) && (-1 < coordY) &&
          !__InlineFirstNonBlockedCharacterIdIn2x2Area(sceneClassUser, coordX, coordY) &&
          !__InlineIs2x2AreaBlocked(sceneClassUser, coordX, coordY)) {
        sceneClassUser->QueueEvent(coordY);
        sceneClassUser->QueueEvent(coordX);
        sceneClassUser->QueueEvent(0x7d02);
        return;
      }
      mainValue3 = (mainValue3 + 1) & 7;
    }
    return;
  }
  case 0x7d07: {
    GameWindowBase* sceneObject;

    if (mainValue3 < 1) {
      mainSwitchValue = 0;
    }
    else {
      mainValue3 = mainSwitchValue - 2;
      sceneClassUser->eventCounter = mainValue3;
      mainSwitchValue = sceneClassUser->queuedEventsArray[mainValue3 >> 8]->queueEvents[mainValue3 & 0xff];
      if (mainSwitchValue < 0) {
        return;
      }
    }
    sceneObject = ObjectList[mainSwitchValue].sceneClassObjectPointer;
    if (sceneObject == nullptr) {
      return;
    }
    if (sceneObject->mainSceneHandler != sceneClassUser->mainSceneHandler) {
      return;
    }
    sceneClassUser->__InlineQueueEvent(sceneObject->matrixIndexYTimes16);
    sceneClassUser->QueueEvent(sceneObject->matrixIndexXTimes16);
    sceneClassUser->QueueEvent(0x7d06);
    return;
  }

  case 0x7d03:
    AutonomousUpdate_0x7d03(sceneClassUser, mainSwitchValue, mainValue3);
    return;
  case 0x7d01:
    AutonomousUpdate_0x7d01_Pathfinding(sceneClassUser);
    return;
  case 0:
    goto label_handle_combat_case_0;
  case 0x7d00:
    AutonomousUpdate_0x7d00_Pathfinding(sceneClassUser);
    return;
  case 0x7d02:
    AutonomousUpdate_0x7d02(sceneClassUser);
    return;

  case 0x7d13:
    AutonomousUpdate_State_0x7d13(sceneClassUser);
    return;

  case 0x7d14: {
    char spellAnimationFile[16];
    ItemStatsTemplate* itemStatsPtr;
    ItemReferenceCollection* itemCollectionPtr;
    GameWindowBase* spellAnimation;
    int32_t itemAttributeB;
    AnimationStatusSpell* spellAnimationStatus;
    int32_t coordY;
    int32_t coordX;
    int32_t directionY;
    int32_t directionX;
    GameWindowBase* sceneObject;

    mainSwitchValue = __InlinePopEventQueueDecrement2(sceneClassUser, mainValue3, mainSwitchValue);

    coreAct = sceneClassUser->genericAct;
    sceneObject = ObjectList[mainSwitchValue].sceneClassObjectPointer;
    coordX = sceneObject->matrixIndexXTimes16;
    coordY = sceneObject->matrixIndexYTimes16;
    mainValue2 = coreAct->GetActionIndexByName(s__magic);
    itemCollectionPtr = ItemStruct12k;
    if (mainValue2 == -1) {

      return;
    }
    mainValue2 = *coreAct->txtContent[mainValue2].ptrFrameStart;
    if (mainValue2 < 1) {

      return;
    }

    itemStatsPtr = ItemStruct12k->itemArray[mainValue2].stats;
    itemAttributeB = itemStatsPtr->bParameter;
    switch (itemAttributeB) {
    case 1:
    case 3:
    case 4:
    case 5:
      break;
    case 2:
    case 7:
    case 8:
      sceneObject = ObjectList[mainSwitchValue].sceneClassObjectPointer;
      sceneObject->primarySwitchSingleParam(0x7d22, (int32_t)(itemStatsPtr->hParameter + (itemStatsPtr->hParameter >> 0x1f & 3U)) >> 2, itemAttributeB);
      if (4 < (itemCollectionPtr->itemArray[mainValue2].stats)->cParameter) {
        sceneObject = ObjectList[mainSwitchValue].sceneClassObjectPointer;
        sceneObject->primarySwitchSingleParam(0x7d22, 0, 0xb);
      }
      if ((itemCollectionPtr->itemArray[mainValue2].stats)->aParameter == 0x2) {

        spellAnimationStatus = new AnimationStatusSpell(spellAnimationFile, sceneObject->matrixIndexXTimes16, sceneObject->matrixIndexYTimes16, ((itemCollectionPtr->itemArray[mainValue2].stats)->hParameter * 0x40) + 0x20);

        if (spellAnimationStatus == nullptr) {
          spellAnimationStatus = nullptr;
        }
        else {
          sceneObject = ObjectList[mainSwitchValue].sceneClassObjectPointer;
        }

        sceneClassUser->mainSceneHandler->StoreAndInitializeObject(spellAnimationStatus);
      }
      goto label_update_unit_orientation;
    case 6:
    case 9:
    case 10:
    case 0xb:
      if ((ObjectList[mainSwitchValue].scriptUserFlags & UserFlag::WANDER_GLOOMY_RELATED) != 0) {
        goto label_update_unit_orientation;
      }
      break;
    default:
      goto label_update_unit_orientation;
    }

    sceneObject = ObjectList[mainSwitchValue].sceneClassObjectPointer;
    sceneObject->primarySwitchSingleParam(0x7d22, (int32_t)(itemStatsPtr->hParameter + (itemStatsPtr->hParameter >> 0x1f & 3U)) >> 2, itemAttributeB);
  label_update_unit_orientation:

    directionX = __InlineSignDifference(sceneClassUser->matrixIndexXTimes16 / 2, coordX / 2);
    directionY = __InlineSignDifference(sceneClassUser->matrixIndexYTimes16 / 2, coordY / 2);
    sceneClassUser->orientation = 0;
    do {
      mainValue3 = sceneClassUser->orientation;
      if ((directionX == DirectionalTuples[mainValue3].rng1) && (directionY == DirectionalTuples[mainValue3].rng2)) {
        break;
      }
      mainValue3 = (mainValue3 + 1) & 7;
      sceneClassUser->orientation = mainValue3;
    } while (mainValue3 < 8);
    sceneClassUser->orientation = (sceneClassUser->orientation - 4) & 7;
    sprintf(spellAnimationFile, s__d_act, (itemCollectionPtr->itemArray[mainValue2].stats)->fParameter);

    spellAnimation = new AnimationSpell(spellAnimationFile, sceneObject->matrixIndexXTimes16, sceneObject->matrixIndexYTimes16);
    if (spellAnimation == nullptr) {
      spellAnimation = nullptr;
    }
    else {
      sceneObject = ObjectList[mainSwitchValue].sceneClassObjectPointer;
    }

    sceneClassUser->mainSceneHandler->StoreAndInitializeObject(spellAnimation);
    sceneClassUser->__InlineQueueEvent(0x60);
    sceneClassUser->QueueEvent(0);
    sceneClassUser->QueueEvent(0x7d18);
    sceneClassUser->__InlineQueueEvent(0x7d1c);
    return;
  }

  case 0x7d15: {
    GameWindowBase* sceneObject;
    SceneClassUser* sceneClassUserCopy;
    int32_t soundEffectIndex;
    BloodObject* bloodObject;

    int32_t hpBoost = 0;
    int32_t damageApplied = __InlinePopEventQueueDecrement(sceneClassUser);
    mainSwitchValue = __InlinePopEventQueueDecrement(sceneClassUser);

    if (sceneClassUser->voluntaryActionSwitchFlag == 0x7d2a) {
      mainValue3 = sceneClassUser->orientation;
      mainValue2 = sceneClassUser->floatMultiplier2_pos2;
      int32_t directionX = sceneClassUser->floatMultiplier1_pos1;

      if (sceneClassUser->mainSceneHandler->PaddedGridMap_Collision[HitRngRelated1[mainValue3].DeltaY1 + mainValue2][HitRngRelated1[mainValue3].DeltaX1 + directionX] == mainSwitchValue) {
        return;
      }
      if (sceneClassUser->mainSceneHandler->PaddedGridMap_Collision[HitRngRelated1[mainValue3].DeltaY2 + mainValue2][HitRngRelated1[mainValue3].DeltaX2 + directionX] == mainSwitchValue) {
        return;
      }
    }
    sceneClassUser->numericalCharacterStats.CurrentHp = sceneClassUser->numericalCharacterStats.CurrentHp - damageApplied;
    ActiveCharacter* activeCharacter = __InlineGetTeamCharacterForSceneUser(sceneClassUser);

    if (activeCharacter != nullptr) {
      if (0 < (activeCharacter->charEquip).equipmentAccessory1.quantity) {
        hpBoost = (activeCharacter->charEquip).equipmentAccessory1.hp;
      }
      if (0 < (activeCharacter->charEquip).equipmentAccessory2.quantity) {
        hpBoost = hpBoost + (activeCharacter->charEquip).equipmentAccessory2.hp;
      }
    }
    if ((-1 < mainSwitchValue) && (sceneObject = ObjectList[mainSwitchValue].sceneClassObjectPointer, sceneObject != nullptr)) {
      mainValue3 = sceneClassUser->numericalCharacterStats.MaxHp;
      if (mainValue3 <= damageApplied) {
        damageApplied = mainValue3;
      }
      sceneObject->primarySwitchSingleParam(0x7d1e, ((sceneClassUser->numericalCharacterStats.ExpPerKill * damageApplied) / mainValue3) + 1, 0);
    }
    if (sceneClassUser == nullptr) {
      sceneClassUserCopy = nullptr;
    }
    else {
      sceneClassUserCopy = sceneClassUser;
    }
    mainValue3 = sceneClassUser->numericalCharacterStats.CurrentHp;
    soundEffectIndex = __InlineGetSoundEffectIndex(sceneClassUser->genericAct, 0 < (hpBoost + mainValue3));
    sceneClassUser->mainSceneHandler->primarySwitchSingleParam_PlaySoundEffect_0x7d0a(soundEffectIndex, sceneClassUserCopy);

    if ((hpBoost + sceneClassUser->numericalCharacterStats.CurrentHp) < 1) {
      sceneClassUser->voluntaryActionSwitchFlag = 0x7d17;
      sceneClassUser->statusInternalTimer = 0;
    }
    else {
      sceneClassUser->__InlineableQueueEvent(0);
      sceneClassUser->__InlineableQueueEvent(0x7d16);
    }
    bloodObject = new BloodObject(sceneClassUser->matrixIndexXTimes16, sceneClassUser->matrixIndexYTimes16, (sceneClassUser->orientation + 3) & 7);
    sceneClassUser->mainSceneHandler->primarySwitchSingleParam_TriggerObjectInitialization_0x7d27(bloodObject, 0x0);
    return;
  }

  case 0x7d16:
    AutonomousUpdate_0x7d16_ReceiveNonFatalDamage(mainValue3, mainSwitchValue, sceneClassUser);
    return;

  case 0x7d17:
    sceneClassUser->voluntaryActionSwitchFlag = 0x7d17;
    sceneClassUser->statusInternalTimer = 0;
    return;

  case 0x7d18:
    AutonomousUpdate_SetStandAnimation_0x7d18(sceneClassUser);
    return;

  case 0x7d19:
    AutonomousUpdate_State_0x7d19(sceneClassUser);
    return;

  case 0x7d1a: {
    mainSwitchValue = sceneClassUser->PopQueuedElement();
    mainValue2 = sceneClassUser->PopQueuedElement();
    for (int32_t counter = 0; counter < 8; counter = counter + 1) {
      mainValue3 = sceneClassUser->orientation;
      int32_t collisionValue = sceneClassUser->mainSceneHandler->GetCollisionMapValueAtCoordindate(HitRngRelated1[mainValue3].DeltaX1 + sceneClassUser->floatMultiplier1_pos1, HitRngRelated1[mainValue3].DeltaY1 + sceneClassUser->floatMultiplier2_pos2);
      if ((collisionValue == mainSwitchValue) || (mainValue3 = sceneClassUser->orientation, collisionValue = sceneClassUser->mainSceneHandler->GetCollisionMapValueAtCoordindate(HitRngRelated1[mainValue3].DeltaX2 + sceneClassUser->floatMultiplier1_pos1, HitRngRelated1[mainValue3].DeltaY2 + sceneClassUser->floatMultiplier2_pos2), collisionValue == mainSwitchValue)) {
        break;
      }
      sceneClassUser->orientation = (sceneClassUser->orientation + 1) & 7;
    }
    mainValue3 = sceneClassUser->statusInternalTimer;
    sceneClassUser->statusInternalTimer = mainValue3 + 1;
    sceneClassUser->SetSpriteFrames(SpriteFrameSceneClassUser::Stand, mainValue3);
    if (FrameRelated != mainValue2) {
      sceneClassUser->mainSceneHandler->primarySwitchSingleParam(0x7d18, sceneClassUser->triggerScriptIdOnTalk, (intptr_t)ObjectList[mainSwitchValue].sceneClassObjectPointer);
      FrameRelated = mainValue2;
    }
    sceneClassUser->ResetEventCounter();
    return;
  }

  default: {
    sceneClassUser->ResetEventCounter();
    char* messageBox1 = s_AI;
    char* messageBox2 = s_Miss_Match;
    WrapperMessageBoxA(messageBox2, messageBox1);
    return;
  }

  case 0x7d1c:
    sceneClassUser->QueueTwoEvents(0x7d1d, 0);
    return;

  case 0x7d1d:
    mainValue3 = sceneClassUser->PopQueuedElement();
    sceneClassUser->SetSpriteFrames(SpriteFrameSceneClassUser::Magic, mainValue3);
    mainSwitchValue = sceneClassUser->genericAct->GetFrameCountForAction(sceneClassUser->actMagic);
    if (mainSwitchValue <= (mainValue3 + 1)) {
      return;
    }
    sceneClassUser->QueueTwoEvents(0x7d1d, mainValue3 + 1);
    return;

  case 0x7d1f: {
    int32_t mapWidth;
    int32_t packedIndex;
    ActiveCharacter* activeCharacter;
    ActiveCharacter** activeCharacterList;
    int32_t loopIndex1;
    SceneClassUser* sceneClassUserCopy;
    int32_t loopIndex2;

    mainSwitchValue = sceneClassUser->PopQueuedElement();
    mainValue2 = sceneClassUser->PopQueuedElement();
    sceneClassUser->voluntaryActionSwitchFlag = 0x7d21;
    if (((sceneClassUser->userFlags & 0x200000) == 0) || (sceneClassUser->mainSceneHandler->mapType == MapType::World)) {
      loopIndex1 = 4;
      loopIndex2 = 0x0;
      do {
        packedIndex = (int32_t)(loopIndex1 + (loopIndex1 >> 0x1f & 7U)) >> 3;
        mapWidth = sceneClassUser->mainSceneHandler->mapWidth;
        mainValue3 = PseudoRng();
        mapWidth = Minimum((((int32_t)((mainValue3 % loopIndex1) + (mainValue3 % loopIndex1 >> 0x1f & 3U)) >> 2) - packedIndex) + mainSwitchValue, ((int32_t)(mapWidth + (mapWidth >> 0x1f & 0xfU)) >> 4) + -4);
        mapWidth = Maximum(1, mapWidth);
        mainSceneHandler = sceneClassUser->mainSceneHandler;
        sceneClassUser->floatMultiplier1_pos1 = mapWidth;
        mapWidth = mainSceneHandler->mapHeight;
        mainValue3 = PseudoRng();
        mapWidth = Minimum((((int32_t)((mainValue3 % loopIndex1) + (mainValue3 % loopIndex1 >> 0x1f & 3U)) >> 2) - packedIndex) + mainValue2, ((int32_t)(mapWidth + (mapWidth >> 0x1f & 0xfU)) >> 4) + -4);
        mapWidth = Maximum(1, mapWidth);
        mainSceneHandler = sceneClassUser->mainSceneHandler;
        sceneClassUser->floatMultiplier2_pos2 = mapWidth;
        mapWidth = mainSceneHandler->HasUnoccupiedTileInRectangularRegion(sceneClassUser->floatMultiplier1_pos1, mapWidth, 2, 2);
        if ((mapWidth == 0) && (mapWidth = sceneClassUser->mainSceneHandler->HasUnoccupiedTileExcludingTypeInRectangularRegion(sceneClassUser->floatMultiplier1_pos1, sceneClassUser->floatMultiplier2_pos2, 2, 2, -1), mapWidth == -1)) {
          break;
        }
        if (0x7f < loopIndex1) {
          loopIndex1 = 9;
          loopIndex2 = loopIndex2 + 1;
        }
        loopIndex1 = loopIndex1 + 1;
      } while (loopIndex2 < 3);
      sceneClassUser->mainSceneHandler->SetCollisionValueInRectangularRegion(sceneClassUser->floatMultiplier1_pos1, sceneClassUser->floatMultiplier2_pos2, 2, 2, *(uint16_t*)&sceneClassUser->objectListId);
      sceneClassUser->floatTimesMultiplier1 = (float)sceneClassUser->floatMultiplier1_pos1 * GridMultiplier_16;
      sceneClassUser->floatTimesMultiplier2 = (float)sceneClassUser->floatMultiplier2_pos2 * GridMultiplier_16;
      mainValue3 = PseudoRng();
      sceneClassUser->statusInternalTimer = mainValue3 & 0x3f;
      sceneClassUserCopy = sceneClassUser;
      sceneClassUserCopy->UpdateObjectOnGrid(sceneClassUser->floatMultiplier1_pos1 << 4, sceneClassUser->floatMultiplier2_pos2 << 4);
      sceneClassUserCopy->primarySwitchSingleParam(0x7d26, 0x0, 0x0);
      if ((sceneClassUser->userFlags & 0x200000) == 0) {
        return;
      }
      sceneClassUserCopy->primarySwitchSingleParam(0x7d06, 0x0, 0x0);
      mainSceneHandler = sceneClassUser->mainSceneHandler;
      mainSceneHandler->primarySwitchSingleParam_UpdateSelectedUnits_0x7d1a((GameWindowBase*)nullptr, 0x0);
      mainSceneHandler->primarySwitchSingleParam_UpdateSelectedUnits_0x7d1a(sceneClassUserCopy, 0x0);
      return;
    }
    if (TeamCharacterList[0] != nullptr) {
      activeCharacterList = TeamCharacterList;
      activeCharacter = TeamCharacterList[0];
      do {
        activeCharacter->shiftedSceneClassUser0x48->primarySwitchSingleParam_SetUserLocationOnScene_0x7d13(sceneClassUser->floatMultiplier1_pos1, sceneClassUser->floatMultiplier2_pos2);
        sceneClassUser->mainSceneHandler->primarySwitchSingleParam_TriggerObjectInitialization_0x7d27((*activeCharacterList)->shiftedSceneClassUser0x48, 0x0);
        sceneClassUser->mainSceneHandler->primarySwitchSingleParam_UpdateSelectedUnits_0x7d1a((*activeCharacterList)->shiftedSceneClassUser0x48, 0x0);
        activeCharacter = activeCharacterList[1];
        activeCharacterList = activeCharacterList + 1;
      } while (activeCharacter != nullptr);
    }

    if (sceneClassUser != nullptr) {
      sceneClassUser->mainSceneHandler->primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(sceneClassUser, 0x0);
      return;
    }
    sceneClassUser->mainSceneHandler->primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(nullptr, 0x0);
    return;
  }

  case 0x7d20:
    sceneClassUser->primarySwitchSingleParam_PrepareMapForUnit_0x7d12(0x0, 0x0);
    return;

  case 0x7d24:
  case 0x7d25:
    return;

  case 0x7d26: {
    int32_t counter;
    int32_t frameCount;

    mainSwitchValue = __InlinePopEventQueueDecrement(sceneClassUser);
    mainValue2 = __InlineCappedPopEventQueueDecrement(sceneClassUser, 5);

    if ((mainSwitchValue < 1) || (5 < mainSwitchValue)) {
      sceneClassUser->eventCounter = 0;

      return;
    }
    if (mainSwitchValue != mainValue2) {
      sceneClassUser->__InlineableQueueEvent(mainValue2);
      sceneClassUser->__InlineableQueueEvent(mainSwitchValue + 1);
      sceneClassUser->__InlineableQueueEvent(0x7d26);
    }
    mainValue2 = sceneClassUser->genericAct->GetActionIndexByName((char*)CattIndexes[(mainSwitchValue * 2) - 1]);
    counter = 0;
    frameCount = sceneClassUser->genericAct->GetFrameCountForAction(mainValue2);
    if (0 < frameCount) {
      do {
        sceneClassUser->__InlineableQueueEvent(mainValue2);
        sceneClassUser->__InlineableQueueEvent(counter);
        sceneClassUser->__InlineableQueueEvent(0x7d27);
        counter = counter + 1;
        frameCount = sceneClassUser->genericAct->GetFrameCountForAction(mainValue2);
      } while (counter < frameCount);
    }
    sceneClassUser->__InlineableQueueEvent(0x7d0d);
    coreAct = sceneClassUser->genericAct;
    mainSwitchValue = coreAct->GetActionIndexByName((char*)CattIndexes[(mainSwitchValue * 2) - 2]);
    frameCount = 0;
    mainValue2 = sceneClassUser->genericAct->GetFrameCountForAction(mainSwitchValue);
    if (mainValue2 < 1) {

      return;
    }
    do {
      sceneClassUser->__InlineableQueueEvent(mainSwitchValue);
      sceneClassUser->__InlineableQueueEvent(frameCount);
      sceneClassUser->__InlineableQueueEvent(0x7d27);
      frameCount = frameCount + 1;
      mainValue2 = sceneClassUser->genericAct->GetFrameCountForAction(mainSwitchValue);
    } while (frameCount < mainValue2);

    return;
  }
  case 0x7d27:
    Autonomous_ApplyDynamicallyLoadedSprite_0x7d27(sceneClassUser);
    return;

  case 0x7d28:
    sceneClassUser->QueueTwoEvents(0x7d29, 0);
    return;

  case 0x7d29: {
    int32_t attackFrameCount = sceneClassUser->PopQueuedElement();
    sceneClassUser->SetSpriteFrames(SpriteFrameSceneClassUser::SpecialAttack, attackFrameCount);
    mainSwitchValue = sceneClassUser->genericAct->GetFrameCountForAction(sceneClassUser->actSpecialAtt);
    if (mainSwitchValue <= (attackFrameCount + 1)) {
      return;
    }
    sceneClassUser->QueueTwoEvents(0x7d29, attackFrameCount + 1);
    return;
  }

  case 0x7d2a: {
    int32_t eventSwitch;

    if (mainValue3 < 1) {
      eventSwitch = 0;
    }
    else {
      mainValue3 = mainSwitchValue - 2;
      sceneClassUser->eventCounter = mainValue3;
      eventSwitch = sceneClassUser->queuedEventsArray[mainValue3 >> 8]->queueEvents[mainValue3 & 0xff];
      if (4 < eventSwitch) {

        return;
      }
    }
    switch (eventSwitch) {
    default:
      sceneClassUser->__InlineQueueEvent(0);

      break;
    case 1:
      if (sceneClassUser->voluntaryActionSwitchFlag != 0x7d2a) {

        return;
      }
      sceneClassUser->__InlineableQueueEvent(0);
      sceneClassUser->__InlineableQueueEvent(4);
      sceneClassUser->__InlineableQueueEvent(0x7d2a);
      sceneClassUser->voluntaryActionSwitchFlag = 0x7d21;

      return;
    case 2:

      mainValue3 = __InlinePopEventQueueDecrement(sceneClassUser);
      mainSwitchValue = sceneClassUser->actGuard1;

      __InlineUpdateSpriteFrames(sceneClassUser, sceneClassUser->actGuard1, mainValue3);
      mainSwitchValue = sceneClassUser->genericAct->GetFrameCountForAction(sceneClassUser->actGuard1);
      if (mainSwitchValue <= (int32_t)(mainValue3 + 1)) {
        sceneClassUser->__InlineableQueueEvent(3);
        sceneClassUser->__InlineableQueueEvent(0x7d2a);
        sceneClassUser->voluntaryActionSwitchFlag = 0x7d2a;

        return;
      }
      sceneClassUser->__InlineableQueueEvent(mainValue3 + 1);
      break;
    case 3:
      sceneClassUser->voluntaryActionSwitchFlag = 0x7d2a;
      mainValue2 = sceneClassUser->genericAct->GetFrameCountForAction(sceneClassUser->actGuard1);
      __InlineUpdateSpriteFrames(sceneClassUser, sceneClassUser->actGuard1, mainValue2 - 1);
      sceneClassUser->__InlineableQueueEvent(3);
      sceneClassUser->__InlineableQueueEvent(0x7d2a);
      return;
    case 4:
      mainValue3 = __InlinePopEventQueueDecrement(sceneClassUser);
      __InlineUpdateSpriteFrames(sceneClassUser, sceneClassUser->actGuard2, mainValue3);
      mainSwitchValue = sceneClassUser->genericAct->GetFrameCountForAction(sceneClassUser->actGuard2);
      if (mainSwitchValue <= (mainValue3 + 1)) {
        return;
      }
      sceneClassUser->__InlineableQueueEvent(mainValue3 + 1);
      sceneClassUser->__InlineableQueueEvent(4);
      sceneClassUser->__InlineableQueueEvent(0x7d2a);
      return;
    }
    sceneClassUser->__InlineableQueueEvent(2);
    sceneClassUser->__InlineableQueueEvent(0x7d2a);
    return;
  }
  }

  exit(0);
}
