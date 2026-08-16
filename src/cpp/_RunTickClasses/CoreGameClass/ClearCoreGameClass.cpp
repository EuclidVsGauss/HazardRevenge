#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/CoreGameClass.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/MusicObject.hpp"
#include "HazardGlobals.hpp"

CoreGameClass::~CoreGameClass() {
  CoreActClass* actObject;

  PtrMusicObject->ReleaseMusicBuffer();
  actObject = this->actWin8;
  if (actObject != nullptr) {
    delete actObject;
  }
  actObject = this->actCursor;
  if (actObject != nullptr) {
    delete actObject;
  }
  if (GameWindowRightSide != nullptr) {
    delete GameWindowRightSide;
  }
  if (GameWindowLeftSidebar != nullptr) {
    delete GameWindowLeftSidebar;
  }
  PixelCalculations_DirectDrawSurface(16, 0);
}
