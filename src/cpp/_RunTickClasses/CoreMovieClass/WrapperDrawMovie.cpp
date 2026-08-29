#include "HazardClasses/CoreMovieClass.hpp"
#include "HazardClasses/DirectDrawClassBase.hpp"
#include "HazardGlobals.hpp"

void __fastcall CoreMovieClass::WrapperDrawMovie() {

  this->directDrawObject->DrawMovie(0, 40, this->buffer204800, 640, 160, 0);
}
