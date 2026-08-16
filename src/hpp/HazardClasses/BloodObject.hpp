#ifndef HAZARD_BLOODOBJECT_HPP
#define HAZARD_BLOODOBJECT_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardTypedef.hpp"

class CoreActClass;

class BloodObject : public GameWindowBase {

public:
  BloodObject(int32_t, int32_t, int32_t);

  virtual void primarySwitchSingleParam(int32_t, intptr_t, intptr_t) override;

  int32_t spriteOrientation;
  int32_t spriteFrameIndex;

  __forceinline void HandleCase7d11(intptr_t param2);
  __forceinline void HandleCase7d3b();
  __forceinline void HandleCase7d3c();
};

#endif
