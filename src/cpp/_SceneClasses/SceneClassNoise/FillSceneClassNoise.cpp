#include <HazardFunctions.hpp>
#include "HazardClasses/SceneClassNoise.hpp"
#include "HazardGlobals.hpp"

SceneClassNoise::SceneClassNoise(int16_t param_1) {
  this->pseudoRng_mod100 = PseudoRng() % 100;
  this->soundEffectIndex = param_1;
}
