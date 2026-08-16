#ifndef HAZARD_SCENECLASSBUTTON_HPP
#define HAZARD_SCENECLASSBUTTON_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardTypedef.hpp"

class CoreActClass;

class SceneClassButton : public GameWindowBase {

public:
  SceneClassButton(int32_t coord1, int32_t coord2, int32_t orientation, int32_t gameFlag, char* actFilename);

  virtual void primarySwitchSingleParam(int32_t, intptr_t, intptr_t) override;

  int32_t counter;
  int32_t gameFlag;
  uint32_t openStatus;
  int32_t actSpriteIndex;
  int32_t spriteIndex;
  CoreActClass* fileObject;

private:
  __forceinline void InitializeObject_0x7d11(SceneHandler* sceneHandler);
  __forceinline void TriggerOnClick_0x7d3c();
  __forceinline void DrawSprite_0x7d3b();
};

#endif
