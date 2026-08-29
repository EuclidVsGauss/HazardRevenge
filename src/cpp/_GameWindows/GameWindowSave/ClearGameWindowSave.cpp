#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowSave.hpp"

GameWindowSave::~GameWindowSave() {
  CoreActClass* actObject;

  actObject = this->actWin9;
  if (actObject != nullptr) {
    delete actObject;
  }
}
