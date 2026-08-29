#include <windows.h>
#include "HazardGlobals.hpp"
#include <sdl3/win2sdl.h>

LRESULT CALLBACK GameLoopCallback(HWND windowHandle, UINT messageId, WPARAM wParam, LPARAM lParam) {

  (void)messageId;
  (void)wParam;
  (void)lParam;

  SDL_Event* event = (SDL_Event*)windowHandle;

  while (SDL_PollEvent(event)) {
    switch (event->type) {

    case SDL_EVENT_QUIT:
      if (FlagRelatedToLoadingSfx == 1) {
        return 0;
      }
      else {
        return 1;
      }

    case SDL_EVENT_WINDOW_FOCUS_GAINED:
      FlagRelatedToLoadingSfx = 1;
      break;

    case SDL_EVENT_WINDOW_FOCUS_LOST:
      FlagRelatedToLoadingSfx = 0;
      break;

    case SDL_EVENT_MOUSE_MOTION:

      if (FlagRelatedToLoadingSfx != 0) {
        SDL_HideCursor();
      }
      else {
        SDL_Cursor* cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_PROGRESS);
        SDL_SetCursor(cursor);
        SDL_ShowCursor();
      }
      break;

    default:
      break;
    }
  }
  return 0;
}
