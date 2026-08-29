#ifndef HAZARD_UNPACKEDFILEPAKSTRUCT_HPP
#define HAZARD_UNPACKEDFILEPAKSTRUCT_HPP

#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardTypedef.hpp"

struct ArchiveEntry;

struct UnpackedFilePakStruct {
  int32_t numberArchiveEntries;
  UnpackedFileBase* unpackedFileObject;
  int32_t filePointer;
  int16_t intArray256[256];
  ArchiveEntry** archiveEntries;
  UnpackedFilePakStruct* previousGlobalAddress;
};
typedef struct UnpackedFilePakStruct UnpackedFilePakStruct, *PUnpackedFilePakStruct;

#endif
