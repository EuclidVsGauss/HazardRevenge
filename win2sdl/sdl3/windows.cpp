#define SDL_MAIN_HANDLED
#include <SDL3/SDL_main.h>
#include "../windows.h"
#include "win2sdl.h"
#include "touch_overlay.h"

#if TOUCH_OVERLAY_ENABLED
#include <deque>
#endif

LPCSTR _lpClassName = nullptr;
LPCSTR _lpWindowName = nullptr;

bool g_sdlInitialized = false;
std::map<SDL_Window*, HWND> g_windowToHWND;
std::map<HWND, SDL_Window*> g_hwndToWindow;
std::map<HWND, LONG> g_windowStyles;
std::map<HWND, LPVOID> g_windowUserData;
std::map<HWND, SDL_Renderer*> g_hwndToRenderer;
std::queue<MSG> g_messageQueue;
#if TOUCH_OVERLAY_ENABLED
static std::deque<SDL_Event> g_deferredEvents;
#endif
DWORD g_lastError = ERROR_SUCCESS;
int g_exitCode = 0;
bool g_quitPosted = false;
std::string g_commandLine;
HWND g_nextHwnd = (HWND)0x1000;
std::map<int, bool> g_keyStates;

std::map<HANDLE, bool> g_heaps;
HANDLE g_processHeap = (HANDLE)0x1;

SDL_Window* g_mainWindow = nullptr;
SDL_Renderer* g_mainRenderer = nullptr;
SDL_AudioStream* g_audioStream = nullptr;
SDL_AudioSpec g_audioSpec;
std::vector<CImpIDirectSoundBuffer*> g_activeBuffers;
SDL_Mutex* g_audioMutex = nullptr;
std::map<IDirectDraw*, SDL_Renderer*> g_ddrawToRenderer;
std::map<IDirectSound*, SDL_AudioStream*> g_dsoundToAudio;

std::map<HICON, SDL_Surface*> g_iconToSurface;

HANDLE g_stdInput = nullptr;
HANDLE g_stdOutput = nullptr;
HANDLE g_stdError = nullptr;

int lstrcmp(LPCSTR a, LPCSTR b) {
  return strcmp(a, b);
}

void __amsg_exit(int rterrnum) {
  exit(rterrnum);
}

void SDLCALL DirectSoundAudioCallback(void* userdata, SDL_AudioStream* stream,
                                      int additional_amount, int total_amount);

void InitSDLTranslationLayer() {
  if (!g_sdlInitialized) {
    SDL_SetMainReady();

    if (!SDL_Init(SDL_INIT_VIDEO)) {
      printf("FATAL: SDL_Init(VIDEO) failed: %s\n", SDL_GetError());
      abort();
    }
    if (!SDL_InitSubSystem(SDL_INIT_AUDIO)) {
      printf("WARNING: SDL audio init failed, running without audio: %s\n", SDL_GetError());
    }

    g_audioMutex = SDL_CreateMutex();

    SDL_zero(g_audioSpec);
    g_audioSpec.freq = 44100;
    g_audioSpec.format = SDL_AUDIO_S16;
    g_audioSpec.channels = 2;

    g_audioStream = SDL_OpenAudioDeviceStream(
        SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &g_audioSpec,
        DirectSoundAudioCallback, nullptr);
    if (!g_audioStream) {
      printf("WARNING: Failed to open SDL audio stream: %s\n", SDL_GetError());
    }
    else {
      if (!SDL_ResumeAudioStreamDevice(g_audioStream)) {
        printf("WARNING: Failed to resume audio stream: %s\n", SDL_GetError());
      }
    }

    SDL_HideCursor();

#if TOUCH_OVERLAY_ENABLED
    TouchOverlay_Init();
#endif

    g_sdlInitialized = true;
    g_heaps[g_processHeap] = true;

    g_commandLine = "program.exe";
  }
}

void ShutdownSDLTranslationLayer() {
  if (g_sdlInitialized) {
    if (g_audioStream) {
      SDL_DestroyAudioStream(g_audioStream);
      g_audioStream = nullptr;
    }

    if (g_audioMutex) {
      SDL_DestroyMutex(g_audioMutex);
      g_audioMutex = nullptr;
    }

    for (auto& pair : g_ddrawToRenderer) {
      delete pair.first;
    }
    g_ddrawToRenderer.clear();

    for (auto& pair : g_dsoundToAudio) {
      delete pair.first;
    }
    g_dsoundToAudio.clear();

    for (auto& pair : g_hwndToRenderer) {
      if (pair.second) {
        SDL_DestroyRenderer(pair.second);
      }
    }
    g_hwndToRenderer.clear();

    for (auto& pair : g_hwndToWindow) {
      if (pair.second) {
        SDL_DestroyWindow(pair.second);
      }
    }
    g_hwndToWindow.clear();
    g_windowToHWND.clear();

    SDL_Quit();
    g_sdlInitialized = false;
  }
}

SDL_Window* GetSDLWindowFromHWND(HWND hwnd) {
  auto it = g_hwndToWindow.find(hwnd);
  return (it != g_hwndToWindow.end()) ? it->second : nullptr;
}

HWND GetHWNDFromSDLWindow(SDL_Window* window) {
  auto it = g_windowToHWND.find(window);
  return (it != g_windowToHWND.end()) ? it->second : nullptr;
}

