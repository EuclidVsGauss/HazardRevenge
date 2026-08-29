#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/UnpackedFile32.hpp"
#include "HazardGlobals.hpp"

int32_t UnpackedFile32::setFilePointer(int32_t requestedPosition, int32_t moveMethod) {
  int32_t newPosition;

  switch (moveMethod) {
  case 0:
    newPosition = requestedPosition;
    break;

  case 1:
    newPosition = this->bytesReadCumulative - this->chunkBufferSize + this->chunkOffset + requestedPosition;
    break;

  case 2:
    newPosition = this->fileStartOffset + requestedPosition;
    break;

  default:
    newPosition = requestedPosition;
    break;
  }

  if (newPosition > this->fileStartOffset) {
    newPosition = this->fileStartOffset;
  }

  newPosition = newPosition & ((newPosition <= 0) - 1);

  if (newPosition >= this->lastReadOffset && newPosition < this->bytesReadCumulative) {
    this->chunkOffset = this->chunkBufferSize - this->bytesReadCumulative + newPosition;
    return newPosition;
  }

  SetFilePointer(this->fileHandleId, newPosition, 0);
  int32_t currentFilePointer = GetCurentFilePointerLocation(this->fileHandleId);
  this->bytesReadCumulative = currentFilePointer;
  this->lastReadOffset = currentFilePointer;

  if (currentFilePointer >= this->fileStartOffset) {
    this->chunkOffset = this->chunkBufferSize;
    return currentFilePointer;
  }

  int32_t bytesRemainingInFile = this->fileStartOffset - currentFilePointer;
  int32_t bytesToRead = this->chunkBufferSize;
  if (bytesRemainingInFile <= this->chunkBufferSize) {
    bytesToRead = bytesRemainingInFile;
  }

  this->lastReadOffset = currentFilePointer;
  this->chunkOffset = this->chunkBufferSize - bytesToRead;
  int32_t bytesActuallyRead = ReadFileWithTranslation(this->fileHandleId, this->cachedFileDataBuffer + this->chunkOffset, bytesToRead);
  this->bytesReadCumulative = this->bytesReadCumulative + bytesActuallyRead;
  return bytesActuallyRead;
}
