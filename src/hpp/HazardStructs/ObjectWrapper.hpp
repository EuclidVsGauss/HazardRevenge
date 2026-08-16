#ifndef HAZARD_HELPERAC85A_HPP
#define HAZARD_HELPERAC85A_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardTypedef.hpp"

struct ObjectWrapper {
  uint32_t scriptUserFlags;
  GameWindowBase* sceneClassObjectPointer;
};
typedef struct ObjectWrapper ObjectWrapper, *PObjectWrapper;

#endif