SDL_Renderer* GetRendererForWindow(HWND hwnd) {
  auto it = g_hwndToRenderer.find(hwnd);
  if (it != g_hwndToRenderer.end()) {
    return it->second;
  }

  SDL_Window* window = GetSDLWindowFromHWND(hwnd);
  if (!window) {
    return nullptr;
  }

  SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
  if (!renderer) {
    return nullptr;
  }
  SDL_SetRenderVSync(renderer, 1);

  SDL_SetRenderLogicalPresentation(renderer, 0, 0,
                                   SDL_LOGICAL_PRESENTATION_DISABLED);

  g_hwndToRenderer[hwnd] = renderer;
  if (!g_mainRenderer) {
    g_mainRenderer = renderer;
  }
  return renderer;
}

// Time functions

void GetLocalTime(SYSTEMTIME* lpSystemTime) {
  time_t now = time(nullptr);
  struct tm* t = localtime(&now);
  lpSystemTime->wYear = t->tm_year + 1900;
  lpSystemTime->wMonth = t->tm_mon + 1;
  lpSystemTime->wDayOfWeek = t->tm_wday;
  lpSystemTime->wDay = t->tm_mday;
  lpSystemTime->wHour = t->tm_hour;
  lpSystemTime->wMinute = t->tm_min;
  lpSystemTime->wSecond = t->tm_sec;
  lpSystemTime->wMilliseconds = 0;
}

void Sleep(DWORD dwMilliseconds) { SDL_Delay(dwMilliseconds); }

DWORD GetTickCount() { return (DWORD)SDL_GetTicks(); }

// Cursor functions

HCURSOR SetCursor(HCURSOR hCursor) {
  if (ARGV_PLAY_IN_FULLSCREEN) {
    SDL_HideCursor();
  }

  if (hCursor == (HCURSOR)IDC_ARROW) {
    SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT));
  }
  else if (hCursor == (HCURSOR)IDC_WAIT) {
    SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAIT));
  }
  else if (hCursor == (HCURSOR)IDC_CROSS) {
    SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR));
  }
  else if (hCursor == (HCURSOR)IDC_HAND) {
    SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_POINTER));
  }

  return hCursor;
}

HCURSOR LoadCursorA(HINSTANCE hInstance, LPCSTR lpCursorName) {
  return (HCURSOR)lpCursorName;
}

static void PumpEventsForTouchOverlay();

BOOL GetCursorPos(LPPOINT lpPoint) {
  if (!lpPoint) {
    return FALSE;
  }

  if (ARGV_PLAY_IN_FULLSCREEN) {
    SDL_HideCursor();
  }
  PumpEventsForTouchOverlay();
#if TOUCH_OVERLAY_ENABLED
  TouchOverlay_MarkCursorSampled();
#endif

  static int lastGameX = -logicalWidth;
  static int lastGameY = -logicalHeight;

#if TOUCH_OVERLAY_ENABLED
  int touchX = 0;
  int touchY = 0;
  if (TouchOverlay_GetGameTouch(&touchX, &touchY)) {
    lastGameX = std::clamp(touchX, 0, logicalWidth - 1);
    lastGameY = std::clamp(touchY, 0, logicalHeight - 1);
    lpPoint->x = lastGameX;
    lpPoint->y = lastGameY;
    return TRUE;
  }

  if (TouchOverlay_IsAnyTouchActive()) {
    lpPoint->x = lastGameX;
    lpPoint->y = lastGameY;
    return TRUE;
  }
#endif

  // Fallback to mouse state (desktop).
  float winX = 0.0f, winY = 0.0f;
  SDL_GetMouseState(&winX, &winY);

  int winW = logicalWidth, winH = logicalHeight;
  if (g_mainWindow) {
    SDL_GetWindowSize(g_mainWindow, &winW, &winH);
  }
  float scale = std::min((float)winW / (float)logicalWidth, (float)winH / (float)logicalHeight);
  float gameX = (winW - (float)logicalWidth * scale) * 0.5f;
  float gameY = (winH - (float)logicalHeight * scale) * 0.5f;

  float lx = (winX - gameX) / scale;
  float ly = (winY - gameY) / scale;

#if TOUCH_OVERLAY_ENABLED
  if (lx >= 0.0f && lx < (float)logicalWidth &&
      ly >= 0.0f && ly < (float)logicalHeight) {
    lastGameX = (int)std::floor(lx);
    lastGameY = (int)std::floor(ly);
  }
#else
  lastGameX = std::clamp((int)std::floor(lx), 0, logicalWidth  - 1);
  lastGameY = std::clamp((int)std::floor(ly), 0, logicalHeight - 1);
#endif

  lpPoint->x = lastGameX;
  lpPoint->y = lastGameY;

  return TRUE;
}

// Keyboard input

static void PumpEventsForTouchOverlay() {
  SDL_PumpEvents();
#if TOUCH_OVERLAY_ENABLED
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (!TouchOverlay_ProcessEvent(event)) {
      g_deferredEvents.push_back(event);
    }
  }
#endif
}

#if TOUCH_OVERLAY_ENABLED
extern int FlagCursorRelated;
#endif

