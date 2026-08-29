#include "HazardGlobals.hpp"
#include "HazardStructs/ErrorEntry.hpp"

#pragma optimize("s", on)

void __cdecl MapErrorCode(uint32_t lastError) {
  int32_t index;

  HandlesLowerValue = lastError;
  for (index = 0; index < 45; index++) {
    if (lastError == LowerUpperErrorDictionary[index].ErrorLowerValue) {
      HandlesUpperValue = LowerUpperErrorDictionary[index].ErrorUpperValue;
      return;
    }
  }
  if ((lastError >= 19) && (lastError <= 36)) {
    HandlesUpperValue = 13;
    return;
  }
  if ((lastError < 188) || (202 < lastError)) {
    HandlesUpperValue = 22;
  }
  else {
    HandlesUpperValue = 8;
  }
}

#pragma optimize("s", off)
