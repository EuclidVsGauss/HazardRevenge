#include "windows.h"
#include "win2sdl.h"

LPCSTR _lpClassName = nullptr;
LPCSTR _lpWindowName = nullptr;

bool g_sdlInitialized = false;
std::map<SDL_Window*, HWND> g_windowToHWND;
std::map<HWND, SDL_Window*> g_hwndToWindow;
std::map<HWND, LONG> g_windowStyles;
std::map<HWND, LPVOID> g_windowUserData;
std::map<HWND, SDL_Renderer*> g_hwndToRenderer;
std::queue<MSG> g_messageQueue;
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
SDL_AudioDeviceID g_audioDevice = 0;
SDL_AudioSpec g_audioSpec;
std::vector<CImpIDirectSoundBuffer*> g_activeBuffers;
SDL_mutex* g_audioMutex = nullptr;
std::map<IDirectDraw*, SDL_Renderer*> g_ddrawToRenderer;
std::map<IDirectSound*, SDL_AudioDeviceID> g_dsoundToAudio;

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

void DirectSoundAudioCallback(void* userdata, Uint8* stream, int len);

void InitSDLTranslationLayer() {
  if (!g_sdlInitialized) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS |
                 SDL_INIT_TIMER) != 0) {
      printf("FATAL: Failed to initialize SDL: %s\n", SDL_GetError());
      abort();
    }

    g_audioMutex = SDL_CreateMutex();

    SDL_AudioSpec desired;
    SDL_zero(desired);
    desired.freq = 44100;
    desired.format = AUDIO_S16LSB;
    desired.channels = 2;
    desired.samples = 1024;
    desired.callback = DirectSoundAudioCallback;
    desired.userdata = nullptr;

    g_audioDevice = SDL_OpenAudioDevice(nullptr, 0, &desired, &g_audioSpec,
                                        SDL_AUDIO_ALLOW_FREQUENCY_CHANGE |
                                            SDL_AUDIO_ALLOW_CHANNELS_CHANGE);
    if (g_audioDevice == 0) {
      printf("WARNING: Failed to open SDL audio device: %s\n", SDL_GetError());
    }
    else {
      SDL_PauseAudioDevice(g_audioDevice, 0);
    }

    SDL_ShowCursor(SDL_DISABLE);

    g_sdlInitialized = true;
    g_heaps[g_processHeap] = true;

    // Initialize command line
    g_commandLine = "program.exe";
  }
}

void ShutdownSDLTranslationLayer() {
  if (g_sdlInitialized) {
    if (g_audioDevice) {
      SDL_CloseAudioDevice(g_audioDevice);
      g_audioDevice = 0;
    }

    if (g_audioMutex) {
      SDL_DestroyMutex(g_audioMutex);
      g_audioMutex = nullptr;
    }

    // CImpIDirectDraw objects were allocated by this layer, so free them.
    // The associated renderers are owned by the window and will be cleaned up
    // below.
    for (auto& pair : g_ddrawToRenderer) {
      delete pair.first; // Free the IDirectDraw struct
    }
    g_ddrawToRenderer.clear();

    // Clean up DirectSound audio devices
    for (auto& pair : g_dsoundToAudio) {
      delete pair.first; // Free the IDirectSound struct
    }
    g_dsoundToAudio.clear();

    // Clean up any remaining renderers. This is the authoritative cleanup.
    for (auto& pair : g_hwndToRenderer) {
      if (pair.second) {
        SDL_DestroyRenderer(pair.second);
      }
    }
    g_hwndToRenderer.clear();

    // Clean up any remaining windows
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

  // Check if a renderer already exists for this window

  auto it = g_hwndToRenderer.find(hwnd);

  if (it != g_hwndToRenderer.end()) {

    return it->second;
  }

  // If not, create one

  SDL_Window* window = GetSDLWindowFromHWND(hwnd);

  if (!window) {

    return nullptr; // No such window
  }

  SDL_Renderer* renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  SDL_RenderSetLogicalSize(renderer, logicalWidth, logicalHeight);

  if (renderer) {

    g_hwndToRenderer[hwnd] = renderer;
    if (!g_mainRenderer) {
      g_mainRenderer = renderer;
    }
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

DWORD GetTickCount() { return SDL_GetTicks(); }

// Cursor functions

HCURSOR SetCursor(HCURSOR hCursor) {

  if (ARGV_PLAY_IN_FULLSCREEN) {
    SDL_ShowCursor(SDL_DISABLE);
  }

  if (hCursor == (HCURSOR)IDC_ARROW) {

    SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
  }
  else if (hCursor == (HCURSOR)IDC_WAIT) {

    SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAIT));
  }
  else if (hCursor == (HCURSOR)IDC_CROSS) {

    SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR));
  }
  else if (hCursor == (HCURSOR)IDC_HAND) {

    SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
  }

  return hCursor;
}

