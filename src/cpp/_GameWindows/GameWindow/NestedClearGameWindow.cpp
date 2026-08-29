#include "HazardClasses/RenderArrays.hpp"
#include "HazardStructs/RenderBufferWrapper.hpp"
#include "HazardStructs/RenderNodeBlock.hpp"

RenderArrays::~RenderArrays() {
  delete[] (this->arrayHeight1_solids_copyFrom);
  delete[] (this->arrayHeight2_shadows_copyFrom);
  delete[] (this->arrayHeight1_copyTo);
  delete[] (this->arrayHeight2_copyTo);
}
