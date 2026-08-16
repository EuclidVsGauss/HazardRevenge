#ifndef HAZARD_SCENECLASSBOX_HPP
#define HAZARD_SCENECLASSBOX_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardTypedef.hpp"

class CoreActClass;

class SceneClassBox : public GameWindowBase {

public:
  SceneClassBox(int32_t coord1, int32_t coord2, int32_t gameFlag, int32_t standAnimationIndex, char* actFilename);

  virtual void primarySwitchSingleParam(int32_t, intptr_t, intptr_t) override;

  int32_t counter;
  int32_t gameFlag;
  uint32_t openStatus;
  int32_t actionIndex;
  int32_t chestDirectionIndex;
  CoreActClass* fileObject;

  __forceinline void Case_0x7d11(intptr_t param2);
  __forceinline void Case_0x7d3b();
  __forceinline void Case_0x7d3c();
  __forceinline void Case_0x7d04(intptr_t param2);
};

#endif
