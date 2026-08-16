#ifndef HAZARD_SCENECLASSMOVETILE_HPP
#define HAZARD_SCENECLASSMOVETILE_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardTypedef.hpp"

class CoreActClass;

class SceneClassMoveTile : public GameWindowBase {

public:
  SceneClassMoveTile(char* param_1, int32_t param_2, int32_t param_3, int32_t param_4, int32_t param_5, int32_t param_6, int32_t param_7, int32_t param_8);

  virtual void primarySwitchSingleParam(int32_t, intptr_t, intptr_t) override;

  int32_t counter;
  int32_t unused1;
  int32_t switchParameter;
  int32_t StandFrameObject;
  int32_t unused2;
  int32_t tmpCoord1;
  int32_t tmpCoord2;
  int32_t coord1Related;
  int32_t coord2Related;
  int32_t gameFlagPartialTrigger1;
  int32_t gameFlagPartialTrigger2;
  int32_t gameFlagFullTrigger;
  int32_t moveTileCoord1;
  int32_t moveTileCoord2;
  CoreActClass* actObject;

  __forceinline void Case_0x7d11(intptr_t param2);
  __forceinline void Case_0x7d3b();
  __forceinline void Case_0x7d3c();
};

#endif
