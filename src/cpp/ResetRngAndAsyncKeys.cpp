#include "HazardGlobals.hpp"

void ResetRngAndAsyncKeys(void) {
  DWORD rawTick;
  int32_t inputArrayIndex;
  int32_t* inputStatePtr;
  LONGLONG tickAsRngSeed;

  rawTick = GetTickCount();
  GatedTick = (float)rawTick;
  tickAsRngSeed = GatedTick;
  SetRngSeed(tickAsRngSeed);
  inputStatePtr = (int32_t*)InputStates128;
  for (inputArrayIndex = 32; inputArrayIndex != 0; inputArrayIndex = inputArrayIndex + -1) {
    *inputStatePtr = 0;
    inputStatePtr = inputStatePtr + 1;
  }
}
