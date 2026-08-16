#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/UnpackedFile32.hpp"
#include "HazardGlobals.hpp"

UnpackedFile32::UnpackedFile32(uint32_t fileHandleId, int32_t chunkSize) {
  int32_t bytesRead;

  int32_t bytesRemaining;
  int32_t nBytesToRead;
  int32_t bufferOffset;

  this->fileHandleId = fileHandleId;
  SetFilePointer(fileHandleId, 0, 2);
  this->fileStartOffset = GetCurentFilePointerLocation(this->fileHandleId);
  this->chunkOffset = 0;
  this->bytesReadCumulative = 0;
  this->chunkBufferSize = chunkSize;
  this->cachedFileDataBuffer = (byte*)malloc(chunkSize);
  SetFilePointer(this->fileHandleId, 0, 0);
  bytesRead = this->bytesReadCumulative;
  if (bytesRead < this->fileStartOffset) {
    bytesRemaining = this->fileStartOffset - bytesRead;
    bufferOffset = this->chunkBufferSize;
    nBytesToRead = bytesRemaining <= bufferOffset ? bufferOffset : bytesRemaining;
    this->chunkOffset = bufferOffset - nBytesToRead;
    this->lastReadOffset = bytesRead;
    bytesRead = ReadFileWithTranslation(this->fileHandleId, this->cachedFileDataBuffer + (bufferOffset - nBytesToRead), nBytesToRead);
    this->bytesReadCumulative = this->bytesReadCumulative + bytesRead;
  }
  else {
    this->chunkOffset = this->chunkBufferSize;
  }
}
