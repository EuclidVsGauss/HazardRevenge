#ifndef WIN2SDL_WINDOWS_H
#define WIN2SDL_WINDOWS_H

#include <SDL.h>
#include <map>

// Basic Windows types
typedef short SHORT;
typedef size_t SIZE_T;
typedef void* HWND;
typedef void* HINSTANCE;
typedef void* HCURSOR;
typedef void* HANDLE;
typedef void* HMODULE;
typedef void* HGDIOBJ;
typedef void* LPVOID;
typedef const void* LPCVOID;
typedef char* LPSTR;
typedef const char* LPCSTR;
typedef uint32_t DWORD;
typedef uint32_t ULONG;
typedef int32_t LONG;
typedef int BOOL;
typedef unsigned char BYTE;
typedef BYTE *LPBYTE;
typedef unsigned short WORD;
typedef unsigned int UINT;
typedef void* LPARAM;
typedef UINT WPARAM;
typedef LONG LRESULT;
typedef void* HBRUSH;
typedef void* HICON;
typedef void* HMENU;

// More basic Windows types from winnt.h, etc.
typedef int64_t LONGLONG;
typedef uint64_t ULONGLONG;
typedef wchar_t WCHAR;
typedef WCHAR* LPWSTR;
typedef const WCHAR* LPCWSTR;
typedef LPWSTR LPWCH;
typedef const WCHAR *LPCWCH;
typedef BOOL *LPBOOL;
typedef WORD* LPWORD;
typedef DWORD* LPDWORD;
typedef uintptr_t UINT_PTR;
typedef void* PVOID;
typedef DWORD LCID;
typedef int (*FARPROC)();

typedef char CHAR;
typedef unsigned short ATOM;

// Dummy/forward-declared structures for compilation
struct _EXCEPTION_RECORD;
struct _CONTEXT;
typedef struct _EXCEPTION_POINTERS {
    struct _EXCEPTION_RECORD *ExceptionRecord;
    struct _CONTEXT *ContextRecord;
} EXCEPTION_POINTERS, *PEXCEPTION_POINTERS;
typedef PEXCEPTION_POINTERS LPEXCEPTION_POINTERS;
typedef struct _EXCEPTION_RECORD EXCEPTION_RECORD, *PEXCEPTION_RECORD;

// Ignore MSVC-specific calling conventions
#define __fastcall
#define __thiscall
#define __cdecl
#define WINAPI

// Exception handling function pointer
typedef LONG (WINAPI *LPTOP_LEVEL_EXCEPTION_FILTER)(PEXCEPTION_POINTERS ExceptionInfo);


// Constants
#define TRUE 1
#define FALSE 0
#define MAX_PATH 260
#define INFINITE 0xFFFFFFFF

// Window styles
#define WS_OVERLAPPED 0x00000000L
#define WS_POPUP 0x80000000L
#define WS_VISIBLE 0x10000000L
#define WS_CAPTION 0x00C00000L
#define WS_SYSMENU 0x00080000L
#define WS_THICKFRAME 0x00040000L
#define WS_MINIMIZEBOX 0x00020000L
#define WS_MAXIMIZEBOX 0x00010000L
#define WS_OVERLAPPEDWINDOW (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)

#define CW_USEDEFAULT ((int)0x80000000)

// ShowWindow commands
#define SW_HIDE 0
#define SW_SHOW 5
#define SW_MINIMIZE 6
#define SW_RESTORE 9

// MessageBox flags
#define MB_OK 0x00000000L
#define MB_OKCANCEL 0x00000001L
#define MB_YESNO 0x00000004L
#define MB_ICONERROR 0x00000010L
#define MB_ICONWARNING 0x00000030L
#define MB_ICONINFORMATION 0x00000040L
#define IDOK 1
#define IDCANCEL 2
#define IDYES 6
#define IDNO 7

