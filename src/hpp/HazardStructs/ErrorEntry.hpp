#ifndef HAZARD_HZERRORITEM_HPP
#define HAZARD_HZERRORITEM_HPP
#include "HazardTypedef.hpp"

struct ErrorEntry {
  int32_t ErrorLowerValue;
  int32_t ErrorUpperValue;
};
typedef struct ErrorEntry ErrorEntry, *PErrorEntry;

#endif
