#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/UnpackedFile32.hpp"
#include "HazardGlobals.hpp"

int32_t UnpackedFile32::readByte() {
  byte byteRead;
  int32_t remainingFileSize;
  int32_t bytesReadThisChunk;
  int32_t sizeToRead;

  bytesReadThisChunk = this->chunkBufferSize;
  if (bytesReadThisChunk <= this->chunkOffset) {
    remainingFileSize = this->bytesReadCumulative;
    if (this->fileStartOffset <= remainingFileSize) {
      return 0xffffffff;
    }
    sizeToRead = this->fileStartOffset - remainingFileSize;
    if (bytesReadThisChunk < sizeToRead) {
      sizeToRead = bytesReadThisChunk;
    }
    this->lastReadOffset = remainingFileSize;
    this->chunkOffset = bytesReadThisChunk - sizeToRead;
    bytesReadThisChunk = ReadFileWithTranslation(this->fileHandleId, (this->cachedFileDataBuffer + (bytesReadThisChunk - sizeToRead)), sizeToRead);
    this->bytesReadCumulative = this->bytesReadCumulative + bytesReadThisChunk;
  }
  byteRead = *(this->cachedFileDataBuffer + this->chunkOffset);
  this->chunkOffset = this->chunkOffset + 1;
  return (uint32_t)byteRead;
}
