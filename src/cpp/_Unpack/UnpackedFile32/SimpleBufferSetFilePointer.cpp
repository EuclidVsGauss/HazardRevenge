#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/UnpackedFile32.hpp"
#include "HazardGlobals.hpp"

int32_t UnpackedFile32::setFilePointer(int32_t requestedPosition, int32_t moveMethod) {
  int32_t bufferSize;
  uint32_t adjustedPosition;
  int32_t currentFilePointer;
  int32_t bytesRemainingInFile;
  int32_t bytesToRead;
  if (moveMethod != 0) {
    if (moveMethod == 1) {
      requestedPosition = (this->bytesReadCumulative - this->chunkBufferSize) + this->chunkOffset + requestedPosition;
    }
    else if (moveMethod == 2) {
      requestedPosition = this->fileStartOffset + requestedPosition;
    }
  }
  if (this->fileStartOffset < requestedPosition) {
    requestedPosition = this->fileStartOffset;
  }
  adjustedPosition = requestedPosition & ((requestedPosition < 1) - 1);
  if ((this->lastReadOffset <= (int32_t)adjustedPosition) && ((int32_t)adjustedPosition < this->bytesReadCumulative)) {
    this->chunkOffset = (this->chunkBufferSize - this->bytesReadCumulative) + adjustedPosition;
    return adjustedPosition;
  }
  SetFilePointer(this->fileHandleId, adjustedPosition, 0);
  currentFilePointer = GetCurentFilePointerLocation(this->fileHandleId);
  this->bytesReadCumulative = currentFilePointer;
  this->lastReadOffset = currentFilePointer;
  if (this->fileStartOffset <= currentFilePointer) {
    this->chunkOffset = this->chunkBufferSize;
    return currentFilePointer;
  }
  bufferSize = this->chunkBufferSize;
  bytesRemainingInFile = this->fileStartOffset - currentFilePointer;
  bytesToRead = bufferSize;
  if (bytesRemainingInFile <= bufferSize) {
    bytesToRead = bytesRemainingInFile;
  }
  this->lastReadOffset = currentFilePointer;
  this->chunkOffset = bufferSize - bytesToRead;
  currentFilePointer = ReadFileWithTranslation(this->fileHandleId, (byte*)((intptr_t)this->cachedFileDataBuffer + (bufferSize - bytesToRead)), bytesToRead);
  this->bytesReadCumulative = this->bytesReadCumulative + currentFilePointer;
  return currentFilePointer;
}
