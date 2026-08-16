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
};

#endif
