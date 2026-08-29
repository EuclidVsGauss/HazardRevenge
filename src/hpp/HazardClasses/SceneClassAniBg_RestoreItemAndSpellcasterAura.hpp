#ifndef HAZARD_SCENECLASSANIBG_RESTOREITEMANDSPELLCASTERAURA_HPP
#define HAZARD_SCENECLASSANIBG_RESTOREITEMANDSPELLCASTERAURA_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardTypedef.hpp"

class CoreActClass;

class SceneClassAniBg_RestoreItemAndSpellcasterAura : public GameWindowBase {

public:
  virtual void primarySwitchSingleParam(int32_t, intptr_t, intptr_t) override;

  SceneClassAniBg_RestoreItemAndSpellcasterAura(char* actName, int32_t positionX, int32_t positionY);

  int32_t actOffsetStand;
  int32_t frame_or_actValueStand;
  int32_t truncatedRng;
  CoreActClass* actObject;

  __forceinline void InitializeObject_0x7d11(intptr_t param2);
  __forceinline void DrawObject_0x7d3b();
  __forceinline void RunTick_0x7d3c();
};

#endif
