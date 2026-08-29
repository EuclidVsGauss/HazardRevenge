#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/UnpackedFile44.hpp"
#include "HazardClasses/UnpackedFile8248.hpp"
#include "HazardGlobals.hpp"

int32_t UnpackedFile8248::readFile(void* destBuffer, int32_t bytesRequested) {
  int32_t literalByte;
  int32_t remainingInFile;
  int32_t destUpperBound;
  int32_t copySize;
  int32_t destBufferOffset;
  uint16_t currentBitStream;
  int32_t bitCount;
  int32_t bytesCopied;

  remainingInFile = this->uncompressedDataLength - this->currentFilePointer;
  if (remainingInFile <= bytesRequested) {
    bytesRequested = remainingInFile;
  }

  bytesCopied = 0;
  if (bytesRequested > 0) {
    do {
      if (this->currentFilePointer >= this->decompressedByteCount) {
        this->lastDecompressionPointer = this->decompressedByteCount;

        if (this->bufferReadOffset < this->bufferAllocationSize) {
        label_read_control_byte:
          currentBitStream = *(byte*)((intptr_t)this->dataBufferMemory + this->bufferReadOffset);
          this->bufferReadOffset = this->bufferReadOffset + 1;
        }
        else if (this->sourceFileReadPosition >= this->compressedDataSize + this->archiveSegmentStartOffset) {
          currentBitStream = 0xffff;
        }
        else {
          this->RefillCompressedBuffer();
          goto label_read_control_byte;
        }

        bitCount = 8;
        do {
          if ((currentBitStream & 1) != 0) {
            int32_t matchHeader;
            UnpackedFile44::readFile(&matchHeader, 2);
            uint16_t matchLength = ((uint16_t)matchHeader >> 12) + 2;
            uint16_t matchSource = (uint16_t)this->decompressedByteCount - (matchHeader & 0xfff);

            while (matchLength > 0) {
              int32_t destPos = this->decompressedByteCount & 0x1fff;
              int32_t chunkSize = matchLength;
              if (chunkSize > 0x2000 - destPos) {
                chunkSize = 0x2000 - destPos;
              }
              int32_t srcPos = matchSource & 0x1fff;
              if (chunkSize > 0x2000 - srcPos) {
                chunkSize = 0x2000 - srcPos;
              }

              memcpy(this->decompressedBuffer + destPos, this->decompressedBuffer + srcPos, chunkSize);

              this->decompressedByteCount = this->decompressedByteCount + chunkSize;
              matchSource = matchSource + chunkSize;
              matchLength = matchLength - chunkSize;
            }
          }
          else {
            if (this->bufferReadOffset < this->bufferAllocationSize) {
            label_read_literal_byte:
              literalByte = *(byte*)((intptr_t)this->dataBufferMemory + this->bufferReadOffset);
              this->bufferReadOffset = this->bufferReadOffset + 1;
            }
            else if (this->sourceFileReadPosition >= this->compressedDataSize + this->archiveSegmentStartOffset) {
              literalByte = -1;
            }
            else {
              this->RefillCompressedBuffer();
              goto label_read_literal_byte;
            }
            this->decompressedBuffer[this->decompressedByteCount & 0x1fff] = (byte)literalByte;
            this->decompressedByteCount = this->decompressedByteCount + 1;
          }
          currentBitStream = currentBitStream >> 1;
          bitCount = bitCount + -1;
        } while (bitCount != 0);
        if (this->decompressedByteCount > this->uncompressedDataLength) {
          this->decompressedByteCount = this->uncompressedDataLength;
        }
      }
      destUpperBound = this->decompressedByteCount - this->currentFilePointer;
      if (bytesRequested - bytesCopied <= destUpperBound) {
        destUpperBound = bytesRequested - bytesCopied;
      }
      destBufferOffset = this->currentFilePointer & 0x1fff;
      copySize = 0x2000 - destBufferOffset;
      if (destUpperBound <= copySize) {
        copySize = destUpperBound;
      }

      memcpy(bytesCopied + (byte*)destBuffer, this->decompressedBuffer + destBufferOffset, copySize);
      bytesCopied = bytesCopied + copySize;

      this->currentFilePointer = this->currentFilePointer + copySize;
    } while (bytesCopied < bytesRequested);
  }
  return bytesCopied;
}
