#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/UnpackedFile44.hpp"
#include "HazardClasses/UnpackedFile8248.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/UnpackedFilePakStruct.hpp"

int32_t UnpackedFile8248::setFilePointer(int32_t param_1, int32_t param_2) {
  int32_t bytesRead;
  UnpackedFileBase* currentSourceObj;
  byte literalByte;
  uint32_t copyLengthRemaining;
  uint32_t copyLength;
  uint32_t newPosition;
  int32_t bufferAllocationSize;
  uint32_t copySpace;
  int32_t bytesToRead;
  int16_t copyCount;
  int32_t currentDecompressedPos;
  uint16_t copyLength16;
  uint32_t* srcDataPtr;
  byte* destPtr;
  uint32_t* destDataPtr;
  uint32_t writePosition;
  byte* srcBytePtr;
  uint32_t controlBit;
  int32_t bitsRemaining;
  uint32_t zero = 0;

  newPosition = param_1;
  if (param_2 != 0) {
    if (param_2 == 1) {
      newPosition = this->currentFilePointer + param_1;
    }
    else {
      newPosition = zero;
      if (param_2 == 2) {
        newPosition = this->uncompressedDataLength + param_1;
      }
    }
  }
  if (this->uncompressedDataLength < (int32_t)newPosition) {
    newPosition = this->uncompressedDataLength;
  }
  newPosition = (((int32_t)newPosition < 1) - 1) & newPosition;
  if ((int32_t)newPosition < this->lastDecompressionPointer) {
    this->currentFilePointer = 0;
    this->decompressedByteCount = 0;
    UnpackedFile44::setFilePointer(0, 0);
  }
  currentDecompressedPos = this->decompressedByteCount;
  copyLengthRemaining = param_1;
  if ((int32_t)newPosition <= currentDecompressedPos) {
    this->currentFilePointer = newPosition;
    return currentDecompressedPos;
  }
  do {
    this->lastDecompressionPointer = currentDecompressedPos;
    if (this->bufferReadOffset < this->bufferAllocationSize) {
    label_read_control_byte1:
      controlBit = this->dataBufferMemory[this->bufferReadOffset];
      this->bufferReadOffset = this->bufferReadOffset + 1;
    }
    else {
      if (this->sourceFileReadPosition < this->compressedDataSize + this->archiveSegmentStartOffset) {
        this->RefillCompressedBuffer();
        goto label_read_control_byte1;
      }
      controlBit = 0xffffffff;
    }
    bitsRemaining = 8;
    do {
      copyLength16 = (uint16_t)copyLengthRemaining;
      if ((controlBit & 1) != 0) {
        bufferAllocationSize = this->bufferAllocationSize;
        param_2 = 2;
        copyLengthRemaining = (((this->compressedDataSize - this->sourceFileReadPosition) + this->archiveSegmentStartOffset) - this->bufferReadOffset) + bufferAllocationSize;
        if ((int32_t)copyLengthRemaining < 3) {
          param_2 = copyLengthRemaining;
        }
        currentDecompressedPos = 0;
        if (0 < param_2) {
          do {
            if (this->bufferAllocationSize <= this->bufferReadOffset) {
              this->RefillCompressedBuffer();
            }
            bytesRead = this->bufferReadOffset;
            copyLength = this->bufferAllocationSize - bytesRead;
            copyLengthRemaining = param_2 - currentDecompressedPos;
            if ((int32_t)copyLength < (param_2 - currentDecompressedPos)) {
              copyLengthRemaining = copyLength;
            }
            srcDataPtr = (uint32_t*)(bytesRead + (intptr_t)this->dataBufferMemory);
            destDataPtr = (uint32_t*)((intptr_t)&param_1 + currentDecompressedPos);
            for (copyLength = copyLengthRemaining >> 2; copySpace = param_2, copyLength != 0; copyLength = copyLength - 1) {
              *destDataPtr = *srcDataPtr;
              srcDataPtr = srcDataPtr + 1;
              destDataPtr = destDataPtr + 1;
            }
            currentDecompressedPos = currentDecompressedPos + copyLengthRemaining;
            for (copyLength = copyLengthRemaining & 3; copyLength != 0; copyLength = copyLength - 1) {
              *(byte*)destDataPtr = *(byte*)srcDataPtr;
              srcDataPtr = (uint32_t*)((intptr_t)srcDataPtr + 1);
              destDataPtr = (uint32_t*)((intptr_t)destDataPtr + 1);
            }

            this->bufferReadOffset = bytesRead + copyLengthRemaining;
          } while (currentDecompressedPos < (int32_t)copySpace);
          copyLength16 = (uint16_t)param_1;
          bufferAllocationSize = 0;
        }
        copyLengthRemaining = (bufferAllocationSize & 0xffff0000) | ((*(int16_t*)&this->decompressedByteCount - (copyLength16 & 0xfff)) & 0xffff);
        copyLength = (copyLength16 >> 0xc) + 2;
        copyCount = (int16_t)copyLength;
        while (param_1 = copyLengthRemaining, copyCount != 0) {
          writePosition = this->decompressedByteCount & 0x1fff;
          copySpace = 0x2000 - writePosition;
          param_2 = copyLength & 0xffff;
          if ((int32_t)copySpace < (int32_t)(copyLength & 0xffff)) {
            param_2 = copySpace;
          }
          copySpace = 0x2000 - (copyLengthRemaining & 0x1fff);
          if ((int32_t)copySpace < param_2) {
            param_2 = copySpace;
          }
          destPtr = this->decompressedBuffer + (copyLengthRemaining & 0x1fff);
          srcBytePtr = this->decompressedBuffer + writePosition;

          memcpy(srcBytePtr, destPtr, (param_2 & 0xffff));
          copyLength = copyLength - param_2;
          copyLengthRemaining = copyLengthRemaining + param_2;
          this->decompressedByteCount = this->decompressedByteCount + (param_2 & 0xffff);
          copyCount = (int16_t)copyLength;
        }
      }
      else {
        if (this->bufferReadOffset < this->bufferAllocationSize) {
        label_read_literal_byte3:
          literalByte = this->dataBufferMemory[this->bufferReadOffset];
          this->bufferReadOffset = this->bufferReadOffset + 1;
        }
        else {
          currentDecompressedPos = this->sourceFileReadPosition;
          if (currentDecompressedPos < this->archiveSegmentStartOffset + this->compressedDataSize) {
            if (this->sourceFileObject->filePointer != currentDecompressedPos) {
              currentSourceObj = this->sourceFileObject->unpackedFileObject;
              currentSourceObj->setFilePointer(currentDecompressedPos, 0);
            }
            bufferAllocationSize = this->bufferAllocationSize;
            bytesToRead = (this->archiveSegmentStartOffset - this->sourceFileReadPosition) + this->compressedDataSize;
            if (bufferAllocationSize <= bytesToRead) {
              bytesToRead = bufferAllocationSize;
            }
            this->bufferReadOffset = bufferAllocationSize - bytesToRead;
            this->currentSegmentStartPointer = this->sourceFileReadPosition;
            currentSourceObj = this->sourceFileObject->unpackedFileObject;
            currentDecompressedPos = currentSourceObj->readFile((this->dataBufferMemory + (bufferAllocationSize - bytesToRead)), bytesToRead);
            currentDecompressedPos = this->sourceFileReadPosition + currentDecompressedPos;
            this->sourceFileReadPosition = currentDecompressedPos;
            this->sourceFileObject->filePointer = currentDecompressedPos;
            goto label_read_literal_byte3;
          }
          literalByte = 0xff;
        }
        this->decompressedBuffer[this->decompressedByteCount & 0x1fff] = literalByte;
        this->decompressedByteCount = this->decompressedByteCount + 1;
      }
      controlBit = controlBit >> 1 & 0x7fff;
      bitsRemaining = bitsRemaining + -1;
    } while (bitsRemaining != 0);
    if (this->uncompressedDataLength < this->decompressedByteCount) {
      this->decompressedByteCount = this->uncompressedDataLength;
    }
    currentDecompressedPos = this->decompressedByteCount;
    if ((int32_t)newPosition <= currentDecompressedPos) {
      this->currentFilePointer = newPosition;
      return currentDecompressedPos;
    }
  } while (true);
}
