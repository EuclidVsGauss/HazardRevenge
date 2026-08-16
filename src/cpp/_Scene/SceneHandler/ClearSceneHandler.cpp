#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardGlobals.hpp"

SceneHandler::~SceneHandler() {
  GameWindowBase* currentWindow;
  int32_t windowIndex;

  windowIndex = 0;
  if (0 < this->gameWindowsCounter) {
    do {
      currentWindow = this->gameWindowsArray[windowIndex];
      if (currentWindow != nullptr) {
        delete currentWindow;
      }
      windowIndex = windowIndex + 1;
    } while (windowIndex < this->gameWindowsCounter);
  }

  delete[] this->gameWindowsArray;

  if (this->mainSceneHandler != nullptr) {

    delete[] this->selectedUnits32;
  }
}
