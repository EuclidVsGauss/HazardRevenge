cmake_minimum_required(VERSION 3.16)
project(HazardRevenge CXX)

# ─── iOS toolchain settings ───────────────────────────────────────────────
if(IOS)
    set(CMAKE_OSX_ARCHITECTURES "arm64" CACHE STRING "iOS device architecture")
    set(CMAKE_OSX_SYSROOT "iphoneos" CACHE STRING "iOS SDK")
    set(CMAKE_OSX_DEPLOYMENT_TARGET "15.0" CACHE STRING "Minimum iOS version")

    # Global (all targets, including SDL's): disable Xcode code signing.
    # We ad-hoc sign the final .app ourselves, then AltStore/SideStore
    # re-signs it with the user's Apple ID.
    set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY ""
            CACHE STRING "" FORCE)
    set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED "NO"
            CACHE STRING "" FORCE)
    set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGNING_ALLOWED "NO"
            CACHE STRING "" FORCE)
    set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGN_STYLE "Manual"
            CACHE STRING "" FORCE)
    set(CMAKE_XCODE_ATTRIBUTE_DEVELOPMENT_TEAM ""
            CACHE STRING "" FORCE)
endif()

# ─── Language & warnings ──────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W3 /wd4996)
else()
    add_compile_options(-Wno-format-security -Wno-deprecated-declarations
            -Wno-unknown-pragmas -fdeclspec
            $<$<CONFIG:Debug>:-O0>
            $<$<CONFIG:Debug>:-g>
            $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
            $<$<CONFIG:Debug>:-fsanitize=address>)
    add_link_options($<$<CONFIG:Debug>:-fsanitize=address>)
endif()

# ─── Backend selection ────────────────────────────────────────────────────
# Three possible backends:
#   * Windows: native Win32 / DirectDraw from the Windows SDK.
#     The engine's own code calls the real API; no win2sdl shim, no SDL.
#   * Everything else (macOS, Linux, iOS): win2sdl shim on top of SDL 2 or 3.
if(WIN32)
    set(BACKEND "win32")
else()
    set(BACKEND "sdl")
endif()
message(STATUS "Backend: ${BACKEND}")

# ─── SDL version switch (only relevant for the "sdl" backend) ─────────────
set(SDL_MAJOR 3 CACHE STRING "SDL major version (2 or 3)")
set_property(CACHE SDL_MAJOR PROPERTY STRINGS 2 3)

set(WIN2SDL_DIR "win2sdl")
if(SDL_MAJOR EQUAL 3)
    set(SDL_PKG     "sdl3")
    set(SDL_CMAKE   "SDL3")
    set(SDL_GIT_TAG "release-3.2.0")
elseif(SDL_MAJOR EQUAL 2)
    set(SDL_PKG     "sdl2")
    set(SDL_CMAKE   "SDL2")
    set(SDL_GIT_TAG "release-2.30.9")
else()
    message(FATAL_ERROR "SDL_MAJOR must be 2 or 3")
endif()
if(BACKEND STREQUAL "sdl")
    message(STATUS "SDL: major=${SDL_MAJOR}, dir=${WIN2SDL_DIR}, tag=${SDL_GIT_TAG}")
endif()

# ─── SDL discovery: find_package → pkg-config → FetchContent ─────────────
if(BACKEND STREQUAL "win32")
    message(STATUS "SDL: skipped (native Win32 backend)")

else() # BACKEND STREQUAL "sdl"
    if(NOT IOS)
        find_package(${SDL_CMAKE} CONFIG QUIET)
        if(TARGET ${SDL_CMAKE}::${SDL_CMAKE})
            set(SDL_TARGET ${SDL_CMAKE}::${SDL_CMAKE})
            message(STATUS "SDL: using find_package(${SDL_CMAKE})")
        else()
            find_package(PkgConfig QUIET)
            if(PkgConfig_FOUND)
                pkg_check_modules(SDLPC QUIET IMPORTED_TARGET ${SDL_PKG})
                if(TARGET PkgConfig::SDLPC)
                    set(SDL_TARGET PkgConfig::SDLPC)
                    message(STATUS "SDL: using pkg-config ${SDL_PKG}")
                endif()
            endif()
        endif()
    else()
        message(STATUS "SDL: iOS target — skipping find_package/pkg-config, using FetchContent")
    endif()

    if(NOT SDL_TARGET)
        message(STATUS "SDL: fetching ${SDL_GIT_TAG} (target: ${CMAKE_SYSTEM_NAME})")
        include(FetchContent)
        FetchContent_Declare(SDL
                GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
                GIT_TAG        ${SDL_GIT_TAG}
                GIT_SHALLOW    TRUE)
        set(SDL_TESTS    OFF CACHE BOOL "" FORCE)
        set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)

        if(IOS)
            set(SDL_SHARED OFF CACHE BOOL "" FORCE)
            set(SDL_STATIC ON  CACHE BOOL "" FORCE)
        endif()

        if(SDL_MAJOR EQUAL 2)
            set(SDL2_DISABLE_SDL2MAIN ON CACHE BOOL "" FORCE)
        endif()
        FetchContent_MakeAvailable(SDL)
        if(TARGET SDL3::SDL3)
            set(SDL_TARGET SDL3::SDL3)
        elseif(TARGET SDL2::SDL2)
            set(SDL_TARGET SDL2::SDL2)
        else()
            set(SDL_TARGET SDL2::SDL2-static)
        endif()
    endif()
