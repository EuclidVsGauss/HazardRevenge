#ifndef HAZARD_SCENECLASSCLOUD_HPP
#define HAZARD_SCENECLASSCLOUD_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardTypedef.hpp"

class CoreActClass;
class large_65736;

class SceneClassCloud : public GameWindowBase {

public:
  SceneClassCloud(char* fileName, char* actName, int32_t startX, int32_t startY, int32_t endX, int32_t endY, int32_t maxFrame);

  virtual ~SceneClassCloud() {}

  virtual void primarySwitchSingleParam(int32_t, intptr_t, intptr_t) override;

  int32_t startGridX;
  int32_t startGridY;
  int32_t targetGridX;
  int32_t targetGridY;
  int32_t actObject;
  int32_t currentFrame;
  int32_t maxFrame;
  CoreActClass* fileObject;
  float toFloat_2;
  float toFloat_1;
  float addToFloat_2;
  float addToFloat_1;

  __forceinline void Case_0x7d11(intptr_t param2);
  __forceinline void Case_0x7d3c();
  __forceinline void Case_0x7d3b();
};

#endif
