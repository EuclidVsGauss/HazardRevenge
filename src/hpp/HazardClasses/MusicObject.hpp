#ifndef HAZARD_MUSICOBJECT_HPP
#define HAZARD_MUSICOBJECT_HPP

#include <windows.h>
#include "HazardClasses/MusicObjectBase.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardTypedef.hpp"

class MusicObject : MusicObjectBase {

public:
  MusicObject(LPDIRECTSOUND);
  virtual ~MusicObject();

  virtual void Nothing() override {};

  virtual void LoadAndPlayNewTrack(uint32_t trackIndex) override;
  virtual void ReleaseMusicBuffer() override;
  virtual void UpdateSoundBuffer() override;
  virtual int32_t CalculateTotalSamples(int32_t) override;

  void DecodeADPCMBlock(int16_t*, int32_t);
  void WriteDecodedAudioToBuffer(uint32_t, DWORD);
  void SetMusicVolume(float);
  int32_t LoadTrackPcm(int32_t trackIndex);
  LPDIRECTSOUNDBUFFER CreateMusicSoundBuffer(LPDIRECTSOUNDBUFFER param_1, int32_t denom2, int32_t denom1, int32_t largeInteger);
  void CloseMusicFile();
  void __fastcall ResetMusicFilePointer();

  LPDIRECTSOUNDBUFFER buffer;
  int32_t audioFrequency;
  int32_t channelCount;
  LPDIRECTSOUND DirectSoundObject;
  int32_t soundVolume;
  int32_t isLooping;
  int32_t flagRanPlayWithoutError;
  int32_t usedForNumerator;
  int32_t numeratorComparator;
  int32_t totalDecodedBytes;
  int32_t usedAsNumerator;
  int32_t usedForGetCurrentPosition;
  LPDIRECTSOUNDBUFFER lpDirectSoundBuffer;
  int32_t prevSample;
  int32_t unused1;
  int32_t unused2;
  int32_t unused3;
  byte adpcmStepIndex;
  byte currentByte;
  byte padding1;
  byte padding2;
  int32_t nibbleToggle;
  UnpackedFileBase* byteStream;
};

#endif