// Virtual key codes
#define VK_LBUTTON 0x01
#define VK_RBUTTON 0x02
#define VK_SHIFT 0x10
#define VK_CONTROL 0x11
#define VK_ESCAPE 0x1B
#define VK_SPACE 0x20
#define VK_LEFT 0x25
#define VK_UP 0x26
#define VK_RIGHT 0x27
#define VK_DOWN 0x28
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_C 0x43
#define VK_F 0x46
#define VK_I 0x49
#define VK_K 0x4B
#define VK_M 0x4D
#define VK_P 0x50
#define VK_U 0x55
#define VK_W 0x57
#define VK_F1 0x70
#define VK_F2 0x71
#define VK_F3 0x72
#define VK_F4 0x73
#define VK_F11 0x7A


// System metrics
#define SM_CXSCREEN 0
#define SM_CYSCREEN 1

// GetWindowLong indices
#define GWL_STYLE (-16)
#define GWL_EXSTYLE (-20)
#define GWL_USERDATA (-21)

// Icon types
#define IDI_APPLICATION 32512
#define IDI_HAND 32513
#define IDI_QUESTION 32514
#define IDI_EXCLAMATION 32515
#define IDI_ASTERISK 32516
#define IDI_WINLOGO 32517
#define IDI_WARNING IDI_EXCLAMATION
#define IDI_ERROR IDI_HAND
#define IDI_INFORMATION IDI_ASTERISK

// Cursor types
#define IDC_ARROW 32512
#define IDC_WAIT 32514
#define IDC_CROSS 32515
#define IDC_HAND 32649

// Stock objects
#define WHITE_BRUSH 0
#define BLACK_BRUSH 4

// File operations
#define GENERIC_READ 0x80000000
#define GENERIC_WRITE 0x40000000
#define CREATE_ALWAYS 2
#define CREATE_NEW 1
#define OPEN_EXISTING 3
#define OPEN_ALWAYS 4
#define TRUNCATE_EXISTING 5
#define FILE_BEGIN 0
#define FILE_CURRENT 1
#define FILE_END 2
#define INVALID_HANDLE_VALUE ((HANDLE)(LONG)-1)
#define FILE_SHARE_READ 0x00000001
#define FILE_SHARE_WRITE 0x00000002
#define FILE_ATTRIBUTE_NORMAL 0x00000080

// Standard handles
#define STD_INPUT_HANDLE ((DWORD)-10)
#define STD_OUTPUT_HANDLE ((DWORD)-11)
#define STD_ERROR_HANDLE ((DWORD)-12)

// Error codes
//https://learn.microsoft.com/en-us/windows/win32/debug/system-error-codes--0-499-
//https://learn.microsoft.com/en-us/windows/win32/debug/system-error-codes--1000-1299-
#define ERROR_SUCCESS 0
#define ERROR_FILE_NOT_FOUND 2
#define ERROR_ACCESS_DENIED 5
#define ERROR_INVALID_HANDLE 6
#define ERROR_WRITE_FAULT 29
#define ERROR_READ_FAULT 30
#define ERROR_INVALID_PARAMETER 87
#define ERROR_IO_DEVICE 1117

// Drive types
#define DRIVE_UNKNOWN 0
#define DRIVE_NO_ROOT_DIR 1
#define DRIVE_REMOVABLE 2
#define DRIVE_FIXED 3
#define DRIVE_REMOTE 4
#define DRIVE_CDROM 5

// File types
#define FILE_TYPE_UNKNOWN 0x0000
#define FILE_TYPE_DISK 0x0001
#define FILE_TYPE_CHAR 0x0002
#define FILE_TYPE_PIPE 0x0003
#define FILE_TYPE_REMOTE 0x8000


#define FILE_ATTRIBUTE_TEMPORARY 0x00000100

//See https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea
#define FILE_FLAG_OVERLAPPED 0x40000000
#define FILE_FLAG_RANDOM_ACCESS 0x10000000
#define FILE_FLAG_SEQUENTIAL_SCAN 0x08000000
#define FILE_FLAG_WRITE_THROUGH 0x80000000

