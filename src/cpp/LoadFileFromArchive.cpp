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
  char fixedSizeFilename[20];
  bool isCompressedFlag;
  UnpackedFilePakStruct* archiveListEntry;

  strcpy(fixedSizeFilename, filename);
  fileHandle = ReadFileFixedSize(fixedSizeFilename, 0x8000, 0);
  archiveListEntry = GlobalUnpackedFilePakStruct;
  if (fileHandle != -1) {
    return new UnpackedFile32(fileHandle, chunkSize);
  }
  for (; archiveListEntry != nullptr; archiveListEntry = archiveListEntry->previousGlobalAddress) {
    for (index = 0; index < archiveListEntry->numberArchiveEntries; index++) {
      comparisonResult = _strcmpi(filename, archiveListEntry->archiveEntries[index]->name);
      if (comparisonResult == 0) {
        isCompressedFlag = *(bool*)&archiveListEntry->archiveEntries[index]->boolean;
        if (isCompressedFlag == false) {
          return new UnpackedFile44(archiveListEntry, archiveListEntry->archiveEntries[index], chunkSize);
        }
        if (isCompressedFlag == true) {
          return new UnpackedFile8248(archiveListEntry, archiveListEntry->archiveEntries[index], chunkSize);
        }
      }
    }
  }
  return nullptr;
}
