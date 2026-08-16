#ifndef HAZARD_ANIMATIONSTATUSSPELL_HPP
#define HAZARD_ANIMATIONSTATUSSPELL_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardTypedef.hpp"

class CoreActClass;

class AnimationStatusSpell : public GameWindowBase {

public:
  AnimationStatusSpell(char*, int32_t, int32_t, int32_t);
  virtual void primarySwitchSingleParam(int32_t, intptr_t, intptr_t) override;

  int32_t actionIndex;
  int32_t repeatCounter;
  int32_t actionFrameCount;
  int32_t currentFrameIndex;
  CoreActClass* coreActClass;

  __forceinline void Case_0x7d11(intptr_t param_2);
  __forceinline void Case_0x7d3b();
  __forceinline void Case_0x7d3c();
};

#endif
