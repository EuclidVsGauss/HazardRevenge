#include "HazardClasses/GameWindowBase.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ObjectWrapper.hpp"

int32_t __fastcall GameWindowBase::TrackObjects(uint32_t userFlags) {
  GameWindowBase* sceneObject;

  IncrementGradually = (IncrementGradually + 1) & 0x7fff;
  sceneObject = ObjectList[IncrementGradually].sceneClassObjectPointer;
  while (sceneObject != nullptr) {
    IncrementGradually = (IncrementGradually + 1) & 0x7fff;
    sceneObject = ObjectList[IncrementGradually].sceneClassObjectPointer;
  }
  ObjectList[IncrementGradually].sceneClassObjectPointer = this;
  ObjectList[IncrementGradually].scriptUserFlags = userFlags;
  return IncrementGradually;
}
