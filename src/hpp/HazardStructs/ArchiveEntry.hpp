#ifndef HAZARD_ARCHIVEENTRY_HPP
#define HAZARD_ARCHIVEENTRY_HPP
#include "HazardTypedef.hpp"

struct ArchiveEntry {
  int16_t boolean;
  int16_t lookupHash;
  int32_t start;
  int32_t compressedLength;
  int32_t uncompressedLength;
  char name[1];
};
typedef struct ArchiveEntry ArchiveEntry, *PArchiveEntry;

#endif
