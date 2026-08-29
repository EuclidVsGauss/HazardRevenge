#ifndef HAZARD_MUSICOBJECTBASE_HPP
#define HAZARD_MUSICOBJECTBASE_HPP
#include "HazardFunctions.hpp"
#include "HazardTypedef.hpp"

class MusicObjectBase {

public:
  MusicObjectBase() {}

  virtual ~MusicObjectBase() {};

  virtual void Nothing() {};

  virtual void LoadAndPlayNewTrack(uint32_t) { ExitGame(); }

  virtual void ReleaseMusicBuffer() { ExitGame(); }

  virtual void UpdateSoundBuffer() {}

  virtual int32_t CalculateTotalSamples(int32_t) { return 1024; }
};

#endif
