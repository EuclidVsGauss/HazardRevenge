#ifndef WIN2SDL_TOUCH_OVERLAY_H
#define WIN2SDL_TOUCH_OVERLAY_H

#include <SDL3/SDL_platform.h>

#ifndef TOUCH_OVERLAY_ENABLED
#if defined(SDL_PLATFORM_IOS) || defined(__IPHONEOS__)
#define TOUCH_OVERLAY_ENABLED 1
#else
#define TOUCH_OVERLAY_ENABLED 0
#endif
#endif

#if TOUCH_OVERLAY_ENABLED

#include <SDL3/SDL.h>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include "../windows.h"

inline constexpr SDL_FingerID NO_FINGER = 0;

enum ButtonTheme {
  THEME_NUMBER,    // Blue / Cyan (1, 2, 3, 4, 5)
  THEME_LETTER,    // Teal / Sky (C, W, M, I)
  THEME_ESC,       // Ruby / Coral (Esc)
  THEME_OK,        // Emerald / Jade (Ok -> Right Click)
  THEME_GUARD,     // Amethyst / Purple (Guard -> Right Click)
  THEME_SPACE,     // Amber / Gold (Space)
  THEME_FN,        // Slate / Steel (F1, F2, F3, F4)
  THEME_DPAD       // Controller Indigo (Up, Down, Left, Right)
};

struct TouchOverlayButton {
  int vKey;
  const char* label;
  const char* subLabel; // e.g. "R-CLK"
  ButtonTheme theme;
  SDL_FRect rect;
  bool isPressed;
  SDL_FingerID heldByFinger;
};

struct ThemeColors {
  SDL_FColor bgNormal;
  SDL_FColor bgPressed;
  SDL_FColor borderNormal;
  SDL_FColor borderPressed;
  SDL_FColor textNormal;
  SDL_FColor textPressed;
};

inline ThemeColors GetThemeColors(ButtonTheme theme) {
  switch (theme) {
  case THEME_NUMBER: // Blue/Cyan
    return {
      { 28/255.f, 38/255.f, 58/255.f, 0.85f },
      { 37/255.f, 99/255.f, 235/255.f, 0.95f },
      { 59/255.f, 130/255.f, 246/255.f, 0.70f },
      { 147/255.f, 197/255.f, 253/255.f, 1.0f },
      { 191/255.f, 219/255.f, 254/255.f, 1.0f },
      { 255/255.f, 255/255.f, 255/255.f, 1.0f }
    };
  case THEME_LETTER: // Teal/Sky
    return {
      { 20/255.f, 44/255.f, 54/255.f, 0.85f },
      { 2/255.f, 132/255.f, 199/255.f, 0.95f },
      { 14/255.f, 165/255.f, 233/255.f, 0.70f },
      { 125/255.f, 211/255.f, 252/255.f, 1.0f },
      { 186/255.f, 230/255.f, 253/255.f, 1.0f },
      { 255/255.f, 255/255.f, 255/255.f, 1.0f }
    };
  case THEME_ESC: // Ruby / Coral
    return {
      { 55/255.f, 24/255.f, 32/255.f, 0.88f },
      { 220/255.f, 38/255.f, 38/255.f, 0.95f },
      { 239/255.f, 68/255.f, 68/255.f, 0.75f },
      { 254/255.f, 202/255.f, 202/255.f, 1.0f },
      { 254/255.f, 226/255.f, 226/255.f, 1.0f },
      { 255/255.f, 255/255.f, 255/255.f, 1.0f }
    };
  case THEME_OK: // Emerald / Green
    return {
      { 20/255.f, 52/255.f, 38/255.f, 0.88f },
      { 5/255.f, 150/255.f, 105/255.f, 0.95f },
      { 16/255.f, 185/255.f, 129/255.f, 0.80f },
      { 167/255.f, 243/255.f, 208/255.f, 1.0f },
      { 209/255.f, 250/255.f, 229/255.f, 1.0f },
      { 255/255.f, 255/255.f, 255/255.f, 1.0f }
    };
  case THEME_GUARD: // Amethyst / Violet
    return {
      { 48/255.f, 26/255.f, 64/255.f, 0.88f },
      { 126/255.f, 34/255.f, 206/255.f, 0.95f },
      { 168/255.f, 85/255.f, 247/255.f, 0.80f },
      { 233/255.f, 213/255.f, 255/255.f, 1.0f },
      { 243/255.f, 232/255.f, 255/255.f, 1.0f },
      { 255/255.f, 255/255.f, 255/255.f, 1.0f }
    };
  case THEME_SPACE: // Amber / Gold
    return {
      { 52/255.f, 40/255.f, 20/255.f, 0.88f },
      { 217/255.f, 119/255.f, 6/255.f, 0.95f },
      { 245/255.f, 158/255.f, 11/255.f, 0.80f },
      { 254/255.f, 240/255.f, 138/255.f, 1.0f },
      { 254/255.f, 243/255.f, 199/255.f, 1.0f },
      { 255/255.f, 255/255.f, 255/255.f, 1.0f }
    };
  case THEME_FN: // Slate / Steel
    return {
      { 32/255.f, 36/255.f, 46/255.f, 0.82f },
      { 71/255.f, 85/255.f, 105/255.f, 0.95f },
      { 100/255.f, 116/255.f, 139/255.f, 0.70f },
      { 226/255.f, 232/255.f, 240/255.f, 1.0f },
      { 203/255.f, 213/255.f, 225/255.f, 1.0f },
      { 255/255.f, 255/255.f, 255/255.f, 1.0f }
    };
  case THEME_DPAD: // Controller Indigo
  default:
    return {
      { 30/255.f, 34/255.f, 48/255.f, 0.88f },
      { 67/255.f, 56/255.f, 202/255.f, 0.95f },
      { 99/255.f, 102/255.f, 241/255.f, 0.80f },
      { 199/255.f, 210/255.f, 254/255.f, 1.0f },
      { 224/255.f, 231/255.f, 255/255.f, 1.0f },
      { 255/255.f, 255/255.f, 255/255.f, 1.0f }
    };
  }
}

