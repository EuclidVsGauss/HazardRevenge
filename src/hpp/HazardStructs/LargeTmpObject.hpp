#ifndef HAZARD_LARGETMPOBJECT_HPP
#define HAZARD_LARGETMPOBJECT_HPP
#include "HazardTypedef.hpp"

struct LargeTmpObject {
  int32_t size;
  int16_t data[111832];
};
typedef struct LargeTmpObject LargeTmpObject, *PLargeTmpObject;

#endif
