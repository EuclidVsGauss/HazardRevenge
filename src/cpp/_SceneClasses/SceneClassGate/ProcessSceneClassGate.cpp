#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/SceneClassGate.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ObjectWrapper.hpp"

__forceinline void Case_0x7d11(SceneClassGate* gate, intptr_t targetObjectIndex) {
  uint32_t trackResult;
  gate->mainSceneHandler = (SceneHandler*)targetObjectIndex;
  trackResult = gate->TrackObjects(0x50);
  gate->mainSceneHandler->SetCollisionValueInRectangularRegion(gate->gateCoord1, gate->gateCoord2, gate->gateHeightOrWidth, gate->gateWidthOrHeight, (int16_t)trackResult);
}

__forceinline void Case_0x7d04(SceneClassGate* gate, intptr_t targetObjectIndex) {
  GameWindowBase* unitWindow;
  GameWindowBase** selectedUnits;
  SceneHandler* sceneHandler;
  int32_t selectedIndex;
  SceneHandler* newSceneHandler;
  int32_t hasSelectedUnit;

  unitWindow = ObjectList[targetObjectIndex].sceneClassObjectPointer;
  if (unitWindow != nullptr) {
    selectedIndex = 0;
    selectedUnits = gate->mainSceneHandler->selectedUnits32;
    while (selectedUnits[selectedIndex] != nullptr && unitWindow != selectedUnits[selectedIndex]) {
      selectedIndex = selectedIndex + 1;
    }

    hasSelectedUnit = (selectedUnits[selectedIndex] != nullptr);
    unitWindow->primarySwitchSingleParam_PrepareMapForUnit_0x7d12(0x0, 0x0);

    unitWindow = ObjectList[targetObjectIndex].sceneClassObjectPointer;
    unitWindow->primarySwitchSingleParam_SetUserLocationOnScene_0x7d13(gate->newSceneCoord1, gate->newSceneCoord2);

    sceneHandler = gate->mainSceneHandler;
    sceneHandler->primarySwitchSingleParam(0x7d08, (intptr_t)gate->newSceneName, (intptr_t)&newSceneHandler);
    newSceneHandler->primarySwitchSingleParam_TriggerObjectInitialization_0x7d27(ObjectList[targetObjectIndex].sceneClassObjectPointer, 0);
    if (hasSelectedUnit) {
      newSceneHandler->primarySwitchSingleParam_UpdateSelectedUnits_0x7d1a(ObjectList[targetObjectIndex].sceneClassObjectPointer, 0);
      if (*gate->mainSceneHandler->selectedUnits32 == nullptr) {
        newSceneHandler->primarySwitchSingleParam(0x7d07, (intptr_t)ObjectList[targetObjectIndex].sceneClassObjectPointer, 0);
      }
    }
  }
}

void SceneClassGate::primarySwitchSingleParam(int32_t switchParam, intptr_t targetObjectIndex, intptr_t param3) {
  (void)param3;

  switch (switchParam) {
  case 0x7d11:
    Case_0x7d11(this, targetObjectIndex);
    break;

  case 0x7d04:
    Case_0x7d04(this, targetObjectIndex);
    break;
  }
}
