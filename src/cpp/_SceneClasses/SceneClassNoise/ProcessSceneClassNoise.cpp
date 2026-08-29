#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneClassNoise.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardGlobals.hpp"

__forceinline void SceneClassNoise::InitializeObject_0x7d11(intptr_t param2) {
  this->mainSceneHandler = (SceneHandler*)param2;
}

__forceinline void SceneClassNoise::RunTick_0x7d3c() {
  int16_t counter;
  SceneHandler* sceneHandler;
  int32_t randomValue;

  if (counter = this->pseudoRng_mod100, this->pseudoRng_mod100 = counter + 1, 0xa0 < counter) {
    randomValue = PseudoRng();
    if (randomValue % 3 == 0) {
      sceneHandler = this->mainSceneHandler;
      sceneHandler->primarySwitchSingleParam(0x7d0a, this->soundEffectIndex, 0x0);
    }
    this->pseudoRng_mod100 = 0;
  }
}

void SceneClassNoise::primarySwitchSingleParam(int32_t switchParam, intptr_t param2, intptr_t param_3) {
  (void)param_3;

  switch (switchParam) {
  case 0x7d11:
    this->InitializeObject_0x7d11(param2);
    break;

  case 0x7d3c:
    this->RunTick_0x7d3c();
  }
}
