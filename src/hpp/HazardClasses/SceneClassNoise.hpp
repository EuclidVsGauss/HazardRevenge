#ifndef HAZARD_SCENECLASSNOISE_HPP
#define HAZARD_SCENECLASSNOISE_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardTypedef.hpp"

class SceneClassNoise : public GameWindowBase {

public:
  SceneClassNoise(int16_t);

  virtual void primarySwitchSingleParam(int32_t, intptr_t, intptr_t) override;

  int16_t pseudoRng_mod100;
  int16_t soundEffectIndex;
};

#endif
