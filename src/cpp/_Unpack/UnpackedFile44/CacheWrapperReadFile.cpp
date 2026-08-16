#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/UnpackedFile44.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/UnpackedFilePakStruct.hpp"

int32_t UnpackedFile44::readFile(void* destBuffer, int32_t requestedBytes) {
  UnpackedFileBase* unpackedFile;
  int32_t bufferAllocSize;
  int32_t totalBytesRead;
  int32_t sourcePos;
  int32_t bytesAvailable;
  int32_t bytesRequested;

  totalBytesRead = ((this->compressedDataSize - this->bufferReadOffset) - this->sourceFileReadPosition) + this->archiveSegmentStartOffset + this->bufferAllocationSize;
  if (totalBytesRead <= requestedBytes) {
    requestedBytes = totalBytesRead;
  }

  for (totalBytesRead = 0; totalBytesRead < requestedBytes; totalBytesRead = totalBytesRead + bytesAvailable) {
    if (this->bufferReadOffset >= this->bufferAllocationSize) {
      sourcePos = this->sourceFileReadPosition;
      if (sourcePos < this->archiveSegmentStartOffset + this->compressedDataSize) {
        if (this->sourceFileObject->filePointer != sourcePos) {
          unpackedFile = this->sourceFileObject->unpackedFileObject;
          unpackedFile->setFilePointer(sourcePos, 0);
        }
        bufferAllocSize = this->bufferAllocationSize;
        bytesRequested = (this->compressedDataSize - this->sourceFileReadPosition) + this->archiveSegmentStartOffset;
        if (bufferAllocSize <= bytesRequested) {
          bytesRequested = bufferAllocSize;
        }
        this->bufferReadOffset = bufferAllocSize - bytesRequested;
        this->currentSegmentStartPointer = this->sourceFileReadPosition;
        unpackedFile = this->sourceFileObject->unpackedFileObject;
        sourcePos = unpackedFile->readFile((this->dataBufferMemory + (bufferAllocSize - bytesRequested)), bytesRequested);
        sourcePos = this->sourceFileReadPosition + sourcePos;
        this->sourceFileReadPosition = sourcePos;
        this->sourceFileObject->filePointer = sourcePos;
      }
      else {
        this->bufferReadOffset = this->bufferAllocationSize;
      }
    }
    bytesAvailable = this->bufferAllocationSize - this->bufferReadOffset;
    if (requestedBytes - totalBytesRead <= bytesAvailable) {
      bytesAvailable = requestedBytes - totalBytesRead;
    }

    memcpy((byte*)destBuffer + totalBytesRead, this->dataBufferMemory + this->bufferReadOffset, bytesAvailable);
    this->bufferReadOffset = this->bufferReadOffset + bytesAvailable;
  }
  return totalBytesRead;
}
