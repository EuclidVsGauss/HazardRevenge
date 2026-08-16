#include "HazardClasses/UnpackedFile44.hpp"
#include "HazardClasses/UnpackedFile8248.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ArchiveEntry.hpp"
#include "HazardStructs/UnpackedFilePakStruct.hpp"

UnpackedFile8248::UnpackedFile8248(UnpackedFilePakStruct* itemToBeLoaded, ArchiveEntry* archiveEntry, int32_t archiveSize) : UnpackedFile44(itemToBeLoaded, archiveEntry, archiveSize) {

  this->currentFilePointer = 0;
  this->decompressedByteCount = 0;
  this->lastDecompressionPointer = 0;
}
