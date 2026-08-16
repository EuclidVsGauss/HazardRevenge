#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneClassRect.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ObjectWrapper.hpp"

__forceinline void SceneClassRect::InitializeObject_0x7d11(SceneHandler* sceneHandler) {
  this->mainSceneHandler = sceneHandler;
  this->mainSceneHandler->primarySwitchSingleParam(0x7d0f, (intptr_t)(GameWindowBase*)this, 0x0);
}

__forceinline void SceneClassRect::Trigger_0x7d3c() {
  int32_t unitRow;
  int32_t unitCol;
  int32_t row;
  int32_t col;
  int32_t unitId;
  int32_t cellValue;

  if (GameFlags[this->gameflagIndex] == 0) {
    for (row = 0; row < this->rectangleHeight; row++) {
      for (col = 0; col < this->rectangleWidth; col++) {
        cellValue = this->mainSceneHandler->PaddedGridMap_Collision[this->lowerY + row][this->lowerX + col];

        if (cellValue >= 0 && cellValue != -1) {
          for (unitRow = 0; unitRow < this->rectangleHeight; unitRow++) {
            for (unitCol = 0; unitCol < this->rectangleWidth; unitCol++) {
              unitId = this->mainSceneHandler->PaddedGridMap_Collision[unitRow + this->lowerY][unitCol + this->lowerX];

              if (unitId >= 0) {
                if ((ObjectList[unitId].scriptUserFlags & 3) == 2 && this->isTriggered == 0) {
                  this->mainSceneHandler->primarySwitchSingleParam(0x7d18, this->dialogueIndex, (intptr_t)ObjectList[unitId].sceneClassObjectPointer);
                  this->mainSceneHandler->sceneCamera->primarySwitchSingleParam(0x7d21, ObjectList[unitId].sceneClassObjectPointer->matrixIndexXTimes16 << 4, ObjectList[unitId].sceneClassObjectPointer->matrixIndexYTimes16 << 4);
                  this->isTriggered++;
                }
              }
            }
          }
          return;
        }
      }
    }
  }
}

void SceneClassRect::primarySwitchSingleParam(int32_t param_1, intptr_t param2, intptr_t param3) {

  (void)param3;

  switch (param_1) {
  case 0x7d11:
    InitializeObject_0x7d11((SceneHandler*)param2);
    return;

  case 0x7d3c:
    Trigger_0x7d3c();
    return;

  default:
    return;
  }
}