static uint32_t g_lastReportedButtons = 0;

static SHORT ReportMouseButtonState(uint32_t buttonMask, bool down) {
  uint32_t previous = g_lastReportedButtons;
  if (down) {
    g_lastReportedButtons |= buttonMask;
  }
  else {
    g_lastReportedButtons &= ~buttonMask;
  }
#if TOUCH_OVERLAY_ENABLED
  if ((g_lastReportedButtons & ~previous) != 0) {
    FlagCursorRelated = -1;
  }
#endif
  return down ? (SHORT)0x8000 : (SHORT)0;
}

SHORT GetAsyncKeyState(int vKey) {
  PumpEventsForTouchOverlay();

#if TOUCH_OVERLAY_ENABLED
  if (TouchOverlay_IsKeyDown(vKey)) {
    if (vKey == VK_LBUTTON) {
      return ReportMouseButtonState(0x1, true);
    }
    if (vKey == VK_RBUTTON) {
      return ReportMouseButtonState(0x2, true);
    }
    return (SHORT)0x8000;
  }

  if (vKey == VK_LBUTTON) {
    if (TouchOverlay_IsGameTouchDown()) {
      return ReportMouseButtonState(0x1, true);
    }
    if (TouchOverlay_HasActiveOverlayTouch() || TouchOverlay_IsAnyTouchActive()) {
      return ReportMouseButtonState(0x1, false);
    }
  }

  if (vKey == VK_RBUTTON) {
    if (TouchOverlay_IsKeyDown(VK_RBUTTON)) {
      return ReportMouseButtonState(0x2, true);
    }
  }
#endif

  const bool* state = SDL_GetKeyboardState(nullptr);

  switch (vKey) {
  case VK_ESCAPE:
    return state[SDL_SCANCODE_ESCAPE] ? 0x8000 : 0;
  case VK_SPACE:
    return state[SDL_SCANCODE_SPACE] ? 0x8000 : 0;
  case VK_LEFT:
    return state[SDL_SCANCODE_LEFT] ? 0x8000 : 0;
  case VK_UP:
    return state[SDL_SCANCODE_UP] ? 0x8000 : 0;
  case VK_RIGHT:
    return state[SDL_SCANCODE_RIGHT] ? 0x8000 : 0;
  case VK_DOWN:
    return state[SDL_SCANCODE_DOWN] ? 0x8000 : 0;
  case VK_SHIFT:
    return (state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_RSHIFT]) ? 0x8000 : 0;
  case VK_CONTROL:
    return (state[SDL_SCANCODE_LCTRL] || state[SDL_SCANCODE_RCTRL]) ? 0x8000 : 0;
  case VK_LBUTTON:
    return ReportMouseButtonState(0x1, (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_MASK(SDL_BUTTON_LEFT)) != 0);
  case VK_RBUTTON:
    return ReportMouseButtonState(0x2, (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_MASK(SDL_BUTTON_RIGHT)) != 0);
  case VK_C:
    return state[SDL_SCANCODE_C] ? 0x8000 : 0;
  case VK_F:
    return state[SDL_SCANCODE_F] ? 0x8000 : 0;
  case VK_I:
    return state[SDL_SCANCODE_I] ? 0x8000 : 0;
  case VK_K:
    return state[SDL_SCANCODE_K] ? 0x8000 : 0;
  case VK_M:
    return state[SDL_SCANCODE_M] ? 0x8000 : 0;
  case VK_P:
    return state[SDL_SCANCODE_P] ? 0x8000 : 0;
  case VK_U:
    return state[SDL_SCANCODE_U] ? 0x8000 : 0;
  case VK_W:
    return state[SDL_SCANCODE_W] ? 0x8000 : 0;
  case VK_1:
    return state[SDL_SCANCODE_1] ? 0x8000 : 0;
  case VK_2:
    return state[SDL_SCANCODE_2] ? 0x8000 : 0;
  case VK_3:
    return state[SDL_SCANCODE_3] ? 0x8000 : 0;
  case VK_4:
    return state[SDL_SCANCODE_4] ? 0x8000 : 0;
  case VK_5:
    return state[SDL_SCANCODE_5] ? 0x8000 : 0;
  case VK_F1:
    return state[SDL_SCANCODE_F1] ? 0x8000 : 0;
  case VK_F2:
    return state[SDL_SCANCODE_F2] ? 0x8000 : 0;
  case VK_F3:
    return state[SDL_SCANCODE_F3] ? 0x8000 : 0;
  case VK_F4:
    return state[SDL_SCANCODE_F4] ? 0x8000 : 0;
  default:
    return 0;
  }
}

// Window functions

