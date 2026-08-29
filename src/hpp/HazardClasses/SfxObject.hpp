#ifndef HAZARD_SFXOBJECT_HPP
#define HAZARD_SFXOBJECT_HPP

#include <windows.h>
#include "HazardClasses/SfxObjectBase.hpp"
#include "HazardTypedef.hpp"

class SfxObject : public SfxObjectBase {

public:
  SfxObject();
  virtual ~SfxObject();
  virtual void WINAPI Nothing() override;
  virtual int32_t RunPlay(LPDIRECTSOUNDBUFFER, int32_t, int32_t) override;
  virtual LPDIRECTSOUNDBUFFER CreateDirectSoundBuffer(int32_t*, int32_t, DWORD) override;
  virtual void CallRuntimeFunction(LPDIRECTSOUNDBUFFER) override;

  int32_t isDirectSoundObjectCreated;
};

#endif