struct TouchOverlayManager {
  std::vector<TouchOverlayButton> buttons;
  std::map<int, bool> keyStates;
  int lastWinW = 0;
  int lastWinH = 0;
  SDL_FRect lastGameDst = {0, 0, 0, 0};

  std::map<SDL_FingerID, std::pair<int, int>> gameTouches;
  SDL_FingerID gameTouchFinger = (SDL_FingerID)-1;
  int gameTouchX = 320;
  int gameTouchY = 240;
  bool gameTouchDown = false;
  bool gameTouchPressReady = true;

  std::map<SDL_FingerID, int> activeFingers;
  bool activeMouseOnButton = false;
  int mouseHeldButton = -1;

  std::pair<int, int> MapToGame(float tx, float ty) const {
    float scale = lastGameDst.w / 640.0f;
    int gameX = (int)std::clamp((tx - lastGameDst.x) / scale, 0.0f, 639.0f);
    int gameY = (int)std::clamp((ty - lastGameDst.y) / scale, 0.0f, 479.0f);
    return { gameX, gameY };
  }

  void Init() {
    buttons.clear();
    keyStates.clear();

    // ── Left Side (11 buttons) ──
    // Row 0
    buttons.push_back({ VK_1, "1", "", THEME_NUMBER, {0,0,0,0}, false, NO_FINGER });
    buttons.push_back({ VK_ESCAPE, "ESC", "PAUSE", THEME_ESC, {0,0,0,0}, false, NO_FINGER });
    // Row 1
    buttons.push_back({ VK_2, "2", "", THEME_NUMBER, {0,0,0,0}, false, NO_FINGER });
    buttons.push_back({ VK_C, "C", "", THEME_LETTER, {0,0,0,0}, false, NO_FINGER });
    // Row 2
    buttons.push_back({ VK_3, "3", "", THEME_NUMBER, {0,0,0,0}, false, NO_FINGER });
    buttons.push_back({ VK_W, "W", "", THEME_LETTER, {0,0,0,0}, false, NO_FINGER });
    // Row 3
    buttons.push_back({ VK_4, "4", "", THEME_NUMBER, {0,0,0,0}, false, NO_FINGER });
    buttons.push_back({ VK_M, "M", "", THEME_LETTER, {0,0,0,0}, false, NO_FINGER });
    // Row 4
    buttons.push_back({ VK_5, "5", "", THEME_NUMBER, {0,0,0,0}, false, NO_FINGER });
    buttons.push_back({ VK_I, "I", "", THEME_LETTER, {0,0,0,0}, false, NO_FINGER });
    // Row 5
    buttons.push_back({ VK_RBUTTON, "OK", "R-CLK", THEME_OK, {0,0,0,0}, false, NO_FINGER });

    // ── Right Side (10 buttons) ──
    // Row 0: Function keys
    buttons.push_back({ VK_F1, "F1", "", THEME_FN, {0,0,0,0}, false, NO_FINGER });
    buttons.push_back({ VK_F2, "F2", "", THEME_FN, {0,0,0,0}, false, NO_FINGER });
    buttons.push_back({ VK_F3, "F3", "", THEME_FN, {0,0,0,0}, false, NO_FINGER });
    buttons.push_back({ VK_F4, "F4", "", THEME_FN, {0,0,0,0}, false, NO_FINGER });
    // Row 1: Action keys
    buttons.push_back({ VK_SPACE, "SPACE", "", THEME_SPACE, {0,0,0,0}, false, NO_FINGER });
    buttons.push_back({ VK_RBUTTON, "GUARD", "R-CLK", THEME_GUARD, {0,0,0,0}, false, NO_FINGER });
    // Rows 2 & 3: D-Pad
    buttons.push_back({ VK_UP, "^", "", THEME_DPAD, {0,0,0,0}, false, NO_FINGER });
    buttons.push_back({ VK_LEFT, "<", "", THEME_DPAD, {0,0,0,0}, false, NO_FINGER });
    buttons.push_back({ VK_DOWN, "v", "", THEME_DPAD, {0,0,0,0}, false, NO_FINGER });
    buttons.push_back({ VK_RIGHT, ">", "", THEME_DPAD, {0,0,0,0}, false, NO_FINGER });
  }

