#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/SceneClassButton.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardExterns/SceneClassButton.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActContent.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

__forceinline void SceneClassButton::InitializeObject_0x7d11(SceneHandler* sceneHandler) {
  this->mainSceneHandler = sceneHandler;
  this->mainSceneHandler->primarySwitchSingleParam(0x7d0f, (intptr_t)(GameWindowBase*)this, 0x0);
}

__forceinline void SceneClassButton::TriggerOnClick_0x7d3c() {
  CoreActClass* actObject;
  int32_t value;
  int32_t row;
  int32_t col;
  int32_t tmp;

  switch (this->openStatus) {
  case 0:
    this->counter = this->counter + 1;
    for (row = 0; row < 2; row++) {
      for (col = 0; col < 2; col++) {
        tmp = this->mainSceneHandler->PaddedGridMap_Collision[this->matrixIndexYTimes16 + row][this->matrixIndexXTimes16 + col];
        if ((0 <= tmp) && (tmp != -1)) {
          row = this->fileObject->GetActionIndexByName(Button0_s_fopen[this->spriteIndex]);
          actObject = this->fileObject;
          this->actSpriteIndex = row;
          this->openStatus = 1;
          this->counter = 0;
          row = actObject->GetActionIndexByName(s__sfx);
          if (row == -1) {
            row = 0;
          }
          else {
            row = *actObject->txtContent[row].ptrFrameStart;
          }
          this->mainSceneHandler->primarySwitchSingleParam_PlaySoundEffect_0x7d0a(row, this);
          if (this->gameFlag != 0) {
            GameFlags[this->gameFlag] = 1;
            return;
          }
          return;
        }
      }
    }
    return;
  case 1:
    row = this->counter;
    col = this->fileObject->GetFrameCountForAction(this->actSpriteIndex);
    this->counter = row + 1;
    if (row >= col - 1) {
      this->actSpriteIndex = this->fileObject->GetActionIndexByName(Button1_s_fopened[this->spriteIndex]);
      this->openStatus = 2;
      this->counter = 0;
      return;
    }
    return;

  case 2:
    for (row = 0; row < 2; row++) {
      for (col = 0; col < 2; col++) {
        value = this->mainSceneHandler->PaddedGridMap_Collision[this->matrixIndexYTimes16 + row][this->matrixIndexXTimes16 + col];
        if ((0 <= value) && (value != -1)) {
          return;
        }
      }
    }
    row = this->fileObject->GetActionIndexByName(Button2_s_fopen[this->spriteIndex]);
    this->actSpriteIndex = row;
    this->openStatus = 3;
    row = this->fileObject->GetFrameCountForAction(row);
    actObject = this->fileObject;
    this->counter = row + -1;
    row = actObject->GetActionIndexByName(s__sfx);
    if (row == -1) {
      row = 0;
    }
    else {
      row = actObject->txtContent[row].ptrFrameStart[1];
    }
    this->mainSceneHandler->primarySwitchSingleParam_PlaySoundEffect_0x7d0a(row, this);
    if (this->gameFlag != 0) {
      GameFlags[this->gameFlag] = 0;
      return;
    }
    return;

  case 3:
    this->counter--;
    if (this->counter <= 0) {
      this->actSpriteIndex = this->fileObject->GetActionIndexByName(Button3_s_fstand[this->spriteIndex]);
      this->openStatus = 0;
      this->counter = 0;
      return;
    }
    return;

  default:
    return;
  }
}

__forceinline void SceneClassButton::DrawSprite_0x7d3b() {
  ActContent* content;
  CoreActClass* actObject;
  ImageVectorWithHeader* solidSprite;
  ImageVectorWithHeader* shadowSprite;
  int32_t actionIndex;
  int32_t spriteX;
  int32_t spriteY;
  uint16_t cnt;

  actionIndex = this->actSpriteIndex;
  actObject = this->fileObject;
  content = actObject->txtContent;
  spriteX = (this->matrixIndexXTimes16 + 1) * 0x10;
  spriteY = (this->matrixIndexYTimes16 + 1) * 0x10;

  if (actionIndex >= 0 && content[actionIndex].numberFrames > 0) {
    cnt = this->counter;

    solidSprite = this->fileObject->solidSpriteMap[content[actionIndex].ptrFrameStart[cnt % content[actionIndex].numberFrames]];
  }
  else {
    solidSprite = nullptr;
  }

  this->mainSceneHandler->sceneCamera->DrawSprite(spriteX, spriteY, solidSprite, spriteY);
  actionIndex = this->actSpriteIndex;
  if (actionIndex >= 0 && this->fileObject->txtContent[actionIndex].numberFrames > 0) {
    cnt = this->counter;

    shadowSprite = this->fileObject->shadowSpriteMap[this->fileObject->txtContent[actionIndex].ptrFrameStart[cnt % this->fileObject->txtContent[actionIndex].numberFrames]];
  }
  else {
    shadowSprite = nullptr;
  }
  this->mainSceneHandler->sceneCamera->DrawSprite(spriteX, spriteY, shadowSprite, -spriteY);
}

void SceneClassButton::primarySwitchSingleParam(int32_t switchParameter, intptr_t param2, intptr_t param3) {

  (void)param3;

  switch (switchParameter) {
  case 0x7d11:
    InitializeObject_0x7d11((SceneHandler*)param2);
    return;

  case 0x7d3b:
    DrawSprite_0x7d3b();
    return;

  case 0x7d3c:
    TriggerOnClick_0x7d3c();
    return;

  default:
    return;
  }
}
