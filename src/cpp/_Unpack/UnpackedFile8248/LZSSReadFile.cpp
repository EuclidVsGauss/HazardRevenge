#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/UnpackedFile44.hpp"
#include "HazardClasses/UnpackedFile8248.hpp"
#include "HazardGlobals.hpp"

int32_t UnpackedFile8248::readFile(void* destBuffer, int32_t bytesRequested) {
  byte literalByte;
  int32_t remainingToCopy;
  uint32_t destUpperBound;
  uint32_t copySize;
  uint32_t destBufferOffset;
  int32_t currentBitStream;
  int32_t bitCount;
  int32_t bytesCopied;

  remainingToCopy = this->uncompressedDataLength - this->currentFilePointer;
  if (remainingToCopy <= bytesRequested) {
    bytesRequested = remainingToCopy;
  }

  bytesCopied = 0;
  if (bytesRequested > 0) {
    do {
      remainingToCopy = bytesCopied;
      if (this->decompressedByteCount <= this->currentFilePointer) {
        this->lastDecompressionPointer = this->decompressedByteCount;

        if (this->bufferReadOffset < this->bufferAllocationSize) {
        label_read_control_byte3:
          currentBitStream = (int32_t)*(byte*)((intptr_t)this->dataBufferMemory + this->bufferReadOffset);
          this->bufferReadOffset = this->bufferReadOffset + 1;
        }
        else {
          if (this->sourceFileReadPosition < this->compressedDataSize + this->archiveSegmentStartOffset) {
            this->RefillCompressedBuffer();
            goto label_read_control_byte3;
          }
          currentBitStream = 0xffffffff;
        }

        bitCount = 8;
        do {
          if ((currentBitStream & 1U) != 0) {
            int32_t matchHeader;
            UnpackedFile44::readFile(&matchHeader, 2);
            int32_t matchLength = ((matchHeader >> 12) & 0xf) + 2;
            int32_t matchDistance = matchHeader & 0xfff;

            int32_t destPos = this->decompressedByteCount & 0x1fff;
            int32_t srcPos = (this->decompressedByteCount - matchDistance) & 0x1fff;

            int32_t remainingInMatch = matchLength;
            while (remainingInMatch > 0) {
              int32_t maxChunkSize = 0x2000 - destPos;
              if (maxChunkSize > 0x2000 - srcPos) {
                maxChunkSize = 0x2000 - srcPos;
              }
              if (maxChunkSize > remainingInMatch) {
                maxChunkSize = remainingInMatch;
              }

              memcpy(this->decompressedBuffer + destPos,
                     this->decompressedBuffer + srcPos,
                     maxChunkSize);

              destPos = (destPos + maxChunkSize) & 0x1fff;
              srcPos = (srcPos + maxChunkSize) & 0x1fff;
              remainingInMatch -= maxChunkSize;
              remainingToCopy = bytesCopied;
            }
            this->decompressedByteCount += matchLength;
          }
          else {
            if (this->bufferReadOffset < this->bufferAllocationSize) {
            label_read_literal_byte1:
              literalByte = *(byte*)((intptr_t)this->dataBufferMemory + this->bufferReadOffset);
              this->bufferReadOffset = this->bufferReadOffset + 1;
            }
            else {
              if (this->sourceFileReadPosition < this->compressedDataSize + this->archiveSegmentStartOffset) {
                this->RefillCompressedBuffer();
                goto label_read_literal_byte1;
              }
              literalByte = 0xff;
            }
            this->decompressedBuffer[this->decompressedByteCount & 0x1fff] = literalByte;
            this->decompressedByteCount = this->decompressedByteCount + 1;
          }
          currentBitStream = currentBitStream >> 1;
          bitCount = bitCount + -1;
        } while (bitCount != 0);
        bitCount = 0;
        if (this->uncompressedDataLength < this->decompressedByteCount) {
          this->decompressedByteCount = this->uncompressedDataLength;
        }
      }
      destUpperBound = this->decompressedByteCount - this->currentFilePointer;
      if (bytesRequested - remainingToCopy <= (int32_t)destUpperBound) {
        destUpperBound = bytesRequested - remainingToCopy;
      }
      destBufferOffset = this->currentFilePointer & 0x1fff;
      copySize = 0x2000 - destBufferOffset;
      if ((int32_t)destUpperBound <= (int32_t)copySize) {
        copySize = destUpperBound;
      }

      memcpy(remainingToCopy + (byte*)destBuffer, this->decompressedBuffer + destBufferOffset, copySize);
      bytesCopied = remainingToCopy + copySize;

      this->currentFilePointer = this->currentFilePointer + copySize;
      if (bytesRequested <= bytesCopied) {
        return bytesCopied;
      }
    } while (true);
  }
  return 0;
}
