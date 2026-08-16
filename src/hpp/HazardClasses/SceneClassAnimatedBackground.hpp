#ifndef HAZARD_SCENECLASSANIMATEDBACKGROUND_HPP
#define HAZARD_SCENECLASSANIMATEDBACKGROUND_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardTypedef.hpp"

class CoreActClass;

class SceneClassAnimatedBackground : public GameWindowBase {

public:
  SceneClassAnimatedBackground(char* actFilename, char* actioName, int32_t coord1, int32_t coord2, int32_t layerOffset);

  virtual ~SceneClassAnimatedBackground() {}

  virtual void primarySwitchSingleParam(int32_t, intptr_t, intptr_t) override;

  int32_t coord2WithLayerOffset;
  int32_t actionIndex;
  int32_t truncatedRng;
  CoreActClass* actObject;
};

#endif
