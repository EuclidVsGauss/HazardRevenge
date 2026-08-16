#include "HazardClasses/SceneClassGate.hpp"
#include "HazardGlobals.hpp"
#include "HazardInlineFunctions.hpp"

SceneClassGate::SceneClassGate(int32_t gateCorner1, int32_t gateCorner2, int32_t gateCorner3, int32_t gateCorner4, char* targetSceneName, int32_t targetCoord1, int32_t targetCoord2) {

  gateCoord1 = gateCorner1;
  gateCoord2 = gateCorner2;
  gateHeightOrWidth = gateCorner3 - gateCorner1 + 1;
  gateWidthOrHeight = gateCorner4 - gateCorner2 + 1;
  newSceneCoord1 = targetCoord1;
  newSceneCoord2 = targetCoord2;

  __InlineCopyString(newSceneName, targetSceneName);
}
