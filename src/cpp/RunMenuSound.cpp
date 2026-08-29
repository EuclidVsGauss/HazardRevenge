#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/SfxObject.hpp"
#include "HazardClasses/UnpackedFile44.hpp"
#include "HazardClasses/UnpackedFile8248.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardGlobals.hpp"

LPDIRECTSOUNDBUFFER __fastcall RunMenuSound(char* soundName, int32_t samplingRate) {
  UnpackedFile8248* audioFile;
  byte* rawData;
  LPDIRECTSOUNDBUFFER soundBuffer;
  int32_t audioDataSize;

  audioFile = (UnpackedFile8248*)UnpackedFileBase::LoadFileFromArchive(soundName, 0x20000);
  if (audioFile == nullptr) {
    return (LPDIRECTSOUNDBUFFER) nullptr;
  }
  audioDataSize = audioFile->uncompressedDataLength;
  rawData = new byte[audioDataSize];
  audioFile->readFile(rawData, audioDataSize);
  soundBuffer = PtrSfxObject->CreateDirectSoundBuffer((int32_t*)rawData, audioDataSize, samplingRate);

  delete audioFile;

  delete rawData;
  return soundBuffer;
}
