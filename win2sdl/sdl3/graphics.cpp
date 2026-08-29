#include "../windows.h"
#include "win2sdl.h"
#include "touch_overlay.h"

class CImpIDirectDrawSurface : public IDirectDrawSurface {

private:
  SDL_Renderer* m_renderer;
  SDL_Texture* m_texture;
  SDL_Surface* m_backingSurface;
  int m_width;
  int m_height;
  RECT m_lockRect;
  bool m_lockActive;

public:
  CImpIDirectDrawSurface(SDL_Renderer* renderer, int width, int height)
      : m_renderer(renderer), m_texture(nullptr), m_backingSurface(nullptr),
        m_width(width), m_height(height) {

    m_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB565,
                                  SDL_TEXTUREACCESS_STREAMING, width, height);
    m_backingSurface = SDL_CreateSurface(m_width, m_height,
                                         SDL_PIXELFORMAT_RGB565);
  }

  ~CImpIDirectDrawSurface() {
    if (m_texture) {
      SDL_DestroyTexture(m_texture);
    }
    if (m_backingSurface) {
      SDL_DestroySurface(m_backingSurface);
    }
  }

  HRESULT QueryInterface(const GUID&, void**) override { return E_FAIL; }

  ULONG AddRef() override { return 1; }

  ULONG Release() override {
    delete this;
    return 0;
  }

  HRESULT GetSurfaceDesc(DDSURFACEDESC* p) override {
    if (p) {
      memset(p, 0, sizeof(DDSURFACEDESC));
      p->dwSize = sizeof(DDSURFACEDESC);
      p->dwWidth = m_width;
      p->dwHeight = m_height;
      p->ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
      p->ddpfPixelFormat.dwRGBBitCount = 16;
      p->ddpfPixelFormat.dwRBitMask = 0xF800;
      p->ddpfPixelFormat.dwGBitMask = 0x07E0;
      p->ddpfPixelFormat.dwBBitMask = 0x001f;
    }
    return S_OK;
  }

  HRESULT IsLost() override { return S_OK; }

  HRESULT Restore() override { return S_OK; }

  HRESULT Lock(LPRECT rect, LPDDSURFACEDESC desc, DWORD flags,
               HANDLE event) override {

    if (!m_backingSurface) {
      m_backingSurface = SDL_CreateSurface(m_width, m_height,
                                           SDL_PIXELFORMAT_XRGB1555);
    }

    if (desc) {
      desc->dwSize = sizeof(DDSURFACEDESC);
      desc->dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
      desc->dwHeight = m_height;
      desc->dwWidth = m_width;
      desc->lPitch = m_backingSurface->pitch;

      if (rect) {
        m_lockRect = *rect;
        m_lockActive = true;
      }
      else {
        m_lockRect = {0, 0, m_width, m_height};
        m_lockActive = false;
      }

      if (rect && m_backingSurface) {
        int bpp = SDL_BYTESPERPIXEL(m_backingSurface->format);
        Uint8* pixelPtr = (Uint8*)m_backingSurface->pixels;
        pixelPtr += (rect->top * m_backingSurface->pitch) + (rect->left * bpp);
        desc->lpSurface = pixelPtr;

        desc->dwHeight = rect->bottom - rect->top;
        desc->dwWidth = rect->right - rect->left;
      }
      else {
        desc->lpSurface = m_backingSurface->pixels;
      }

      desc->ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
      desc->ddpfPixelFormat.dwRGBBitCount = 16;
      desc->ddpfPixelFormat.dwRBitMask = 0xF800;
      desc->ddpfPixelFormat.dwGBitMask = 0x07E0;
      desc->ddpfPixelFormat.dwBBitMask = 0x001f;
    }

    return S_OK;
  }

  HRESULT Unlock(LPRECT rect) override {
    m_lockActive = false;
    if (m_backingSurface) {
      SDL_UpdateTexture(m_texture, nullptr, m_backingSurface->pixels,
                        m_backingSurface->pitch);

      int winW = logicalWidth, winH = logicalHeight;
      if (g_mainWindow) {
        SDL_GetWindowSize(g_mainWindow, &winW, &winH);
      }
      float scale = std::min((float)winW / (float)logicalWidth, (float)winH / (float)logicalHeight);
      float gameW = (float)logicalWidth * scale;
      float gameH = (float)logicalHeight * scale;
      float gameX = (winW - gameW) * 0.5f;
      float gameY = (winH - gameH) * 0.5f;
      SDL_FRect gameDst = { gameX, gameY, gameW, gameH };

      SDL_SetRenderDrawColor(m_renderer, 15, 17, 23, 255);
      SDL_RenderClear(m_renderer);

      SDL_RenderTexture(m_renderer, m_texture, nullptr, &gameDst);

      SDL_SetRenderDrawColor(m_renderer, 45, 52, 70, 255);
      SDL_RenderRect(m_renderer, &gameDst);

#if TOUCH_OVERLAY_ENABLED
      TouchOverlay_Render(m_renderer, winW, winH, gameDst);
#endif

      SDL_RenderPresent(m_renderer);
    }
    return S_OK;
  }

  HRESULT Blt(LPRECT, IDirectDrawSurface*, LPRECT, DWORD, void*) override {
    return S_OK;
  }
};

