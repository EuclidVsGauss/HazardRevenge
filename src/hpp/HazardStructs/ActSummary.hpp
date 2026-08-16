#ifndef HAZARD_HELPEROBJECTACT_HPP
#define HAZARD_HELPEROBJECTACT_HPP

#include "HazardTypedef.hpp"

struct ActContent;

struct ActSummary {
  char actFilename[16];
  char sprFilename[16];
  int32_t actDimension1;
  int32_t actDimension2;
  int32_t numberSprFrames;
  int32_t numberActLines;
  ActContent* ptrTxtContent;
  ActSummary* formerLoadMainMenuOrAct;
};
typedef struct ActSummary ActSummary, *PActSummary;

#endif
