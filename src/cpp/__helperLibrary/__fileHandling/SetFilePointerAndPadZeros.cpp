#include "HazardGlobals.hpp"
#include "HazardStructs/FileHandleComponent.hpp"
#include "HazardStructs/HandleEntry.hpp"

#pragma optimize("s", on)

int32_t __cdecl SetFilePointerAndPadZeros(uint32_t fileHandle, int32_t targetPosition) {
  int32_t currentPosition;
  int32_t fileSize;
  uint32_t bytesRemaining;
  int32_t bytesWritten;
  HANDLE hFile;
  BOOL setEndResult;
  int32_t returnValue = 0;
  char zeroBuffer[4096];

  if (fileHandle >= uNumber) {
    HandlesUpperValue = 9;
    return -1;
  }

  uint32_t component_index = (int32_t)fileHandle >> 5;
  uint32_t slot_index = fileHandle & 0x1f;
  FileHandleComponent* component = FileHandleComponentAddresses[component_index];
  HandleEntry* entry = &component->entries[slot_index];

  if ((entry->flags & 1) != 0) {
    currentPosition = SetFilePointer(fileHandle, 0, 1);
    if ((currentPosition != -1) && (fileSize = SetFilePointer(fileHandle, 0, 2), fileSize != -1)) {
      bytesRemaining = targetPosition - fileSize;
      if ((int32_t)bytesRemaining < 1) {
        if ((int32_t)bytesRemaining < 0) {
          SetFilePointer(fileHandle, targetPosition, 0);
          hFile = GetIndexedFileHandle(fileHandle);
          setEndResult = SetEndOfFile(hFile);
          returnValue = (setEndResult != 0) - 1;
          if (returnValue == -1) {
            HandlesUpperValue = 0xd;
            HandlesLowerValue = GetLastError();
          }
        }
      }
      else {
        memset(zeroBuffer, 0, 0x1000);
        int32_t textModeFlag = SetFileTextModeFlag(fileHandle, 0x8000);
        do {
          uint32_t chunkSize = 0x1000;
          if ((int32_t)bytesRemaining < 0x1000) {
            chunkSize = bytesRemaining;
          }
          bytesWritten = WriteFileWithTranslation(fileHandle, zeroBuffer, chunkSize);
          if (bytesWritten == -1) {
            if (HandlesLowerValue == 5) {
              HandlesUpperValue = 0xd;
            }
            returnValue = -1;
            break;
          }
          bytesRemaining = bytesRemaining - bytesWritten;
        } while (0 < (int32_t)bytesRemaining);
        SetFileTextModeFlag(fileHandle, textModeFlag);
      }
      SetFilePointer(fileHandle, currentPosition, 0);
      return returnValue;
    }
  }
  else {
    HandlesUpperValue = 9;
  }
  return -1;
}

#pragma optimize("s", off)