  void UpdateLayout(int winW, int winH, const SDL_FRect& gameDst) {
    if (buttons.empty()) Init();
    lastWinW = winW;
    lastWinH = winH;
    lastGameDst = gameDst;

    bool isLandscape = (winW >= winH);

    if (isLandscape) {
      // ──────────────── Landscape Layout ────────────────
      // Left sidebar: [0 .. gameDst.x]
      float leftSpace = gameDst.x;
      float panelW = std::clamp(leftSpace - 12.0f, 100.0f, 155.0f);
      float leftX = std::max(6.0f, (leftSpace - panelW) * 0.5f);

      float colGap = 6.0f;
      float colW = (panelW - colGap) * 0.5f;
      float c0_x = leftX;
      float c1_x = leftX + colW + colGap;

      float rowGap = 5.0f;
      float rowH = std::clamp((winH - 40.0f) / 6.0f - rowGap, 32.0f, 50.0f);
      float totalLeftH = 6 * rowH + 5 * rowGap;
      float startY = (winH - totalLeftH) * 0.5f;

      // Left buttons (indices 0..10):
      // Row 0: ESC, OK
      buttons[0].rect = { c0_x, startY + 0 * (rowH + rowGap), colW, rowH };
      buttons[1].rect = { c1_x, startY + 0 * (rowH + rowGap), colW, rowH };
      // Row 1: 1, C
      buttons[2].rect = { c0_x, startY + 1 * (rowH + rowGap), colW, rowH };
      buttons[3].rect = { c1_x, startY + 1 * (rowH + rowGap), colW, rowH };
      // Row 2: 2, W
      buttons[4].rect = { c0_x, startY + 2 * (rowH + rowGap), colW, rowH };
      buttons[5].rect = { c1_x, startY + 2 * (rowH + rowGap), colW, rowH };
      // Row 3: 3, M
      buttons[6].rect = { c0_x, startY + 3 * (rowH + rowGap), colW, rowH };
      buttons[7].rect = { c1_x, startY + 3 * (rowH + rowGap), colW, rowH };
      // Row 4: 4, I
      buttons[8].rect = { c0_x, startY + 4 * (rowH + rowGap), colW, rowH };
      buttons[9].rect = { c1_x, startY + 4 * (rowH + rowGap), colW, rowH };
      // Row 5: 5 (spans full panel width)
      buttons[10].rect = { c0_x, startY + 5 * (rowH + rowGap), panelW, rowH };

      // Right sidebar: [gameDst.x + gameDst.w .. winW]
      float rightSpace = winW - (gameDst.x + gameDst.w);
      float rightPanelW = std::clamp(rightSpace - 12.0f, 110.0f, 155.0f);
      float rightX = winW - std::max(6.0f, (rightSpace - rightPanelW) * 0.5f) - rightPanelW;

      // Function keys row (F1..F4):
      float fGap = 4.0f;
      float fW = (rightPanelW - 3 * fGap) / 4.0f;
      float fH = rowH * 0.75f;
      float rStartY = startY;

      // F1, F2, F3, F4 (indices 11..14)
      for (int i = 0; i < 4; i++) {
        buttons[11 + i].rect = { rightX + i * (fW + fGap), rStartY, fW, fH };
      }

      // Action row: SPACE & GUARD (indices 15..16)
      float actY = rStartY + fH + 7.0f;
      float actW = (rightPanelW - colGap) * 0.5f;
      float actH = rowH * 0.95f;
      buttons[15].rect = { rightX, actY, actW, actH };                 // SPACE
      buttons[16].rect = { rightX + actW + colGap, actY, actW, actH }; // GUARD

      // D-Pad cluster (indices 17..20: UP, LEFT, DOWN, RIGHT)
      float dpadSize = std::clamp((rightPanelW - 12.0f) / 3.0f, 38.0f, 50.0f);
      float dpadGap = 5.0f;
      float dpadCenterX = rightX + rightPanelW * 0.5f;
      float dpadTopY = actY + actH + 10.0f;

      // UP (index 17)
      buttons[17].rect = { dpadCenterX - dpadSize * 0.5f, dpadTopY, dpadSize, dpadSize };
      // LEFT (index 18)
      buttons[18].rect = { dpadCenterX - dpadSize * 1.5f - dpadGap, dpadTopY + dpadSize + dpadGap, dpadSize, dpadSize };
      // DOWN (index 19)
      buttons[19].rect = { dpadCenterX - dpadSize * 0.5f, dpadTopY + dpadSize + dpadGap, dpadSize, dpadSize };
      // RIGHT (index 20)
      buttons[20].rect = { dpadCenterX + dpadSize * 0.5f + dpadGap, dpadTopY + dpadSize + dpadGap, dpadSize, dpadSize };

    } else {
      // ──────────────── Portrait Layout ────────────────
      float bottomY = gameDst.y + gameDst.h + 8.0f;
      float availH = winH - bottomY - 8.0f;
      float halfW = (winW - 24.0f) * 0.5f;

      // Left panel on bottom-left:
      float colGap = 5.0f;
      float colW = (halfW - colGap) * 0.5f;
      float rowGap = 4.0f;
      float rowH = std::clamp((availH - 24.0f) / 6.0f, 26.0f, 44.0f);

      for (int r = 0; r < 5; r++) {
        buttons[r * 2].rect     = { 8.0f, bottomY + r * (rowH + rowGap), colW, rowH };
        buttons[r * 2 + 1].rect = { 8.0f + colW + colGap, bottomY + r * (rowH + rowGap), colW, rowH };
      }
      buttons[10].rect = { 8.0f, bottomY + 5 * (rowH + rowGap), halfW, rowH };

      // Right panel on bottom-right:
      float rX = winW * 0.5f + 4.0f;
      float fGap = 3.0f;
      float fW = (halfW - 3 * fGap) / 4.0f;
      float fH = rowH * 0.75f;
      for (int i = 0; i < 4; i++) {
        buttons[11 + i].rect = { rX + i * (fW + fGap), bottomY, fW, fH };
      }
      float actY = bottomY + fH + 5.0f;
      float actW = (halfW - colGap) * 0.5f;
      float actH = rowH * 0.85f;
      buttons[15].rect = { rX, actY, actW, actH };
      buttons[16].rect = { rX + actW + colGap, actY, actW, actH };

      float dpadSize = std::clamp((halfW - 10.0f) / 3.0f, 30.0f, 44.0f);
      float dpadGap = 4.0f;
      float dpadCenterX = rX + halfW * 0.5f;
      float dpadTopY = actY + actH + 6.0f;
      buttons[17].rect = { dpadCenterX - dpadSize * 0.5f, dpadTopY, dpadSize, dpadSize };
      buttons[18].rect = { dpadCenterX - dpadSize * 1.5f - dpadGap, dpadTopY + dpadSize + dpadGap, dpadSize, dpadSize };
      buttons[19].rect = { dpadCenterX - dpadSize * 0.5f, dpadTopY + dpadSize + dpadGap, dpadSize, dpadSize };
      buttons[20].rect = { dpadCenterX + dpadSize * 0.5f + dpadGap, dpadTopY + dpadSize + dpadGap, dpadSize, dpadSize };
    }
  }

