#ifndef HAZARD_SCENECLASSRECT_HPP
#define HAZARD_SCENECLASSRECT_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardTypedef.hpp"

class SceneClassRect : public GameWindowBase {

public:
  SceneClassRect(int32_t lowerX, int32_t lowerY, int32_t upperX, int32_t upperY, int32_t dialogueIndex, int32_t flagIndex);
  virtual ~SceneClassRect();
  virtual void primarySwitchSingleParam(int32_t, intptr_t, intptr_t) override;

  int32_t lowerX;
  int32_t lowerY;
  int32_t rectangleWidth;
  int32_t rectangleHeight;
  int32_t gameflagIndex;
  int32_t dialogueIndex;
  int32_t isTriggered;

private:
  __forceinline void InitializeObject_0x7d11(SceneHandler* sceneHandler);
  __forceinline void Trigger_0x7d3c();
};

#endif
