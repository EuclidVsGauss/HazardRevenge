#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneClassMap.hpp"
#include "HazardClasses/Tilemap.hpp"

SceneClassMap::SceneClassMap(char* fileName, SceneHandler* param_2) : tileLayout() {
  this->mainSceneHandler = param_2;
  this->LoadTmpFile(fileName);
}
