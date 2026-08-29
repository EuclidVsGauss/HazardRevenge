#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/IntegerVirtualKeyPair.hpp"

int32_t __fastcall GetTickCountsAndAsyncStates(int32_t* outCursorX, int32_t* outCursorY, int32_t* outMouseInput) {
  int32_t loopCounter;
  SHORT rightButtonState;
  int32_t currentTick;
  IntegerVirtualKeyPair* inputEntry;
  int32_t gatedTickFloat;
  tagPOINT cursorPos;

  currentTick = GetTickCount();
  gatedTickFloat = GatedTick;
  if (gatedTickFloat > currentTick) {
    do {
      currentTick = GetTickCount();
      gatedTickFloat = GatedTick;
    } while (gatedTickFloat > currentTick);
  }
  GetCursorPos(&cursorPos);
  *outCursorX = cursorPos.x;
  *outCursorY = cursorPos.y;
  MouseInput = (uint32_t)(GetAsyncKeyState(VK_LBUTTON) != 0) + (((uint32_t)(GetAsyncKeyState(VK_RBUTTON) != 0) + (MouseInput * 8)) * 2);
  *outMouseInput = MouseInput;
  for (uint32_t i = 0; i < 22; i++) {
    loopCounter = InputCodes[i].index;
    rightButtonState = GetAsyncKeyState(InputCodes[i].virtualKey);
    InputStates128[loopCounter] = (rightButtonState != 0) + ((InputStates128[loopCounter] & 1U) * 16);
  }

  GatedTick = (Fixed1000 / (float)TimeResolution_45or15) + GatedTick;
  if (GatedTick <= (float)currentTick - Fixed500) {
    GatedTick = (float)currentTick;
  }
  gatedTickFloat = GatedTick;
  return (gatedTickFloat >= currentTick);
}
