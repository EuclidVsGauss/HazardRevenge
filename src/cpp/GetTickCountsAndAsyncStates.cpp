#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/IntegerVirtualKeyPair.hpp"
#ifndef _MSC_VER
#include <SDL3/SDL_platform.h>
#endif

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
    uint32_t diff = (uint32_t)(gatedTickFloat - currentTick);
#if defined(SDL_PLATFORM_IOS) || defined(__IPHONEOS__)
    if (diff > 1) {
      Sleep(diff - 1);
    }
#endif
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
