#include "HazardPatches.hpp"
#include "HazardClasses/CoreMovieClass.hpp"
#include "HazardClasses/MusicObjectBase.hpp"
#include "HazardGlobals.hpp"

int32_t CoreMovieClass::runTick() {
  int32_t mouseInput;
  int32_t mouseY;
  int32_t mouseX;
  bool isMoviePlaying;

  GetTickCountsAndAsyncStates(&mouseX, &mouseY, &mouseInput);
  this->LoadMovieChunks();
  this->WrapperDrawMovie();
  this->callCounter++;

#if PATCH_MAKE_ALL_INTROS_SKIPPABLE == 0
  isMoviePlaying = ((this->callCounter < (int32_t)this->nFrames) && ((this->movieIndex != 0 || (InputStates128[1] == '\0'))));
#else
  isMoviePlaying = ((this->callCounter < this->nFrames) && (InputStates128[1] == '\0'));
#endif

  if (isMoviePlaying) {
    return 2;
  }
  return 0;
}
