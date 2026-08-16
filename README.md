# Hazard RevEngE

An educational project for building a ***rev***erse ***eng***ineered ***e***ngine for the Korean real-time action RPG ***Hazard***.

All Windows and DirectX calls are mapped to SDL2 functions (located in the `win2sdl` directory), preserving the original game logic while enabling cross-platform compatibility on systems that support SDL2.

Optional patches are available in `src/hpp/HazardPatches.hpp` to toggle between English and Korean fonts or to address known bugs in the original game.

**Note**: Game assets (`hazard.pak`, `visual.pak`, `music.pak`) are not included and must be obtained separately.