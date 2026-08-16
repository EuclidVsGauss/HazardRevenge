#include <stdio.h>
#include "HazardClasses/AnimationSpell.hpp"
#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/AnimationSummon.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowSpellcast.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardEnums/SpellEffect.hpp"
#include "HazardExterns/GameWindowSpellcast.hpp"
#include "HazardGlobals.hpp"
#include "HazardInlineFunctions.hpp"
#include "HazardStructs/ActiveCharacter.hpp"
#include "HazardStructs/InventoryItemSpell.hpp"
#include "HazardStructs/ItemReferenceCollection.hpp"
#include "HazardStructs/ItemReferenceStruct.hpp"
#include "HazardStructs/NumericalCharacterStats.hpp"
#include "HazardStructs/ObjectWrapper.hpp"

void __fastcall GameWindowSpellcast::CreateSpellAnimationObject() {
  InventoryItemSpell* spellItemPtr;
  GameWindowBase* sceneUserPtr;
  GameWindowBase* targetObjectPtr;
  NumericalCharacterStats* characterStatsPtr;
  uint32_t randomValue;
  AnimationSpell* spellAnimPtr;
  GameWindowBase* gameWindowBasePtr;
  int32_t targetX;
  int32_t targetY;
  int32_t targetIndex;
  GameWindowBase* thisGameWindow;
  SceneHandler* mainHandler;
  int32_t spellPowerValue;
  int32_t spellEffectValue;
  int32_t spellLevelCheck;
  int32_t spellTargetPower;
  int32_t statusSpellFunction;
  GameWindowSpellcast* selfRefernce;
  int32_t mapWidthClamped;
  char spellActFilename[20];
  int32_t spellEffectAlias;
  InventoryItemSpell* itemPtr;

  if (this->isActiveFlag != 0) {
    spellItemPtr = this->spellItem;
    spellLevelCheck = spellItemPtr->spellType;
    switch (spellLevelCheck) {
    case 1: {
      spellLevelCheck = this->incrementIndex;
      targetX = PseudoRng();
      targetX = ((targetX % spellLevelCheck) - (spellLevelCheck / 2)) + this->coord1;
      if (targetX < 2) {
        targetX = 1;
      }
      spellEffectValue = __InlineMinimum(((this->sceneClassUser->mainSceneHandler->mapWidth / 16) - 2), targetX);
      spellLevelCheck = this->incrementIndex;
      targetY = PseudoRng();
      targetY = ((targetY % spellLevelCheck) - (spellLevelCheck / 2)) + this->coord2;
      if (targetY < 2) {
        targetY = 1;
      }
      mainHandler = this->sceneClassUser->mainSceneHandler;

      targetIndex = __InlineMinimum((int32_t)((mainHandler->mapHeight / 16) - 2), targetY);
      if ((*(byte*)&this->loopMax_spellRange & 3) == 0) {

        gameWindowBasePtr = new AnimationSpell(this->spellAnimationAct, this->coord1, this->coord2);

      label_get_main_handler_and_store:
        mainHandler = this->sceneClassUser->mainSceneHandler;
      label_store_animation_object:

        mainHandler->StoreAndInitializeObject(gameWindowBasePtr);
      }
      else {

        spellLevelCheck = mainHandler->PaddedGridMap_Collision[targetIndex][spellEffectValue];
        if (-1 < spellLevelCheck) {
          spellItemPtr = this->spellItem;
          spellEffectAlias = spellItemPtr->spellEffect;
          switch (spellEffectAlias) {
          case SpellEffect::FireDamage:
          case SpellEffect::LightningDamage:
          case SpellEffect::WindDamage:
          case SpellEffect::EarthDamage:
            if ((ObjectList[spellLevelCheck].scriptUserFlags & 3) == 1) {
            label_apply_spell_effect:
              targetObjectPtr = ObjectList[spellLevelCheck].sceneClassObjectPointer;
              targetObjectPtr->primarySwitchSingleParam_0x7d22(spellItemPtr->spellPower, spellEffectAlias);
            }
            break;
          case SpellEffect::IceDamage:
          case SpellEffect::Gloomy:
          case SpellEffect::Wander:
            if ((ObjectList[spellLevelCheck].scriptUserFlags & 3) == 1) {
              targetObjectPtr = ObjectList[spellLevelCheck].sceneClassObjectPointer;
              targetObjectPtr->primarySwitchSingleParam_0x7d22(spellItemPtr->spellPower, spellEffectAlias);
            }
            if (((ObjectList[spellLevelCheck].scriptUserFlags & 3) == 1) && (4 < this->spellItem->spellLevel)) {
              targetObjectPtr = ObjectList[spellLevelCheck].sceneClassObjectPointer;
              targetObjectPtr->primarySwitchSingleParam_0x7d22(0, 0xb);
            }
            if (this->spellItem->spellEffect == 2) {

              targetObjectPtr = ObjectList[spellLevelCheck].sceneClassObjectPointer;
              gameWindowBasePtr = new AnimationStatusSpell(this->spellAnimationAct, targetObjectPtr->matrixIndexXTimes16, targetObjectPtr->matrixIndexYTimes16, this->spellItem->spellPower << 5);

              this->sceneClassUser->mainSceneHandler->StoreAndInitializeObject(gameWindowBasePtr);
            }
            break;
          case SpellEffect::HealAlly:
          case SpellEffect::CureGloomy:
          case SpellEffect::CureWander:
          case SpellEffect::CureAllEffects:
            if ((ObjectList[spellLevelCheck].scriptUserFlags & 3) != 1) {
              goto label_apply_spell_effect;
            }
          }

          targetObjectPtr = ObjectList[spellLevelCheck].sceneClassObjectPointer;
          spellAnimPtr = new AnimationSpell(this->spellAnimationAct, targetObjectPtr->matrixIndexXTimes16, targetObjectPtr->matrixIndexYTimes16);

          this->sceneClassUser->mainSceneHandler->StoreAndInitializeObject(spellAnimPtr);
        }
        this->incrementIndex = this->incrementIndex + 1;
      }
    } break;
    case 2: {
      sceneUserPtr = this->sceneClassUser;
      randomValue = this->orientationRelated & 7;
      spellTargetPower = (sceneUserPtr->matrixIndexXTimes16 + (AnimationLookup[randomValue * 2] * 2));
      spellPowerValue = (sceneUserPtr->matrixIndexYTimes16 + (AnimationLookup[(randomValue * 2) + 1] * 2));

      this->orientationRelated = ((((-((this->loopMax_spellRange & 1U) != 0) & 0xfe) + 1) * this->incrementIndex) + this->orientationRelated) & 7;

      spellLevelCheck = sceneUserPtr->mainSceneHandler->PaddedGridMap_Collision[spellPowerValue][spellTargetPower];
      if ((-1 < spellLevelCheck) && ((ObjectList[spellLevelCheck].scriptUserFlags & 3) == 1)) {
        targetObjectPtr = ObjectList[spellLevelCheck].sceneClassObjectPointer;
        spellEffectValue = spellItemPtr->spellEffect;
        if (spellEffectValue == 2) {
          spellEffectValue = 2;
          targetIndex = spellItemPtr->spellPower;
          statusSpellFunction = 0x7d22;
        }
        else {
          targetIndex = spellItemPtr->spellPower;
          statusSpellFunction = 0x7d33;
        }
        targetObjectPtr->primarySwitchSingleParam(statusSpellFunction, targetIndex, spellEffectValue);
        targetObjectPtr = ObjectList[spellLevelCheck].sceneClassObjectPointer;
        spellTargetPower = targetObjectPtr->matrixIndexXTimes16;
        spellPowerValue = targetObjectPtr->matrixIndexYTimes16;
      }
      if (this->spellItem->spellEffect == 2) {

        gameWindowBasePtr = new AnimationStatusSpell(this->spellAnimationAct, spellTargetPower, spellPowerValue, this->spellItem->spellPower << 5);

        this->sceneClassUser->mainSceneHandler->StoreAndInitializeObject(gameWindowBasePtr);
        this->incrementIndex = this->incrementIndex + 1;
      }
      else {

        spellAnimPtr = new AnimationSpell(this->spellAnimationAct, spellTargetPower, spellPowerValue);

        this->sceneClassUser->mainSceneHandler->StoreAndInitializeObject(spellAnimPtr);
        this->incrementIndex = this->incrementIndex + 1;
      }
    } break;
    case 3: {
      do {

        spellEffectValue = this->loopMax_spellRange + -1;
        sceneUserPtr = this->sceneClassUser;
        this->loopMax_spellRange = spellEffectValue;
        spellLevelCheck = sceneUserPtr->matrixIndexXTimes16 + -0xe + ((spellEffectValue / 0xf) * 2);
        if (spellLevelCheck < 3) {
          spellLevelCheck = 2;
        }
        mainHandler = sceneUserPtr->mainSceneHandler;
        targetIndex = mainHandler->mapWidth;
        mapWidthClamped = ((int32_t)(targetIndex + (targetIndex >> 0x1f & 0xfU)) >> 4) + -2;
        if (spellLevelCheck <= mapWidthClamped) {
          mapWidthClamped = spellLevelCheck;
        }
        spellLevelCheck = sceneUserPtr->matrixIndexYTimes16 + -0xe + ((spellEffectValue % 0xf) * 2);
        if (spellLevelCheck < 3) {
          spellLevelCheck = 2;
        }
        spellEffectValue = mainHandler->mapHeight;
        spellEffectValue = ((int32_t)(spellEffectValue + (spellEffectValue >> 0x1f & 0xfU)) >> 4) + -2;
        if (spellLevelCheck <= spellEffectValue) {
          spellEffectValue = spellLevelCheck;
        }
        spellLevelCheck = mainHandler->PaddedGridMap_Collision[spellEffectValue][mapWidthClamped];
        if ((-1 < spellLevelCheck) && ((ObjectList[spellLevelCheck].scriptUserFlags & 3) == 1)) {
          targetObjectPtr = ObjectList[spellLevelCheck].sceneClassObjectPointer;
          targetObjectPtr->primarySwitchSingleParam_0x7d22(this->spellItem->spellPower, this->spellItem->spellEffect);
          if (this->spellItem->spellEffect != 2) {

            targetObjectPtr = ObjectList[spellLevelCheck].sceneClassObjectPointer;
            gameWindowBasePtr = new AnimationSpell(this->spellAnimationAct, targetObjectPtr->matrixIndexXTimes16, targetObjectPtr->matrixIndexYTimes16);
            mainHandler = this->sceneClassUser->mainSceneHandler;

            goto label_store_animation_object;
          }

          targetObjectPtr = ObjectList[spellLevelCheck].sceneClassObjectPointer;
          gameWindowBasePtr = new AnimationStatusSpell(this->spellAnimationAct, targetObjectPtr->matrixIndexXTimes16, targetObjectPtr->matrixIndexYTimes16, this->spellItem->spellPower << 5);
          goto label_get_main_handler_and_store;
        }
        randomValue = PseudoRng();
        if ((randomValue & 0xf) == 0) {

          spellAnimPtr = new AnimationSpell(this->spellAnimationAct, mapWidthClamped, spellEffectValue);

          this->sceneClassUser->mainSceneHandler->StoreAndInitializeObject(spellAnimPtr);
        }
        randomValue = PseudoRng();
        if ((randomValue & 0x7f) == 0) {

          sprintf(spellActFilename, s__d_act, this->spellItem->typeId);

          gameWindowBasePtr = new AnimationSummon(spellActFilename);

          mainHandler = this->sceneClassUser->mainSceneHandler;

          mainHandler->primarySwitchSingleParam_TriggerObjectInitialization_0x7d27(gameWindowBasePtr, 0x0);
        }

      } while (0 < this->loopMax_spellRange);
    } break;
    default:
      break;
    }
    spellLevelCheck = this->loopMax_spellRange;
    this->loopMax_spellRange = spellLevelCheck + -1;
    if (0 < spellLevelCheck) {

      return;
    }
    itemPtr = this->spellItem;
    selfRefernce = this;
    if (itemPtr->spellType == 1) {
      if (itemPtr->spellLevel < 6) {
        itemPtr->spellExp = itemPtr->spellExp + 1;
        spellItemPtr = this->spellItem;
        if ((&spellItemPtr->spellPower)[spellItemPtr->spellLevel] <= spellItemPtr->spellExp) {
          spellItemPtr->spellLevel = spellItemPtr->spellLevel + 1;
          this->spellItem->spellExp = 0;
          spellItemPtr = this->spellItem;
          if (((spellItemPtr->spellLevel & 1) == 1) && (spellItemPtr->typeId < 264)) {
            spellItemPtr->typeId = spellItemPtr->typeId + 1;
            this->spellItem->actOffset = ItemStruct12k->itemArray[this->spellItem->typeId].actOffset;
          }
        }
      }
    }
    else if ((itemPtr->spellType == 3) && (itemPtr->spellLevel < 6)) {
      itemPtr->spellExp = itemPtr->spellExp + 1;
      spellItemPtr = this->spellItem;
      if ((&spellItemPtr->spellPower)[spellItemPtr->spellLevel] <= spellItemPtr->spellExp) {
        spellItemPtr->spellLevel = spellItemPtr->spellLevel + 1;
        spellLevelCheck = 0x7d0c;
        this->spellItem->spellExp = 0;
        mainHandler = this->mainSceneHandler;
        thisGameWindow = mainHandler;
        goto label_dispatch_spell_switch;
      }
    }
    mainHandler = this->mainSceneHandler;
    spellLevelCheck = 0x7d0c;
    thisGameWindow = mainHandler;
  }
  else {
    characterStatsPtr = this->characterInventory->characterBaseStats;
    randomValue = characterStatsPtr->TimeGauge;

    characterStatsPtr->TimeGauge = randomValue + 1;
    if ((int32_t)randomValue < 0x140) {

      return;
    }
    thisGameWindow = this;
    selfRefernce = nullptr;
    spellLevelCheck = 0x7d22;
  }

label_dispatch_spell_switch:
  thisGameWindow->primarySwitchSingleParam(spellLevelCheck, (intptr_t)selfRefernce, 0x0);
}
