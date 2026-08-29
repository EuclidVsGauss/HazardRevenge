#include "HazardClasses/UnpackedFileTiny.hpp"

UnpackedFileTiny::~UnpackedFileTiny() throw() {

  WrapperCloseFileHandle(this->fileHandleIndex);
}
