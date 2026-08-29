#ifndef HAZARD_SFXOBJECTBASE_HPP
#define HAZARD_SFXOBJECTBASE_HPP

#include <windows.h>
#include "HazardFunctions.hpp"
#include "HazardTypedef.hpp"

class SfxObjectBase {

public:
  SfxObjectBase() {}

  virtual ~SfxObjectBase() {};

  virtual void WINAPI Nothing();

  virtual int32_t RunPlay(LPDIRECTSOUNDBUFFER, int32_t, int32_t) {
    ExitGame();
    return 0;
  }

  virtual LPDIRECTSOUNDBUFFER CreateDirectSoundBuffer(int32_t*, int32_t, DWORD) {
    ExitGame();
    return (LPDIRECTSOUNDBUFFER) nullptr;
  }

  virtual void CallRuntimeFunction(LPDIRECTSOUNDBUFFER) { ExitGame(); }
};

#endif
