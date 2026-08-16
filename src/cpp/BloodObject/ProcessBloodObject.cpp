#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/BloodObject.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardExterns/BloodObject.hpp"
#include "HazardInlineFunctions.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

__forceinline void BloodObject::HandleCase7d11(intptr_t param2) {
  this->mainSceneHandler = (SceneHandler*)param2;
  this->mainSceneHandler->primarySwitchSingleParam(0x7d0f, (intptr_t)this, 0x0);
}

__forceinline void BloodObject::HandleCase7d3b() {
  int32_t drawX = this->matrixIndexXTimes16;
  int32_t drawY = this->matrixIndexYTimes16;
  SceneHandler* mainSceneHandler = this->mainSceneHandler;
  int32_t xTimes16PlusOne = (drawX + 1) * 0x10;
  int32_t yTimes16PlusOne = (drawY + 1) * 0x10;

  if (mainSceneHandler->PaddedGridMap_Visibility[drawY >> 1][drawX >> 1] == 0) {
    return;
  }
  ImageVectorWithHeader* solidSpriteFrame = __InlineGetSolidSpriteFrameForActionWithOrientation(BloodActStand, BloodActObject, this->spriteOrientation, this->spriteFrameIndex);
  mainSceneHandler->sceneCamera->DrawSprite(xTimes16PlusOne, yTimes16PlusOne, solidSpriteFrame, yTimes16PlusOne + 480);
}

__forceinline void BloodObject::HandleCase7d3c() {
  this->spriteFrameIndex++;
  if (this->spriteFrameIndex < NestedContentFromAct + -1) {
    return;
  }
  this->mainSceneHandler->primarySwitchSingleParam(0x7d0c, (intptr_t)this, 0x0);
}

void BloodObject::primarySwitchSingleParam(int32_t switchParam, intptr_t param2, intptr_t param3) {
  (void)param3;

  switch (switchParam) {
  case 0x7d11:
    HandleCase7d11(param2);
    return;

  case 0x7d3b:
    HandleCase7d3b();
    return;

  case 0x7d3c:
    HandleCase7d3c();
    return;
  }
}
