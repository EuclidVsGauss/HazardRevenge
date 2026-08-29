#ifndef HAZARD_COREMOVIECLASS_HPP
#define HAZARD_COREMOVIECLASS_HPP

#include "HazardClasses/RunTickClass.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardTypedef.hpp"

class DirectDrawClassBase;
class UnpackedFile8248;

class CoreMovieClass : public RunTickClass {

public:
  CoreMovieClass(int32_t);
  virtual ~CoreMovieClass();
  virtual int32_t runTick() override;

  void(__fastcall WrapperDrawMovie)();
  void __fastcall LoadMovieChunks();

  DirectDrawClassBase* directDrawObject;
  UnpackedFileBase* visualsUnpackedFile;
  int32_t callCounter;
  int32_t nFrames;
  int32_t playSpeed;
  int32_t bufferCountInt16;
  int32_t movieIndex;
  int16_t* colorMapBuffer512b;
  int16_t* buffer204800;
  LPDIRECTSOUNDBUFFER latestLpDirectSoundBuffer;
};

#endif