//See https://learn.microsoft.com/en-us/windows/win32/debug/system-error-codes--0-499-
#define NO_ERROR 0
#define ERROR_BROKEN_PIPE 0x6D

#define INVALID_SET_FILE_POINTER (-1)

// Structures
typedef struct tagPOINT {
    LONG x;
    LONG y;
} POINT, *LPPOINT;

typedef struct tagRECT {
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;
} RECT, *LPRECT;

typedef struct tagMSG {
    HWND hwnd;
    UINT message;
    WPARAM wParam;
    LPARAM lParam;
    DWORD time;
    POINT pt;
} MSG, *LPMSG;

typedef struct tagWNDCLASSA {
    UINT style;
    LRESULT (*lpfnWndProc)(HWND, UINT, WPARAM, LPARAM);
    int cbClsExtra;
    int cbWndExtra;
    HINSTANCE hInstance;
    HICON hIcon;
    HCURSOR hCursor;
    HBRUSH hbrBackground;
    LPCSTR lpszMenuName;
    LPCSTR lpszClassName;
} WNDCLASSA, *LPWNDCLASSA;

typedef struct _SYSTEMTIME {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} SYSTEMTIME;

typedef struct _STARTUPINFOA {
    DWORD cb;
    LPSTR lpReserved;
    LPSTR lpDesktop;
    LPSTR lpTitle;
    DWORD dwX;
    DWORD dwY;
    DWORD dwXSize;
    DWORD dwYSize;
    DWORD dwXCountChars;
    DWORD dwYCountChars;
    DWORD dwFillAttribute;
    DWORD dwFlags;
    WORD wShowWindow;
    WORD cbReserved2;
    BYTE* lpReserved2;
    HANDLE hStdInput;
    HANDLE hStdOutput;
    HANDLE hStdError;
} STARTUPINFOA;

typedef struct _OVERLAPPED {
    UINT_PTR Internal;
    UINT_PTR InternalHigh;
    union {
        struct {
            DWORD Offset;
            DWORD OffsetHigh;
        };
        PVOID Pointer;
    };
    HANDLE  hEvent;
} OVERLAPPED, *LPOVERLAPPED;

typedef struct _cpinfo {
    UINT  MaxCharSize;
    BYTE  DefaultChar[2];
    BYTE  LeadByte[12];
} CPINFO, *LPCPINFO;

// Window Messages (subset)
#define WM_CLOSE 0x0010
#define WM_DESTROY 0x0002
#define WM_QUIT 0x0012
#define WM_ACTIVATEAPP 0x001C
#define WM_SETCURSOR 0x0020
#define WM_KEYDOWN 0x0100
#define WM_KEYUP 0x0101
#define WM_MOUSEMOVE 0x0200
#define WM_LBUTTONDOWN 0x0201
#define WM_LBUTTONUP 0x0202

// Memory allocation flags
#define HEAP_ZERO_MEMORY 0x00000008
#define MEM_COMMIT 0x1000
#define MEM_RESERVE 0x2000
#define MEM_RELEASE 0x8000
#define PAGE_READWRITE 0x04

// Function declarations
int lstrcmp(LPCSTR a, LPCSTR b);
void __amsg_exit(int);

void GetLocalTime(SYSTEMTIME* lpSystemTime);
HCURSOR SetCursor(HCURSOR hCursor);
void PostQuitMessage(int nExitCode);
BOOL ShowWindow(HWND hWnd, int nCmdShow);
int MessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);
void Sleep(DWORD dwMilliseconds);
DWORD GetTickCount();
BOOL GetCursorPos(LPPOINT lpPoint);
SHORT GetAsyncKeyState(int vKey);
LPSTR GetCommandLineA();
HWND CreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName,
                      DWORD dwStyle, int X, int Y, int nWidth, int nHeight,
                      HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
