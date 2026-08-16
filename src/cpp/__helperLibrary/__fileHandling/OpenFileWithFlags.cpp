#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/FileHandleComponent.hpp"
#include "HazardStructs/HandleEntry.hpp"

#pragma optimize("s", on)

int32_t __cdecl OpenFileWithFlags(char* filename, uint32_t largeSize, uint32_t size64, uint32_t zero) {
  int32_t returnValue;
  HANDLE hFile;
  DWORD fileTypeInt;
  int32_t filePointerResult;
  int32_t readTranslationResult;
  bool isSizeNot128_pakTrue;
  SECURITY_ATTRIBUTES securityAttributes;
  DWORD shareMode;
  DWORD desiredAccess;
  DWORD creationDisposition;
  uint8_t fileFlags;

  isSizeNot128_pakTrue = (largeSize & 128) == 0;
  securityAttributes.nLength = 0xc;
  securityAttributes.lpSecurityDescriptor = (LPVOID) nullptr;
  fileFlags = isSizeNot128_pakTrue ? 0 : 0x10;
  securityAttributes.bInheritHandle = (BOOL)isSizeNot128_pakTrue;
  if (((largeSize & 0x8000) == 0) && ((largeSize & 0x4000) != 0 || (ReadFileFlag != 0x8000))) {
    fileFlags |= 0x80;
  }
  returnValue = largeSize & 3;
  if (returnValue == 0) {
    desiredAccess = GENERIC_READ;
  }
  else if (returnValue == 1) {
    desiredAccess = GENERIC_WRITE;
  }
  else if (returnValue == 2) {
    desiredAccess = GENERIC_READ | GENERIC_WRITE;
  }
  else {
    HandlesUpperValue = 0x16;
    HandlesLowerValue = 0;
    return -1;
  }

  if (size64 == 0x10) {
    shareMode = 0;
  }
  else if (size64 == 32) {
    shareMode = 1;
  }
  else if (size64 == 48) {
    shareMode = 2;
  }
  else if (size64 == 64) {
    shareMode = 3;
  }
  else {
    HandlesUpperValue = 0x16;
    HandlesLowerValue = 0;
    return -1;
  }

  returnValue = largeSize & 0x700;
  if (returnValue <= 0x400) {
    if (returnValue == 0x400 || returnValue == 0) {
      creationDisposition = OPEN_ALWAYS;
    }
    else if (returnValue == 0x100) {
      creationDisposition = TRUNCATE_EXISTING;
    }
    else if (returnValue == 0x200) {
      creationDisposition = OPEN_EXISTING;
    }
    else if (returnValue == 0x300) {
      creationDisposition = CREATE_ALWAYS;
    }
    else {
      HandlesUpperValue = 0x16;
      HandlesLowerValue = 0;
      return -1;
    }
  }
  else {

    creationDisposition = CREATE_NEW;
  }

  fileTypeInt = FILE_ATTRIBUTE_NORMAL;
  if (((largeSize & 0x100) != 0) && ((~ReadFileRelated & zero & 0x80) == 0)) {
    fileTypeInt = FILE_ATTRIBUTE_TEMPORARY;
  }
  if ((largeSize & 64) != 0) {
    fileTypeInt |= FILE_FLAG_OVERLAPPED;
  }
  if ((largeSize & 0x1000) != 0) {
    fileTypeInt |= FILE_FLAG_SEQUENTIAL_SCAN;
  }
  if ((largeSize & 32) == 0) {
    if ((largeSize & 16) != 0) {
      fileTypeInt |= FILE_FLAG_WRITE_THROUGH;
    }
  }
  else {
    fileTypeInt |= FILE_FLAG_RANDOM_ACCESS;
  }

  returnValue = AllocateFileHandleSlot();
  if (returnValue == -1) {
    HandlesLowerValue = 0;
    HandlesUpperValue = 0x18;
    return -1;
  }

  hFile = CreateFileA(filename, desiredAccess, shareMode, &securityAttributes, creationDisposition, fileTypeInt, nullptr);
  if (hFile == INVALID_HANDLE_VALUE) {
    DWORD error = GetLastError();
    MapErrorCode(error);
    return -1;
  }

  fileTypeInt = GetFileType(hFile);
  if (fileTypeInt == FILE_TYPE_UNKNOWN) {
    CloseHandle(hFile);
    DWORD error = GetLastError();
    MapErrorCode(error);
    return -1;
  }

  if (fileTypeInt == FILE_TYPE_DISK) {
    fileFlags |= 0x40;
  }
  else if (fileTypeInt == FILE_TYPE_CHAR) {
    fileFlags |= 8;
  }

  SetStdHandle_(returnValue, hFile);

  FileHandleComponent* component = FileHandleComponentAddresses[returnValue >> 5];
  HandleEntry* entry = &component->entries[returnValue & 0x1f];
  entry->flags = fileFlags | 1;

  if ((((fileFlags & 0x48) == 0) && ((fileFlags & 0x80) != 0)) && ((largeSize & 2) != 0)) {
    filePointerResult = SetFilePointer(returnValue, -1, 2);
    if (filePointerResult == -1) {
      if (HandlesLowerValue != 131) {
        WrapperCloseFileHandle(returnValue);
        return -1;
      }
    }
    else {
      size64 = size64 & 0xffffff;
      readTranslationResult = ReadFileWithTranslation(returnValue, (byte*)((uintptr_t)&size64 + 3), 1);
      if ((((readTranslationResult == 0) && ((byte)size64 == 0x1a)) && (filePointerResult = SetFilePointerAndPadZeros(returnValue, filePointerResult), filePointerResult == -1)) || (filePointerResult = SetFilePointer(returnValue, 0, 0), filePointerResult == -1)) {
        WrapperCloseFileHandle(returnValue);
        return -1;
      }
    }
  }

  if (filename[0] != 0) {
    return returnValue;
  }

  if ((largeSize & 8) != 0) {
    entry->flags |= 0x20;
    return returnValue;
  }

  return returnValue;
}

#pragma optimize("s", off)
