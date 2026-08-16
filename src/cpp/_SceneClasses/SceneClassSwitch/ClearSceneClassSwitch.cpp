#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/SceneClassSwitch.hpp"

SceneClassSwitch::~SceneClassSwitch() {
  CoreActClass* actObject;

  actObject = this->actObject;
  if (actObject != nullptr) {
    delete actObject;
  }
}