HWND CreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName,
                     DWORD dwStyle, int X, int Y, int nWidth, int nHeight,
                     HWND hWndParent, HMENU hMenu, HINSTANCE hInstance,
                     LPVOID lpParam) {
  _lpClassName = lpClassName;
  _lpWindowName = lpWindowName;

  SDL_SetHint(SDL_HINT_TOUCH_MOUSE_EVENTS, "1");
  SDL_SetHint(SDL_HINT_MOUSE_TOUCH_EVENTS, "1");
  InitSDLTranslationLayer();

  SDL_WindowFlags flags = 0;

  if (ARGV_PLAY_IN_FULLSCREEN) {
    if (dwStyle & WS_POPUP) {
      flags |= SDL_WINDOW_BORDERLESS;
    }
  }

  if (dwStyle & WS_THICKFRAME) {
    flags |= SDL_WINDOW_RESIZABLE;
  }

  int winX = (X != CW_USEDEFAULT && X != 0) ? X : SDL_WINDOWPOS_CENTERED;
  int winY = (Y != CW_USEDEFAULT && Y != 0) ? Y : SDL_WINDOWPOS_CENTERED;
  int winW = (ARGV_PLAY_IN_FULLSCREEN && nWidth > 0) ? nWidth : logicalWidth;
  int winH = (ARGV_PLAY_IN_FULLSCREEN && nHeight > 0) ? nHeight : logicalHeight;

  SDL_Window* window = SDL_CreateWindow(
      lpWindowName ? lpWindowName : "Window",
      winW, winH,
      ARGV_PLAY_IN_FULLSCREEN ? (flags | SDL_WINDOW_FULLSCREEN) : flags);

  if (!window) {
    g_lastError = ERROR_ACCESS_DENIED;
    return nullptr;
  }

  SDL_SetWindowPosition(window, winX, winY);

  if (!g_mainWindow) {
    g_mainWindow = window;
  }

  bool grab = ARGV_PLAY_IN_FULLSCREEN ? true : false;
  SDL_SetWindowMouseGrab(window, grab);
  SDL_SetWindowKeyboardGrab(window, grab);

  if (ARGV_PLAY_IN_FULLSCREEN) {
    SDL_HideCursor();
  }

  HWND hwnd = g_nextHwnd;
  g_nextHwnd = (HWND)((size_t)g_nextHwnd + 1);

  g_windowToHWND[window] = hwnd;
  g_hwndToWindow[hwnd] = window;
  g_windowStyles[hwnd] = dwStyle;

  return hwnd;
}

BOOL ShowWindow(HWND hWnd, int nCmdShow) {
  SDL_Window* window = GetSDLWindowFromHWND(hWnd);
  if (!window) {
    return FALSE;
  }

  switch (nCmdShow) {
  case SW_HIDE:
    SDL_HideWindow(window);
    break;

  case SW_SHOW: {
    SDL_ShowWindow(window);
    SDL_RaiseWindow(window);
    bool grab = ARGV_PLAY_IN_FULLSCREEN ? true : false;
    SDL_SetWindowMouseGrab(window, grab);
    SDL_SetWindowKeyboardGrab(window, grab);
    if (ARGV_PLAY_IN_FULLSCREEN) {
      SDL_HideCursor();
    }
    break;
  }

  case SW_MINIMIZE:
    SDL_MinimizeWindow(window);
    break;

  case SW_RESTORE:
    SDL_RestoreWindow(window);
    break;
  }

  return TRUE;
}

BOOL CloseWindow(HWND hWnd) {
  SDL_Window* window = GetSDLWindowFromHWND(hWnd);
  if (!window) {
    return FALSE;
  }

  auto it = g_hwndToRenderer.find(hWnd);
  if (it != g_hwndToRenderer.end()) {
    SDL_DestroyRenderer(it->second);
    g_hwndToRenderer.erase(it);
  }

  SDL_DestroyWindow(window);

  g_windowToHWND.erase(window);
  g_hwndToWindow.erase(hWnd);
  g_windowStyles.erase(hWnd);
  g_windowUserData.erase(hWnd);

  return TRUE;
}

LONG GetWindowLongA(HWND hWnd, int nIndex) {
  if (nIndex == GWL_STYLE) {
    auto it = g_windowStyles.find(hWnd);
    return (it != g_windowStyles.end()) ? it->second : 0;
  }
  else if (nIndex == GWL_USERDATA) {
    auto it = g_windowUserData.find(hWnd);
    return (LONG)(size_t)(it != g_windowUserData.end() ? it->second : nullptr);
  }
  return 0;
}

LONG SetWindowLongA(HWND hWnd, int nIndex, LONG dwNewLong) {
  LONG oldValue = GetWindowLongA(hWnd, nIndex);

  if (nIndex == GWL_STYLE) {
    g_windowStyles[hWnd] = dwNewLong;
  }
  else if (nIndex == GWL_USERDATA) {
    g_windowUserData[hWnd] = (LPVOID)(size_t)dwNewLong;
  }

  return oldValue;
}

BOOL RegisterClassA(const WNDCLASSA* lpWndClass) {
  return TRUE;
}

HWND FindWindowA(LPCSTR lpClassName, LPCSTR lpWindowName) {
  for (auto& pair : g_hwndToWindow) {
    if (lpWindowName) {
      SDL_Window* win = pair.second;
      const char* title = SDL_GetWindowTitle(win);
      if (title && strcmp(title, lpWindowName) == 0) {
        return pair.first;
      }
    }
  }
  return nullptr;
}

BOOL SetForegroundWindow(HWND hWnd) {
  SDL_Window* window = GetSDLWindowFromHWND(hWnd);
  if (!window) {
    return FALSE;
  }
  SDL_RaiseWindow(window);
  return TRUE;
}

