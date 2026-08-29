#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/RenderArrays.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/RenderListEntry.hpp"

void RenderArrays::InitializeRenderingArrays(int32_t windowWidth, int32_t windowHeight) {

  this->windowWidth = windowWidth;
  this->windowHeight = windowHeight;

  this->arrayHeight1_solids_copyFrom = (RenderListEntry * (*)[480]) new byte[windowHeight * sizeof(RenderListEntry*)];
  this->arrayHeight2_shadows_copyFrom = (RenderListEntry * (*)[480]) new int32_t*[this->windowHeight];
  this->arrayHeight1_copyTo = (RenderListEntry * (*)[480]) new byte[this->windowHeight * sizeof(RenderListEntry*)];
  this->arrayHeight2_copyTo = (RenderListEntry * (*)[480]) new byte[this->windowHeight * sizeof(RenderListEntry*)];
  this->ptrWrapper = &this->wrapper1;
  this->PrepareNextRenderBuffer();
  this->PrepareNextRenderBuffer();
}
