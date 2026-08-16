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
  if (0 < bytesToRead) {
    do {
      chunkRemaining = this->chunkBufferSize;
      if (chunkRemaining <= this->chunkOffset) {
        newBytesRead = this->bytesReadCumulative;
        if (newBytesRead < this->fileStartOffset) {
          nBytesToRead = this->fileStartOffset - newBytesRead;
          if (chunkRemaining < nBytesToRead) {
            nBytesToRead = chunkRemaining;
          }
          this->chunkOffset = chunkRemaining - nBytesToRead;
          this->lastReadOffset = newBytesRead;
          chunkRemaining = ReadFileWithTranslation(this->fileHandleId, (byte*)((chunkRemaining - nBytesToRead) + (intptr_t)this->cachedFileDataBuffer), nBytesToRead);
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
    } while (bytesCopied < bytesToRead);
  }
  return bytesCopied;
}