class CImpIDirectDraw : public IDirectDraw {

private:
  SDL_Renderer* m_renderer;
  SDL_Window* m_window;

public:
  CImpIDirectDraw(SDL_Renderer* renderer, SDL_Window* window)
      : m_renderer(renderer), m_window(window) {}

  HRESULT QueryInterface(const GUID&, void**) override { return E_FAIL; }

  ULONG AddRef() override { return 1; }

  ULONG Release() override {
    delete this;
    return 0;
  }

  HRESULT SetCooperativeLevel(HWND, DWORD) override { return S_OK; }

  HRESULT SetDisplayMode(DWORD width, DWORD height, DWORD bpp) override {
    if (m_window) {
      SDL_WindowFlags flags = SDL_GetWindowFlags(m_window);
      if (!(flags & SDL_WINDOW_FULLSCREEN)) {
        SDL_SetWindowSize(m_window, width, height);
      }
    }
    return S_OK;
  }

  HRESULT RestoreDisplayMode() override { return S_OK; }

  HRESULT CreateSurface(DDSURFACEDESC* desc, IDirectDrawSurface** surf,
                        IUnknown* unk) override {

    int width = 0;
    int height = 0;

    if (desc->dwFlags & DDSD_CAPS &&
        desc->ddsCaps.dwCaps & DDSCAPS_PRIMARYSURFACE) {
      width = logicalWidth;
      height = logicalHeight;
    }
    else {
      width = (desc->dwFlags & DDSD_WIDTH) && desc->dwWidth ? desc->dwWidth : logicalWidth;
      height = (desc->dwFlags & DDSD_HEIGHT) && desc->dwHeight ? desc->dwHeight : logicalHeight;
    }

    *surf = new CImpIDirectDrawSurface(m_renderer, width, height);
    return S_OK;
  }
};

HRESULT DirectDrawCreate(LPGUID lpGUID, IDirectDraw** lplpDD,
                         LPUNKNOWN pUnkOuter) {
  InitSDLTranslationLayer();

  if (!lplpDD) {
    return E_FAIL;
  }

  HWND hwnd = nullptr;
  if (!g_hwndToWindow.empty()) {
    hwnd = g_hwndToWindow.begin()->first;
  }

  if (!hwnd) {
    hwnd = CreateWindowExA(0, _lpClassName, _lpWindowName, WS_VISIBLE,
                           CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,
                           NULL, NULL, NULL, NULL);
    if (!hwnd) {
      return E_FAIL;
    }
  }

  SDL_Window* window = GetSDLWindowFromHWND(hwnd);
  SDL_Renderer* renderer = GetRendererForWindow(hwnd);
  if (!renderer) {
    return E_FAIL;
  }

  IDirectDraw* ddraw = new CImpIDirectDraw(renderer, window);
  g_ddrawToRenderer[ddraw] = renderer;
  *lplpDD = ddraw;

  return DD_OK;
}
