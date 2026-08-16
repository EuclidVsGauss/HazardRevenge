#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowCharacter.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardEnums/WindowToggle.hpp"
#include "HazardExterns/GameWindowCharacter.hpp"
#include "HazardGlobals.hpp"
#include "HazardInlineFunctions.hpp"
#include "HazardStructs/ActiveCharacter.hpp"
#include "HazardStructs/CharacterEquipment.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"
#include "HazardStructs/InventoryItemAccessory.hpp"
#include "HazardStructs/InventoryItemArmor.hpp"
#include "HazardStructs/InventoryItemBoots.hpp"
#include "HazardStructs/InventoryItemBracer.hpp"
#include "HazardStructs/InventoryItemSharant.hpp"
#include "HazardStructs/InventoryItemWeapon.hpp"
#include "HazardStructs/NumericalCharacterStats.hpp"
#include "HazardStructs/WindowReference.hpp"

const int32_t CharacterWindow_ExpHover_LowerX_338 = 338;
const int32_t CharacterWindow_ExpHover_UpperX_372 = 372;
const int32_t CharacterWindow_ExpHover_LowerY_24 = 24;
const int32_t CharacterWindow_ExpHover_UpperY_31 = 31;
const int32_t Sidebar_Width_145 = 145;
const int32_t CharacterWindow_Width_248 = 248;
const int32_t CharacterWindow_Height_288 = 288;