BOOL GetMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);
BOOL PeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
LRESULT DispatchMessageA(const MSG* lpMsg);
BOOL TranslateMessage(const MSG* lpMsg);
int GetSystemMetrics(int nIndex);
HGDIOBJ GetStockObject(int i);
HWND FindWindowA(LPCSTR lpClassName, LPCSTR lpWindowName);
BOOL CloseWindow(HWND hWnd);
BOOL RegisterClassA(const WNDCLASSA* lpWndClass);
BOOL SetForegroundWindow(HWND hWnd);
BOOL SetCurrentDirectoryA(LPCSTR lpPathName);
UINT GetDriveTypeA(LPCSTR lpRootPathName);
LONG GetWindowLongA(HWND hWnd, int nIndex);
HCURSOR LoadCursorA(HINSTANCE hInstance, LPCSTR lpCursorName);
LONG SetWindowLongA(HWND hWnd, int nIndex, LONG dwNewLong);
LRESULT DefWindowProcA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

// Memory management
LPVOID HeapAlloc(HANDLE hHeap, DWORD dwFlags, SIZE_T dwBytes);
BOOL HeapFree(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem);
LPVOID HeapReAlloc(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem, SIZE_T dwBytes);
HANDLE HeapCreate(DWORD flOptions, SIZE_T dwInitialSize, SIZE_T dwMaximumSize);
BOOL HeapDestroy(HANDLE hHeap);
LPVOID VirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect);
BOOL VirtualFree(LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType);

// Process management
HMODULE GetModuleHandleA(LPCSTR lpModuleName);
void* GetProcAddress(HMODULE hModule, LPCSTR lpProcName);
DWORD GetVersion();
void GetStartupInfoA(STARTUPINFOA* lpStartupInfo);
void ExitProcess(UINT uExitCode);
HANDLE GetCurrentProcess();
BOOL TerminateProcess(HANDLE hProcess, UINT uExitCode);

// File operations
BOOL ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead,
              DWORD* lpNumberOfBytesRead, void* lpOverlapped);
BOOL WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite,
               DWORD* lpNumberOfBytesWritten, void* lpOverlapped);
BOOL CloseHandle(HANDLE hObject);
DWORD GetLastError();
DWORD SetFilePointer(HANDLE hFile, LONG lDistanceToMove, LONG* lpDistanceToMoveHigh, DWORD dwMoveMethod);
BOOL SetEndOfFile(HANDLE hFile);
BOOL FlushFileBuffers(HANDLE hFile);
HANDLE GetStdHandle(DWORD nStdHandle);
DWORD GetFileType(HANDLE hFile);
void SetHandleCount(UINT uNumber);

// String operations
int WideCharToMultiByte(UINT CodePage, DWORD dwFlags, const wchar_t* lpWideCharStr,
                        int cchWideChar, LPSTR lpMultiByteStr, int cbMultiByte,
                        LPCSTR lpDefaultChar, BOOL* lpUsedDefaultChar);
int MultiByteToWideChar(UINT CodePage, DWORD dwFlags, LPCSTR lpMultiByteStr,
                        int cbMultiByte, wchar_t* lpWideCharStr, int cchWideChar);
BOOL GetCPInfo(UINT CodePage, LPCPINFO lpCPInfo);

// Environment
LPSTR GetEnvironmentStrings();
LPWSTR GetEnvironmentStringsW();
BOOL FreeEnvironmentStringsA(LPSTR penv);
BOOL FreeEnvironmentStringsW(LPWSTR penv);

// DirectX types and interfaces
// typedef struct IDirectDraw IDirectDraw;
typedef struct IDirectSound IDirectSound;
typedef struct IDirectSoundBuffer IDirectSoundBuffer;
// typedef struct IDirectDrawSurface IDirectDrawSurface;
typedef IDirectSound* LPDIRECTSOUND;
typedef IDirectSoundBuffer* LPDIRECTSOUNDBUFFER;
typedef LPDIRECTSOUNDBUFFER* LPLPDIRECTSOUNDBUFFER;
typedef const WCHAR* LPCWSTR;
typedef void* LPGUID;
typedef void* LPUNKNOWN;
typedef long HRESULT;

