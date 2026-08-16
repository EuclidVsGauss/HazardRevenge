#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/IntegerVirtualKeyPair.hpp"

int32_t __fastcall GetTickCountsAndAsyncStates(int32_t* outCursorX, int32_t* outCursorY, int32_t* outMouseInput) {
  int32_t loopCounter;
  SHORT rightButtonState;
  SHORT leftButtonState;
  uint32_t currentTick;
  IntegerVirtualKeyPair* inputEntry;
  ulonglong gatedTickFloat;
  tagPOINT cursorPos;

  currentTick = GetTickCount();
  gatedTickFloat = GatedTick;
  if (currentTick < gatedTickFloat) {
    do {
      currentTick = GetTickCount();
      gatedTickFloat = GatedTick;
    } while (currentTick < gatedTickFloat);
  }
  GetCursorPos(&cursorPos);
  *outCursorX = cursorPos.x;
  *outCursorY = cursorPos.y;
  rightButtonState = GetAsyncKeyState(VK_RBUTTON);
  loopCounter = MouseInput * 8;
  leftButtonState = GetAsyncKeyState(VK_LBUTTON);
  MouseInput = (uint32_t)(leftButtonState != 0) + (((uint32_t)(rightButtonState != 0) + loopCounter) * 2);
  inputEntry = InputCodes;
  *outMouseInput = MouseInput;
  do {
    loopCounter = inputEntry->index;
    rightButtonState = GetAsyncKeyState(inputEntry->virtualKey);
    inputEntry = inputEntry + 1;
    InputStates128[loopCounter] = (rightButtonState != 0) + ((InputStates128[loopCounter] & 1U) * 16);
  } while (inputEntry < InputCodes + 22);

  GatedTick = (Fixed1000 / (float)TimeResolution_45or15) + GatedTick;
  if (GatedTick <= (float)currentTick - Fixed500) {
    GatedTick = (float)currentTick;
  }
  gatedTickFloat = GatedTick;
  return (currentTick <= gatedTickFloat);
}