HCURSOR LoadCursorA(HINSTANCE hInstance, LPCSTR lpCursorName) {

  // Return the cursor ID as-is for SetCursor to interpret

  return (HCURSOR)lpCursorName;
}

BOOL GetCursorPos(LPPOINT lpPoint) {

  if (!lpPoint) {
    return FALSE;
  }

  if (ARGV_PLAY_IN_FULLSCREEN) {
    SDL_ShowCursor(SDL_DISABLE);
  }

  int winX = 0, winY = 0;
  SDL_GetMouseState(&winX, &winY);

  float lx = (float)winX;
  float ly = (float)winY;

  SDL_Renderer* renderer = g_mainRenderer;
  if (!renderer && !g_hwndToRenderer.empty()) {
    renderer = g_hwndToRenderer.begin()->second;
  }

  if (renderer) {
    SDL_RenderWindowToLogical(renderer, winX, winY, &lx, &ly);
  }

  int clX = std::max(0, std::min(logicalWidth, (int)std::floor(lx)));
  int clY = std::max(0, std::min(logicalHeight, (int)std::floor(ly)));

  lpPoint->x = clX;
  lpPoint->y = clY;

  return TRUE;
}

// Keyboard input

SHORT GetAsyncKeyState(int vKey) {

  // Map virtual key codes to SDL scancodes

  const Uint8* state = SDL_GetKeyboardState(nullptr);

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
    return (state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_RSHIFT]) ? 0x8000
                                                                      : 0;

  case VK_CONTROL:
    return (state[SDL_SCANCODE_LCTRL] || state[SDL_SCANCODE_RCTRL]) ? 0x8000
                                                                    : 0;

  case VK_LBUTTON:
    return (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(1)) ? 0x8000 : 0;

  case VK_RBUTTON:
    return (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(3)) ? 0x8000 : 0;

  case VK_C:
    return state[SDL_SCANCODE_C] ? 0x8000 : 0;

  case VK_M:
    return state[SDL_SCANCODE_M] ? 0x8000 : 0;

  case VK_W:
    return state[SDL_SCANCODE_W] ? 0x8000 : 0;

  case VK_I:
    return state[SDL_SCANCODE_I] ? 0x8000 : 0;

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

  InitSDLTranslationLayer();

  Uint32 flags = SDL_WINDOW_SHOWN;

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
  int winW = ARGV_PLAY_IN_FULLSCREEN ? nWidth : logicalWidth;
  int winH = ARGV_PLAY_IN_FULLSCREEN ? nHeight : logicalHeight;

  SDL_Window* window = SDL_CreateWindow(
      lpWindowName ? lpWindowName : "Window",
      winX, winY, winW, winH,
      ARGV_PLAY_IN_FULLSCREEN ? SDL_WINDOW_FULLSCREEN_DESKTOP : flags);

  if (!window) {

    g_lastError = ERROR_ACCESS_DENIED;

    return nullptr;
  }

  if (!g_mainWindow) {
    g_mainWindow = window;
  }

  SDL_SetWindowGrab(window, ARGV_PLAY_IN_FULLSCREEN ? SDL_TRUE : SDL_FALSE);

  if (ARGV_PLAY_IN_FULLSCREEN) {
    SDL_ShowCursor(SDL_DISABLE);
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

  case SW_SHOW:

    SDL_ShowWindow(window);

    SDL_RaiseWindow(window);

    SDL_SetWindowGrab(window, ARGV_PLAY_IN_FULLSCREEN ? SDL_TRUE : SDL_FALSE);

    if (ARGV_PLAY_IN_FULLSCREEN) {
      SDL_ShowCursor(SDL_DISABLE);
    }

    break;

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

  // Destroy the associated renderer first

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

  // In SDL, we don't need to register window classes

  // Just return success

  return TRUE;
}

