# 1. Project and CMake Setup
# =================================================
cmake_minimum_required(VERSION 3.16)
project(HazardRevenge CXX)

# 2. Modern C++ and Compiler Settings
# =================================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set standard compiler flags for warnings and debugging
set(CMAKE_CXX_FLAGS "-Wno-format-security -Wno-deprecated-declarations  -Wno-unknown-pragmas -fdeclspec")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -fsanitize=address -fsanitize-address-use-after-scope -fno-omit-frame-pointer -fdeclspec")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_EXE_LINKER_FLAGS "")

# For Apple Silicon (arm64) and a modern macOS version (e.g., Big Sur 11.0+)
set(CMAKE_OSX_ARCHITECTURES "arm64")
set(CMAKE_OSX_DEPLOYMENT_TARGET "15.0")

message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "CXX Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Targeting macOS ${CMAKE_OSX_DEPLOYMENT_TARGET} on ${CMAKE_OSX_ARCHITECTURES}")

# 3. Find Dependencies (via pkg-config)
# =================================================
find_package(PkgConfig REQUIRED)

pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
pkg_check_modules(SDL2_MIXER REQUIRED IMPORTED_TARGET SDL2_mixer)

message(STATUS "Found SDL2 via pkg-config: ${SDL2_LIBRARIES}")
message(STATUS "Found SDL2_mixer via pkg-config: ${SDL2_MIXER_LIBRARIES}")

# 4. Gather Source Files
# =================================================
# Include the project's header directory
include_directories(src/hpp win2sdl)
if(CMAKE_OSX_SYSROOT)
    include_directories(SYSTEM ${CMAKE_OSX_SYSROOT}/usr/include)
endif()

# Source files
set(SOURCES
        win2sdl/windows.cpp
        win2sdl/audio.cpp
        win2sdl/graphics.cpp
        src/main.cpp
        src/globals.cpp
        src/cpp/__helperLibrary/__fileHandling/AllocateFileHandleSlot.cpp
        src/cpp/__helperLibrary/__fileHandling/CloseAndResetStdHandle.cpp
        src/cpp/__helperLibrary/__fileHandling/GetCurentFilePointerLocation.cpp
        src/cpp/__helperLibrary/__fileHandling/GetIndexedFileHandle.cpp
        src/cpp/__helperLibrary/__fileHandling/MapErrorCode.cpp
        src/cpp/__helperLibrary/__fileHandling/OpenFileWithFlags.cpp
        src/cpp/__helperLibrary/__fileHandling/ReadFileFixedSize.cpp
        src/cpp/__helperLibrary/__fileHandling/ReadFileWithTranslation.cpp
        src/cpp/__helperLibrary/__fileHandling/SetFilePointer.cpp
        src/cpp/__helperLibrary/__fileHandling/SetFilePointerAndPadZeros.cpp
        src/cpp/__helperLibrary/__fileHandling/SetFileTextModeFlag.cpp
        src/cpp/__helperLibrary/__fileHandling/SetStdHandle.cpp
        src/cpp/__helperLibrary/__fileHandling/WrapperCloseFileHandle.cpp
        src/cpp/__helperLibrary/__fileHandling/WriteFileWithTranslation.cpp
        src/cpp/__helperLibrary/PseudoRng.cpp
        src/cpp/__helperLibrary/ReadInterpolatableString.cpp
        src/cpp/ConvertRGBPaletteTo16Bit.cpp
        src/cpp/CoreActClass/ClearCoreActClass.cpp
        src/cpp/CoreGameLoop.cpp
        src/cpp/Create16BitImageFromPalette.cpp
        src/cpp/DecodeShadowSprite.cpp
        src/cpp/DecodeSolidSprite.cpp
        src/cpp/ExitGame.cpp
        src/cpp/GetTickCountsAndAsyncStates.cpp
        src/cpp/InitializeMusicObject.cpp
        src/cpp/InitializeSfxObject.cpp
        src/cpp/IsGreaterThanFloat.cpp
        src/cpp/LoadFileFromArchive.cpp
        src/cpp/MainFunction.cpp
        src/cpp/Maximum.cpp
        src/cpp/Minimum.cpp
        src/cpp/ParseBmpFile.cpp
        src/cpp/PixelCalculations_DirectDrawSurface.cpp
        src/cpp/ProcessPakFile.cpp
        src/cpp/ReleaseDirectDraw.cpp
        src/cpp/ResetRngAndAsyncKeys.cpp
        src/cpp/RunMenuSound.cpp
        src/cpp/SaveScreenshot.cpp
        src/cpp/SetRngSeed.cpp
        src/cpp/ShutDownMusicObject.cpp
        src/cpp/ShutDownSfxObject.cpp
        src/cpp/TalkboxTextFontRelated.cpp
        src/cpp/TrackObjects.cpp
        src/cpp/ValidateDirectXInstallation.cpp
        src/cpp/WrapperMessageBoxA.cpp
)

if(APPLE)
    list(APPEND SOURCES
            src/cpp/__callback/GameLoopCallback.macos.cpp
    )
else()
    list(APPEND SOURCES
            src/cpp/__callback/GameLoopCallback.cpp
    )
