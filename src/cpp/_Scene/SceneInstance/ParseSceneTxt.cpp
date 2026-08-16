#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/EventHandler.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneClassAnimatedBackground.hpp"
#include "HazardClasses/SceneClassBoss.hpp"
#include "HazardClasses/SceneClassBox.hpp"
#include "HazardClasses/SceneClassButton.hpp"
#include "HazardClasses/SceneClassCamera.hpp"
#include "HazardClasses/SceneClassCloud.hpp"
#include "HazardClasses/SceneClassCommand.hpp"
#include "HazardClasses/SceneClassDoor.hpp"
#include "HazardClasses/SceneClassGate.hpp"
#include "HazardClasses/SceneClassGate0.hpp"
#include "HazardClasses/SceneClassItem.hpp"
#include "HazardClasses/SceneClassMap.hpp"
#include "HazardClasses/SceneClassMoveTile.hpp"
#include "HazardClasses/SceneClassNoise.hpp"
#include "HazardClasses/SceneClassRect.hpp"
#include "HazardClasses/SceneClassSwitch.hpp"
#include "HazardClasses/SceneClassUser.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardClasses/SceneInstance.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardEnums/MapType.hpp"
#include "HazardEnums/SceneCommands.hpp"
#include "HazardExterns/SceneInstance.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/WindowReference.hpp"