int GetSystemMetrics(int nIndex) {
  InitSDLTranslationLayer();

  const SDL_DisplayMode* mode =
      SDL_GetCurrentDisplayMode(SDL_GetPrimaryDisplay());
  if (!mode) {
    return (nIndex == SM_CXSCREEN) ? logicalWidth : ((nIndex == SM_CYSCREEN) ? logicalHeight : 0);
  }

  switch (nIndex) {
  case SM_CXSCREEN:
    return mode->w;
  case SM_CYSCREEN:
    return mode->h;
  default:
    return 0;
  }
}

HGDIOBJ GetStockObject(int i) {
  return (HGDIOBJ)(size_t)(i + 1);
}

// Message handling

void PostQuitMessage(int nExitCode) {
  g_exitCode = nExitCode;
  g_quitPosted = true;

  MSG msg = {0};
  msg.message = WM_QUIT;
  msg.wParam = (WPARAM)(uintptr_t)nExitCode;
  g_messageQueue.push(msg);
}

BOOL GetMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin,
                 UINT wMsgFilterMax) {
  InitSDLTranslationLayer();

  if (g_quitPosted && !g_messageQueue.empty()) {
    *lpMsg = g_messageQueue.front();
    g_messageQueue.pop();
    return FALSE;
  }

  SDL_Event event;
  if (SDL_WaitEvent(&event)) {
    lpMsg->hwnd = nullptr;
    lpMsg->time = (DWORD)SDL_GetTicks();

    switch (event.type) {
    case SDL_EVENT_QUIT:
      PostQuitMessage(0);
      *lpMsg = g_messageQueue.front();
      g_messageQueue.pop();
      return FALSE;

    case SDL_EVENT_KEY_DOWN:
      lpMsg->message = WM_KEYDOWN;
      lpMsg->wParam = (WPARAM)(uintptr_t)event.key.key;
      break;

    case SDL_EVENT_KEY_UP:
      lpMsg->message = WM_KEYUP;
      lpMsg->wParam = (WPARAM)(uintptr_t)event.key.key;
      break;

    case SDL_EVENT_MOUSE_MOTION:
      lpMsg->message = WM_MOUSEMOVE;
      lpMsg->pt.x = (LONG)event.motion.x;
      lpMsg->pt.y = (LONG)event.motion.y;
      break;

    case SDL_EVENT_MOUSE_BUTTON_DOWN:
      lpMsg->message =
          (event.button.button == SDL_BUTTON_LEFT) ? WM_LBUTTONDOWN : 0;
      break;

    case SDL_EVENT_MOUSE_BUTTON_UP:
      lpMsg->message =
          (event.button.button == SDL_BUTTON_LEFT) ? WM_LBUTTONUP : 0;
      break;
    }

    return TRUE;
  }
  return FALSE;
}

BOOL PeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin,
                  UINT wMsgFilterMax, UINT wRemoveMsg) {
  InitSDLTranslationLayer();

  if (!g_messageQueue.empty()) {
    *lpMsg = g_messageQueue.front();
    if (wRemoveMsg) {
      g_messageQueue.pop();
    }
    return TRUE;
  }

  SDL_Event event;
#if TOUCH_OVERLAY_ENABLED
  if (!g_deferredEvents.empty()) {
    event = g_deferredEvents.front();
    if (wRemoveMsg) {
      g_deferredEvents.pop_front();
    }
  }
  else
#endif
  if (SDL_PollEvent(&event)) {
#if TOUCH_OVERLAY_ENABLED
    if (TouchOverlay_ProcessEvent(event)) {
      return FALSE;
    }
#endif
  }
  else {
    return FALSE;
  }

  lpMsg->hwnd = nullptr;
  lpMsg->time = (DWORD)SDL_GetTicks();
  lpMsg->message = 0;
  lpMsg->wParam = 0;
  lpMsg->lParam = 0;
  lpMsg->pt.x = 0;
  lpMsg->pt.y = 0;

  switch (event.type) {
    case SDL_EVENT_QUIT:          PostQuitMessage(0); break;
    case SDL_EVENT_KEY_DOWN:      lpMsg->message = WM_KEYDOWN;
      lpMsg->wParam = (WPARAM)(uintptr_t)event.key.key; break;
    case SDL_EVENT_KEY_UP:        lpMsg->message = WM_KEYUP;
      lpMsg->wParam = (WPARAM)(uintptr_t)event.key.key; break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
      lpMsg->message = (event.button.button == SDL_BUTTON_LEFT) ? WM_LBUTTONDOWN : 0;
      lpMsg->pt.x = (LONG)event.button.x;
      lpMsg->pt.y = (LONG)event.button.y;
      break;
    case SDL_EVENT_MOUSE_BUTTON_UP:
      lpMsg->message = (event.button.button == SDL_BUTTON_LEFT) ? WM_LBUTTONUP : 0;
      lpMsg->pt.x = (LONG)event.button.x;
      lpMsg->pt.y = (LONG)event.button.y;
      break;
    case SDL_EVENT_MOUSE_MOTION:
      lpMsg->message = WM_MOUSEMOVE;
      lpMsg->pt.x = (LONG)event.motion.x;
      lpMsg->pt.y = (LONG)event.motion.y;
      break;
  }
  return TRUE;
}

LRESULT DispatchMessageA(const MSG* lpMsg) { return 0; }

