#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/SceneClassGate0.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardClasses/SceneInstance.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActiveCharacter.hpp"
#include "HazardStructs/ObjectWrapper.hpp"

__forceinline void Case_0x7d11(intptr_t unitIndex, SceneClassGate0* gate0) {
  uint32_t collisionFlags;
  gate0->mainSceneHandler = (SceneHandler*)unitIndex;
  collisionFlags = gate0->TrackObjects(0x50);
  gate0->mainSceneHandler->SetCollisionValueInRectangularRegion(gate0->gateCoord1, gate0->gateCoord2, gate0->gateHeightOrWidth, gate0->gateWidthOrHeight, (int16_t)collisionFlags);
}

__forceinline void Case_0x7d04(intptr_t unitIndex, SceneClassGate0* gate0) {
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
      if (TeamCharacterList[teamIndex]->shiftedSceneClassUser0x48->mainSceneHandler != gate0->mainSceneHandler) {
        break;
      }
      teamIndex = teamIndex + 1;
    }
    if (TeamCharacterList[teamIndex] == nullptr) {
      selectedUnitIndex = 0;
      selectedUnitsStart = gate0->mainSceneHandler->selectedUnits32;
      while ((selectedUnitsStart[selectedUnitIndex] != nullptr && (targetUnit != selectedUnitsStart[selectedUnitIndex]))) {
        selectedUnitIndex = selectedUnitIndex + 1;
      }
      hasSelectedUnit = (selectedUnitsStart[selectedUnitIndex] != nullptr);
      targetUnit->primarySwitchSingleParam_PrepareMapForUnit_0x7d12(0x0, 0x0);
      targetUnit = ObjectList[unitIndex].sceneClassObjectPointer;
      targetUnit->primarySwitchSingleParam_SetUserLocationOnScene_0x7d13(gate0->newSceneCoord1, gate0->newSceneCoord2);
      gate0->mainSceneHandler->primarySwitchSingleParam(0x7d08, (intptr_t)gate0->newSceneName, (intptr_t)(void**)&worldScene);
      worldScene->primarySwitchSingleParam_TriggerObjectInitialization_0x7d27(ObjectList[unitIndex].sceneClassObjectPointer, 0);
      if (hasSelectedUnit) {
        worldScene->primarySwitchSingleParam_UpdateSelectedUnits_0x7d1a((GameWindowBase*)nullptr, 0);
        worldScene->primarySwitchSingleParam_UpdateSelectedUnits_0x7d1a(ObjectList[unitIndex].sceneClassObjectPointer, 0);
        if (*gate0->mainSceneHandler->selectedUnits32 == nullptr) {
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
    Case_0x7d11(unitIndex, this);
    break;
  case 0x7d04:
    Case_0x7d04(unitIndex, this);
    break;
  }
}
