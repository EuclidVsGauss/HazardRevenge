#ifndef WIN2SDL_H
#define WIN2SDL_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <dlfcn.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <unistd.h>
#include "../windows.h"

extern bool ARGV_PLAY_IN_FULLSCREEN;
extern LPCSTR _lpClassName;
extern LPCSTR _lpWindowName;

const int logicalWidth = 640;
const int logicalHeight = 480;

class CImpIDirectSoundBuffer;

// Internal state
extern bool g_sdlInitialized;
extern std::map<SDL_Window*, HWND> g_windowToHWND;
extern std::map<HWND, SDL_Window*> g_hwndToWindow;
extern std::map<HWND, LONG> g_windowStyles;
extern std::map<HWND, LPVOID> g_windowUserData;
extern std::map<HWND, SDL_Renderer*> g_hwndToRenderer;
extern std::queue<MSG> g_messageQueue;
extern DWORD g_lastError;
extern int g_exitCode;
extern bool g_quitPosted;
extern std::string g_commandLine;
extern HWND g_nextHwnd;
extern std::map<int, bool> g_keyStates;

// Heap management (simplified)
extern std::map<HANDLE, bool> g_heaps;
extern HANDLE g_processHeap;

// DirectX state
extern SDL_Window* g_mainWindow;
extern SDL_Renderer* g_mainRenderer;
extern SDL_AudioStream* g_audioStream; // SDL3: opaque audio stream
extern SDL_AudioSpec g_audioSpec;
extern std::vector<CImpIDirectSoundBuffer*> g_activeBuffers;
extern SDL_Mutex* g_audioMutex; // SDL3: SDL_Mutex
extern std::map<IDirectDraw*, SDL_Renderer*> g_ddrawToRenderer;
extern std::map<IDirectSound*, SDL_AudioStream*> g_dsoundToAudio;

// Icon/Surface storage
extern std::map<HICON, SDL_Surface*> g_iconToSurface;

// Standard handles
extern HANDLE g_stdInput;
extern HANDLE g_stdOutput;
extern HANDLE g_stdError;

// Internal helper functions
void InitSDLTranslationLayer();
void ShutdownSDLTranslationLayer();
SDL_Window* GetSDLWindowFromHWND(HWND hwnd);
HWND GetHWNDFromSDLWindow(SDL_Window* window);
SDL_Renderer* GetRendererForWindow(HWND hwnd);

// SDL rendering and audio context
SDL_Renderer* GetSDLRenderer(IDirectDraw* ddraw);
SDL_AudioStream* GetSDLAudioDevice(IDirectSound* dsound);

#endif // WIN2SDL_H
