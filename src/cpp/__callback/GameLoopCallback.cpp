#include "HazardGlobals.hpp"

LRESULT CALLBACK GameLoopCallback(HWND param_1, UINT param_2, WPARAM param_3, LPARAM param_4) {
  HCURSOR cursorHandle;
  uint32_t windowStyleFlags;
  LRESULT defaultResult;

  switch (param_2) {
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;

  case WM_CLOSE:
    if (FlagRelatedToLoadingSfx == 1) {
      return 0;
    }
    break;

  case WM_ACTIVATEAPP:
    FlagRelatedToLoadingSfx = param_3;
    if (param_3 == 0) {
      if (DirectDrawObject != nullptr) {
        DirectDrawObject->RestoreDisplayMode();
      }
      windowStyleFlags = GetWindowLongA(param_1, -0x10);
      SetWindowLongA(param_1, -0x10, windowStyleFlags | 0x80000);
      return 0;
    }
    windowStyleFlags = GetWindowLongA(param_1, -0x10);
    SetWindowLongA(param_1, -0x10, windowStyleFlags & 0xfff7ffff);
    return 0;

  case WM_SETCURSOR:
    if (FlagRelatedToLoadingSfx != 0) {
      SetCursor((HCURSOR) nullptr);
      return 1;
    }
    cursorHandle = LoadCursorA((HINSTANCE) nullptr, (LPCSTR)0x7f8a);
    SetCursor(cursorHandle);
    return 1;
  }
  defaultResult = DefWindowProcA(param_1, param_2, param_3, param_4);
  return defaultResult;
}
