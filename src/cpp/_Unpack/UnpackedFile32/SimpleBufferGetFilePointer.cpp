#include "HazardClasses/UnpackedFile32.hpp"
#include "HazardGlobals.hpp"

int32_t UnpackedFile32::getFilePointer() {
  return (this->bytesReadCumulative - this->chunkBufferSize) + this->chunkOffset;
}
