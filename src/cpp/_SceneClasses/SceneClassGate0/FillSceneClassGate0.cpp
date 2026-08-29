#include "HazardClasses/SceneClassGate0.hpp"
#include "HazardGlobals.hpp"
#include "HazardInlineFunctions.hpp"

SceneClassGate0::SceneClassGate0(int32_t x1, int32_t y1, int32_t x2, int32_t y2, char* sceneName, int32_t newX, int32_t newY) {

  gateCoord1 = x1;
  gateCoord2 = y1;
  gateHeightOrWidth = x2 - x1 + 1;
  gateWidthOrHeight = y2 - y1 + 1;
  newSceneCoord1 = newX;
  newSceneCoord2 = newY;

  __InlineCopyString(newSceneName, sceneName);
}
