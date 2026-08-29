#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardClasses/SceneInstance.hpp"
#include "HazardEnums/MapType.hpp"
#include "HazardExterns/SceneInstance.hpp"
#include "HazardGlobals.hpp"
#include "HazardInlineFunctions.hpp"

SceneInstance::SceneInstance(char* sceneName) {
  this->large65736 = new SceneHandler();
  this->latestUnitToMoveToNewScene = nullptr;
  this->sceneInstanceIndex_10to14 = (NewSceneIndex % 5) + 10;
  NewSceneIndex = NewSceneIndex + 1;
  this->sceneLinesToBeParsed = 0;
  this->sceneLinesCurrentlyParsed = 0;

  __InlineCopyString(this->sceneName, sceneName);
  __InlineCopyString(this->large65736->sceneName, sceneName);

  this->large65736->primarySwitchSingleParam(0x7d11, (intptr_t)this, MapType::Field);
}
