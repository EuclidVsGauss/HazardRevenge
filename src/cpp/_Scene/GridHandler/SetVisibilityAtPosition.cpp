#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardGlobals.hpp"

void GridHandler::SetVisibilityAtPosition(int32_t param_1, int32_t param_2, int32_t param_3) {
  byte visibilityDelta = (param_3 != 0) ? 1 : -1;
  this->PaddedGridMap_Visibility[param_2][param_1] = this->PaddedGridMap_Visibility[param_2][param_1] + visibilityDelta;
}
