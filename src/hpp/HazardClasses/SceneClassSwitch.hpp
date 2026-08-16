#ifndef HAZARD_SCENECLASSSWITCH_HPP
#define HAZARD_SCENECLASSSWITCH_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardTypedef.hpp"

class CoreActClass;

class SceneClassSwitch : public GameWindowBase {

public:
  SceneClassSwitch(int32_t coord1, int32_t coord2, int32_t directionIndex, int32_t gameFlagIndex, char* actFile, int32_t isPermanent);
  virtual ~SceneClassSwitch();
  virtual void primarySwitchSingleParam(int32_t, intptr_t, intptr_t) override;

  int32_t currentFrame;
  int32_t gameFlagIndex;
  uint32_t currentState;
  int32_t actionIndex;
  int32_t directionIndex;
  int32_t isPermanent;
  CoreActClass* actObject;

  __forceinline void Case_0x7d11(intptr_t param2);
  __forceinline void Case_0x7d3b();
  __forceinline void Case_0x7d3c();
  __forceinline void Case_0x7d04();
};

#endif
