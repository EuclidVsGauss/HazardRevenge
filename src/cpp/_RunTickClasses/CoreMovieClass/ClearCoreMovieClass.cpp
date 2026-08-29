#include "HazardClasses/CoreMovieClass.hpp"
#include "HazardClasses/DirectDrawClassBase.hpp"
#include "HazardClasses/MusicObjectBase.hpp"
#include "HazardClasses/SfxObject.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardGlobals.hpp"

CoreMovieClass::~CoreMovieClass() {
  DirectDrawClassBase* directDrawObject;

  UnpackedFileBase::CloseUnpackedFile(this->visualsUnpackedFile);
  this->directDrawObject->Nothing1();
  this->directDrawObject->Nothing4();
  delete[] this->colorMapBuffer512b;
  delete[] this->buffer204800;
  directDrawObject = this->directDrawObject;
  if (directDrawObject != nullptr) {
    delete directDrawObject;
  }
  TimeResolution_45or15 = this->playSpeed;
  if (this->movieIndex != 0) {
    PixelCalculations_DirectDrawSurface(32, 0);
  }
  PtrSfxObject->CallRuntimeFunction(this->latestLpDirectSoundBuffer);
}
