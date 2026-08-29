#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/UnpackedFile44.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/UnpackedFilePakStruct.hpp"

int32_t UnpackedFile44::readByte() {
  int32_t byteRead;
  UnpackedFileBase* unpackedFile;
  int32_t allocationSize;
  int32_t bytesActuallyRead;
  int32_t proposedReadSize;

  if (this->bufferReadOffset >= this->bufferAllocationSize) {
    bytesActuallyRead = this->sourceFileReadPosition;
    if (bytesActuallyRead >= this->compressedDataSize + this->archiveSegmentStartOffset) {
      return -1;
    }
    if (this->sourceFileObject->filePointer != bytesActuallyRead) {
      unpackedFile = this->sourceFileObject->unpackedFileObject;
      unpackedFile->setFilePointer(bytesActuallyRead, 0);
    }
    proposedReadSize = (this->compressedDataSize - this->sourceFileReadPosition) + this->archiveSegmentStartOffset;
    allocationSize = this->bufferAllocationSize;
    proposedReadSize = allocationSize <= proposedReadSize ? allocationSize : proposedReadSize;
    this->bufferReadOffset = allocationSize - proposedReadSize;
    this->currentSegmentStartPointer = this->sourceFileReadPosition;
    unpackedFile = this->sourceFileObject->unpackedFileObject;
    bytesActuallyRead = unpackedFile->readFile(this->dataBufferMemory + this->bufferReadOffset, proposedReadSize);
    bytesActuallyRead = this->sourceFileReadPosition + bytesActuallyRead;
    this->sourceFileReadPosition = bytesActuallyRead;
    this->sourceFileObject->filePointer = bytesActuallyRead;
  }
  byteRead = this->dataBufferMemory[this->bufferReadOffset];
  this->bufferReadOffset++;
  return byteRead;
}
