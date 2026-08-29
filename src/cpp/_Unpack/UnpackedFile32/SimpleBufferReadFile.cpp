#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/UnpackedFile32.hpp"
#include "HazardGlobals.hpp"

int32_t UnpackedFile32::readFile(void* buffer, int32_t bytesToRead) {
  int32_t bytesCopied;
  int32_t newBytesRead;
  int32_t chunkRemaining;
  int32_t bytesAvailable;
  int32_t nBytesToRead;
  int32_t remainingBytesToCopy;

  bytesAvailable = ((this->fileStartOffset - this->chunkOffset) - this->bytesReadCumulative) + this->chunkBufferSize;
  if (bytesAvailable <= bytesToRead) {
    bytesToRead = bytesAvailable;
  }

  bytesCopied = 0;
  while (bytesCopied < bytesToRead) {
    chunkRemaining = this->chunkBufferSize;
    if (this->chunkOffset >= chunkRemaining) {
      newBytesRead = this->bytesReadCumulative;
      if (newBytesRead < this->fileStartOffset) {
        nBytesToRead = this->fileStartOffset - newBytesRead;
        if (nBytesToRead > chunkRemaining) {
          nBytesToRead = chunkRemaining;
        }
        int32_t diff = chunkRemaining - nBytesToRead;
        this->chunkOffset = diff;
        this->lastReadOffset = newBytesRead;
        chunkRemaining = ReadFileWithTranslation(this->fileHandleId, &this->cachedFileDataBuffer[diff], nBytesToRead);
        this->bytesReadCumulative = this->bytesReadCumulative + chunkRemaining;
      }
      else {
        this->chunkOffset = chunkRemaining;
      }
    }
    remainingBytesToCopy = this->chunkBufferSize - this->chunkOffset;
    if (bytesToRead - bytesCopied <= remainingBytesToCopy) {
      remainingBytesToCopy = bytesToRead - bytesCopied;
    }
    memcpy((byte*)buffer + bytesCopied, this->cachedFileDataBuffer + this->chunkOffset, remainingBytesToCopy);
    bytesCopied = bytesCopied + remainingBytesToCopy;
    this->chunkOffset = this->chunkOffset + remainingBytesToCopy;
  }
  return bytesCopied;
}
