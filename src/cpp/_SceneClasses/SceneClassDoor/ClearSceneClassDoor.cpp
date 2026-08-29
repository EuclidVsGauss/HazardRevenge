#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/SceneClassDoor.hpp"

SceneClassDoor::~SceneClassDoor() {
  CoreActClass* actPtr;

  actPtr = this->actClass;
  if (actPtr != nullptr) {
    delete actPtr;
  }
}