// struct IDirectDrawSurface;

typedef struct _GUID {
    DWORD Data1;
    WORD  Data2;
    WORD  Data3;
    BYTE  Data4[8];
} GUID;

struct IUnknown {
    virtual HRESULT QueryInterface(const GUID&, void**) = 0;
    virtual ULONG AddRef() = 0;
    virtual ULONG Release() = 0;
    virtual ~IUnknown() {}
};

// typedef unsigned long ULONG;

typedef struct _DDSCAPS2 {
    DWORD dwCaps;
    DWORD dwCaps2;
    DWORD dwCaps3;
    DWORD dwCaps4;
} DDSCAPS2;

typedef struct _DDPIXELFORMAT {
    DWORD dwSize;
    DWORD dwFlags;
    DWORD dwFourCC;
    DWORD dwRGBBitCount;
    DWORD dwRBitMask;
    DWORD dwGBitMask;
    DWORD dwBBitMask;
    DWORD dwRGBAlphaBitMask;
} DDPIXELFORMAT;

typedef struct _DDSURFACEDESC {
    DWORD           dwSize;
    DWORD           dwFlags;
    DWORD           dwHeight;
    DWORD           dwWidth;
    LONG            lPitch;
    DWORD           dwBackBufferCount;
    DWORD           dwMipMapCount;
    DWORD           dwAlphaBitDepth;
    DWORD           dwReserved;
    LPVOID          lpSurface;
    DWORD           dwColorSpaceLowValue;
    DWORD           dwColorSpaceHighValue;
    DDPIXELFORMAT   ddpfPixelFormat;
    DDSCAPS2        ddsCaps;
    DWORD           dwTextureStage;
//} DDSURFACEDESC;
}*LPDDSURFACEDESC, DDSURFACEDESC;


#define DDSD_CAPS 0x00000001
#define DDSD_HEIGHT 0x00000002
#define DDSD_WIDTH 0x00000004
#define DDSCAPS_PRIMARYSURFACE 0x00000200

#define CALLBACK

#define S_OK 0x00000000
#define E_FAIL 0x80004005
#define E_POINTER 0x80004003L
#define DSERR_ALLOCATED 0x8878000A
#define DD_OK S_OK

//TODO, originally tWAVEFORMATEX
typedef struct WAVEFORMAT {
    WORD  wFormatTag;
    WORD  nChannels;
    DWORD nSamplesPerSec;
    DWORD nAvgBytesPerSec;
    WORD  nBlockAlign;
    //  WORD  wBitsPerSample;
    //  WORD  cbSize;
} WAVEFORMAT, *PWAVEFORMAT, *NPWAVEFORMAT, *LPWAVEFORMAT;

typedef struct pcmwaveformat_tag {
    WAVEFORMAT wf;
    WORD       wBitsPerSample;
} PCMWAVEFORMAT, *PPCMWAVEFORMAT, *NPPCMWAVEFORMAT, *LPPCMWAVEFORMAT;


typedef pcmwaveformat_tag* LPWAVEFORMATEX;

typedef struct DSBUFFERDESC {
    DWORD dwSize;
    DWORD dwFlags;
    DWORD dwBufferBytes;
    DWORD dwReserved;
    LPWAVEFORMATEX lpwfxFormat;
    GUID guid3DAlgorithm;
} DSBUFFERDESC;

typedef DSBUFFERDESC *LPCDSBUFFERDESC;

typedef struct _DDSURFACEDESC2 {
  DWORD      dwSize;
  DWORD      dwFlags;
  DWORD      dwHeight;
  DWORD      dwWidth;
  union {
    LONG  lPitch;
    DWORD dwLinearSize;
  } DUMMYUNIONNAMEN;
  DDSCAPS2   ddsCaps;
  DWORD      dwTextureStage;
} *LPDDSURFACEDESC2, DDSURFACEDESC2;

