#include "HazardClasses/UnpackedFileTiny.hpp"

UnpackedFileTiny::~UnpackedFileTiny() {

  WrapperCloseFileHandle(this->fileHandleIndex);
}
