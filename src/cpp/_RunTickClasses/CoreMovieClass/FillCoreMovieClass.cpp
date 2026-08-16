#include "HazardClasses/CoreMovieClass.hpp"
#include "HazardClasses/DirectDrawClass.hpp"
#include "HazardClasses/DirectDrawClassBase.hpp"
#include "HazardClasses/MusicObjectBase.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardExterns/CoreMovieClass.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/VisualTxtItem.hpp"

CoreMovieClass::CoreMovieClass(int32_t movieIndex) {
  UnpackedFileBase* visualTxtContent;
  int16_t* dataStreamBuffer;
  int16_t* colorMapBuffer;
  LPDIRECTSOUNDBUFFER soundBuffer;
  VisualTxtItem* visualTxtItem;
  int32_t* colorMapAsInt;
  int16_t* currentItemArray;

  if (VisualFlag_InitiallyMinusOne < 0) {
    visualTxtContent = UnpackedFileBase::LoadFileFromArchive(s_visual_txt, 0x20000);
    visualTxtItem = VisualTxtItems;
    while (visualTxtItem < VisualTxtItems + 6) {
      ReadInterpolatableString(visualTxtContent, s__s__s__d,
                               visualTxtItem->visualMovieName,
                               visualTxtItem->visualSoundName,
                               &visualTxtItem->samplingRate);
      visualTxtItem = visualTxtItem + 1;
    }

    if (visualTxtContent != nullptr) {
      delete visualTxtContent;
    }
  }

  this->directDrawObject = new DirectDrawClass();
  this->callCounter = 0;
  this->nFrames = 0;
  this->bufferCountInt16 = 102400;

  dataStreamBuffer = new int16_t[102400];
  this->buffer204800 = dataStreamBuffer;
  colorMapBuffer = new int16_t[256];
  this->colorMapBuffer512b = colorMapBuffer;

  soundBuffer = RunMenuSound(
      VisualTxtItems[movieIndex].visualSoundName,
      VisualTxtItems[movieIndex].samplingRate);
  this->latestLpDirectSoundBuffer = soundBuffer;
  this->movieIndex = movieIndex;

  currentItemArray = this->buffer204800;
  memset(currentItemArray, 0, 204800);

  colorMapAsInt = (int32_t*)this->colorMapBuffer512b;
  memset(colorMapAsInt, 0, 512);

  visualTxtContent = UnpackedFileBase::LoadFileFromArchive(
      VisualTxtItems[movieIndex].visualMovieName, 0x20000);
  this->visualsUnpackedFile = visualTxtContent;
  visualTxtContent->readFile((&this->nFrames), 2);

  this->playSpeed = TimeResolution_45or15;
  TimeResolution_45or15 = 15;
  ResetRngAndAsyncKeys();
}