HWND FindWindowA(LPCSTR lpClassName, LPCSTR lpWindowName) {

  // Simple implementation: search through our windows

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

  SDL_DisplayMode mode;

  SDL_GetCurrentDisplayMode(0, &mode);

  switch (nIndex) {

  case SM_CXSCREEN:
    return mode.w;

  case SM_CYSCREEN:
    return mode.h;

  default:
    return 0;
  }
}

HGDIOBJ GetStockObject(int i) {

  // Return dummy handles for stock objects

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

    return FALSE; // WM_QUIT returns FALSE
  }

  SDL_Event event;

  if (SDL_WaitEvent(&event)) {

    lpMsg->hwnd = nullptr;

    lpMsg->time = SDL_GetTicks();

    // Convert SDL event to Windows message

    switch (event.type) {

    case SDL_QUIT:

      PostQuitMessage(0);

      *lpMsg = g_messageQueue.front();

      g_messageQueue.pop();

      return FALSE;

    case SDL_KEYDOWN:

      lpMsg->message = WM_KEYDOWN;

      lpMsg->wParam = (WPARAM)(uintptr_t)event.key.keysym.sym;

      break;

    case SDL_KEYUP:

      lpMsg->message = WM_KEYUP;

      lpMsg->wParam = (WPARAM)(uintptr_t)event.key.keysym.sym;

      break;

    case SDL_MOUSEMOTION:

      lpMsg->message = WM_MOUSEMOVE;

      lpMsg->pt.x = event.motion.x;

      lpMsg->pt.y = event.motion.y;

      break;

    case SDL_MOUSEBUTTONDOWN:

      lpMsg->message =
          (event.button.button == SDL_BUTTON_LEFT) ? WM_LBUTTONDOWN : 0;

      break;

    case SDL_MOUSEBUTTONUP:

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

  if (SDL_PollEvent(&event)) {

    lpMsg->hwnd = nullptr;

    lpMsg->time = SDL_GetTicks();

    switch (event.type) {

    case SDL_QUIT:

      PostQuitMessage(0);

      break;

    case SDL_KEYDOWN:

      lpMsg->message = WM_KEYDOWN;

      lpMsg->wParam = (WPARAM)(uintptr_t)event.key.keysym.sym;

      break;

    case SDL_KEYUP:

      lpMsg->message = WM_KEYUP;

      lpMsg->wParam = (WPARAM)(uintptr_t)event.key.keysym.sym;

      break;
    }

    return TRUE;
  }

  return FALSE;
}

LRESULT DispatchMessageA(const MSG* lpMsg) {

  // In a full implementation, this would call the window procedure

  // For now, just return 0

  return 0;
}

BOOL TranslateMessage(const MSG* lpMsg) {

  // SDL handles key translation internally

  return TRUE;
}

LRESULT DefWindowProcA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {

  // Default message processing

  return 0;
}

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

  int buttonid;

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

  // Simplified: just use malloc

  return malloc(dwSize);
}

BOOL VirtualFree(LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType) {

  free(lpAddress);

  return TRUE;
}

// Process functions

HMODULE GetModuleHandleA(LPCSTR lpModuleName) {

  if (lpModuleName == nullptr) {

    return (HMODULE)0x400000; // Dummy base address
  }

  return nullptr;
}

void* GetProcAddress(HMODULE hModule, LPCSTR lpProcName) {

  return dlsym(RTLD_DEFAULT, lpProcName);
}

DWORD GetVersion() {

  return 0x00000a00; // Windows 10 version
}

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

