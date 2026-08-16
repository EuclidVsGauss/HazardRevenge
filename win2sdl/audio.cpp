#include "windows.h"
#include "win2sdl.h"



class CImpIDirectSoundBuffer : public IDirectSoundBuffer {
private:
  Uint8* m_rawBuffer;
  DWORD m_bufferSize;
  pcmwaveformat_tag m_format;
  double m_playCursor; // Fractional to allow for resampling
  LONG m_volume;
  LONG m_pan;
  bool m_isPlaying;
  bool m_isLooping;

public:
  CImpIDirectSoundBuffer(DWORD bufferSize, LPWAVEFORMATEX format)
      : m_bufferSize(bufferSize), m_playCursor(0), m_volume(0), m_pan(0),
        m_isPlaying(false), m_isLooping(false) {
    if (format) {
      m_format = *format;
    }
    else {
      memset(&m_format, 0, sizeof(m_format));
      m_format.wf.wFormatTag = 1;
      m_format.wf.nChannels = 2;
      m_format.wf.nSamplesPerSec = 44100;
      m_format.wBitsPerSample = 16;
      m_format.wf.nBlockAlign = 4;
      m_format.wf.nAvgBytesPerSec = 44100 * 4;
    }
    m_rawBuffer = (Uint8*)SDL_malloc(bufferSize);
    if (m_rawBuffer) {
      memset(m_rawBuffer, (m_format.wBitsPerSample == 8) ? 128 : 0, bufferSize);
    }

    if (g_audioMutex) {
      SDL_LockMutex(g_audioMutex);
      g_activeBuffers.push_back(this);
      SDL_UnlockMutex(g_audioMutex);
    }
  }

  ~CImpIDirectSoundBuffer() {
    if (g_audioMutex) {
      SDL_LockMutex(g_audioMutex);
      m_isPlaying = false;
      auto it = std::find(g_activeBuffers.begin(), g_activeBuffers.end(), this);
      if (it != g_activeBuffers.end()) {
        g_activeBuffers.erase(it);
      }
      SDL_UnlockMutex(g_audioMutex);
    }
    if (m_rawBuffer) {
      SDL_free(m_rawBuffer);
    }
  }

  HRESULT QueryInterface(const GUID&, void**) override { return E_FAIL; }

  ULONG AddRef() override { return 1; }

  ULONG Release() override {
    Stop();
    delete this;
    return 0;
  }

  HRESULT GetStatus(LPDWORD lpdwStatus) override {
    if (!lpdwStatus) {
      return E_POINTER;
    }
    *lpdwStatus = m_isPlaying ? 1 : 0; // DSBSTATUS_PLAYING
    if (m_isLooping) {
      *lpdwStatus |= 2; // DSBSTATUS_LOOPING
    }
    return S_OK;
  }

  HRESULT SetCurrentPosition(DWORD dwNewPosition) override {
    SDL_LockMutex(g_audioMutex);
    m_playCursor = (double)dwNewPosition;
    SDL_UnlockMutex(g_audioMutex);
    return S_OK;
  }

  HRESULT GetCurrentPosition(LPDWORD lpdwCurrentPlayCursor,
                             LPDWORD lpdwCurrentWriteCursor) override {
    if (lpdwCurrentPlayCursor) {
      *lpdwCurrentPlayCursor = (DWORD)m_playCursor % m_bufferSize;
    }
    if (lpdwCurrentWriteCursor) {
      *lpdwCurrentWriteCursor = ((DWORD)m_playCursor + 2048) % m_bufferSize;
    }
    return S_OK;
  }

  HRESULT SetPan(LONG lPan) override {
    SDL_LockMutex(g_audioMutex);
    m_pan = lPan;
    SDL_UnlockMutex(g_audioMutex);
    return S_OK;
  }

  HRESULT SetVolume(LONG lVolume) override {
    SDL_LockMutex(g_audioMutex);
    m_volume = lVolume;
    SDL_UnlockMutex(g_audioMutex);
    return S_OK;
  }

  HRESULT Lock(DWORD dwWriteCursor, DWORD dwWriteBytes, LPVOID* lplpvAudioPtr1,
               LPDWORD lpdwAudioBytes1, LPVOID* lplpvAudioPtr2,
               LPDWORD lpdwAudioBytes2, DWORD dwFlags) override {
    if (!m_rawBuffer) {
      return E_FAIL;
    }

    if (dwFlags & 1) { // DSBLOCK_FROMWRITECURSOR
                       // Just use provided cursor for now
    }
    if (dwFlags & 2) { // DSBLOCK_ENTIREBUFFER
      dwWriteCursor = 0;
      dwWriteBytes = m_bufferSize;
    }

    dwWriteCursor %= m_bufferSize;

    *lplpvAudioPtr1 = m_rawBuffer + dwWriteCursor;
    if (dwWriteCursor + dwWriteBytes > m_bufferSize) {
      *lpdwAudioBytes1 = m_bufferSize - dwWriteCursor;
      *lplpvAudioPtr2 = m_rawBuffer;
      *lpdwAudioBytes2 = dwWriteBytes - *lpdwAudioBytes1;
    }
    else {
      *lpdwAudioBytes1 = dwWriteBytes;
      *lplpvAudioPtr2 = nullptr;
      *lpdwAudioBytes2 = 0;
    }
    return S_OK;
  }

  HRESULT Unlock(LPVOID lpvAudioPtr1, DWORD dwAudioBytes1, LPVOID lpvAudioPtr2,
                 DWORD dwAudioBytes2) override {
    return S_OK;
  }