// DirectDraw Surface interface (simplified)
class IDirectDrawSurface : public IUnknown { // __stdcall?
public:
    virtual HRESULT GetSurfaceDesc(DDSURFACEDESC*) = 0;
    virtual HRESULT IsLost() = 0;
    virtual HRESULT Restore() = 0;
    virtual HRESULT Lock(LPRECT,LPDDSURFACEDESC,DWORD,HANDLE) = 0;
    virtual HRESULT Unlock( LPRECT) = 0;
    virtual HRESULT Blt(LPRECT,IDirectDrawSurface*,LPRECT,DWORD,void*) = 0;
};

// DirectDraw interface (simplified)
class IDirectDraw : public IUnknown { // __stdcall?
public:
    virtual HRESULT SetCooperativeLevel(HWND, DWORD) = 0;
    virtual HRESULT SetDisplayMode(DWORD, DWORD, DWORD) = 0;
    virtual HRESULT CreateSurface(DDSURFACEDESC*, IDirectDrawSurface**, IUnknown*) = 0;
    virtual HRESULT RestoreDisplayMode() = 0;
};

// DirectSound interface (simplified)
struct IDirectSound : public IUnknown {
    virtual HRESULT SetCooperativeLevel(HWND  unnamedParam1,DWORD unnamedParam2) = 0;
    virtual HRESULT CreateSoundBuffer( LPCDSBUFFERDESC lpcDSBufferDesc, LPLPDIRECTSOUNDBUFFER lplpDirectSoundBuffer, LPUNKNOWN pUnkOuter ) = 0;
};

// DirectSound interface (simplified)
struct IDirectSoundBuffer : public IUnknown {
    virtual HRESULT GetStatus(LPDWORD lpdwStatus) = 0;
    virtual HRESULT SetCurrentPosition(DWORD unnamedParam2) = 0;
    virtual HRESULT GetCurrentPosition( LPDWORD lpdwCurrentPlayCursor, LPDWORD lpdwCurrentWriteCursor ) = 0;
    virtual HRESULT SetPan(LONG lPan) = 0;
    virtual HRESULT Play(DWORD dwReserved1, DWORD dwReserved2, DWORD dwFlags) = 0;
    virtual HRESULT Stop() = 0;
    virtual HRESULT SetVolume( LONG lVolume ) = 0;
    virtual HRESULT Lock( DWORD dwWriteCursor, DWORD dwWriteBytes, LPVOID* lplpvAudioPtr1, LPDWORD lpdwAudioBytes1, LPVOID* lplpvAudioPtr2, LPDWORD lpdwAudioBytes2, DWORD dwFlags ) = 0;
    virtual HRESULT Unlock( LPVOID lpvAudioPtr1, DWORD dwAudioBytes1, LPVOID lpvAudioPtr2, DWORD dwAudioBytes2 ) = 0;
};






// DirectX functions
HRESULT DirectDrawCreate(LPGUID lpGUID, IDirectDraw** lplpDD, LPUNKNOWN pUnkOuter);
HRESULT DirectSoundCreate(LPGUID lpGuid, IDirectSound** ppDS, LPUNKNOWN pUnkOuter);

// winnls.h (include Windows.h)
UINT GetOEMCP();
UINT GetACP();


HICON LoadIconA(HINSTANCE hInstance,LPCSTR lpIconName);

typedef struct _SECURITY_ATTRIBUTES {
  DWORD  nLength;
  LPVOID lpSecurityDescriptor;
  BOOL   bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;


HANDLE CreateFileA(
  LPCSTR                lpFileName,
  DWORD                 dwDesiredAccess,
  DWORD                 dwShareMode,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  DWORD                 dwCreationDisposition,
  DWORD                 dwFlagsAndAttributes,
  HANDLE                hTemplateFile
);

BOOL WINAPI SetStdHandle(
  DWORD  nStdHandle,
  HANDLE hHandle
);

int _stricmp(
   const char *string1,
   const char *string2
);

int __cdecl _strcmpi(char *_Str1,char *_Str2);

typedef LONG *PLONG;


#endif // WIN32_TO_SDL_H