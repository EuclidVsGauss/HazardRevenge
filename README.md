# Hazard: Revenge

[![Build Status]][actions] [![Fuzzy Progress]][progress] [![Code Progress]][progress] ![macOS](https://img.shields.io/badge/macOS-%E2%9C%93-brightgreen)
![iOS](https://img.shields.io/badge/iOS-%E2%9C%93-brightgreen)
![Linux](https://img.shields.io/badge/Linux-%E2%9A%A0-orange)
![Windows](https://img.shields.io/badge/Windows-%E2%9A%A0-orange)

An educational project for building a ***rev***erse ***eng***ineered ***e***ngine for the Korean real-time action RPG ***Hazard*** (해저드).

All Windows and DirectX calls are mapped to SDL3 calls (located in the `win2sdl` directory), preserving the original game logic while enabling cross-platform compatibility on systems that support SDL3.

**Note**: Game assets (`hazard.pak`, `visual.pak`, `music.pak`) are not included and must be obtained separately.


[Build Status]: https://github.com/EuclidVsGauss/HazardRevenge/actions/workflows/build.yml/badge.svg
[actions]: https://github.com/EuclidVsGauss/HazardRevenge/actions/workflows/build.yml
[Code Progress]: https://decomp.dev/EuclidVsGauss/HazardRevenge.svg?mode=shield&measure=code&label=Exact
[Fuzzy Progress]: https://decomp.dev/EuclidVsGauss/HazardRevenge.svg?mode=shield&measure=fuzzy_match_percent&label=Fuzzy
[progress]: https://decomp.dev/EuclidVsGauss/HazardRevenge

## Features

- **32-bit → 64-bit port** — The engine is portable across 32-bit and 64-bit architectures.
- **Windowed or fullscreen** — Can be launched in either mode (see [Command-line flags](#command-line-flags) below).
- **Optional patches** — Optional patches are available in `src/hpp/HazardPatches.hpp` to toggle between English and Korean fonts, make intros skippable, and/or to address known bugs in the original game.
- **Cross-platform via SDL** — All Windows/DirectX calls are routed through SDL (2 or 3), enabling the game to run on non-Windows platforms (e.g., macOS, Linux, iOS). 

**Note:** Has only been tested on macOS and iOS so far.

## Decompilation status
[<img src="https://decomp.dev/EuclidVsGauss/HazardRevenge.svg?w=512&h=256" width="512" height="256">][progress]

## Installation

### Dependencies

- **CMake ≥ 3.16**
- A **C++17** compiler (MSVC, Clang, or GCC)
- **SDL** — one of the following discovery paths is used automatically:
    1. `find_package(SDL2/SDL3 CONFIG)` — preferred if SDL is installed system-wide
    2. `pkg-config` (`sdl2` / `sdl3`) — typical on Linux/macOS package managers
    3. **FetchContent** — if SDL isn't found locally, CMake downloads and builds SDL from source (`release-2.30.9` or `release-3.2.0` depending on `SDL_MAJOR`)
- On macOS, if SDL was installed via **Homebrew**, the dylib is copied into the app bundle's `Frameworks/` folder as a post-build step.


### Build
#### Windows / macOS / Linux 
Run `make windows`, `make macos` or `make linux` to build the executable, which will be placed in `build-win`, `build-mac` or `build-linux` accordingly. 
Place the asset files (`hazard.pak`, `visual.pak`, `music.pak`) in a directory of your choice. 
Open a terminal, navigate to the directory with the asset files and run the executable from that directory.

#### iOS
Place `hazard.pak`, `visual.pak`, `music.pak` in the directory `ios/assets/`. Place a `hazard.sav` in the directory to also transfer a save file.  
Replace `ios/Assets.xcassets/AppIcon.appiconset/icon-1024.png` by a .png of your choice (same name, 1024x1024, no alpha channel). 
Run `make ios` to build the .ipa file. Transfer it to your phone and install it via sideloading (e.g. AltStore or SideStore).

### Command-line flags
Run it in either fullscreen or windowed mode on Windows/macOS/Linux using any of the below flags

| Flag | Effect |
|------|--------|
| `--fullscreen`, `--full-screen` | Run in fullscreen (default) |
| `--window`, `--windowed` | Run in windowed mode |

### Patches
Edit `src/hpp/HazardPatches.hpp` and rebuild. Set the variable to 1 to enable the patch or 0 to disable the patch.  Notable variables:
- PATCH_SKIP_CD_CHECK
- PATCH_SKIP_ALL_INTROS
- PATCH_USE_KOREAN_FONT (**Note:** Requires `hazard.pak` with Korean font.)
- PATCH_FIX_UNEQUIP_BUG