  HRESULT Play(DWORD dwReserved1, DWORD dwReserved2, DWORD dwFlags) override {
    SDL_LockMutex(g_audioMutex);
    m_isLooping = (dwFlags & 1) != 0;
    m_isPlaying = true;
    SDL_UnlockMutex(g_audioMutex);
    return S_OK;
  }

  HRESULT Stop() override {
    SDL_LockMutex(g_audioMutex);
    m_isPlaying = false;
    SDL_UnlockMutex(g_audioMutex);
    return S_OK;
  }

  bool IsPlaying() const { return m_isPlaying; }

  void Mix(float* output, int numFrames) {
    if (!m_isPlaying || !m_rawBuffer) {
      return;
    }

    float vol = std::pow(10.0f, m_volume / 2000.0f);
    float leftVol = vol;
    float rightVol = vol;
    if (m_pan < 0) {
      rightVol *= std::pow(10.0f, m_pan / 2000.0f);
    }
    else if (m_pan > 0) {
      leftVol *= std::pow(10.0f, -m_pan / 2000.0f);
    }

    double resampleStep = (double)m_format.wf.nSamplesPerSec / g_audioSpec.freq;
    int channels = m_format.wf.nChannels;
    int bits = m_format.wBitsPerSample;
    int blockAlign = m_format.wf.nBlockAlign;

    for (int i = 0; i < numFrames; ++i) {
      DWORD pos = (DWORD)m_playCursor % m_bufferSize;
      float left = 0, right = 0;

      if (bits == 8) {
        if (channels == 1) {
          left = right = (m_rawBuffer[pos] - 128) / 128.0f;
        }
        else {
          left = (m_rawBuffer[pos] - 128) / 128.0f;
          right = (m_rawBuffer[(pos + 1) % m_bufferSize] - 128) / 128.0f;
        }
      }
      else if (bits == 16) {
        if (channels == 1) {
          int16_t sample;
          memcpy(&sample, m_rawBuffer + pos, 2);
          left = right = sample / 32768.0f;
        }
        else {
          int16_t s1, s2;
          memcpy(&s1, m_rawBuffer + pos, 2);
          memcpy(&s2, m_rawBuffer + ((pos + 2) % m_bufferSize), 2);
          left = s1 / 32768.0f;
          right = s2 / 32768.0f;
        }
      }

      output[i * 2] += left * leftVol;
      output[i * 2 + 1] += right * rightVol;

      m_playCursor += resampleStep * blockAlign;
      if (!m_isLooping && m_playCursor >= m_bufferSize) {
        m_isPlaying = false;
        m_playCursor = 0;
        break;
      }
      while (m_playCursor >= (double)m_bufferSize) {
        m_playCursor -= (double)m_bufferSize;
      }
    }
  }
};

void DirectSoundAudioCallback(void* userdata, Uint8* stream, int len) {
  SDL_memset(stream, 0, len);
  if (!g_audioMutex) {
    return;
  }

  SDL_LockMutex(g_audioMutex);

  // len is in bytes. For S16 Stereo, each sample pair is 4 bytes.
  int numFrames = len / 4;
  float* mixBuffer = new float[numFrames * 2];
  SDL_memset(mixBuffer, 0, numFrames * 2 * sizeof(float));

  for (CImpIDirectSoundBuffer* buffer : g_activeBuffers) {
    buffer->Mix(mixBuffer, numFrames);
  }

  // Convert float back to S16
  Sint16* out = (Sint16*)stream;
  for (int i = 0; i < numFrames * 2; ++i) {
    float sample = mixBuffer[i];
    if (sample > 1.0f) {
      sample = 1.0f;
    }
    if (sample < -1.0f) {
      sample = -1.0f;
    }
    out[i] = (Sint16)(sample * 32767.0f);
  }

  delete[] mixBuffer;
  SDL_UnlockMutex(g_audioMutex);
}

class CImpIDirectSound : public IDirectSound {
public:
  CImpIDirectSound() {}

  ~CImpIDirectSound() {}

  HRESULT QueryInterface(const GUID&, void**) override { return E_FAIL; }

  ULONG AddRef() override { return 1; }

  ULONG Release() override {
    delete this;
    return 0;
  }

  HRESULT SetCooperativeLevel(HWND hwnd, DWORD dwLevel) override {
    return S_OK;
  }

  HRESULT CreateSoundBuffer(LPCDSBUFFERDESC lpcDSBufferDesc,
                            LPLPDIRECTSOUNDBUFFER lplpDirectSoundBuffer,
                            LPUNKNOWN pUnkOuter) override {
    if (!lpcDSBufferDesc || !lplpDirectSoundBuffer) {
      return E_POINTER;
    }
    *lplpDirectSoundBuffer = new CImpIDirectSoundBuffer(
        lpcDSBufferDesc->dwBufferBytes, lpcDSBufferDesc->lpwfxFormat);
    return S_OK;
  }
};

HRESULT DirectSoundCreate(LPGUID lpGuid, IDirectSound** ppDS,
                          LPUNKNOWN pUnkOuter) {
  InitSDLTranslationLayer();
  if (!ppDS) {
    return E_FAIL;
  }
  *ppDS = new CImpIDirectSound();
  return S_OK;
}

SDL_AudioDeviceID GetSDLAudioDevice(IDirectSound* dsound) {

  auto it = g_dsoundToAudio.find(dsound);

  return (it != g_dsoundToAudio.end()) ? it->second : 0;
}