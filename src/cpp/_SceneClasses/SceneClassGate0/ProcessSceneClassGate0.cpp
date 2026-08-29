#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/SceneClassGate0.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardClasses/SceneInstance.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActiveCharacter.hpp"
#include "HazardStructs/ObjectWrapper.hpp"

__forceinline void SceneClassGate0::InitializeObject_0x7d11(intptr_t unitIndex) {
  uint32_t collisionFlags;
  this->mainSceneHandler = (SceneHandler*)unitIndex;
  collisionFlags = this->TrackObjects(0x50);
  this->mainSceneHandler->SetCollisionValueInRectangularRegion(this->gateCoord1, this->gateCoord2, this->gateHeightOrWidth, this->gateWidthOrHeight, (int16_t)collisionFlags);
}

__forceinline void SceneClassGate0::TriggerInteraction_0x7d04(intptr_t unitIndex) {
  GameWindowBase* targetUnit;
  GameWindowBase** selectedUnitsStart;
  SceneInstance* worldScene;
  int32_t teamIndex;
  int32_t selectedUnitIndex;
  int32_t hasSelectedUnit;

  targetUnit = ObjectList[unitIndex].sceneClassObjectPointer;
  if (targetUnit != nullptr) {
    teamIndex = 0;
    while (TeamCharacterList[teamIndex] != nullptr) {
      if (TeamCharacterList[teamIndex]->sceneClassUser->mainSceneHandler != this->mainSceneHandler) {
        break;
      }
      teamIndex = teamIndex + 1;
    }
    if (TeamCharacterList[teamIndex] == nullptr) {
      selectedUnitIndex = 0;
      selectedUnitsStart = this->mainSceneHandler->selectedUnits32;
      while ((selectedUnitsStart[selectedUnitIndex] != nullptr && (targetUnit != selectedUnitsStart[selectedUnitIndex]))) {
        selectedUnitIndex = selectedUnitIndex + 1;
      }
      hasSelectedUnit = (selectedUnitsStart[selectedUnitIndex] != nullptr);
      targetUnit->primarySwitchSingleParam_PrepareMapForUnit_0x7d12(0x0, 0x0);
      targetUnit = ObjectList[unitIndex].sceneClassObjectPointer;
      targetUnit->primarySwitchSingleParam_SetUserLocationOnScene_0x7d13(this->newSceneCoord1, this->newSceneCoord2);
      this->mainSceneHandler->primarySwitchSingleParam(0x7d08, (intptr_t)this->newSceneName, (intptr_t)(void**)&worldScene);
      worldScene->primarySwitchSingleParam_TriggerObjectInitialization_0x7d27(ObjectList[unitIndex].sceneClassObjectPointer, 0);
      if (hasSelectedUnit) {
        worldScene->primarySwitchSingleParam_UpdateSelectedUnits_0x7d1a((GameWindowBase*)nullptr, 0);
        worldScene->primarySwitchSingleParam_UpdateSelectedUnits_0x7d1a(ObjectList[unitIndex].sceneClassObjectPointer, 0);
        if (*this->mainSceneHandler->selectedUnits32 == nullptr) {
          worldScene->primarySwitchSingleParam(0x7d07, (intptr_t)ObjectList[unitIndex].sceneClassObjectPointer, 0);
        }
      }
    }
  }
}

void SceneClassGate0::primarySwitchSingleParam(int32_t switchParam, intptr_t unitIndex, intptr_t param3) {
  (void)param3;
  switch (switchParam) {
  case 0x7d11:
    this->InitializeObject_0x7d11(unitIndex);
    break;
  case 0x7d04:
    this->TriggerInteraction_0x7d04(unitIndex);
    break;
  }
}
