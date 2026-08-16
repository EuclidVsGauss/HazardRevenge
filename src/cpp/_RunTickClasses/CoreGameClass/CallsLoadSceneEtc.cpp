#include "HazardClasses/CoreGameClass.hpp"
#include "HazardClasses/EventHandler.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/MusicObject.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardExterns/CoreGameClass.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/QueueEventContainer.hpp"
#include "HazardStructs/WindowReference.hpp"

void CoreGameClass::CallsLoadSceneEtc() {
  GameWindowBase** gameWindowsPtr;
  GameWindowBase* currentWindow;
  float deltaTime;
  int32_t isActiveWindow;
  SceneHandler* sceneHandlerTemp;
  int32_t currentEvent;
  int32_t windowIndex;
  WindowReference* windowRefPtr;
  intptr_t windowAddress;

  deltaTime = this->float_600000 - (Fixed1000 / (float)TimeResolution_45or15);
  this->float_600000 = deltaTime;
  if (deltaTime <= Fixed0) {
    currentEvent = this->currentMusicIndex;
    if (currentEvent == 0) {
      PtrMusicObject->ReleaseMusicBuffer();
      this->float_600000 = 600000.0;
    }
    else {
      (PtrMusicObject->LoadAndPlayNewTrack)(currentEvent + 1);
      currentEvent = (PtrMusicObject->CalculateTotalSamples)(this->currentMusicIndex + 1);
      this->float_600000 = (float)(currentEvent + 0x14) * Fixed1000;
    }
  }

  this->callSceneCounter = this->callSceneCounter + 1;
  if ((MouseButtonClick & 0x33) == 0) {
    FlagCursorRelated = -1;
  }

  while (true) {
    if (this->eventCounter > 0) {
      this->eventCounter--;
      currentEvent = this->queuedEventsArray[this->eventCounter >> 8]->queueEvents[this->eventCounter & 0xff];
    }
    else {
      currentEvent = 0;
    }

    switch (currentEvent) {
    case 0: {
      goto label_exit;
    }
    case 0x7d00: {
      if (this->eventCounter > 0) {
        this->eventCounter--;
        currentEvent = this->queuedEventsArray[this->eventCounter >> 8]->queueEvents[this->eventCounter & 0xff];
      }
      else {
        currentEvent = 0;
      }

      if (this->initializedGW0s[0].windowAddress == currentEvent) {
        this->initializedGW0s[0].windowAddress = -1;
      }
      currentWindow = this->gameWindowsArray[currentEvent];
      if (currentWindow != nullptr) {
        delete currentWindow;
      }
      break;
    }
    case 0x7d01:
      if (this->eventCounter > 0) {
        this->eventCounter--;
        currentEvent = this->queuedEventsArray[this->eventCounter >> 8]->queueEvents[this->eventCounter & 0xff];
      }
      else {
        currentEvent = 0;
      }
      gameWindowsPtr = this->gameWindowsArray;
      if (gameWindowsPtr[currentEvent] != nullptr) {
        windowIndex = this->initializedGW0s[0].windowAddress;
        if (((windowIndex != -1) && (windowIndex != currentEvent)) && (currentWindow = gameWindowsPtr[windowIndex], currentWindow != nullptr)) {
          currentWindow->primarySwitchSingleParam(0x7d0d, 0x0, 0x0);
        }
        windowIndex = this->initializedGW0s[1].windowAddress;
        this->initializedGW0s[0].windowAddress = currentEvent;
        if (windowIndex != -1) {
          gameWindowsPtr = this->gameWindowsArray;
          currentWindow = gameWindowsPtr[currentEvent];
          if (currentWindow != nullptr) {
            sceneHandlerTemp = static_cast<SceneHandler*>(currentWindow);
          }
          else {
            sceneHandlerTemp = nullptr;
          }
          currentWindow = gameWindowsPtr[windowIndex];
          currentWindow->primarySwitchSingleParam(0x7d07, (intptr_t)sceneHandlerTemp, 0x0);
        }
      }
      break;
    }
  }
label_exit:

  if ((this->initializedGW0s[6].windowAddress == -1) &&
      (this->initializedGW0s[0].windowAddress != -1) &&
      (this->initializedGW0s[5].windowAddress == -1)) {
    isActiveWindow = 1;
  }
  else {
    isActiveWindow = 0;
  }

  this->primarySwitchSingleParam(0x7d35, 0, 0x1);
  this->primarySwitchSingleParam(0x7d35, 0, 0x2);
  windowIndex = 9;
  windowRefPtr = this->initializedGW0s + 9;
  int32_t currentCursorWindow = FlagCursorRelated;
  do {
    if ((windowRefPtr->windowAddress != -1) && (currentWindow = this->gameWindowsArray[windowRefPtr->windowAddress], currentWindow != nullptr)) {
      if (
          ((
               (
                   ((currentCursorWindow == -1) &&
                    (windowRefPtr->coords[0] <= CursorXCoord &&
                     CursorXCoord < windowRefPtr->coords[2])) &&
                   (windowRefPtr->coords[1] <= CursorYCoord)) &&
               (CursorYCoord < windowRefPtr->coords[3])) ||
           (currentCursorWindow == windowIndex))) {
        currentWindow->primarySwitchSingleParam(0x7d0e, 0x1, 0x0);
        currentCursorWindow = windowIndex;
        FlagCursorRelated = windowIndex;
      }
      else {
        currentWindow->primarySwitchSingleParam(0x7d0e, 0x0, 0x0);
        currentCursorWindow = FlagCursorRelated;
      }
    }
    windowIndex = windowIndex + -1;
    windowRefPtr = windowRefPtr + -1;
  } while (0 <= windowIndex);

  for (windowIndex = 1; windowIndex < 20; windowIndex = windowIndex + 1) {
    windowAddress = (this->initializedGW0s[windowIndex].windowAddress);
    if ((windowAddress != -1) && (currentWindow = this->gameWindowsArray[windowAddress], currentWindow != nullptr)) {
      currentWindow->primarySwitchSingleParam(0x7d3c, 0x0, 0x0);
    }
  }

  windowIndex = this->initializedGW0s[0].windowAddress;
  if (isActiveWindow != 0) {
    this->gameWindowsArray[windowIndex]->primarySwitchSingleParam(0x7d3c, 0x0, 0x0);
    return;
  }

  if (windowIndex != -1) {
    this->gameWindowsArray[windowIndex]->primarySwitchSingleParam(0x7d3c, 0x1, 0x0);
  }
}
