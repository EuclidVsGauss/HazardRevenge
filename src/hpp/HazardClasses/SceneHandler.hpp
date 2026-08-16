#ifndef HAZARD_SCENEHANDLER_HPP
#define HAZARD_SCENEHANDLER_HPP

#include "HazardClasses/EventHandler.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardEnums/MapType.hpp"
#include "HazardTypedef.hpp"

class SceneClassCameraBase;
class SceneClassCommand;

class SceneHandler : public EventHandler, public GridHandler, public GameWindowBase {

public:
  SceneHandler();
  virtual ~SceneHandler();
  virtual void primarySwitchSingleParam(int32_t, intptr_t, intptr_t) override;

  int32_t StoreAndInitializeObject(GameWindowBase*);

  int32_t mapWidth;
  int32_t mapHeight;
  int32_t isViewportEnabled;
  int32_t isMagicEnabled;
  MapTypeEnum mapType;
  SceneClassCameraBase* sceneCamera;
  GameWindowBase* matrix_128x128[128][128];
  GameWindowBase* currentObject;
  GameWindowBase** selectedUnits32;
  char sceneName[20];
  GameWindowBase** gameWindowsArray;
  int32_t gameWindowsCounter;
  SceneClassCommand* sceneClassCommand;
  int32_t sceneMusicIndex;

  __forceinline void Case_0x7d11(intptr_t param_1);
  __forceinline void Case_0x7d3b();
  __forceinline void Case_0x7d3c(intptr_t param_1);
  __forceinline void Case_0x7d0e(int32_t switchConstant, intptr_t param_1, intptr_t param_2);
  __forceinline void Case_0x7d2b(intptr_t param_1);
  __forceinline void Case_0x7d2c(intptr_t param_1);
  __forceinline void Case_0x7d08_0x7d17_0x7d18_0x7d25_0x7d35_0x7d37_0x7d39(int32_t switchConstant, intptr_t param_1, intptr_t param_2);
  __forceinline void Case_0x7d21(intptr_t param_1, intptr_t param_2);
  __forceinline void Case_0x7d26();
  __forceinline void Case_0x7d07(intptr_t param_1);
  __forceinline void Case_0x7d1a(intptr_t param_1);
  __forceinline void Case_0x7d29(intptr_t param_1, intptr_t param_2);
  __forceinline void Case_0x7d0f(intptr_t param_1, intptr_t param_2);
  __forceinline void Case_0x7d10(intptr_t param1);
  __forceinline void Case_0x7d0a(intptr_t param_1, intptr_t param_2);
  __forceinline void Case_0x7d0d();
  __forceinline void Case_0x7d27(intptr_t param_1);
  __forceinline void Case_0x7d0c(intptr_t param_1);
};

#endif
