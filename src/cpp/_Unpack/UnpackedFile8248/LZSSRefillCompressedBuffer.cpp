#include "HazardClasses/UnpackedFile44.hpp"
#include "HazardClasses/UnpackedFile8248.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/UnpackedFilePakStruct.hpp"

void UnpackedFile8248::RefillCompressedBuffer() {
  UnpackedFileBase* fileObject;
  int32_t allocationSize;
  int32_t currentReadPosition;
  int32_t bytesRemainingToRead;

  currentReadPosition = this->sourceFileReadPosition;
  if (currentReadPosition < this->archiveSegmentStartOffset + this->compressedDataSize) {
    if (this->sourceFileObject->filePointer != currentReadPosition) {
      fileObject = this->sourceFileObject->unpackedFileObject;
      fileObject->setFilePointer(currentReadPosition, 0);
    }
    bytesRemainingToRead = (this->archiveSegmentStartOffset - this->sourceFileReadPosition) + this->compressedDataSize;
    allocationSize = this->bufferAllocationSize;
    bytesRemainingToRead = allocationSize <= bytesRemainingToRead ? allocationSize : bytesRemainingToRead;
    this->bufferReadOffset = allocationSize - bytesRemainingToRead;
    this->currentSegmentStartPointer = this->sourceFileReadPosition;
    fileObject = this->sourceFileObject->unpackedFileObject;
    currentReadPosition = fileObject->readFile(this->dataBufferMemory + this->bufferReadOffset, bytesRemainingToRead);
    currentReadPosition = this->sourceFileReadPosition + currentReadPosition;
    this->sourceFileReadPosition = currentReadPosition;
    this->sourceFileObject->filePointer = currentReadPosition;
    return;
  }
  this->bufferReadOffset = this->bufferAllocationSize;
}
