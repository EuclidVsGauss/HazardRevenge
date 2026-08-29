#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/PathfindingState.hpp"
#include "HazardClasses/SceneClassUser.hpp"

SceneClassUser::~SceneClassUser() {
  PathfindingState* pathfindingObj;
  CoreActClass* actObj;

  pathfindingObj = this->allySupportPathfinding;
  if (pathfindingObj != nullptr) {
    pathfindingObj->ReturnMemoryPool();
    delete pathfindingObj;
  }
  pathfindingObj = this->pathfindingInputObj;
  if (pathfindingObj != nullptr) {
    pathfindingObj->ReturnMemoryPool();
    delete pathfindingObj;
  }
  actObj = this->genericAct;
  if (actObj != nullptr) {
    delete actObj;
  }
}
