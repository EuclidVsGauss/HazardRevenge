#ifndef HAZARD_SCENEINSTANCE_HPP
#define HAZARD_SCENEINSTANCE_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardTypedef.hpp"

class SceneInstance : public SceneHandler {

public:
  SceneInstance(char*);
  virtual ~SceneInstance();
  virtual void primarySwitchSingleParam(int32_t, intptr_t, intptr_t) override;

  void ParseSceneTxt();

  int32_t sceneInstanceIndex_10to14;
  int32_t sceneLinesCurrentlyParsed;
  int32_t sceneLinesToBeParsed;
  GameWindowBase* latestUnitToMoveToNewScene;
  char sceneName[24];
  SceneHandler* large65736;

  __forceinline void Case_0x7d11(intptr_t param_1);
  __forceinline void Case_0x7d3c();
  __forceinline void Case_0x7d07(int32_t switchParam, intptr_t param_1, intptr_t param_2);
  __forceinline void Case_0x7d1a(int32_t switchParam, intptr_t param_1, intptr_t param_2);
  __forceinline void Case_0x7d2b(int32_t switchParam, intptr_t param_1, intptr_t param_2);
  __forceinline void Case_0x7d27(int32_t switchParam, intptr_t param_1, intptr_t param_2);
};

#endif
