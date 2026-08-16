#include <windows.h>
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardClasses/UnpackedFileTiny.hpp"
#include "HazardGlobals.hpp"

void __fastcall ProcessPakFile(char* pakFilename) {
  int32_t fileHandle;
  UnpackedFileTiny* pakFileTiny;
  UnpackedFileBase* pakFileLarge;

  fileHandle = ReadFileFixedSize(pakFilename, 0x8000, 0);
  if (fileHandle != -1) {
    pakFileTiny = new UnpackedFileTiny();
    if (pakFileTiny != nullptr) {
      pakFileTiny->fileHandleIndex = fileHandle;
      UnpackedFileBase::LoadAndClosePak(pakFileTiny);
      return;
    }
    UnpackedFileBase::LoadAndClosePak((UnpackedFileTiny*)nullptr);
    return;
  }
  else {
    pakFileLarge = UnpackedFileBase::LoadFileFromArchive(pakFilename, 0x20000);
    if (pakFileLarge != nullptr) {
      UnpackedFileBase::LoadAndClosePak(pakFileLarge);
    }
    return;
  }
}
