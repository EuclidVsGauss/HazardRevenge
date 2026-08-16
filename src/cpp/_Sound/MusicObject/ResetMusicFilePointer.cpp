#include "HazardClasses/MusicObject.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardGlobals.hpp"

void __fastcall MusicObject::ResetMusicFilePointer() {
  this->byteStream->setFilePointer(16, 0);
  this->unused3 = 0;
  this->unused1 = 0;
  this->unused2 = 0;
  this->prevSample = 0;
  this->nibbleToggle = 0;
}
