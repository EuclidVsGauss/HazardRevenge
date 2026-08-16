#ifndef HAZARD_DIRECTDRAWCLASS_HPP
#define HAZARD_DIRECTDRAWCLASS_HPP

#include "HazardClasses/DirectDrawClassBase.hpp"
#include "HazardTypedef.hpp"

class DirectDrawClass : public DirectDrawClassBase {

public:
  virtual ~DirectDrawClass() {}

  void* Nothing1() override { return (void*)nullptr; }

  void* Nothing2() override { return (void*)nullptr; }

  void DrawMovie(int32_t param1_0, int32_t param2_40, int16_t* array, int32_t width_640, int32_t height_160, byte param_6) override;

  void* Nothing3() override { return (void*)nullptr; }

  void* Nothing4() override { return (void*)nullptr; }
};

#endif
