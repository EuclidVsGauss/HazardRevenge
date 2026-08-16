#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ArchiveEntry.hpp"
#include "HazardStructs/UnpackedFilePakStruct.hpp"

void __fastcall UnpackedFileBase::LoadAndClosePak(UnpackedFileBase* param_1) {
  UnpackedFilePakStruct* pakStruct;
  ArchiveEntry** archiveEntryPtr;
  ArchiveEntry* archiveEntries;
  int32_t entryIndex;
  int32_t entryCounter;
  int16_t* hashTableArray;
  int32_t archiveOffset;
  byte nameLength;

  entryCounter = 0;
  nameLength = 0;
  if (param_1 != nullptr) {
    pakStruct = (UnpackedFilePakStruct*)malloc(sizeof(UnpackedFilePakStruct));
    hashTableArray = pakStruct->intArray256;
    for (entryIndex = 256; entryIndex != 0; entryIndex = entryIndex + -1) {
      *hashTableArray = -1;
      hashTableArray = hashTableArray + 1;
    }
    param_1->setFilePointer(-9, 2);
    param_1->readFile(&archiveOffset, 4);
    param_1->readFile(&pakStruct->numberArchiveEntries, 4);
    if (pakStruct->numberArchiveEntries < 1) {
      free(pakStruct);
      return;
    }
    archiveEntryPtr = (ArchiveEntry**)malloc(pakStruct->numberArchiveEntries * sizeof(ArchiveEntry*));
    pakStruct->archiveEntries = archiveEntryPtr;
    entryIndex = param_1->getFilePointer();

    int32_t malloc_size = entryIndex + -8 + ((pakStruct->numberArchiveEntries * 6) - archiveOffset);
    archiveEntries = (ArchiveEntry*)malloc(malloc_size);
    *pakStruct->archiveEntries = archiveEntries;
    param_1->setFilePointer(archiveOffset, 0);

    for (archiveOffset = 0; entryCounter < pakStruct->numberArchiveEntries; entryCounter++) {
      pakStruct->archiveEntries[entryCounter] = (ArchiveEntry*)((*pakStruct->archiveEntries)->name + archiveOffset + -0x10);
      param_1->readFile(&nameLength, 1);
      param_1->readFile((&pakStruct->archiveEntries[entryCounter]->boolean), 1);
      param_1->readFile((&pakStruct->archiveEntries[entryCounter]->start), 4);
      param_1->readFile((&pakStruct->archiveEntries[entryCounter]->compressedLength), 4);
      param_1->readFile((&pakStruct->archiveEntries[entryCounter]->uncompressedLength), 4);
      param_1->readFile(pakStruct->archiveEntries[entryCounter]->name, nameLength + 1);
      archiveEntries = pakStruct->archiveEntries[entryCounter];
      int32_t nameLength = strlen(archiveEntries->name);
      nameLength = (nameLength > 0xf) ? 0xf : nameLength;
      int32_t lookupHash = (nameLength << 4) | (archiveEntries->name[0] & 0xf);
      archiveEntries->lookupHash = pakStruct->intArray256[lookupHash];
      pakStruct->intArray256[lookupHash] = (int16_t)entryCounter;
      archiveOffset = archiveOffset + 21 + nameLength;
    }
    pakStruct->filePointer = param_1->getFilePointer();
    pakStruct->previousGlobalAddress = GlobalUnpackedFilePakStruct;
    pakStruct->unpackedFileObject = param_1;
    GlobalUnpackedFilePakStruct = pakStruct;
  }
}
