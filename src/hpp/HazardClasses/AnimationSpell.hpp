#ifndef HAZARD_ANIMATIONSPELL_HPP
#define HAZARD_ANIMATIONSPELL_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardTypedef.hpp"

class CoreActClass;

class AnimationSpell : public GameWindowBase {

public:
  AnimationSpell(char*, int32_t, int32_t);

  virtual void primarySwitchSingleParam(int32_t, intptr_t, intptr_t) override;

  int32_t stand;
  int32_t numberOfFramesForStandAnimation;
  int32_t presumablyCurrentAnimationIndex;
  CoreActClass* actWithSfx;

  __forceinline void InitializeObject_0x7d11(intptr_t param_2);
  __forceinline void DrawObject_0x7d3b();
  __forceinline void RunTick_0x7d3c();
};

#endif
