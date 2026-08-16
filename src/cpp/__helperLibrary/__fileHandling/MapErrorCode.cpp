#include "HazardGlobals.hpp"
#include "HazardStructs/ErrorEntry.hpp"

#pragma optimize("s", on)

void __cdecl MapErrorCode(uint32_t lastError) {
  ErrorEntry* errorItem;
  int32_t index;
  index = 0;
  HandlesLowerValue = lastError;
  errorItem = LowerUpperErrorDictionary;
  do {
    if (lastError == errorItem->ErrorLowerValue) {
      HandlesUpperValue = LowerUpperErrorDictionary[index].ErrorUpperValue;
      return;
    }
    errorItem = errorItem + 1;
    index = index + 1;
  } while ((intptr_t)errorItem < ((intptr_t)LowerUpperErrorDictionary) + 0x168);
  if ((18 < lastError) && (lastError < 37)) {
    HandlesUpperValue = 13;
    return;
  }
  if ((lastError < 188) || (HandlesUpperValue = 8, 202 < lastError)) {
    HandlesUpperValue = 22;
  }
}

#pragma optimize("s", off)