  int HitTest(float x, float y) {
    for (size_t i = 0; i < buttons.size(); i++) {
      const SDL_FRect& r = buttons[i].rect;
      if (x >= r.x && x <= r.x + r.w && y >= r.y && y <= r.y + r.h) {
        return (int)i;
      }
    }
    return -1;
  }

  void RecalculateKeyState(int vKey) {
    bool down = false;
    for (const auto& btn : buttons) {
      if (btn.vKey == vKey && btn.isPressed) {
        down = true;
        break;
      }
    }
    keyStates[vKey] = down;
  }

  bool ProcessEvent(const SDL_Event& event) {
    if (lastWinW <= 0 || lastWinH <= 0) return false;

    // ── Finger Touch Events ──
    if (event.type == SDL_EVENT_FINGER_DOWN) {
      float tx = event.tfinger.x * (float)lastWinW;
      float ty = event.tfinger.y * (float)lastWinH;
      int hit = HitTest(tx, ty);
      if (hit >= 0) {
        buttons[hit].isPressed = true;
        buttons[hit].heldByFinger = event.tfinger.fingerID;
        keyStates[buttons[hit].vKey] = true;
        activeFingers[event.tfinger.fingerID] = hit;
        return true;
      }
      // Check if inside game
      if (tx >= lastGameDst.x && tx <= lastGameDst.x + lastGameDst.w &&
          ty >= lastGameDst.y && ty <= lastGameDst.y + lastGameDst.h) {
        bool wasTouchDown = !gameTouches.empty();
        auto [gameX, gameY] = MapToGame(tx, ty);
        gameTouches[event.tfinger.fingerID] = { gameX, gameY };
        gameTouchDown = true;
        gameTouchFinger = event.tfinger.fingerID;
        gameTouchX = gameX;
        gameTouchY = gameY;
        if (!wasTouchDown) {
          gameTouchPressReady = false;
        }
        activeFingers[event.tfinger.fingerID] = -1;
      }
      else {
        activeFingers[event.tfinger.fingerID] = -2;
      }
      return false;
    }

    if (event.type == SDL_EVENT_FINGER_MOTION) {
      float tx = event.tfinger.x * (float)lastWinW;
      float ty = event.tfinger.y * (float)lastWinH;

      auto gameTouch = gameTouches.find(event.tfinger.fingerID);
      if (gameTouch != gameTouches.end()) {
        auto [gameX, gameY] = MapToGame(tx, ty);
        gameTouch->second = { gameX, gameY };
        if (event.tfinger.fingerID == gameTouchFinger) {
          gameTouchX = gameX;
          gameTouchY = gameY;
        }
        return false;
      }

      auto it = activeFingers.find(event.tfinger.fingerID);
      if (it != activeFingers.end() && it->second >= 0) {
        int oldHit = it->second;
        int newHit = HitTest(tx, ty);
        if (newHit != oldHit) {
          buttons[oldHit].isPressed = false;
          buttons[oldHit].heldByFinger = -1;
          RecalculateKeyState(buttons[oldHit].vKey);

          if (newHit >= 0) {
            buttons[newHit].isPressed = true;
            buttons[newHit].heldByFinger = event.tfinger.fingerID;
            keyStates[buttons[newHit].vKey] = true;
            it->second = newHit;
          } else {
            it->second = -2;
          }
        }
        return true;
      }
      return false;
    }

    if (event.type == SDL_EVENT_FINGER_UP || event.type == SDL_EVENT_FINGER_CANCELED) {
      auto gameTouch = gameTouches.find(event.tfinger.fingerID);
      if (gameTouch != gameTouches.end()) {
        gameTouches.erase(gameTouch);
        gameTouchDown = !gameTouches.empty();
        if (gameTouches.empty()) {
          gameTouchPressReady = true;
        }
        if (event.tfinger.fingerID == gameTouchFinger) {
          if (!gameTouches.empty()) {
            gameTouchFinger = gameTouches.begin()->first;
            gameTouchX = gameTouches.begin()->second.first;
            gameTouchY = gameTouches.begin()->second.second;
          }
          else {
            gameTouchFinger = (SDL_FingerID)-1;
          }
        }
      }

      auto it = activeFingers.find(event.tfinger.fingerID);
      if (it != activeFingers.end()) {
        int btnIdx = it->second;
        if (btnIdx >= 0 && btnIdx < (int)buttons.size()) {
          buttons[btnIdx].isPressed = false;
          buttons[btnIdx].heldByFinger = -1;
          RecalculateKeyState(buttons[btnIdx].vKey);
        }
        activeFingers.erase(it);
        return true;
      }
      return false;
    }

    // ── Mouse Fallback (Desktop / Simulator) ──
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT) {
      int hit = HitTest(event.button.x, event.button.y);
      if (hit >= 0) {
        buttons[hit].isPressed = true;
        keyStates[buttons[hit].vKey] = true;
        activeMouseOnButton = true;
        mouseHeldButton = hit;
        return true;
      }
    }
    if (event.type == SDL_EVENT_MOUSE_BUTTON_UP && event.button.button == SDL_BUTTON_LEFT) {
      if (activeMouseOnButton) {
        if (mouseHeldButton >= 0 && mouseHeldButton < (int)buttons.size()) {
          buttons[mouseHeldButton].isPressed = false;
          RecalculateKeyState(buttons[mouseHeldButton].vKey);
        }
        activeMouseOnButton = false;
        mouseHeldButton = -1;
        return true;
      }
    }

