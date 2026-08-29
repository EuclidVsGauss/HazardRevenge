#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameOverWindow.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardEnums/SoundEffect.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"
#include "HazardStructs/WindowReference.hpp"

__forceinline void GameOverWindow::InitializeObject_0x7d11(intptr_t param_3) {
  WindowReference windowReference;
  windowReference.coords[0] = 0;
  windowReference.coords[1] = 0;
  windowReference.coords[2] = 640;
  windowReference.coords[3] = 480;
  windowReference.windowAddress = (intptr_t)this;
  this->mainSceneHandler = (SceneHandler*)param_3;
  this->mainSceneHandler->primarySwitchSingleParam(0x7d16, 7, (intptr_t)&windowReference);
  this->mainSceneHandler->primarySwitchSingleParam(0x7d0a, SoundEffect::GameOver, 0);
}

__forceinline void GameOverWindow::RunTick_0x7d3c() {

  int32_t frameCounter = this->runGWC_Counter_Max3839;
  this->runGWC_Counter_Max3839 = frameCounter + 1;
  if (3840 <= frameCounter) {
    this->mainSceneHandler->primarySwitchSingleParam(0x7d1d, 0, 0);
  }
  if (this->runGWC_Counter_Max3839 < 640) {
    return;
  }
  if (this->runGWC_Counter_Max3839 % 0x100 != 0) {
    return;
  }

  this->mainSceneHandler->primarySwitchSingleParam(0x7d21, PseudoRng(), PseudoRng());
}

__forceinline void GameOverWindow::DrawObject_0x7d3b() {
  ImageVectorWithHeader* sprite;

  CoreActClass* actObject = this->wincAct;
  int32_t frame = this->frame;
  sprite = actObject->__InlineGetSolidSpriteFrameForAction(frame, 0);
  GameWindowRightSide->RenderClippedSprite(-85, 152, sprite, -0xffff);
}

void GameOverWindow::primarySwitchSingleParam(int32_t operation, intptr_t windowRef, intptr_t param_3) {

  (void)param_3;

  switch (operation) {
  case 0x7d11: {
    this->InitializeObject_0x7d11(windowRef);
    return;
  }
  case 0x7d3c: {
    this->RunTick_0x7d3c();
    return;
  }
  case 0x7d3b: {
    this->DrawObject_0x7d3b();
    return;
  }
  }
}