BOOL TranslateMessage(const MSG* lpMsg) { return TRUE; }

LRESULT DefWindowProcA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) { return 0; }

int MessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType) {
  InitSDLTranslationLayer();

  SDL_MessageBoxButtonData buttons[3];
  int numButtons = 0;

  if (uType & MB_OKCANCEL) {
    buttons[0] = {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, IDOK, "OK"};
    buttons[1] = {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, IDCANCEL, "Cancel"};
    numButtons = 2;
  }
  else if (uType & MB_YESNO) {
    buttons[0] = {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, IDYES, "Yes"};
    buttons[1] = {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, IDNO, "No"};
    numButtons = 2;
  }
  else {
    buttons[0] = {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, IDOK, "OK"};
    numButtons = 1;
  }

  SDL_MessageBoxData data = {0};

  if (uType & MB_ICONERROR) {
    data.flags = SDL_MESSAGEBOX_ERROR;
  }
  else if (uType & MB_ICONWARNING) {
    data.flags = SDL_MESSAGEBOX_WARNING;
  }
  else if (uType & MB_ICONINFORMATION) {
    data.flags = SDL_MESSAGEBOX_INFORMATION;
  }

  data.window = GetSDLWindowFromHWND(hWnd);
  data.title = lpCaption;
  data.message = lpText;
  data.numbuttons = numButtons;
  data.buttons = buttons;

  int buttonid = 0;
  SDL_ShowMessageBox(&data, &buttonid);

  return buttonid;
}

// Memory management

LPVOID HeapAlloc(HANDLE hHeap, DWORD dwFlags, SIZE_T dwBytes) {
  void* ptr = malloc(dwBytes);
  if (ptr && (dwFlags & HEAP_ZERO_MEMORY)) {
    memset(ptr, 0, dwBytes);
  }
  return ptr;
}

BOOL HeapFree(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem) {
  free(lpMem);
  return TRUE;
}

LPVOID HeapReAlloc(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem, SIZE_T dwBytes) {
  return realloc(lpMem, dwBytes);
}

HANDLE HeapCreate(DWORD flOptions, SIZE_T dwInitialSize, SIZE_T dwMaximumSize) {
  HANDLE heap = (HANDLE)((size_t)g_nextHwnd);
  g_nextHwnd = (HWND)((size_t)g_nextHwnd + 1);
  g_heaps[heap] = true;
  return heap;
}

BOOL HeapDestroy(HANDLE hHeap) {
  g_heaps.erase(hHeap);
  return TRUE;
}

LPVOID VirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType,
                    DWORD flProtect) {
  return malloc(dwSize);
}

BOOL VirtualFree(LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType) {
  free(lpAddress);
  return TRUE;
}

// Process functions

HMODULE GetModuleHandleA(LPCSTR lpModuleName) {
  if (lpModuleName == nullptr) {
    return (HMODULE)0x400000;
  }
  return nullptr;
}

void* GetProcAddress(HMODULE hModule, LPCSTR lpProcName) {
  return dlsym(RTLD_DEFAULT, lpProcName);
}

DWORD GetVersion() { return 0x00000a00; }

void GetStartupInfoA(STARTUPINFOA* lpStartupInfo) {
  memset(lpStartupInfo, 0, sizeof(STARTUPINFOA));
  lpStartupInfo->cb = sizeof(STARTUPINFOA);
}

void ExitProcess(UINT uExitCode) {
  ShutdownSDLTranslationLayer();
  exit(uExitCode);
}

HANDLE GetCurrentProcess() { return (HANDLE)0xffffffff; }

BOOL TerminateProcess(HANDLE hProcess, UINT uExitCode) {
  if (hProcess == GetCurrentProcess()) {
    ExitProcess(uExitCode);
  }
  return FALSE;
}

LPSTR GetCommandLineA() { return "\"c:\\\""; }

// File operations using standard C FILE*

BOOL ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead,
              DWORD* lpNumberOfBytesRead, void* lpOverlapped) {
  if (!hFile || hFile == INVALID_HANDLE_VALUE) {
    g_lastError = ERROR_INVALID_HANDLE;
    if (lpNumberOfBytesRead) {
      *lpNumberOfBytesRead = 0;
    }
    return FALSE;
  }

  FILE* fp = (FILE*)hFile;
  size_t bytesRead = fread(lpBuffer, 1, nNumberOfBytesToRead, fp);
  if (lpNumberOfBytesRead) {
    *lpNumberOfBytesRead = bytesRead;
  }

  if (bytesRead < nNumberOfBytesToRead) {
    if (feof(fp)) {
      return TRUE;
    }
    g_lastError = ERROR_READ_FAULT;
    return FALSE;
  }
  return TRUE;
}

BOOL WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite,
               DWORD* lpNumberOfBytesWritten, void* lpOverlapped) {
  if (!hFile || hFile == INVALID_HANDLE_VALUE) {
    g_lastError = ERROR_INVALID_HANDLE;
    if (lpNumberOfBytesWritten) {
      *lpNumberOfBytesWritten = 0;
    }
    return FALSE;
  }

  FILE* fp = (FILE*)hFile;
  size_t bytesWritten = fwrite(lpBuffer, 1, nNumberOfBytesToWrite, fp);
  if (lpNumberOfBytesWritten) {
    *lpNumberOfBytesWritten = bytesWritten;
  }

  if (bytesWritten < nNumberOfBytesToWrite) {
    g_lastError = ERROR_WRITE_FAULT;
    return FALSE;
  }
  return TRUE;
}

