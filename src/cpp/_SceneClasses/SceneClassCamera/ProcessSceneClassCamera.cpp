#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneClassCamera.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardGlobals.hpp"

__forceinline void SceneClassCamera::Case_0x7d11(intptr_t param_2) {
  this->mainSceneHandler = (SceneHandler*)param_2;
  this->mainSceneHandler->primarySwitchSingleParam(0x7d0f, (intptr_t)(GameWindowBase*)this, 0x1);
  this->mainSceneHandler->primarySwitchSingleParam_0x7d29(0x2, this);
}

__forceinline void SceneClassCamera::Case_0x7d3c() {
  int32_t cameraXOffset;
  int32_t cameraYOffset;
  int32_t xStep;
  int32_t yStep;

  cameraXOffset = this->cameraCoordX;
  if ((this->cameraOffsetX != cameraXOffset) || (this->cameraOffsetY != this->cameraCoordY)) {
    cameraYOffset = this->cameraOffsetX - cameraXOffset;
    yStep = cameraYOffset;
    if (cameraYOffset < 0) {
      yStep = -cameraYOffset;
    }
    yStep = (yStep / 10) + 1;
    if (0x10 <= yStep) {
      yStep = 0x10;
    }
    if (cameraYOffset <= yStep) {
      yStep = cameraYOffset;
    }
    if (cameraYOffset < 0) {
      cameraYOffset = -cameraYOffset;
    }
    cameraYOffset = (cameraYOffset / 10) + 1;
    if (0x10 <= cameraYOffset) {
      cameraYOffset = 0x10;
    }
    xStep = -cameraYOffset;
    if (-cameraYOffset < yStep) {
      xStep = yStep;
    }
    this->cameraCoordX = cameraXOffset + xStep;
    yStep = this->cameraOffsetY - this->cameraCoordY;
    cameraXOffset = yStep;
    if (yStep < 0) {
      cameraXOffset = -yStep;
    }
    cameraXOffset = (cameraXOffset / 10) + 1;
    if (0x10 <= cameraXOffset) {
      cameraXOffset = 0x10;
    }
    if (yStep <= cameraXOffset) {
      cameraXOffset = yStep;
    }
    if (yStep < 0) {
      yStep = -yStep;
    }
    yStep = (yStep / 10) + 1;
    if (0x10 <= yStep) {
      yStep = 0x10;
    }
    xStep = -yStep;
    if (-yStep < cameraXOffset) {
      xStep = cameraXOffset;
    }
    this->cameraCoordY = this->cameraCoordY + xStep;
    return;
  }
}

__forceinline void SceneClassCamera::Case_0x7d00(int32_t param2AsInt, int32_t param3AsInt) {
  SceneHandler* mainSceneHandlerCopy;
  int32_t xClamped;
  int32_t yClamped;

  mainSceneHandlerCopy = this->mainSceneHandler;
  xClamped = this->cameraOffsetX + param2AsInt;
  yClamped = mainSceneHandlerCopy->mapWidth + -0x1ff;
  if (xClamped <= yClamped) {
    yClamped = xClamped;
  }
  if (yClamped <= 0x10) {
    yClamped = 0x10;
  }
  this->cameraOffsetX = yClamped;
  yClamped = mainSceneHandlerCopy->mapHeight + -0x1f0;
  xClamped = this->cameraOffsetY + param3AsInt;
  if (xClamped <= yClamped) {
    yClamped = xClamped;
  }
  if (yClamped <= 0x10) {
    yClamped = 0x10;
  }
  this->cameraOffsetY = yClamped;
}

__forceinline void SceneClassCamera::Case_0x7d21(int32_t param2AsInt, int32_t param3AsInt) {
  SceneHandler* mainSceneHandlerCopy;
  int32_t xClamped;
  int32_t yClamped;

  mainSceneHandlerCopy = this->mainSceneHandler;
  xClamped = (mainSceneHandlerCopy->mapWidth + -0x1ff);
  if (param2AsInt + -0xf7 <= xClamped) {
    xClamped = param2AsInt + -0xf7;
  }
  if (xClamped <= 0x10) {
    xClamped = 0x10;
  }
  this->cameraOffsetX = xClamped;
  yClamped = mainSceneHandlerCopy->mapHeight + -0x1f0;
  if (param3AsInt + -0xf0 <= yClamped) {
    yClamped = param3AsInt + -0xf0;
  }
  if (yClamped <= 0x10) {
    yClamped = 0x10;
  }
  this->cameraOffsetY = yClamped;
  if (this->status == 0) {
    this->cameraCoordX = xClamped;
    this->cameraCoordY = yClamped;
    this->status = 1;
  }
}

void SceneClassCamera::primarySwitchSingleParam(int32_t switchParam, intptr_t param_2, intptr_t param_3) {
  switch (switchParam) {
  case 0x7d11:
    Case_0x7d11(param_2);
    return;

  case 0x7d3c:
    Case_0x7d3c();
    break;

  case 0x7d00:
    Case_0x7d00(param_2, param_3);
    return;

  case 0x7d21:
    Case_0x7d21(param_2, param_3);
    break;
  }
}
