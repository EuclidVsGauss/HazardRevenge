#include <stdio.h>
#include "HazardClasses/MusicObject.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardExterns/MusicObject.hpp"
#include "HazardGlobals.hpp"

int32_t MusicObject::LoadTrackPcm(int32_t trackIndex) {
  UnpackedFileBase* unpackedFile;
  char trackName[20];
  int32_t bytesPerChannel;

  sprintf(trackName, s_track_02d_pcm, trackIndex);
  unpackedFile = UnpackedFileBase::LoadFileFromArchive(trackName, 0x20000);
  this->byteStream = unpackedFile;
  if (unpackedFile != nullptr) {
    unpackedFile->readFile(&this->buffer, 4);
    this->byteStream->readFile(&this->audioFrequency, 4);
    this->byteStream->readFile(&this->channelCount, 4);
    this->byteStream->readFile(&bytesPerChannel, 4);
    this->unused3 = 0;
    this->unused1 = 0;
    this->unused2 = 0;
    this->prevSample = 0;
    this->nibbleToggle = 0;
    return bytesPerChannel * 2;
  }
  return 0;
}
