#ifndef HAZARD_DIRECTDRAWCLASSBASE_HPP
#define HAZARD_DIRECTDRAWCLASSBASE_HPP
#include "HazardTypedef.hpp"

class DirectDrawClassBase {

public:
  virtual ~DirectDrawClassBase() {}

  virtual void* Nothing1() { return (void*)nullptr; }

  virtual void* Nothing2() { return (void*)nullptr; }

  virtual void DrawMovie(int32_t, int32_t, int16_t*, int32_t, int32_t, byte) {};

  virtual void* Nothing3() { return (void*)nullptr; }

  virtual void* Nothing4() { return (void*)nullptr; }
};

#endif
