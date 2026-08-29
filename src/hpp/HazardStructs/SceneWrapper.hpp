#ifndef HAZARD_AC7HELPERNEW_HPP
#define HAZARD_AC7HELPERNEW_HPP

#include "HazardTypedef.hpp"
class SceneHandler;

struct SceneWrapper {
  char sceneName[24];
  SceneHandler* sceneInstance;
};
typedef struct SceneWrapper SceneWrapper, *PSceneWrapper;

#endif
