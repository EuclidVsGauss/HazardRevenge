#ifndef HAZARD_ANIMATIONSUMMON_HPP
#define HAZARD_ANIMATIONSUMMON_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardTypedef.hpp"

class CoreActClass;

class AnimationSummon : public GameWindowBase {

public:
  AnimationSummon(char*);
  virtual void primarySwitchSingleParam(int32_t, intptr_t, intptr_t) override;

  int32_t firstStandActIndex;
  int32_t unused;
  int32_t maxStandActIndex;
  int32_t currentStandIndex;
  CoreActClass* coreActClass;

  __forceinline void Case_0x7d11(intptr_t param_2);
  __forceinline void Case_0x7d3b();
  __forceinline void Case_0x7d3c();
};

#endif
