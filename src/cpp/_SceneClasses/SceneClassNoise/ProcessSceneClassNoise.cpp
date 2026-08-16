#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneClassNoise.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardGlobals.hpp"

__forceinline void Case_0x7d11(SceneClassNoise* __this, intptr_t param2) {
  __this->mainSceneHandler = (SceneHandler*)param2;
}

__forceinline void Case_0x7d3c(SceneClassNoise* __this) {
  int16_t counter;
  SceneHandler* sceneHandler;
  int32_t randomValue;

  if (counter = __this->pseudoRng_mod100, __this->pseudoRng_mod100 = counter + 1, 0xa0 < counter) {
    randomValue = PseudoRng();
    if (randomValue % 3 == 0) {
      sceneHandler = __this->mainSceneHandler;
      sceneHandler->primarySwitchSingleParam(0x7d0a, __this->soundEffectIndex, 0x0);
    }
    __this->pseudoRng_mod100 = 0;
  }
}

void SceneClassNoise::primarySwitchSingleParam(int32_t switchParam, intptr_t param2, intptr_t param_3) {
  (void)param_3;

  switch (switchParam) {
  case 0x7d11:
    Case_0x7d11(this, param2);
    break;

  case 0x7d3c:
    Case_0x7d3c(this);
  }
}
