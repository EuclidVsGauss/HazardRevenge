#include "HazardGlobals.hpp"

void __fastcall WrapperMessageBoxA(LPCSTR text, LPCSTR caption) {
  MessageBoxA(GameFullscreenWindow, text, caption, 0);
}
