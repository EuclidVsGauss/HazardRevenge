#ifndef HAZARD_ITEMSTATSHELPER_16INTS_HPP
#define HAZARD_ITEMSTATSHELPER_16INTS_HPP
#include "HazardTypedef.hpp"

struct ItemStatsTemplate {
  int32_t itemGroup;
  int32_t aParameter;
  int32_t bParameter;
  int32_t cParameter;
  int32_t dParameter;
  int32_t eParameter;
  int32_t fParameter;
  int32_t gParameter;
  int32_t hParameter;
  int32_t iParameter;
  int32_t jParameter;
  int32_t kParameter;
  int32_t lParameter;
  int32_t mParameter;
  int32_t nParameter;
  int32_t stopParameter;
};
typedef struct ItemStatsTemplate ItemStatsTemplate, *PItemStatsTemplate;

#endif
