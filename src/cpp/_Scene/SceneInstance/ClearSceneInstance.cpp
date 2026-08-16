#include "HazardClasses/EventHandler.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardClasses/SceneInstance.hpp"
#include "HazardEnums/MapType.hpp"
#include "HazardExterns/SceneInstance.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/QueueEventContainer.hpp"

SceneInstance::~SceneInstance() {
  int32_t switchParam;
  intptr_t arg1;
  intptr_t arg2;

  while (this->eventCounter > 0) {

    this->eventCounter--;
    switchParam = this->queuedEventsArray[this->eventCounter >> 8]->queueEvents[this->eventCounter & 0xff];
    if (switchParam == 0) {
      break;
    }

    if (this->eventCounter > 0) {
      this->eventCounter--;
      arg1 = this->queuedEventsArray[this->eventCounter >> 8]->queueEvents[this->eventCounter & 0xff];
    }
    else {
      arg1 = 0x0;
    }

    if (this->eventCounter > 0) {
      this->eventCounter--;
      arg2 = this->queuedEventsArray[this->eventCounter >> 8]->queueEvents[this->eventCounter & 0xff];
    }
    else {
      arg2 = 0x0;
    }

    this->large65736->primarySwitchSingleParam(switchParam, arg1, arg2);
  }

  if (this->large65736->mapType == MapType::World) {
    this->large65736->primarySwitchSingleParam(0x7d07, (intptr_t)nullptr, 0x0);
  }

  if (strcmp(this->sceneName, s_macro) == 0) {
    this->large65736->sceneCamera->primarySwitchSingleParam(0x7d21, 0x10, 0x10);
  }

  if (this->latestUnitToMoveToNewScene != nullptr) {
    this->latestUnitToMoveToNewScene->primarySwitchSingleParam(0x7d06, 0, 0);
  }
}