LPSTR GetCommandLineA() { return const_cast<char*>(g_commandLine.c_str()); }

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

      return TRUE; // Reached end of file, but read was successful.
    }

    g_lastError = ERROR_READ_FAULT;

    return FALSE; // An error occurred.
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

    // This translation layer assumes that any handle passed to CloseHandle

    // that is not a known window handle is a file handle.

    // This may need to be expanded if other handle types are used.

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

    g_lastError = ERROR_IO_DEVICE; // Generic error

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

  // Simplified: assume UTF-8

  if (cbMultiByte == 0) {

    return cchWideChar * 4; // Estimate
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


// Helper functions to get SDL objects from DirectX interfaces

SDL_Renderer* GetSDLRenderer(IDirectDraw* ddraw) {

  auto it = g_ddrawToRenderer.find(ddraw);

  return (it != g_ddrawToRenderer.end()) ? it->second : nullptr;
}



LPWSTR GetEnvironmentStringsW() {

  // Not implemented, return null to force ANSI path

  return NULL;
}

BOOL FreeEnvironmentStringsW(LPWSTR penv) {

  // Nothing to free

  return TRUE;
}

DWORD GetFileType(HANDLE hFile) {

  // Not implemented, return disk file type

  (void)hFile;

  return 1; // FILE_TYPE_DISK
}

void SetHandleCount(UINT uNumber) {

  // Not implemented

  (void)uNumber;
}

// Dummy

UINT GetOEMCP() { return 0; }

UINT GetACP() { return 0; }

BOOL GetCPInfo(UINT CodePage, LPCPINFO lpCPInfo) { return TRUE; }

// HICON LoadIconA(HINSTANCE hInstance,LPCSTR lpIconName) {

//     return 0;

// }

// Icon loading

HICON LoadIconA(HINSTANCE hInstance, LPCSTR lpIconName) {

  InitSDLTranslationLayer();

  // Handle predefined system icons

  int iconSize = 32; // Default icon size

  SDL_Surface* iconSurface = nullptr;

  // Check if it's a system icon (resource ID)

  if ((size_t)lpIconName <= 0xffff) {

    DWORD iconId = (DWORD)(size_t)lpIconName;

    // Create a simple colored surface for system icons

    // In a real implementation, you'd load actual icon resources

    iconSurface =
        SDL_CreateRGBSurface(0, iconSize, iconSize, 32,

                             0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);

    if (iconSurface) {

      // Fill with a color based on icon type

      Uint32 color;

      switch (iconId) {

      case IDI_APPLICATION:

        color = SDL_MapRGB(iconSurface->format, 0, 120, 215); // Blue

        break;

      case IDI_ERROR:

        color = SDL_MapRGB(iconSurface->format, 255, 0, 0); // Red

        break;

      case IDI_WARNING:

        color = SDL_MapRGB(iconSurface->format, 255, 165, 0); // Orange

        break;

      case IDI_INFORMATION:

        color = SDL_MapRGB(iconSurface->format, 0, 120, 215); // Blue

        break;

      case IDI_QUESTION:

        color = SDL_MapRGB(iconSurface->format, 0, 120, 215); // Blue

        break;

      default:

        color = SDL_MapRGB(iconSurface->format, 128, 128, 128); // Gray

        break;
      }

      SDL_FillRect(iconSurface, nullptr, color);
    }
  }
  else {

    // It's a filename - try to load from file

    iconSurface = SDL_LoadBMP(lpIconName);

    if (!iconSurface) {

      // Try with common icon extensions

      std::string iconPath = lpIconName;

      // Try .ico extension (SDL doesn't support .ico natively, so try .bmp)

      if (iconPath.find(".ico") != std::string::npos) {

        iconPath.replace(iconPath.find(".ico"), 4, ".bmp");

        iconSurface = SDL_LoadBMP(iconPath.c_str());
      }

      // If still not found, try adding .bmp

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

  // Store the surface and return a handle

  HICON hIcon =
      (HICON)((size_t)iconSurface + 0x10000); // Offset to avoid collision

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

  // Map Windows creation disposition and access to fopen modes

  if (dwCreationDisposition == CREATE_ALWAYS) {

    mode = (dwDesiredAccess & GENERIC_WRITE) ? "w+b" : "wb";
  }
  else if (dwCreationDisposition == CREATE_NEW) {

    // Use 'x' mode for exclusive creation, available in C11

    mode = (dwDesiredAccess & GENERIC_WRITE) ? "w+bx" : "wbx";
  }
  else if (dwCreationDisposition == OPEN_EXISTING) {

    mode = (dwDesiredAccess & GENERIC_WRITE) ? "r+b" : "rb";
  }
  else if (dwCreationDisposition == OPEN_ALWAYS) {

    // a+b is the closest equivalent: opens for reading and appending, creates
    // if not exists.

    mode = (dwDesiredAccess & GENERIC_WRITE) ? "a+b" : "rb";
  }
  else if (dwCreationDisposition == TRUNCATE_EXISTING) {

    mode = (dwDesiredAccess & GENERIC_WRITE) ? "w+b" : "wb";
  }
  else {

    mode = "rb"; // Default to read-only
  }

  FILE* fp = fopen(lpFileName, mode);

  if (!fp) {

    g_lastError = ERROR_FILE_NOT_FOUND; // Simplified error

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
