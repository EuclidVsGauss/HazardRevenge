#include "HazardClasses/MusicObject.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"

void MusicObject::CloseMusicFile() {
  if (this->byteStream != nullptr) {
    UnpackedFileBase::CloseUnpackedFile(this->byteStream);
  }
  this->byteStream = nullptr;
}
