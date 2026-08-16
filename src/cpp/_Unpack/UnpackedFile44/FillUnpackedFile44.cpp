#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/UnpackedFile44.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ArchiveEntry.hpp"
#include "HazardStructs/UnpackedFilePakStruct.hpp"

UnpackedFile44::UnpackedFile44(UnpackedFilePakStruct* itemToBeLoaded, ArchiveEntry* archiveEntry, int32_t chunkSize) {
  UnpackedFileBase* innerFileObject;
  int32_t remainingInSegment;
  int32_t totalUncompressedSize;
  int32_t bytesToReadFromFile;

  this->sourceFileObject = itemToBeLoaded;
  this->archiveEntryMetadata = archiveEntry;
  totalUncompressedSize = archiveEntry->uncompressedLength;
  this->bufferReadOffset = 0;
  this->uncompressedDataLength = totalUncompressedSize;
  this->currentSegmentStartPointer = archiveEntry->start;
  this->archiveSegmentStartOffset = archiveEntry->start;
  this->sourceFileReadPosition = archiveEntry->start;
  this->compressedDataSize = archiveEntry->compressedLength;
  this->bufferAllocationSize = chunkSize;
  this->dataBufferMemory = (byte*)malloc(chunkSize);
  totalUncompressedSize = this->sourceFileReadPosition;
  if (totalUncompressedSize < this->compressedDataSize + this->archiveSegmentStartOffset) {
    if (this->sourceFileObject->filePointer != totalUncompressedSize) {
      innerFileObject = this->sourceFileObject->unpackedFileObject;
      innerFileObject->setFilePointer(totalUncompressedSize, 0);
    }
    bytesToReadFromFile = (this->compressedDataSize - this->sourceFileReadPosition) + this->archiveSegmentStartOffset;
    remainingInSegment = this->bufferAllocationSize;
    if (remainingInSegment <= bytesToReadFromFile) {
      bytesToReadFromFile = remainingInSegment;
    }
    this->bufferReadOffset = remainingInSegment - bytesToReadFromFile;
    this->currentSegmentStartPointer = this->sourceFileReadPosition;
    innerFileObject = this->sourceFileObject->unpackedFileObject;
    totalUncompressedSize = innerFileObject->readFile((this->dataBufferMemory + (remainingInSegment - bytesToReadFromFile)), bytesToReadFromFile);
    totalUncompressedSize = this->sourceFileReadPosition + totalUncompressedSize;
    this->sourceFileReadPosition = totalUncompressedSize;
    this->sourceFileObject->filePointer = totalUncompressedSize;
  }
  else {
    this->bufferReadOffset = this->bufferAllocationSize;
  }
}