endif()

# ─── Sources ─────────────────────────────────────────────────────────────
set(SOURCES
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
        src/cpp/__helperLibrary/IsGreaterThanFloat.cpp
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

# ─── Backend-specific sources ─────────────────────────────────────────────
if(BACKEND STREQUAL "win32")
    list(APPEND SOURCES src/cpp/__callback/GameLoopCallback.cpp)

elseif(BACKEND STREQUAL "sdl")
    if(SDL_MAJOR EQUAL 3)
        list(APPEND SOURCES src/cpp/__callback/GameLoopCallback.sdl3.cpp)
        list(APPEND SOURCES win2sdl/sdl3/windows.cpp)
        list(APPEND SOURCES win2sdl/sdl3/audio.cpp)
        list(APPEND SOURCES win2sdl/sdl3/graphics.cpp)
    elseif(SDL_MAJOR EQUAL 2)
        list(APPEND SOURCES src/cpp/__callback/GameLoopCallback.sdl2.cpp)
        list(APPEND SOURCES win2sdl/sdl2/windows.cpp)
        list(APPEND SOURCES win2sdl/sdl2/audio.cpp)
        list(APPEND SOURCES win2sdl/sdl2/graphics.cpp)
    endif()
endif()

# ─── Target ───────────────────────────────────────────────────────────────
add_executable(HazardRevenge ${SOURCES} ${SOURCES_CLASSES} ${HEADERS})

# ─── Include directories ──────────────────────────────────────────────────
target_include_directories(HazardRevenge PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/hpp)

# win2sdl headers only on the SDL backend — on Windows they would shadow
# the real <windows.h> / <ddraw.h> etc. from the Windows SDK.
if(BACKEND STREQUAL "sdl")
    target_include_directories(HazardRevenge PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/${WIN2SDL_DIR})
endif()

# ─── Link libraries ───────────────────────────────────────────────────────
if(SDL_TARGET)
    target_link_libraries(HazardRevenge PRIVATE ${SDL_TARGET})
endif()

if(BACKEND STREQUAL "win32")
    target_link_libraries(HazardRevenge PRIVATE
            ddraw
            dsound
            winmm
            user32
            gdi32)
endif()

# ─── iOS bundle metadata ──────────────────────────────────────────────────
if(IOS)
    set_target_properties(HazardRevenge PROPERTIES
            MACOSX_BUNDLE TRUE
            MACOSX_BUNDLE_BUNDLE_NAME "HazardRevenge"
            MACOSX_BUNDLE_GUI_IDENTIFIER "com.yourname.hazardrevenge"
            MACOSX_BUNDLE_BUNDLE_VERSION "1.0"
            MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0")
endif()

if(IOS)
    set(ASSET_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ios/assets")

    # Recurse through the asset directory and add every file as a
    # resource of the app bundle.
    file(GLOB_RECURSE ASSET_FILES
            RELATIVE "${ASSET_DIR}"
            "${ASSET_DIR}/*")

    foreach(relpath IN LISTS ASSET_FILES)
        get_filename_component(subdir "${relpath}" DIRECTORY)
        target_sources(HazardRevenge PRIVATE
                "${ASSET_DIR}/${relpath}")
        set_source_files_properties("${ASSET_DIR}/${relpath}"
                PROPERTIES
                MACOSX_PACKAGE_LOCATION "Resources/${subdir}")
    endforeach()
endif()

if(IOS)
    set_target_properties(HazardRevenge PROPERTIES
            XCODE_ATTRIBUTE_ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon"
    )
endif()

if(IOS)
    set(ASSET_CATALOG "${CMAKE_CURRENT_SOURCE_DIR}/ios/Assets.xcassets")
    target_sources(HazardRevenge PRIVATE "${ASSET_CATALOG}")
    set_source_files_properties("${ASSET_CATALOG}"
            PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
endif()

if(IOS)
    set_target_properties(HazardRevenge PROPERTIES
            MACOSX_BUNDLE_INFO_PLIST
            "${CMAKE_CURRENT_SOURCE_DIR}/ios/Info.plist.in")
endif()

# ─── Output layout ────────────────────────────────────────────────────────
set_target_properties(HazardRevenge PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# ─── macOS Homebrew SDL fixup (only when SDL came from Homebrew) ──────────
if(APPLE AND NOT IOS AND NOT SDL_TARGET)
    find_program(BREW brew)
    if(BREW)
        execute_process(COMMAND ${BREW} --prefix ${SDL_PKG}
                OUTPUT_VARIABLE _sdl_prefix
                OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
        if(_sdl_prefix AND EXISTS "${_sdl_prefix}/lib/libSDL${SDL_MAJOR}.dylib")
            add_custom_command(TARGET HazardRevenge POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E make_directory
                    "$<TARGET_FILE_DIR:HazardRevenge>/../Frameworks"
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${_sdl_prefix}/lib/libSDL${SDL_MAJOR}.dylib"
                    "$<TARGET_FILE_DIR:HazardRevenge>/../Frameworks/")
            target_link_options(HazardRevenge PRIVATE
                    -Wl,-rpath,@executable_path/../Frameworks)
        endif()
    endif()
endif()