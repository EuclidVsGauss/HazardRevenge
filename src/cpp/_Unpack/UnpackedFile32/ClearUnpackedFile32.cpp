#include "HazardClasses/UnpackedFile32.hpp"
#include "HazardGlobals.hpp"

UnpackedFile32::~UnpackedFile32() {
  free(this->cachedFileDataBuffer);
  WrapperCloseFileHandle(this->fileHandleId);
}
