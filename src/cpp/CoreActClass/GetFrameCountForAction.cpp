#include "HazardClasses/CoreActClass.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActContent.hpp"

int32_t CoreActClass::GetFrameCountForAction(int32_t actionId) {
  if (actionId == -1) {
    return 1;
  }
  return this->txtContent[actionId].numberFrames;
}
