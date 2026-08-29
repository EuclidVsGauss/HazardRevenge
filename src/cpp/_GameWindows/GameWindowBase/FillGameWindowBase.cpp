#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneHandler.hpp"

GameWindowBase::GameWindowBase() {
  mainSceneHandler = nullptr;
  previousObject = nullptr;
  nextObject = nullptr;
  matrixIndexY = 0x0;
  matrixIndexX = 0x0;
  matrixIndexYTimes16 = 0x0;
  matrixIndexXTimes16 = 0x0;
}
