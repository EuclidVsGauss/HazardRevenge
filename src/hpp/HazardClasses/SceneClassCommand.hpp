#ifndef HAZARD_SCENECLASSCOMMAND_HPP
#define HAZARD_SCENECLASSCOMMAND_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardTypedef.hpp"

class SceneClassCommand : public GameWindowBase {

public:
  SceneClassCommand();
  virtual void primarySwitchSingleParam(int32_t, intptr_t, intptr_t) override;

  int32_t initMinus1;
  int32_t unused;
  int32_t initialDragCoordX;
  int32_t initialDragCoordY;
  int32_t currentDragCoordX;
  int32_t currentDragCoordY;
  int32_t flag;

  __forceinline void Case_0x7d11(intptr_t param_2);
  __forceinline void DrawSelectionRectangle_0x7d3b();
  __forceinline void Case_0x7d0e(intptr_t param_2);
};

#endif