    return false;
  }

  void Render(SDL_Renderer* renderer, int winW, int winH, const SDL_FRect& gameDst) {
    if (buttons.empty() || winW != lastWinW || winH != lastWinH) {
      UpdateLayout(winW, winH, gameDst);
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    for (const auto& btn : buttons) {
      ThemeColors colors = GetThemeColors(btn.theme);
      const SDL_FColor& bg = btn.isPressed ? colors.bgPressed : colors.bgNormal;
      const SDL_FColor& border = btn.isPressed ? colors.borderPressed : colors.borderNormal;
      const SDL_FColor& textCol = btn.isPressed ? colors.textPressed : colors.textNormal;

      // 1. Glow on press
      if (btn.isPressed) {
        SDL_FRect glow = { btn.rect.x - 2.0f, btn.rect.y - 2.0f, btn.rect.w + 4.0f, btn.rect.h + 4.0f };
        SDL_SetRenderDrawColorFloat(renderer, border.r, border.g, border.b, 0.35f);
        SDL_RenderFillRect(renderer, &glow);
      }

      // 2. Button Body Fill
      SDL_SetRenderDrawColorFloat(renderer, bg.r, bg.g, bg.b, bg.a);
      SDL_RenderFillRect(renderer, &btn.rect);

      // 3. Bevel highlight (top edge)
      if (!btn.isPressed) {
        SDL_SetRenderDrawColorFloat(renderer, border.r * 1.2f, border.g * 1.2f, border.b * 1.2f, 0.45f);
        SDL_RenderLine(renderer, btn.rect.x + 2.0f, btn.rect.y + 1.0f, btn.rect.x + btn.rect.w - 3.0f, btn.rect.y + 1.0f);
      }

      // 4. Border Outline
      SDL_SetRenderDrawColorFloat(renderer, border.r, border.g, border.b, border.a);
      SDL_RenderRect(renderer, &btn.rect);

      // 5. Draw Arrows (for D-Pad) or Text
      float yOffset = btn.isPressed ? 1.5f : 0.0f;

      if (btn.theme == THEME_DPAD) {
        float cx = btn.rect.x + btn.rect.w * 0.5f;
        float cy = btn.rect.y + btn.rect.h * 0.5f + yOffset;
        float r = btn.rect.w * 0.26f;

        SDL_Vertex verts[3];
        verts[0].color = textCol;
        verts[1].color = textCol;
        verts[2].color = textCol;
        verts[0].tex_coord = {0,0};
        verts[1].tex_coord = {0,0};
        verts[2].tex_coord = {0,0};

        if (btn.vKey == VK_UP) {
          verts[0].position = { cx, cy - r };
          verts[1].position = { cx - r, cy + r * 0.8f };
          verts[2].position = { cx + r, cy + r * 0.8f };
        } else if (btn.vKey == VK_DOWN) {
          verts[0].position = { cx, cy + r };
          verts[1].position = { cx - r, cy - r * 0.8f };
          verts[2].position = { cx + r, cy - r * 0.8f };
        } else if (btn.vKey == VK_LEFT) {
          verts[0].position = { cx - r, cy };
          verts[1].position = { cx + r * 0.8f, cy - r };
          verts[2].position = { cx + r * 0.8f, cy + r };
        } else if (btn.vKey == VK_RIGHT) {
          verts[0].position = { cx + r, cy };
          verts[1].position = { cx - r * 0.8f, cy - r };
          verts[2].position = { cx - r * 0.8f, cy + r };
        }
        SDL_RenderGeometry(renderer, nullptr, verts, 3, nullptr, 0);

      } else {
        // Draw Text Label
        int labelLen = (int)strlen(btn.label);
        float scale = (labelLen > 4) ? 1.3f : ((btn.rect.w < 40.0f) ? 1.3f : 1.7f);

        float textW = (float)labelLen * 8.0f * scale;
        float textH = 8.0f * scale;
        float tx = btn.rect.x + (btn.rect.w - textW) * 0.5f;
        float ty = btn.rect.y + (btn.rect.h - textH) * 0.5f + yOffset;

        if (btn.subLabel && btn.subLabel[0] != '\0') {
          ty = btn.rect.y + (btn.rect.h - textH) * 0.5f - 4.0f + yOffset;
        }

        SDL_SetRenderDrawColorFloat(renderer, textCol.r, textCol.g, textCol.b, textCol.a);
        SDL_SetRenderScale(renderer, scale, scale);
        SDL_RenderDebugText(renderer, tx / scale, ty / scale, btn.label);

        // Sublabel (e.g. "R-CLK" for Ok and Guard)
        if (btn.subLabel && btn.subLabel[0] != '\0') {
          float subScale = 0.9f;
          int subLen = (int)strlen(btn.subLabel);
          float subW = (float)subLen * 8.0f * subScale;
          float subX = btn.rect.x + (btn.rect.w - subW) * 0.5f;
          float subY = ty + textH + 2.0f;
          SDL_SetRenderDrawColorFloat(renderer, textCol.r * 0.85f, textCol.g * 0.85f, textCol.b * 0.85f, 0.80f);
          SDL_SetRenderScale(renderer, subScale, subScale);
          SDL_RenderDebugText(renderer, subX / subScale, subY / subScale, btn.subLabel);
        }

        SDL_SetRenderScale(renderer, 1.0f, 1.0f);
      }
    }
  }
};

