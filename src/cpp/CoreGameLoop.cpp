#include "HazardPatches.hpp"
#include "HazardClasses/CoreGameClass.hpp"
#include "HazardClasses/CoreLoadSavedGames.hpp"
#include "HazardClasses/CoreMovieClass.hpp"
#include "HazardClasses/CoreStartMenu.hpp"
#include "HazardClasses/MusicObjectBase.hpp"
#include "HazardClasses/RunTickClass.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/GameState.hpp"

void CoreGameLoop() {
  UnpackedFileBase* dwBufferBytes;
  LPDIRECTSOUNDBUFFER pSoundBuffer;
  int32_t runTickResult;
  RunTickClass* coreClass;
  CoreGameClass* coreClass2;
  CoreGameClass* pNewCoreGame;
  int32_t linesReadCount;
  int32_t sfxIndex;
  char sfxNameBuffer[20];
  int32_t loadSfxSwitch;

  loadSfxSwitch = GameStateFlag;
  switch (loadSfxSwitch) {
  case 0:
    dwBufferBytes = UnpackedFileBase::LoadFileFromArchive(s_sfx_txt, 0x20000);
    while (ReadInterpolatableString(dwBufferBytes, s__d__s__d, &linesReadCount, sfxNameBuffer, &sfxIndex), 0 < linesReadCount) {
      pSoundBuffer = RunMenuSound((char*)sfxNameBuffer, sfxIndex);
      ListOfSfxBuffers[linesReadCount] = pSoundBuffer;
    }
    UnpackedFileBase::CloseUnpackedFile(dwBufferBytes);

#if PATCH_SKIP_ALL_INTROS == 0
    coreClass = new CoreMovieClass(5);
    CurrentRunTickClass = coreClass;
    GameStateFlag = 8;
#else
    coreClass = new CoreStartMenu();
    GameStateFlag = 5;
    CurrentRunTickClass = coreClass;
#endif
    return;

  case 2:
    runTickResult = CurrentRunTickClass->runTick();
    if (runTickResult == 0) {
      if (CurrentRunTickClass != nullptr) {
        delete CurrentRunTickClass;
      }
      coreClass = new CoreMovieClass(0);
      CurrentRunTickClass = coreClass;
      GameStateFlag = 4;
      return;
    }
    break;
  case 3:
    runTickResult = CurrentRunTickClass->runTick();
    if (runTickResult != 0) {
      if (runTickResult == 1) {
        if (CurrentRunTickClass != nullptr) {
          delete CurrentRunTickClass;
        }
        coreClass = new CoreStartMenu();
        GameStateFlag = 5;
        CurrentRunTickClass = coreClass;
        return;
      }
      break;
    }
    if (CurrentRunTickClass != nullptr) {
      delete CurrentRunTickClass;
    }
    coreClass2 = new CoreGameClass(&GlobalHazGameState);
    if (coreClass2 != nullptr) {

      CurrentRunTickClass = coreClass2;
      GameStateFlag = 6;
      return;
    }
    CurrentRunTickClass = nullptr;
    GameStateFlag = 6;
    return;
  case 4:
    runTickResult = CurrentRunTickClass->runTick();
    if (runTickResult == 0) {
      if (CurrentRunTickClass != nullptr) {
        delete CurrentRunTickClass;
      }
      coreClass = new CoreStartMenu();
      GameStateFlag = 5;
      CurrentRunTickClass = coreClass;
      return;
    }
    break;
  case 5:
    runTickResult = CurrentRunTickClass->runTick();
    switch (runTickResult) {
    case 1:
      if (CurrentRunTickClass != nullptr) {
        delete CurrentRunTickClass;
      }
      coreClass2 = new CoreGameClass((GameState*)nullptr);
      if ((coreClass2 != nullptr) && (pNewCoreGame = coreClass2, pNewCoreGame != nullptr)) {

        CurrentRunTickClass = pNewCoreGame;
        GameStateFlag = 6;
        return;
      }
      break;
    case 2:
      if (CurrentRunTickClass != nullptr) {
        delete CurrentRunTickClass;
      }
      coreClass = new CoreLoadSavedGames();
      CurrentRunTickClass = coreClass;
      GameStateFlag = 3;
      return;

    case 3:
      GameStateFlag = 7;
      return;

    case 4:
      if (CurrentRunTickClass != nullptr) {
        delete CurrentRunTickClass;
      }
      coreClass = new CoreMovieClass(0);
      CurrentRunTickClass = coreClass;
      GameStateFlag = 4;
      return;
    default:
      return;
    }
    CurrentRunTickClass = nullptr;
    GameStateFlag = 6;
    return;
  case 6:
    runTickResult = CurrentRunTickClass->runTick();
    switch (runTickResult) {
    case 1:
      if (CurrentRunTickClass != nullptr) {
        delete CurrentRunTickClass;
      }
      coreClass = new CoreStartMenu();
      GameStateFlag = 5;
      CurrentRunTickClass = coreClass;
      return;
    case 2:
      if (CurrentRunTickClass != nullptr) {
        delete CurrentRunTickClass;
      }
      coreClass = new CoreMovieClass(runTickResult);
      if (coreClass != nullptr) {
        runTickResult = 0;
        CurrentRunTickClass = coreClass;
        GameStateFlag = 4;
        return;
      }
      break;
    case 3:
      if (CurrentRunTickClass != nullptr) {
        delete CurrentRunTickClass;
      }
      coreClass = new CoreMovieClass(runTickResult);
      if (coreClass != nullptr) {
        runTickResult = 1;
        CurrentRunTickClass = coreClass;
        GameStateFlag = 4;
        return;
      }
      break;
    case 4:
      if (CurrentRunTickClass != nullptr) {
        delete CurrentRunTickClass;
      }
      coreClass = new CoreMovieClass(runTickResult);
      if (coreClass != nullptr) {
        runTickResult = 2;
        CurrentRunTickClass = coreClass;
        GameStateFlag = 4;
        return;
      }
      break;

    case 5:
      if (CurrentRunTickClass != nullptr) {
        delete CurrentRunTickClass;
      }
      coreClass = new CoreMovieClass(3);
      if (coreClass != nullptr) {
        CurrentRunTickClass = coreClass;
        GameStateFlag = 4;
        return;
      }
      break;

    default:
      return;
    }
    CurrentRunTickClass = nullptr;
    GameStateFlag = 4;
    return;

  case 7:
    if (CurrentRunTickClass != nullptr) {
      delete CurrentRunTickClass;
    }
    CurrentRunTickClass = nullptr;
    GameStateFlag = 0;
    FlagGameIsRunning = 0;
    break;

  case 8:
    runTickResult = CurrentRunTickClass->runTick();
    if (runTickResult == 0) {
      if (CurrentRunTickClass != nullptr) {
        delete CurrentRunTickClass;
      }
      CurrentRunTickClass = new CoreMovieClass(4);
      ;
      GameStateFlag = 2;
      return;
    }
  }
}
