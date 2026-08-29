#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/SceneClassGate.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ObjectWrapper.hpp"

__forceinline void SceneClassGate::InitializeObject_0x7d11(intptr_t targetObjectIndex) {
  uint32_t trackResult;
  this->mainSceneHandler = (SceneHandler*)targetObjectIndex;
  trackResult = this->TrackObjects(0x50);
  this->mainSceneHandler->SetCollisionValueInRectangularRegion(this->gateCoord1, this->gateCoord2, this->gateHeightOrWidth, this->gateWidthOrHeight, (int16_t)trackResult);
}

__forceinline void SceneClassGate::TriggerInteraction_0x7d04(intptr_t targetObjectIndex) {
  GameWindowBase* unitWindow;
  GameWindowBase** selectedUnits;
  SceneHandler* sceneHandler;
  int32_t selectedIndex;
  SceneHandler* newSceneHandler;
  int32_t hasSelectedUnit;

  unitWindow = ObjectList[targetObjectIndex].sceneClassObjectPointer;
  if (unitWindow != nullptr) {
    selectedIndex = 0;
    selectedUnits = this->mainSceneHandler->selectedUnits32;
    while (selectedUnits[selectedIndex] != nullptr && unitWindow != selectedUnits[selectedIndex]) {
      selectedIndex = selectedIndex + 1;
    }

    hasSelectedUnit = (selectedUnits[selectedIndex] != nullptr);
    unitWindow->primarySwitchSingleParam_PrepareMapForUnit_0x7d12(0x0, 0x0);

    unitWindow = ObjectList[targetObjectIndex].sceneClassObjectPointer;
    unitWindow->primarySwitchSingleParam_SetUserLocationOnScene_0x7d13(this->newSceneCoord1, this->newSceneCoord2);

    sceneHandler = this->mainSceneHandler;
    sceneHandler->primarySwitchSingleParam(0x7d08, (intptr_t)this->newSceneName, (intptr_t)&newSceneHandler);
    newSceneHandler->primarySwitchSingleParam_TriggerObjectInitialization_0x7d27(ObjectList[targetObjectIndex].sceneClassObjectPointer, 0);
    if (hasSelectedUnit) {
      newSceneHandler->primarySwitchSingleParam_UpdateSelectedUnits_0x7d1a(ObjectList[targetObjectIndex].sceneClassObjectPointer, 0);
      if (*this->mainSceneHandler->selectedUnits32 == nullptr) {
        newSceneHandler->primarySwitchSingleParam(0x7d07, (intptr_t)ObjectList[targetObjectIndex].sceneClassObjectPointer, 0);
      }
    }
  }
}

void SceneClassGate::primarySwitchSingleParam(int32_t switchParam, intptr_t targetObjectIndex, intptr_t param3) {
  (void)param3;

  switch (switchParam) {
  case 0x7d11:
    this->InitializeObject_0x7d11(targetObjectIndex);
    break;

  case 0x7d04:
    this->TriggerInteraction_0x7d04(targetObjectIndex);
    break;
  }
}