inline TouchOverlayManager& GetTouchOverlay() {
  static TouchOverlayManager s_instance;
  return s_instance;
}

inline void TouchOverlay_Init() {
  GetTouchOverlay().Init();
}

inline bool TouchOverlay_ProcessEvent(const SDL_Event& event) {
  return GetTouchOverlay().ProcessEvent(event);
}

inline void TouchOverlay_Render(SDL_Renderer* renderer, int winW, int winH, const SDL_FRect& gameDst) {
  GetTouchOverlay().Render(renderer, winW, winH, gameDst);
}

inline bool TouchOverlay_IsKeyDown(int vKey) {
  return GetTouchOverlay().keyStates[vKey];
}

inline bool TouchOverlay_IsGameTouchDown() {
  return GetTouchOverlay().gameTouchDown && GetTouchOverlay().gameTouchPressReady;
}

inline void TouchOverlay_MarkCursorSampled() {
  GetTouchOverlay().gameTouchPressReady = true;
}

inline bool TouchOverlay_GetGameTouch(int* outX, int* outY) {
  if (GetTouchOverlay().gameTouchDown) {
    if (outX) *outX = GetTouchOverlay().gameTouchX;
    if (outY) *outY = GetTouchOverlay().gameTouchY;
    return true;
  }
  return false;
}

inline bool TouchOverlay_HasActiveOverlayTouch() {
  for (const auto& btn : GetTouchOverlay().buttons) {
    if (btn.isPressed) return true;
  }
  return false;
}

inline bool TouchOverlay_IsAnyTouchActive() {
  return !GetTouchOverlay().activeFingers.empty();
}

#endif // TOUCH_OVERLAY_ENABLED

#endif // WIN2SDL_TOUCH_OVERLAY_H