BOOL CloseHandle(HANDLE hObject) {
  if (hObject && hObject != INVALID_HANDLE_VALUE) {
    FILE* fp = (FILE*)hObject;
    return fclose(fp) == 0;
  }
  g_lastError = ERROR_INVALID_HANDLE;
  return FALSE;
}

DWORD SetFilePointer(HANDLE hFile, LONG lDistanceToMove,
                     LONG* lpDistanceToMoveHigh, DWORD dwMoveMethod) {
  if (!hFile || hFile == INVALID_HANDLE_VALUE) {
    g_lastError = ERROR_INVALID_HANDLE;
    return INVALID_SET_FILE_POINTER;
  }

  FILE* fp = (FILE*)hFile;
  int whence;
  switch (dwMoveMethod) {
  case FILE_BEGIN:
    whence = SEEK_SET;
    break;
  case FILE_CURRENT:
    whence = SEEK_CUR;
    break;
  case FILE_END:
    whence = SEEK_END;
    break;
  default:
    g_lastError = ERROR_INVALID_PARAMETER;
    return INVALID_SET_FILE_POINTER;
  }

  if (fseek(fp, lDistanceToMove, whence) != 0) {
    g_lastError = ERROR_IO_DEVICE;
    return INVALID_SET_FILE_POINTER;
  }

  long new_pos = ftell(fp);
  if (new_pos < 0) {
    g_lastError = ERROR_IO_DEVICE;
    return INVALID_SET_FILE_POINTER;
  }
  return (DWORD)new_pos;
}

BOOL SetEndOfFile(HANDLE hFile) {
  if (!hFile || hFile == INVALID_HANDLE_VALUE) {
    g_lastError = ERROR_INVALID_HANDLE;
    return FALSE;
  }
  FILE* fp = (FILE*)hFile;
  long pos = ftell(fp);
  if (pos < 0) {
    g_lastError = ERROR_IO_DEVICE;
    return FALSE;
  }
  return ftruncate(fileno(fp), pos) == 0;
}

BOOL FlushFileBuffers(HANDLE hFile) {
  if (!hFile || hFile == INVALID_HANDLE_VALUE) {
    g_lastError = ERROR_INVALID_HANDLE;
    return FALSE;
  }
  FILE* fp = (FILE*)hFile;
  return fflush(fp) == 0;
}

DWORD GetLastError() { return g_lastError; }

// Directory functions

BOOL SetCurrentDirectoryA(LPCSTR lpPathName) { return chdir(lpPathName) == 0; }

UINT GetDriveTypeA(LPCSTR lpRootPathName) {
  struct statvfs stat;
  if (statvfs(lpRootPathName ? lpRootPathName : "/", &stat) == 0) {
    return DRIVE_FIXED;
  }
  return DRIVE_UNKNOWN;
}

// String conversion (simplified)

int WideCharToMultiByte(UINT CodePage, DWORD dwFlags,
                        const wchar_t* lpWideCharStr,
                        int cchWideChar, LPSTR lpMultiByteStr, int cbMultiByte,
                        LPCSTR lpDefaultChar, BOOL* lpUsedDefaultChar) {
  if (cbMultiByte == 0) {
    return cchWideChar * 4;
  }
  wcstombs(lpMultiByteStr, lpWideCharStr, cbMultiByte);
  return strlen(lpMultiByteStr);
}

int MultiByteToWideChar(UINT CodePage, DWORD dwFlags, LPCSTR lpMultiByteStr,
                        int cbMultiByte, wchar_t* lpWideCharStr,
                        int cchWideChar) {
  if (cchWideChar == 0) {
    return strlen(lpMultiByteStr) + 1;
  }
  mbstowcs(lpWideCharStr, lpMultiByteStr, cchWideChar);
  return wcslen(lpWideCharStr);
}

// Environment

LPSTR GetEnvironmentStrings() {
  extern char** environ;
  static std::string envBlock;
  envBlock.clear();
  for (char** env = environ; *env; ++env) {
    envBlock += *env;
    envBlock += '\0';
  }
  envBlock += '\0';
  return const_cast<char*>(envBlock.c_str());
}

BOOL FreeEnvironmentStringsA(LPSTR penv) { return TRUE; }

SDL_Renderer* GetSDLRenderer(IDirectDraw* ddraw) {
  auto it = g_ddrawToRenderer.find(ddraw);
  return (it != g_ddrawToRenderer.end()) ? it->second : nullptr;
}

LPWSTR GetEnvironmentStringsW() { return NULL; }

BOOL FreeEnvironmentStringsW(LPWSTR penv) { return TRUE; }

DWORD GetFileType(HANDLE hFile) {
  (void)hFile;
  return 1;
}

void SetHandleCount(UINT uNumber) { (void)uNumber; }

UINT GetOEMCP() { return 0; }

UINT GetACP() { return 0; }

BOOL GetCPInfo(UINT CodePage, LPCPINFO lpCPInfo) { return TRUE; }

// Icon loading

