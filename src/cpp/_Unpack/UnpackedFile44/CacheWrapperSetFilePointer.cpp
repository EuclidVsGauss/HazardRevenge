#include "HazardClasses/UnpackedFile44.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/UnpackedFilePakStruct.hpp"

int32_t UnpackedFile44::setFilePointer(int32_t newPosition, int32_t origin) {
  UnpackedFileBase* segmentPointer;
  int32_t allocatedBufferSize;
  int32_t updatedReadPosition;
  int32_t readChunkSize;
  int32_t segmentEndPosition;
  int32_t segmentStart;

  switch (origin) {
  case 0:
    newPosition = this->archiveSegmentStartOffset + newPosition;
    break;
  case 1:
    newPosition = (this->sourceFileReadPosition - this->bufferAllocationSize) + this->bufferReadOffset + newPosition;
    break;
  case 2:
    newPosition = this->compressedDataSize + this->archiveSegmentStartOffset + newPosition;
    break;
  }

  segmentStart = this->archiveSegmentStartOffset;
  segmentEndPosition = this->compressedDataSize + segmentStart;
  if (segmentEndPosition < newPosition) {
    newPosition = segmentEndPosition;
  }
  if (newPosition <= segmentStart) {
    newPosition = segmentStart;
  }
  if ((this->currentSegmentStartPointer <= newPosition) && (newPosition < this->sourceFileReadPosition)) {
    this->bufferReadOffset = (this->bufferAllocationSize - this->sourceFileReadPosition) + newPosition;
    return newPosition;
  }
  this->sourceFileReadPosition = newPosition;
  this->currentSegmentStartPointer = newPosition;
  if (segmentEndPosition <= newPosition) {
    this->bufferReadOffset = this->bufferAllocationSize;
    return newPosition;
  }
  if (this->sourceFileObject->filePointer != newPosition) {
    segmentPointer = this->sourceFileObject->unpackedFileObject;
    segmentPointer->setFilePointer(newPosition, 0);
  }
  readChunkSize = (this->archiveSegmentStartOffset - this->sourceFileReadPosition) + this->compressedDataSize;
  allocatedBufferSize = this->bufferAllocationSize;
  if (allocatedBufferSize <= readChunkSize) {
    readChunkSize = allocatedBufferSize;
  }
  this->bufferReadOffset = allocatedBufferSize - readChunkSize;
  this->currentSegmentStartPointer = this->sourceFileReadPosition;
  segmentPointer = this->sourceFileObject->unpackedFileObject;
  updatedReadPosition = segmentPointer->readFile((this->dataBufferMemory + this->bufferReadOffset), readChunkSize);
  updatedReadPosition = this->sourceFileReadPosition + updatedReadPosition;
  this->sourceFileReadPosition = updatedReadPosition;
  this->sourceFileObject->filePointer = updatedReadPosition;
  return updatedReadPosition;
}
