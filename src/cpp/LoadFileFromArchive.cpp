#include "HazardClasses/UnpackedFile32.hpp"
#include "HazardClasses/UnpackedFile44.hpp"
#include "HazardClasses/UnpackedFile8248.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ArchiveEntry.hpp"
#include "HazardStructs/UnpackedFilePakStruct.hpp"

UnpackedFileBase* __cdecl UnpackedFileBase::LoadFileFromArchive(char* filename, int32_t chunkSize) {

  int32_t fileHandle;
  int32_t comparisonResult;
  int32_t index;
  char fixedSizeFilename[128];
  int8_t isCompressedFlag;
  UnpackedFilePakStruct* archiveListEntry;

  strcpy(fixedSizeFilename, filename);
  for (index = 0; fixedSizeFilename[index] != '\0'; index++) {
    if (fixedSizeFilename[index] == '/') {
      fixedSizeFilename[index] = '\\';
    }
  }
  fileHandle = ReadFileFixedSize(fixedSizeFilename, 0x8000, 0);
  if (fileHandle != -1) {
    return new UnpackedFile32(fileHandle, chunkSize);
  }
  archiveListEntry = GlobalUnpackedFilePakStruct;
  for (; archiveListEntry != nullptr; archiveListEntry = archiveListEntry->previousGlobalAddress) {
    for (index = 0; index < archiveListEntry->numberArchiveEntries; index++) {
      comparisonResult = _strcmpi(filename, archiveListEntry->archiveEntries[index]->name);
      if (comparisonResult == 0) {
        isCompressedFlag = archiveListEntry->archiveEntries[index]->boolean;
        switch (isCompressedFlag) {
        case 0:
          return new UnpackedFile44(archiveListEntry, archiveListEntry->archiveEntries[index], chunkSize);
        case 1:
          return new UnpackedFile8248(archiveListEntry, archiveListEntry->archiveEntries[index], chunkSize);
        }
      }
    }
  }
  return nullptr;
}