endif()

file(GLOB SOURCES_CLASSES
        "src/cpp/_Animations/AnimationSpell/*.cpp"
        "src/cpp/_Animations/AnimationStatusSpell/*.cpp"
        "src/cpp/_Animations/AnimationSummon/*.cpp"
        "src/cpp/_GameWindows/GameOverWindow/*.cpp"
        "src/cpp/_GameWindows/GameWindow/*.cpp"
        "src/cpp/_GameWindows/GameWindowBase/*.cpp"
        "src/cpp/_GameWindows/GameWindowBuy/*.cpp"
        "src/cpp/_GameWindows/GameWindowCharacter/*.cpp"
        "src/cpp/_GameWindows/GameWindowDialogue/*.cpp"
        "src/cpp/_GameWindows/GameWindowInventory/*.cpp"
        "src/cpp/_GameWindows/GameWindowMenu/*.cpp"
        "src/cpp/_GameWindows/GameWindowMerchant/*.cpp"
        "src/cpp/_GameWindows/GameWindowRegroup/*.cpp"
        "src/cpp/_GameWindows/GameWindowSave/*.cpp"
        "src/cpp/_GameWindows/GameWindowSell/*.cpp"
        "src/cpp/_GameWindows/GameWindowSidebar/*.cpp"
        "src/cpp/_GameWindows/GameWindowSpellcast/*.cpp"
        "src/cpp/_GameWindows/GameWindowWeapon/*.cpp"
        "src/cpp/_RunTickClasses/CoreGameClass/*.cpp"
        "src/cpp/_RunTickClasses/CoreLoadSavedGames/*.cpp"
        "src/cpp/_RunTickClasses/CoreMovieClass/*.cpp"
        "src/cpp/_RunTickClasses/CoreStartMenu/*.cpp"
        "src/cpp/_Scene/SceneInstance/*.cpp"
        "src/cpp/_Scene/EventHandler/*.cpp"
        "src/cpp/_Scene/GridHandler/*.cpp"
        "src/cpp/_Scene/SceneHandler/*.cpp"
        "src/cpp/_SceneClasses/SceneClassAniBg/*.cpp"
        "src/cpp/_SceneClasses/SceneClassAniBg_2/*.cpp"
        "src/cpp/_SceneClasses/SceneClassBoss/*.cpp"
        "src/cpp/_SceneClasses/SceneClassBox/*.cpp"
        "src/cpp/_SceneClasses/SceneClassButton/*.cpp"
        "src/cpp/_SceneClasses/SceneClassCamera/*.cpp"
        "src/cpp/_SceneClasses/SceneClassCameraBase/*.cpp"
        "src/cpp/_SceneClasses/SceneClassCloud/*.cpp"
        "src/cpp/_SceneClasses/SceneClassCommand/*.cpp"
        "src/cpp/_SceneClasses/SceneClassDoor/*.cpp"
        "src/cpp/_SceneClasses/SceneClassGate/*.cpp"
        "src/cpp/_SceneClasses/SceneClassGate0/*.cpp"
        "src/cpp/_SceneClasses/SceneClassItem/*.cpp"
        "src/cpp/_SceneClasses/SceneClassMap/*.cpp"
        "src/cpp/_SceneClasses/SceneClassMoveTile/*.cpp"
        "src/cpp/_SceneClasses/SceneClassNoise/*.cpp"
        "src/cpp/_SceneClasses/SceneClassRect/*.cpp"
        "src/cpp/_SceneClasses/SceneClassSwitch/*.cpp"
        "src/cpp/_SceneClasses/SceneClassUser/*.cpp"
        "src/cpp/_Sound/MusicObject/*.cpp"
        "src/cpp/_Sound/SfxObject/*.cpp"
        "src/cpp/_Sound/SfxObjectBase/*.cpp"
        "src/cpp/_Unpack/UnpackedFile32/*.cpp"
        "src/cpp/_Unpack/UnpackedFile44/*.cpp"
        "src/cpp/_Unpack/UnpackedFile8248/*.cpp"
        "src/cpp/_Unpack/UnpackedFileBase/*.cpp"
        "src/cpp/_Unpack/UnpackedFileTiny/*.cpp"
        "src/cpp/BloodObject/*.cpp"
        "src/cpp/CoreActClass/*.cpp"
        "src/cpp/PathfindingState/*.cpp"
        "src/cpp/TmpPaddedObjects/*.cpp"
        "src/cpp/TmpTileLayout/*.cpp"
)

# Header files for dependency tracking
file(GLOB_RECURSE HEADERS
        "src/hpp/*.hpp"
)

# 4. Create Executable Target
# =================================================
# Create executable target with specific output name
add_executable(HazardRevenge ${SOURCES} ${SOURCES_CLASSES} ${HEADERS})

# 6. Link Libraries
# =================================================
# Link the executable against SDL2 and SDL2_mixer.
# The `SDL2::` imported targets also handle include directories automatically.
target_link_libraries(HazardRevenge PRIVATE
        PkgConfig::SDL2
        PkgConfig::SDL2_MIXER
)

set_target_properties(HazardRevenge PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)