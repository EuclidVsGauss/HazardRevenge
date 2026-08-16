#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameOverWindow.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardEnums/SoundEffect.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"
#include "HazardStructs/WindowReference.hpp"

__forceinline void Case_0x7d11(GameOverWindow* _this, intptr_t windowRef) {
  WindowReference windowReference;
  windowReference.coords[0] = 0;
  windowReference.coords[1] = 0;
  windowReference.coords[2] = 640;
  windowReference.coords[3] = 480;
  _this->mainSceneHandler = (SceneHandler*)windowRef;
  windowReference.windowAddress = (intptr_t)_this;
  _this->mainSceneHandler->primarySwitchSingleParam(0x7d16, 7, (intptr_t)&windowReference);
  _this->mainSceneHandler->primarySwitchSingleParam(0x7d0a, SoundEffect::GameOver, 0);
}

__forceinline void Case_0x7d3c(GameOverWindow* _this) {

  int32_t frameCounter = _this->runGWC_Counter_Max3839;
  _this->runGWC_Counter_Max3839 = frameCounter + 1;
  if (3840 <= frameCounter) {
    _this->mainSceneHandler->primarySwitchSingleParam(0x7d1d, 0, 0);
  }
  if (_this->runGWC_Counter_Max3839 < 640) {
    return;
  }
  if ((_this->runGWC_Counter_Max3839 & 0x800000ff) != 0) {
    return;
  }

  SceneHandler* handler = _this->mainSceneHandler;

  int32_t randomX = PseudoRng();
  int32_t randomY = PseudoRng();

  handler->primarySwitchSingleParam(0x7d21, randomY, randomX);
}

__forceinline void Case_0x7d3b(GameOverWindow* _this) {

  ImageVectorWithHeader* sprite;

  sprite = GameOverWindow::__InlineGetSolidSpriteFrameForAction(_this->frame, _this->wincAct, 0);

  int32_t posX = -85;
  int32_t posY = 152;
  int32_t layer = -0xffff;

  GameWindowRightSide->RenderClippedSprite(posX, posY, sprite, layer);
}

void GameOverWindow::primarySwitchSingleParam(int32_t operation, intptr_t windowRef, intptr_t param_3) {

  (void)param_3;

  switch (operation) {
  case 0x7d11: {
    Case_0x7d11(this, windowRef);
    return;
  }
  case 0x7d3c: {
    Case_0x7d3c(this);
    return;
  }
  case 0x7d3b: {
    Case_0x7d3b(this);
    return;
  }
  }
}