void SceneInstance::ParseSceneTxt() {
  int32_t* intPointer;
  uint32_t byteReadValue;
  int32_t compareResult;
  GameWindowBase* userObjectPtr;
  GameWindowBase* initialisedObject;
  bool booleanFlag;
  int32_t switchVariable;
  char filename[128];
  char stringBuffer[128];

  if (GlobalSceneInstanceIndex == 0) {
    UnpackedSceneTxtContent = UnpackedFileBase::LoadFileFromArchive(s_scene_txt, 0x20000);
    do {
      byteReadValue = UnpackedSceneTxtContent->readByte();
      while (byteReadValue != L'#') {
        byteReadValue = UnpackedSceneTxtContent->readByte();
      }
      ReadInterpolatableString(UnpackedSceneTxtContent, InterpolatableString, stringBuffer);
      switchVariable = strcmp(this->sceneName, stringBuffer);

    } while (switchVariable != 0);
    byteReadValue = UnpackedSceneTxtContent->readByte();
    stringBuffer[0] = byteReadValue;
    while (stringBuffer[0] != '#') {
      stringBuffer[1] = byteReadValue;
      if (stringBuffer[1] == '\r') {
        intPointer = &this->sceneLinesToBeParsed;
        *intPointer = *intPointer + 1;
      }
      byteReadValue = UnpackedSceneTxtContent->readByte();
      stringBuffer[0] = byteReadValue;
    }
    if (UnpackedSceneTxtContent != nullptr) {
      delete UnpackedSceneTxtContent;
    }
    UnpackedSceneTxtContent = UnpackedFileBase::LoadFileFromArchive(s_scene_txt, 0x20000);
    do {
      byteReadValue = UnpackedSceneTxtContent->readByte();
      while (byteReadValue != L'#') {
        byteReadValue = UnpackedSceneTxtContent->readByte();
      }
      ReadInterpolatableString(UnpackedSceneTxtContent, InterpolatableString, stringBuffer);
      switchVariable = strcmp(this->sceneName, stringBuffer);

    } while (switchVariable != 0);
    this->mainSceneHandler->primarySwitchSingleParam_LoadingMarkers_0x7d31(3, 0x0);
    GlobalSceneInstanceIndex = this->sceneInstanceIndex_10to14;
  }
  if (GlobalSceneInstanceIndex != this->sceneInstanceIndex_10to14) {
    return;
  }
  ReadInterpolatableString(UnpackedSceneTxtContent, InterpolatableString, stringBuffer);
  if (stringBuffer[0] == '#') {
    if (UnpackedSceneTxtContent != nullptr) {
      delete UnpackedSceneTxtContent;
    }
    GlobalSceneInstanceIndex = 0;
    this->mainSceneHandler->primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(this, 0x0);
    this->mainSceneHandler->primarySwitchSingleParam_SetWindow_0x7d16(this->sceneInstanceIndex_10to14, nullptr);
    this->mainSceneHandler->StoreAndInitializeObject(this->large65736);
    this->mainSceneHandler->primarySwitchSingleParam_0x7d28(this->large65736, this->sceneName);
    this->mainSceneHandler->primarySwitchSingleParam_LoadingMarkers_0x7d31(0, 0x0);
    return;
  }
  switchVariable = this->sceneLinesCurrentlyParsed + 1;
  this->sceneLinesCurrentlyParsed = switchVariable;
  this->mainSceneHandler->primarySwitchSingleParam_LoadingMarkers_0x7d31((10 - ((switchVariable * 10) / this->sceneLinesToBeParsed)), 0x0);
  if (stringBuffer[0] == ';') {
    byteReadValue = UnpackedSceneTxtContent->readByte();
    while (byteReadValue != '\n') {
      byteReadValue = UnpackedSceneTxtContent->readByte();
    }
    return;
  }

  switchVariable = 0;
  for (int32_t i = 0; i < 30; i++) {
    if (strcmp(stringBuffer, PointerKeyValuePair_ARRAY[i].Key) == 0) {
      switchVariable = i;
      break;
    }
  }

  switch (PointerKeyValuePair_ARRAY[switchVariable].Value) {
  case 1:
    ReadInterpolatableString(UnpackedSceneTxtContent, InterpolatableString, filename);
    booleanFlag = filename[0] == '!';
    switchVariable = atoi(filename + (int32_t)booleanFlag);
    if (GameFlags[switchVariable] != (int32_t)booleanFlag) {
      return;
    }
    switchVariable = 0;
    do {
      ReadInterpolatableString(UnpackedSceneTxtContent, InterpolatableString, stringBuffer);
      if (stringBuffer[0] == ';') {
        byteReadValue = UnpackedSceneTxtContent->readByte();
        while (byteReadValue != '\n') {
          byteReadValue = UnpackedSceneTxtContent->readByte();
        }
      }

      compareResult = strcmp(s_if, stringBuffer);

      if (compareResult == 0) {
        switchVariable = switchVariable + 1;
      }

      compareResult = strcmp(s_endif, stringBuffer);

      if (compareResult == 0) {
        switchVariable = switchVariable + -1;
      }

      compareResult = strcmp(s_elseif, stringBuffer);

      if ((compareResult == 0) && (switchVariable == 0)) {
        return;
      }
      if (switchVariable < 0) {
        return;
      }
    } while (true);
  case 2:
    switchVariable = 0;
    do {
      ReadInterpolatableString(UnpackedSceneTxtContent, InterpolatableString, stringBuffer);
      if (stringBuffer[0] == ';') {
        byteReadValue = UnpackedSceneTxtContent->readByte();
        while (byteReadValue != '\n') {
          byteReadValue = UnpackedSceneTxtContent->readByte();
        }
      }
      compareResult = strcmp(s_if, stringBuffer);

      if (compareResult == 0) {
        switchVariable = switchVariable + 1;
      }

      compareResult = strcmp(s_endif, stringBuffer);

      if (compareResult == 0) {
        switchVariable = switchVariable + -1;
      }
      if (switchVariable < 0) {
        return;
      }
    } while (true);
  case 3:
    return;
  case SceneCommands::scene_command: {
    int32_t isCommandAvailable;

    ReadInterpolatableString(UnpackedSceneTxtContent, s__d, &isCommandAvailable);
    if (isCommandAvailable != 0) {
      return;
    }
    initialisedObject = new SceneClassCommand();

    break;
  }
  case SceneCommands::scene_camera: {
    int32_t isCameraAvailable;

    ReadInterpolatableString(UnpackedSceneTxtContent, s__d, &isCameraAvailable);
    initialisedObject = new SceneClassCamera(0x0, 0x0);
    break;
  }
  case SceneCommands::scene_talkbox: {
    int32_t scriptId;

    ReadInterpolatableString(UnpackedSceneTxtContent, s__d, &scriptId);

    this->large65736->__InlineQueueEvent(0);
    this->large65736->__InlineQueueEvent(scriptId);
    this->large65736->__InlineQueueEvent(0x7d02);

    return;
    break;
  }
  case SceneCommands::scene_door: {
    int32_t coord1;
    int32_t coord2;
    int32_t orientation;
    int32_t gameFlag;
    char doorModelAct[128];

    ReadInterpolatableString(UnpackedSceneTxtContent, s__s__d__d__x__d, doorModelAct, &coord1, &coord2, &orientation, &gameFlag);
    initialisedObject = new SceneClassDoor(coord1, coord2, orientation, gameFlag, doorModelAct);

    break;
  }
  case SceneCommands::scene_button: {
    int32_t gameFlag;
    int32_t orientation;
    int32_t coord2;
    int32_t coord1;
    char actFilename[128];

    ReadInterpolatableString(UnpackedSceneTxtContent, s__s__d__d__d__d, actFilename, &coord1, &coord2, &orientation, &gameFlag);
    initialisedObject = new SceneClassButton(coord1, coord2, orientation, gameFlag, actFilename);

    break;
  }
  case SceneCommands::scene_movetile: {
    int32_t coord1;
    int32_t coord2;
    int32_t arg1;
    int32_t arg2;
    int32_t arg3;
    int32_t arg4;
    int32_t arg5;
    char actName[128];

    ReadInterpolatableString(UnpackedSceneTxtContent, s__s__d__d__d__d__d__d__d, actName, &coord1, &coord2, &arg1, &arg2, &arg3, &arg4, &arg5);
    initialisedObject = new SceneClassMoveTile(actName, coord1, coord2, arg1, arg2, arg3, arg4, arg5);

    break;
  }
  case SceneCommands::scene_check: {
    int32_t gameFlagId;
    int32_t gameFlagValue;

    ReadInterpolatableString(UnpackedSceneTxtContent, s__d__d, &gameFlagId, &gameFlagValue);
    GameFlags[gameFlagId] = gameFlagValue;
    return;
    break;
  }
  case SceneCommands::scene_music: {
    int32_t trackId;

    ReadInterpolatableString(UnpackedSceneTxtContent, s__d, &trackId);
    this->large65736->primarySwitchSingleParam(0x7d29, 0x0, trackId);
    return;
    break;
  }
  case SceneCommands::scene_type: {
    int32_t mapType;

    ReadInterpolatableString(UnpackedSceneTxtContent, s__d, &mapType);
    (this->large65736)->mapType = MapTypeEnum(mapType);
    if (mapType != 2) {
      return;
    }
    this->large65736->primarySwitchSingleParam(0x7d2d, 0x0, 0x0);

    return;
    break;
  }
  case SceneCommands::scene_viewport: {
    int32_t isViewportEnabled;

    ReadInterpolatableString(UnpackedSceneTxtContent, s__d, &isViewportEnabled);
    this->large65736->isViewportEnabled = isViewportEnabled;

    return;
    break;
  }
  case SceneCommands::scene_magic: {
    int32_t isMagicEnabled;

    ReadInterpolatableString(UnpackedSceneTxtContent, s__d, &isMagicEnabled);
    this->large65736->isMagicEnabled = isMagicEnabled;
    return;
    break;
  }
  case SceneCommands::scene_gate: {
    int32_t lowerCoord1;
    int32_t lowerCoord2;
    int32_t upperCoord1;
    int32_t upperCoord2;
    int32_t newCoord1;
    int32_t newCoord2;
    char newSceneName[128];

    ReadInterpolatableString(UnpackedSceneTxtContent, s__d__d__d__d__s__d__d, &lowerCoord1, &lowerCoord2, &upperCoord1, &upperCoord2, newSceneName, &newCoord1, &newCoord2);
    initialisedObject = new SceneClassGate(lowerCoord1, lowerCoord2, upperCoord1, upperCoord2, newSceneName, newCoord1, newCoord2);

    break;
  }
  case SceneCommands::scene_anibg: {
    int32_t coord1;
    int32_t coord2;
    int32_t layerOffset;
    char actFilename[128];
    char actionName[128];

    ReadInterpolatableString(UnpackedSceneTxtContent, s__s__s__d__d__d, actFilename, actionName, &coord1, &coord2, &layerOffset);
    initialisedObject = new SceneClassAnimatedBackground(actFilename, actionName, coord1, coord2, layerOffset);

    break;
  }
  case SceneCommands::scene_cloud: {
    int32_t startX;
    int32_t startY;
    int32_t endX;
    int32_t endY;
    int32_t maxFrame;
    char filename_local[128];
    char actFilenameEtc_local[128];

    ReadInterpolatableString(UnpackedSceneTxtContent, s__s__s__d__d__d__d__d, filename_local, actFilenameEtc_local, &startX, &startY, &endX, &endY, &maxFrame);
    initialisedObject = new SceneClassCloud(filename_local, actFilenameEtc_local, startX, startY, endX, endY, maxFrame);

    break;
  }
  case SceneCommands::scene_map: {
    char mapNameTmp[128];
    ReadInterpolatableString(UnpackedSceneTxtContent, InterpolatableString, mapNameTmp);
    initialisedObject = new SceneClassMap(mapNameTmp, this->large65736);
    break;
  }
  case 0x13: {
    int32_t coord1;
    int32_t coord2;
    int32_t userFlags;
    char userName[128];

    ReadInterpolatableString(UnpackedSceneTxtContent, s__s__d__d__x, userName, &coord1, &coord2, &userFlags);
    userObjectPtr = new SceneClassUser(coord1, coord2, userName, userFlags, 0, 0);
    this->large65736->StoreAndInitializeObject(userObjectPtr);
    return;
    break;
  }
  case SceneCommands::scene_talker: {
    int32_t coord1;
    int32_t coord2;
    int32_t userFlags;
    int32_t scriptId;
    char actFilename[128];

    ReadInterpolatableString(UnpackedSceneTxtContent, s__s__d__d__x__d, actFilename, &coord1, &coord2, &userFlags, &scriptId);
    userObjectPtr = new SceneClassUser(coord1, coord2, actFilename, userFlags, scriptId, 0);
    this->large65736->StoreAndInitializeObject(userObjectPtr);
    return;
  }
  case SceneCommands::scene_box0: {
    int32_t coord1;
    int32_t coord2;
    int32_t gameFlag;
    int32_t actionIndex;
    char actFilenameEtc_local[128];

    ReadInterpolatableString(UnpackedSceneTxtContent, s__s__d__d__d__d, actFilenameEtc_local, &coord1, &coord2, &actionIndex, &gameFlag);
    initialisedObject = new SceneClassBox(coord1, coord2, gameFlag, actionIndex, actFilenameEtc_local);

    break;
  }
  case SceneCommands::scene_box: {
    int32_t coord1;
    int32_t coord2;
    int32_t actionIndex;
    char actFilename[128];

    ReadInterpolatableString(UnpackedSceneTxtContent, s__s__d__d__d, actFilename, &coord1, &coord2, &actionIndex);
    initialisedObject = new SceneClassBox(coord1, coord2, 0, actionIndex, actFilename);

    break;
  }
  case SceneCommands::scene_noise: {
    int16_t soundEffectIndex;

    ReadInterpolatableString(UnpackedSceneTxtContent, s__d, &soundEffectIndex);
    initialisedObject = new SceneClassNoise(soundEffectIndex);

    break;
  }
  case SceneCommands::scene_item: {
    int32_t coord1;
    int32_t coord2;
    int32_t itemType;

    ReadInterpolatableString(UnpackedSceneTxtContent, s__d__d__d, &coord1, &coord2, &itemType);
    initialisedObject = new SceneClassItem(coord1, coord2, itemType, 10000);

    break;
  }
  case SceneCommands::scene_switch: {
    int32_t coord1;
    int32_t coord2;
    int32_t orienatation;
    int32_t gameFlagIndex;
    int32_t isPermanent;
    char actFilename[128];

    ReadInterpolatableString(UnpackedSceneTxtContent, s__s__d__d__d__d__d, actFilename, &coord1, &coord2, &orienatation, &gameFlagIndex, &isPermanent);
    initialisedObject = new SceneClassSwitch(coord1, coord2, orienatation, gameFlagIndex, actFilename, isPermanent);

    break;
  }
  default:
    WrapperMessageBoxA(stringBuffer, s_Wrong_Message);
    return;
  case SceneCommands::scene_gate0: {
    int32_t lowerCoord1;
    int32_t lowerCoord2;
    int32_t upperCoord1;
    int32_t upperCoord2;
    int32_t newCoord1;
    int32_t newCoord2;
    char newSceneName[128];

    ReadInterpolatableString(UnpackedSceneTxtContent, s__d__d__d__d__s__d__d, &lowerCoord1, &lowerCoord2, &upperCoord1, &upperCoord2, newSceneName, &newCoord1, &newCoord2);
    initialisedObject = new SceneClassGate0(lowerCoord1, lowerCoord2, upperCoord1, upperCoord2, newSceneName, newCoord1, newCoord2);
    break;
  }
  case SceneCommands::scene_rect: {
    int32_t lowerCoord1;
    int32_t lowerCoord2;
    int32_t upperCoord1;
    int32_t upperCoord2;
    int32_t dialogueIndex;
    int32_t gameFlagIndex;

    ReadInterpolatableString(UnpackedSceneTxtContent, s__d__d__d__d__d__d, &lowerCoord1, &lowerCoord2, &upperCoord1, &upperCoord2, &dialogueIndex, &gameFlagIndex);
    initialisedObject = new SceneClassRect(lowerCoord1, lowerCoord2, upperCoord1, upperCoord2, dialogueIndex, gameFlagIndex);
    break;
  }
  case SceneCommands::scene_user0: {
    int32_t coord1;
    int32_t coord2;
    int32_t user0Flags;
    int32_t deathScriptId;
    char actFilename[128];

    ReadInterpolatableString(UnpackedSceneTxtContent, s__s__d__d__x__d, actFilename, &coord1, &coord2, &user0Flags, &deathScriptId);
    userObjectPtr = new SceneClassUser(coord1, coord2, actFilename, user0Flags, 0, deathScriptId);
    this->large65736->StoreAndInitializeObject(userObjectPtr);
    return;
  }
  case SceneCommands::scene_step: {
    int32_t stepIndex;
    ReadInterpolatableString(UnpackedSceneTxtContent, s__d, &stepIndex);
    return;
  }
  case SceneCommands::scene_boss: {
    int32_t coord1;
    int32_t coord2;
    int32_t gameFlag1;
    int32_t gameFlag2;
    char actFile[128];

    ReadInterpolatableString(UnpackedSceneTxtContent, s__s__d__d__d__d, actFile, &coord1, &coord2, &gameFlag1, &gameFlag2);
    initialisedObject = new SceneClassBoss(actFile, coord1, coord2, gameFlag1, gameFlag2);

    break;
  }
  }
  this->large65736->StoreAndInitializeObject(initialisedObject);
}
