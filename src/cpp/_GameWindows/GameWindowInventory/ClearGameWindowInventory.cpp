#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowInventory.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/InventoryItemStruct.hpp"
#include "HazardStructs/WindowReference.hpp"

GameWindowInventory::~GameWindowInventory() {
  SceneHandler* sceneHandler;
  CoreActClass* actObject;

  if ((this->itemHeldInCursor).quantity != 0) {
    this->primarySwitchSingleParam(0x7d2e, (intptr_t)&this->itemHeldInCursor, 0x0);
  }
  sceneHandler = this->mainSceneHandler;
  sceneHandler->primarySwitchSingleParam(0x7d14, 0, 0x3);
  sceneHandler = this->mainSceneHandler;
  sceneHandler->primarySwitchSingleParam_SetWindow_0x7d16(4, nullptr);
  actObject = this->win3actPointer;
  if (actObject != nullptr) {
    delete actObject;
  }
}
