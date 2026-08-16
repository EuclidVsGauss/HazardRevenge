#include "HazardGlobals.hpp"

#pragma optimize("s", on)

int32_t __cdecl ReadFileFixedSize(char* filename, uint32_t size, uint32_t zero) {
  int32_t fileHandle;

  fileHandle = OpenFileWithFlags(filename, size, 64, zero);
  return fileHandle;
}

#pragma optimize("s", off)
