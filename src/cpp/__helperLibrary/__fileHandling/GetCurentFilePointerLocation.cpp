#include "HazardGlobals.hpp"

#pragma optimize("s", on)

__declspec(nothrow) int32_t __cdecl GetCurentFilePointerLocation(uint32_t fileHandle) {
  int32_t currentPosition;
  currentPosition = SetFilePointer(fileHandle, 0, 1);
  return currentPosition;
}

#pragma optimize("s", off)
