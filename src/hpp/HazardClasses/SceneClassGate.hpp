#ifndef HAZARD_SCENECLASSGATE_HPP
#define HAZARD_SCENECLASSGATE_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardTypedef.hpp"

class SceneClassGate : public GameWindowBase {

public:
  SceneClassGate(int32_t param_1, int32_t param_2, int32_t param_3, int32_t param_4, char* param_5, int32_t param_6, int32_t param_7);
  virtual ~SceneClassGate();
  virtual void primarySwitchSingleParam(int32_t, intptr_t, intptr_t) override;

  char newSceneName[20];
  int32_t gateCoord1;
  int32_t gateCoord2;
  int32_t gateHeightOrWidth;
  int32_t gateWidthOrHeight;
  int32_t newSceneCoord1;
  int32_t newSceneCoord2;
};

#endif