void GameWindowCharacter::primarySwitchSingleParam(int32_t switchParam, intptr_t param_2, intptr_t param_3) {

  ImageVectorWithHeader* spriteFrame;
  uint32_t totalExp;
  int32_t activeCharIndex;
  uint32_t totalLandRes;
  int32_t previousNextLevelHoldFlag;

  int32_t totalIceRes;
  int32_t totalWindRes;
  int32_t totalGuard;
  int32_t totalCurrentMp;
  int32_t totalMaxMp;
  int32_t totalLightningRes;
  int32_t totalFireRes;
  int32_t totalToHit;
  int32_t totalPower;
  int32_t totalSpeed;
  int32_t totalCurrentHp;
  int32_t totalMaxHp;

  int32_t equipSharantCount1;
  int32_t equipSharantCount2;
  int32_t equipSharantCount3;
  int32_t equipSharantCount4;
  int32_t equipSharantCount5;
  int32_t equipSharantCount6;

  ActiveCharacter* activeCharacter;
  NumericalCharacterStats* baseStats;

  uint32_t totalBarrageRaw;
  WindowReference windowReference;
  int32_t yBoundaryDelta;
  int32_t totalBarrage;

  (void)param_3;

  switch (switchParam) {
  case 0x7d11:
    this->mainSceneHandler = (SceneHandler*)param_2;

    this->primarySwitchSingleParam(0x7d16, 0x0, (intptr_t)nullptr);
    return;

  case 0x7d3b:

    spriteFrame = __InlineGetSolidSpriteFrameForAction(this->actFrame, this->win1Act, 0);
    GameWindowRightSide->RenderClippedSprite(this->staticXBoundary - Sidebar_Width_145, this->dynamicYBoundary, spriteFrame, DrawLayer::Layer0xFFF6);

    activeCharIndex = __InlineGetActiveCharacterIndex(*this->mainSceneHandler->selectedUnits32);
    activeCharacter = TeamCharacterList[activeCharIndex];
    if (activeCharacter == nullptr) {
      return;
    }
    if (ExperienceTable_CharacterWindow[4] == 666) {
      float previousLevel = ExpRequirementLevel4;
      for (int32_t tmp = 3; tmp < 72; tmp++) {
        ExperienceTable_CharacterWindow[tmp] = previousLevel;
        previousLevel = ExpIncreasePerLevel * previousLevel;
      }
    }

    baseStats = activeCharacter->characterBaseStats;
    totalPower = baseStats->Power;
    totalToHit = baseStats->ToHit;
    totalGuard = baseStats->Guard;
    totalSpeed = baseStats->Speed;

    totalFireRes = baseStats->FireResistance;

    totalMaxHp = baseStats->MaxHp;
    totalWindRes = baseStats->WindResistance;
    totalLandRes = baseStats->LandResistance;
    totalMaxMp = baseStats->MaxMp;
    totalIceRes = baseStats->IceResistance;
    totalCurrentHp = baseStats->CurrentHp;
    totalLightningRes = baseStats->LightningResistance;
    totalCurrentMp = baseStats->CurrentMp;
    if (0 < (activeCharacter->charEquip).equipmentWeapon.quantity) {
      totalPower = totalPower + ((activeCharacter->charEquip).equipmentWeapon.currentPower / 100);
      totalToHit = totalToHit + ((activeCharacter->charEquip).equipmentWeapon.toHit / 100);
      totalFireRes = totalFireRes + (activeCharacter->charEquip).equipmentWeapon.resFire;
      totalIceRes = totalIceRes + (activeCharacter->charEquip).equipmentWeapon.resIce;
      totalLightningRes = totalLightningRes + (activeCharacter->charEquip).equipmentWeapon.resLightning;
      totalWindRes = totalWindRes + (activeCharacter->charEquip).equipmentWeapon.resWind;
      totalLandRes = totalLandRes + (activeCharacter->charEquip).equipmentWeapon.resLand;
      equipSharantCount1 = (activeCharacter->charEquip).equipmentWeapon.mp;
      totalMaxMp = totalMaxMp + equipSharantCount1;
      totalCurrentMp = totalCurrentMp + equipSharantCount1;
    }
    if (0 < (activeCharacter->charEquip).equipmentArmor.quantity) {
      totalPower = totalPower + ((activeCharacter->charEquip).equipmentArmor.currentPower / 100);
      totalToHit = totalToHit + ((activeCharacter->charEquip).equipmentArmor.currentToHit / 100);
      totalGuard = totalGuard + ((activeCharacter->charEquip).equipmentArmor.currentGuard / 100);
      totalSpeed = totalSpeed + ((activeCharacter->charEquip).equipmentArmor.currentSpeed / 100);
      totalFireRes = totalFireRes + (activeCharacter->charEquip).equipmentArmor.resFire;
      totalIceRes = totalIceRes + (activeCharacter->charEquip).equipmentArmor.resIce;
      totalLightningRes = totalLightningRes + (activeCharacter->charEquip).equipmentArmor.resLightning;
      totalWindRes = totalWindRes + (activeCharacter->charEquip).equipmentArmor.resWind;
      totalLandRes = totalLandRes + (activeCharacter->charEquip).equipmentArmor.resLand;
      equipSharantCount1 = (activeCharacter->charEquip).equipmentArmor.mp;
      totalMaxMp = totalMaxMp + equipSharantCount1;
      totalCurrentMp = totalCurrentMp + equipSharantCount1;
    }
    if (0 < (activeCharacter->charEquip).equipmentBracer.quantity) {
      totalPower = totalPower + ((activeCharacter->charEquip).equipmentBracer.currentPower / 100);
      totalGuard = totalGuard + ((activeCharacter->charEquip).equipmentBracer.currentGuard / 100);
      totalLandRes = totalLandRes + (activeCharacter->charEquip).equipmentBracer.resLand;
    }
    if (0 < (activeCharacter->charEquip).equipmentBoots.quantity) {
      totalSpeed = totalSpeed + (activeCharacter->charEquip).equipmentBoots.speed;
      totalFireRes = totalFireRes + (activeCharacter->charEquip).equipmentBoots.resFire;
      totalIceRes = totalIceRes + (activeCharacter->charEquip).equipmentBoots.resIce;
      totalLightningRes = totalLightningRes + (activeCharacter->charEquip).equipmentBoots.resLightning;
      totalWindRes = totalWindRes + (activeCharacter->charEquip).equipmentBoots.resWind;
      totalLandRes = totalLandRes + (activeCharacter->charEquip).equipmentBoots.resLand;
    }
    if (0 < (activeCharacter->charEquip).equipmentAccessory1.quantity) {
      equipSharantCount1 = (activeCharacter->charEquip).equipmentAccessory1.hp;
      totalMaxHp = totalMaxHp + equipSharantCount1;
      totalCurrentHp = totalCurrentHp + equipSharantCount1;
      equipSharantCount1 = (activeCharacter->charEquip).equipmentAccessory1.mp;
      totalMaxMp = totalMaxMp + equipSharantCount1;
      totalCurrentMp = totalCurrentMp + equipSharantCount1;
      totalLandRes = totalLandRes + (activeCharacter->charEquip).equipmentAccessory1.resLand;
      totalLightningRes = totalLightningRes + (activeCharacter->charEquip).equipmentAccessory1.resLightning;
      totalFireRes = totalFireRes + (activeCharacter->charEquip).equipmentAccessory1.resFire;
      totalWindRes = totalWindRes + (activeCharacter->charEquip).equipmentAccessory1.resWind;
      totalIceRes = totalIceRes + (activeCharacter->charEquip).equipmentAccessory1.resIce;
      totalPower = totalPower + ((activeCharacter->charEquip).equipmentAccessory1.power / 100);
      totalGuard = totalGuard + ((activeCharacter->charEquip).equipmentAccessory1.guard / 100);
    }
    if (0 < (activeCharacter->charEquip).equipmentAccessory2.quantity) {
      equipSharantCount1 = (activeCharacter->charEquip).equipmentAccessory2.hp;
      totalMaxHp = totalMaxHp + equipSharantCount1;
      totalCurrentHp = totalCurrentHp + equipSharantCount1;
      equipSharantCount1 = (activeCharacter->charEquip).equipmentAccessory2.mp;
      totalMaxMp = totalMaxMp + equipSharantCount1;
      totalCurrentMp = totalCurrentMp + equipSharantCount1;
      totalLightningRes = totalLightningRes + (activeCharacter->charEquip).equipmentAccessory2.resLightning;
      totalLandRes = totalLandRes + (activeCharacter->charEquip).equipmentAccessory2.resLand;
      totalFireRes = totalFireRes + (activeCharacter->charEquip).equipmentAccessory2.resFire;
      totalWindRes = totalWindRes + (activeCharacter->charEquip).equipmentAccessory2.resWind;
      totalIceRes = totalIceRes + (activeCharacter->charEquip).equipmentAccessory2.resIce;
      totalPower = totalPower + ((activeCharacter->charEquip).equipmentAccessory2.power / 100);
      totalGuard = totalGuard + ((activeCharacter->charEquip).equipmentAccessory2.guard / 100);
    }
    equipSharantCount1 = (activeCharacter->charEquip).SharantSlot1.quantity;
    equipSharantCount2 = (activeCharacter->charEquip).SharantSlot2.quantity;
    equipSharantCount3 = (activeCharacter->charEquip).SharantSlot3.quantity;
    equipSharantCount4 = (activeCharacter->charEquip).SharantSlot4.quantity;
    equipSharantCount5 = (activeCharacter->charEquip).SharantSlot5.quantity;
    equipSharantCount6 = (activeCharacter->charEquip).SharantSlot6.quantity;
    totalBarrage = ((uint32_t)(0 < equipSharantCount1) + (uint32_t)(0 < equipSharantCount2) + (uint32_t)(0 < equipSharantCount3) + (uint32_t)(0 < equipSharantCount4) + (uint32_t)(0 < equipSharantCount5) + (uint32_t)(0 < equipSharantCount6));

    totalBarrageRaw = baseStats->Barrage;
    totalBarrage = (totalBarrage + totalBarrageRaw) * 5;

    spriteFrame = __InlineGetSolidSpriteFrameForAction(this->actBody, this->win1Act, activeCharacter->characterId);
    GameWindowRightSide->RenderClippedSprite(this->staticXBoundary - Sidebar_Width_145, this->dynamicYBoundary, spriteFrame, DrawLayer::Layer0xFFF6);
    DisplayNumericalValue(0xcc, 0x1c, activeCharacter->characterBaseStats->Level, this->actLvNum);
    if (this->boolHoldToShowNextLevelExp == 0) {
      totalExp = activeCharacter->characterBaseStats->Experience;
    }
    else {
      totalExp = ExperienceTable_CharacterWindow[activeCharacter->characterBaseStats->Level];
    }

    DisplayNumericalValue(325, 28, totalExp, this->actNumber1);
    DisplayNumericalValue(0x16b, 0x35, totalPower, this->actNumber1);
    DisplayNumericalValue(0x16b, 0x49, totalToHit, this->actNumber1);
    DisplayNumericalValue(0x16b, 0x5d, totalGuard, this->actNumber1);
    DisplayNumericalValue(363, 113, totalSpeed, this->actNumber1);
    DisplayNumericalValue(349, 134, totalFireRes, this->actNumber1);
    DisplayNumericalValue(0x15d, 0x96, totalIceRes, this->actNumber1);
    DisplayNumericalValue(0x15d, 0xa6, totalLightningRes, this->actNumber1);
    DisplayNumericalValue(0x15d, 0xb6, totalWindRes, this->actNumber1);
    DisplayNumericalValue(349, 198, totalLandRes, this->actNumber1);
    DisplayNumericalValue(0x12a, 0x35, activeCharacter->characterBaseStats->PowerGrowth, this->actNumber1);
    DisplayNumericalValue(0x12a, 0x49, activeCharacter->characterBaseStats->ToHitGrowth, this->actNumber1);
    DisplayNumericalValue(0x12a, 0x5d, activeCharacter->characterBaseStats->GuardGrowth, this->actNumber1);
    DisplayNumericalValue(0x12a, 0x71, activeCharacter->characterBaseStats->SpeedGrowth, this->actNumber1);
    DisplayNumericalValue(0x15c, 0xdd, activeCharacter->characterBaseStats->Eye, this->actNumber1);
    DisplayNumericalValue(0x15c, 0xed, totalBarrage, this->actNumber1);
    DisplayNumericalValue(0xd9, 0x105, totalCurrentHp, this->actHp1);
    DisplayNumericalValue(0xfe, 0x105, totalMaxHp, this->actHp2);
    DisplayNumericalValue(0x148, 0x105, totalCurrentMp, this->actMp1);
    DisplayNumericalValue(0x16c, 0x105, totalMaxMp, this->actMp2);
    return;

  case 0x7d3c:
    switch (this->hideOpenCloseFlag) {
    default:
      return;
    case WindowToggle::Closing: {
      yBoundaryDelta = this->dynamicYBoundary + -16;
      if (yBoundaryDelta < -0x120) {
        yBoundaryDelta = -0x120;
      }
      this->dynamicYBoundary = yBoundaryDelta;
      if (yBoundaryDelta == -0x120) {
        this->mainSceneHandler->primarySwitchSingleParam(0x7d0c, (intptr_t)this, 0x0);
      }
      this->primarySwitchSingleParam(0x7d16, 0x0, (intptr_t)nullptr);
      return;
    }

    case WindowToggle::Hidden: {
      yBoundaryDelta = this->dynamicYBoundary + 0x10;
      yBoundaryDelta = yBoundaryDelta & ((0 < yBoundaryDelta) - 1);
      this->dynamicYBoundary = yBoundaryDelta;
      if (yBoundaryDelta == 0) {
        this->hideOpenCloseFlag = 1;
      }
      this->primarySwitchSingleParam(0x7d16, 0x0, (intptr_t)nullptr);
      return;
    }
    case WindowToggle::Opening: {
      if (this->mainSceneHandler->selectedUnits32 != nullptr && this->mainSceneHandler->selectedUnits32[0] != nullptr) {
        return;
      }
    }
    }

  case 0x7d0c:
    this->hideOpenCloseFlag = WindowToggle::Closing;
    return;

  case 0x7d16:
    windowReference.coords[0] = Sidebar_Width_145;
    windowReference.coords[1] = 0;
    windowReference.coords[2] = Sidebar_Width_145 + CharacterWindow_Width_248;
    windowReference.coords[3] = this->dynamicYBoundary + CharacterWindow_Height_288;
    windowReference.windowAddress = (intptr_t)this;
    this->mainSceneHandler->primarySwitchSingleParam(0x7d16, 2, (intptr_t)&windowReference);
    return;

  case 0x7d0e:
    if (param_2 != 0x0) {
      if (
          (((MouseButtonClick == 0) || (this->staticXBoundary + CharacterWindow_ExpHover_LowerX_338 > CursorXCoord)) || (CursorXCoord > this->staticXBoundary + CharacterWindow_ExpHover_UpperX_372)) || (this->dynamicYBoundary + CharacterWindow_ExpHover_LowerY_24 > CursorYCoord || (CursorYCoord > this->dynamicYBoundary + CharacterWindow_ExpHover_UpperY_31))) {
        previousNextLevelHoldFlag = 0;
      }
      else {
        previousNextLevelHoldFlag = 1;
      }
      this->boolHoldToShowNextLevelExp = previousNextLevelHoldFlag;

      this->mainSceneHandler->primarySwitchSingleParam(0x7d17, 0, 0x0);
      return;
    }
    break;

  case 0x7d20:
    this->hideOpenCloseFlag = ((1 < (int32_t)this->hideOpenCloseFlag) - 1) & 2;
    return;
  }
}
