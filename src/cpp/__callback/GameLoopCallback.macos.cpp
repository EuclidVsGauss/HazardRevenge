#include <win2sdl.h>
#include <windows.h>
#include "HazardClasses/AnimationSpell.hpp"
#include "HazardGlobals.hpp"

LRESULT CALLBACK GameLoopCallback(HWND windowHandle, UINT messageId, WPARAM wParam, LPARAM lParam) {

  (void)messageId;
  (void)wParam;
  (void)lParam;

  SDL_Event* event = (SDL_Event*)windowHandle;

  while (SDL_PollEvent(event)) {
    switch (event->type) {
    case SDL_QUIT:
      if (FlagRelatedToLoadingSfx == 1) {

        return 0;
      }
      else {

        return 1;
      }

    case SDL_WINDOWEVENT:
      if (event->window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {

        FlagRelatedToLoadingSfx = 1;
      }
      else if (event->window.event == SDL_WINDOWEVENT_FOCUS_LOST) {

        FlagRelatedToLoadingSfx = 0;
      }
      break;

    case SDL_MOUSEMOTION:

      if (FlagRelatedToLoadingSfx != 0) {

        SDL_ShowCursor(SDL_DISABLE);
      }
      else {

        SDL_Cursor* cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAITARROW);
        SDL_SetCursor(cursor);
        SDL_ShowCursor(SDL_ENABLE);
      }
      break;
    }
  }
  return 0;
}
