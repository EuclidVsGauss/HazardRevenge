#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/UnpackedFile32.hpp"
#include "HazardGlobals.hpp"

int32_t UnpackedFile32::readByte() {
  int32_t byteRead;
  int32_t remainingFileSize;
  int32_t bytesReadThisChunk;
  int32_t sizeToRead;

  bytesReadThisChunk = this->chunkBufferSize;
  if (this->chunkOffset >= bytesReadThisChunk) {
    remainingFileSize = this->bytesReadCumulative;
    if (remainingFileSize >= this->fileStartOffset) {
      return -1;
    }
    sizeToRead = this->fileStartOffset - remainingFileSize;
    if (sizeToRead > bytesReadThisChunk) {
      sizeToRead = bytesReadThisChunk;
    }
    bytesReadThisChunk = bytesReadThisChunk - sizeToRead;
    this->lastReadOffset = remainingFileSize;
    this->chunkOffset = bytesReadThisChunk;
    bytesReadThisChunk = ReadFileWithTranslation(this->fileHandleId, this->cachedFileDataBuffer + bytesReadThisChunk, sizeToRead);
    this->bytesReadCumulative = this->bytesReadCumulative + bytesReadThisChunk;
  }
  byteRead = *(this->cachedFileDataBuffer + this->chunkOffset);
  this->chunkOffset = this->chunkOffset + 1;
  return byteRead;
}
