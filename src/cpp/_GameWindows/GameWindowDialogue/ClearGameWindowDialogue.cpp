#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowDialogue.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardStructs/TextBuffer.hpp"
#include "HazardStructs/WindowReference.hpp"

GameWindowDialogue::~GameWindowDialogue() {
  SceneHandler* sceneHandler;
  UnpackedFileBase* script;
  GameWindowBase* gwCopy;
  CoreActClass* actObject;

  sceneHandler = this->mainSceneHandler;
  sceneHandler->primarySwitchSingleParam_SetWindow_0x7d16(5, nullptr);

  script = this->ptrScriptTxt;
  if (script != nullptr) {
    delete script;
  }

  gwCopy = this->saveGameWindowCopy;
  if (gwCopy != nullptr) {
    delete gwCopy;
  }

  actObject = this->win4Act;
  if (actObject != nullptr) {
    delete actObject;
  }

  delete (this->struct94kb_2);
  delete (this->struct94kb_1);
  delete (this->screen_480x640x2);
}