HICON LoadIconA(HINSTANCE hInstance, LPCSTR lpIconName) {
  InitSDLTranslationLayer();

  int iconSize = 32;
  SDL_Surface* iconSurface = nullptr;

  if ((size_t)lpIconName <= 0xffff) {
    DWORD iconId = (DWORD)(size_t)lpIconName;

    iconSurface = SDL_CreateSurface(iconSize, iconSize, SDL_PIXELFORMAT_ARGB8888);

    if (iconSurface) {
      const SDL_PixelFormatDetails* fmtDetails =
          SDL_GetPixelFormatDetails(iconSurface->format);

      Uint32 color;
      switch (iconId) {
      case IDI_APPLICATION:
        color = SDL_MapRGB(fmtDetails, nullptr, 0, 120, 215);
        break;
      case IDI_ERROR:
        color = SDL_MapRGB(fmtDetails, nullptr, 255, 0, 0);
        break;
      case IDI_WARNING:
        color = SDL_MapRGB(fmtDetails, nullptr, 255, 165, 0);
        break;
      case IDI_INFORMATION:
        color = SDL_MapRGB(fmtDetails, nullptr, 0, 120, 215);
        break;
      case IDI_QUESTION:
        color = SDL_MapRGB(fmtDetails, nullptr, 0, 120, 215);
        break;
      default:
        color = SDL_MapRGB(fmtDetails, nullptr, 128, 128, 128);
        break;
      }

      SDL_FillSurfaceRect(iconSurface, nullptr, color);
    }
  }
  else {
    iconSurface = SDL_LoadBMP(lpIconName);

    if (!iconSurface) {
      std::string iconPath = lpIconName;
      if (iconPath.find(".ico") != std::string::npos) {
        iconPath.replace(iconPath.find(".ico"), 4, ".bmp");
        iconSurface = SDL_LoadBMP(iconPath.c_str());
      }
      if (!iconSurface && iconPath.find(".bmp") == std::string::npos) {
        iconPath = lpIconName;
        iconPath += ".bmp";
        iconSurface = SDL_LoadBMP(iconPath.c_str());
      }
    }
  }

  if (!iconSurface) {
    g_lastError = ERROR_FILE_NOT_FOUND;
    return nullptr;
  }

  HICON hIcon = (HICON)((size_t)iconSurface + 0x10000);
  g_iconToSurface[hIcon] = iconSurface;

  g_lastError = ERROR_SUCCESS;
  return hIcon;
}

// File operations

HANDLE CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode,
                   SECURITY_ATTRIBUTES* lpSecurityAttributes,
                   DWORD dwCreationDisposition,
                   DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
  if (!lpFileName) {
    g_lastError = ERROR_INVALID_HANDLE;
    return INVALID_HANDLE_VALUE;
  }

  const char* mode = nullptr;

  if (dwCreationDisposition == CREATE_ALWAYS) {
    mode = (dwDesiredAccess & GENERIC_WRITE) ? "w+b" : "wb";
  }
  else if (dwCreationDisposition == CREATE_NEW) {
    mode = (dwDesiredAccess & GENERIC_WRITE) ? "w+bx" : "wbx";
  }
  else if (dwCreationDisposition == OPEN_EXISTING) {
    mode = (dwDesiredAccess & GENERIC_WRITE) ? "r+b" : "rb";
  }
  else if (dwCreationDisposition == OPEN_ALWAYS) {
    mode = (dwDesiredAccess & GENERIC_WRITE) ? "a+b" : "rb";
  }
  else if (dwCreationDisposition == TRUNCATE_EXISTING) {
    mode = (dwDesiredAccess & GENERIC_WRITE) ? "w+b" : "wb";
  }
  else {
    mode = "rb";
  }

  FILE* fp = fopen(lpFileName, mode);
  if (!fp) {
    g_lastError = ERROR_FILE_NOT_FOUND;
    return INVALID_HANDLE_VALUE;
  }

  g_lastError = ERROR_SUCCESS;
  return (HANDLE)fp;
}

// Standard handle management

BOOL SetStdHandle(DWORD nStdHandle, HANDLE hHandle) {
  switch (nStdHandle) {
  case STD_INPUT_HANDLE:
    g_stdInput = hHandle;
    return TRUE;
  case STD_OUTPUT_HANDLE:
    g_stdOutput = hHandle;
    return TRUE;
  case STD_ERROR_HANDLE:
    g_stdError = hHandle;
    return TRUE;
  default:
    g_lastError = ERROR_INVALID_HANDLE;
    return FALSE;
  }
}

HANDLE GetStdHandle(DWORD nStdHandle) {
  switch (nStdHandle) {
  case STD_INPUT_HANDLE:
    return g_stdInput ? g_stdInput : (HANDLE)stdin;
  case STD_OUTPUT_HANDLE:
    return g_stdOutput ? g_stdOutput : (HANDLE)stdout;
  case STD_ERROR_HANDLE:
    return g_stdError ? g_stdError : (HANDLE)stderr;
  default:
    g_lastError = ERROR_INVALID_HANDLE;
    return INVALID_HANDLE_VALUE;
  }
}

int __cdecl _strcmpi(char* _Str1, char* _Str2) {
  return strcasecmp(_Str1, _Str2);
}
