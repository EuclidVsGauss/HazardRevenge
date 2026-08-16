#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/UnpackedFile44.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/UnpackedFilePakStruct.hpp"

int32_t UnpackedFile44::readByte() {
  byte byteRead;
  UnpackedFileBase* unpackedFile;
  int32_t allocationSize;
  int32_t bytesActuallyRead;
  int32_t proposedReadSize;

  if (this->bufferAllocationSize <= this->bufferReadOffset) {
    bytesActuallyRead = this->sourceFileReadPosition;
    if (this->compressedDataSize + this->archiveSegmentStartOffset <= bytesActuallyRead) {
      return 0xffffffff;
    }
    if (this->sourceFileObject->filePointer != bytesActuallyRead) {
      unpackedFile = this->sourceFileObject->unpackedFileObject;
      unpackedFile->setFilePointer(bytesActuallyRead, 0);
    }
    proposedReadSize = (this->compressedDataSize - this->sourceFileReadPosition) + this->archiveSegmentStartOffset;
    allocationSize = this->bufferAllocationSize;
    if (allocationSize <= proposedReadSize) {
      proposedReadSize = allocationSize;
    }
    this->bufferReadOffset = allocationSize - proposedReadSize;
    this->currentSegmentStartPointer = this->sourceFileReadPosition;
    unpackedFile = this->sourceFileObject->unpackedFileObject;
    bytesActuallyRead = unpackedFile->readFile((this->dataBufferMemory + (allocationSize - proposedReadSize)), proposedReadSize);
    bytesActuallyRead = this->sourceFileReadPosition + bytesActuallyRead;
    this->sourceFileReadPosition = bytesActuallyRead;
    this->sourceFileObject->filePointer = bytesActuallyRead;
  }
  byteRead = *(byte*)((intptr_t)this->dataBufferMemory + this->bufferReadOffset);
  this->bufferReadOffset = this->bufferReadOffset + 1;
  return (int32_t)byteRead;
}
