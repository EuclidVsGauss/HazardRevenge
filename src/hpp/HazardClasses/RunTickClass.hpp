#ifndef HAZARD_RUNTICKCLASS_HPP
#define HAZARD_RUNTICKCLASS_HPP
#include "HazardTypedef.hpp"

class RunTickClass {

public:
  virtual ~RunTickClass() {}

  virtual int32_t runTick() { return 0; }
};

#endif
