#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/UnpackedFile44.hpp"
#include "HazardClasses/UnpackedFile8248.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/UnpackedFilePakStruct.hpp"

int32_t UnpackedFile8248::readByte() {
  int32_t filePosDifference;
  UnpackedFileBase* unpackedObject;
  int32_t copyOffset;
  byte literalByte;
  int32_t loopCounter;
  uint32_t decompressedOffset;
  int32_t bufferSizeCheck;
  uint32_t copyWindowSpace;
  int32_t bytesToRead;
  int16_t copyLength16;
  uint16_t copyLength16u;
  byte* sourcePtr;
  byte* windowSourcePtr;
  uint32_t windowReadPosition;
  byte* destinationPtr;
  uint32_t windowWritePosition;
  byte* windowDestinationPtr;
  uint32_t commandBuffer[2] = {0};
  byte bitFlag;
  uint32_t copySize;
  int32_t bitCount;

  if (this->currentFilePointer < this->decompressedByteCount) {
    goto label_return_decompressed_byte;
  }
  if (this->uncompressedDataLength <= this->currentFilePointer) {
    return -1;
  }
  this->lastDecompressionPointer = this->decompressedByteCount;

  if (this->bufferReadOffset < this->bufferAllocationSize) {
  label_read_control_byte2:
    bitFlag = this->dataBufferMemory[this->bufferReadOffset];
    this->bufferReadOffset = this->bufferReadOffset + 1;
  }
  else {
    if (this->sourceFileReadPosition < this->compressedDataSize + this->archiveSegmentStartOffset) {
      this->RefillCompressedBuffer();
      goto label_read_control_byte2;
    }
    bitFlag = 0xff;
  }

  windowReadPosition = commandBuffer[0];
  for (bitCount = 0; bitCount < 8; bitCount++) {
    copyLength16u = (uint16_t)windowReadPosition;
    if ((bitFlag & 1) != 0) {
      bufferSizeCheck = this->bufferAllocationSize;
      commandBuffer[1] = 2;
      loopCounter = (((this->compressedDataSize - this->sourceFileReadPosition) + this->archiveSegmentStartOffset) - this->bufferReadOffset) + bufferSizeCheck;
      if (loopCounter < 3) {
        commandBuffer[1] = loopCounter;
      }
      loopCounter = 0;
      if (0 < (int32_t)commandBuffer[1]) {
        do {
          if (this->bufferAllocationSize <= this->bufferReadOffset) {
            this->RefillCompressedBuffer();
          }
          filePosDifference = this->bufferReadOffset;
          decompressedOffset = this->bufferAllocationSize - filePosDifference;
          windowReadPosition = commandBuffer[1] - loopCounter;
          if ((int32_t)decompressedOffset < (int32_t)(commandBuffer[1] - loopCounter)) {
            windowReadPosition = decompressedOffset;
          }
          sourcePtr = this->dataBufferMemory + filePosDifference;
          destinationPtr = (byte*)((intptr_t)commandBuffer + loopCounter);
          copyOffset = commandBuffer[1];
          loopCounter = loopCounter + windowReadPosition;
          memcpy(destinationPtr, sourcePtr, windowReadPosition);

          this->bufferReadOffset = filePosDifference + windowReadPosition;
        } while (loopCounter < copyOffset);
        copyLength16u = (uint16_t)commandBuffer[0];
        bufferSizeCheck = 0;
      }
      windowReadPosition = (bufferSizeCheck & 0xffff0000) | ((*(int16_t*)&this->decompressedByteCount - (copyLength16u & 0xfff)) & 0xffff);
      decompressedOffset = (copyLength16u >> 0xc) + 2;
      copyLength16 = (int16_t)decompressedOffset;
      while (commandBuffer[0] = windowReadPosition, copyLength16 != 0) {
        windowWritePosition = this->decompressedByteCount & 0x1fff;
        copyWindowSpace = 0x2000 - windowWritePosition;
        copySize = decompressedOffset & 0xffff;
        if ((int32_t)copyWindowSpace < (int32_t)(decompressedOffset & 0xffff)) {
          copySize = copyWindowSpace;
        }
        copyWindowSpace = 0x2000 - (windowReadPosition & 0x1fff);
        if ((int32_t)copyWindowSpace < (int32_t)copySize) {
          copySize = copyWindowSpace;
        }
        windowSourcePtr = this->decompressedBuffer + (windowReadPosition & 0x1fff);
        windowDestinationPtr = this->decompressedBuffer + windowWritePosition;

        memcpy(windowDestinationPtr, windowSourcePtr, (copySize & 0xffff));
        decompressedOffset = decompressedOffset - copySize;
        windowReadPosition = windowReadPosition + copySize;
        this->decompressedByteCount = this->decompressedByteCount + (copySize & 0xffff);
        copyLength16 = (int16_t)decompressedOffset;
      }
    }
    else {
      if (this->bufferReadOffset < this->bufferAllocationSize) {
      label_read_literal_byte2:
        literalByte = this->dataBufferMemory[this->bufferReadOffset];
        this->bufferReadOffset = this->bufferReadOffset + 1;
      }
      else {
        loopCounter = this->sourceFileReadPosition;
        if (loopCounter < this->archiveSegmentStartOffset + this->compressedDataSize) {
          if (this->sourceFileObject->filePointer != loopCounter) {
            unpackedObject = this->sourceFileObject->unpackedFileObject;
            unpackedObject->setFilePointer(loopCounter, 0);
          }
          bufferSizeCheck = this->bufferAllocationSize;
          bytesToRead = (this->archiveSegmentStartOffset - this->sourceFileReadPosition) + this->compressedDataSize;
          if (bufferSizeCheck <= bytesToRead) {
            bytesToRead = bufferSizeCheck;
          }
          this->bufferReadOffset = bufferSizeCheck - bytesToRead;
          this->currentSegmentStartPointer = this->sourceFileReadPosition;
          unpackedObject = this->sourceFileObject->unpackedFileObject;
          loopCounter = unpackedObject->readFile((this->dataBufferMemory + (bufferSizeCheck - bytesToRead)), bytesToRead);
          loopCounter = this->sourceFileReadPosition + loopCounter;
          this->sourceFileReadPosition = loopCounter;
          this->sourceFileObject->filePointer = loopCounter;
          goto label_read_literal_byte2;
        }
        literalByte = 0xff;
      }
      this->decompressedBuffer[this->decompressedByteCount & 0x1fff] = literalByte;
      this->decompressedByteCount = this->decompressedByteCount + 1;
    }
    bitFlag = bitFlag >> 1;
  }
  if (this->uncompressedDataLength < this->decompressedByteCount) {
    this->decompressedByteCount = this->uncompressedDataLength;
  }
label_return_decompressed_byte:
  literalByte = this->decompressedBuffer[this->currentFilePointer & 0x1fff];
  this->currentFilePointer = this->currentFilePointer + 1;
  return literalByte;
}
