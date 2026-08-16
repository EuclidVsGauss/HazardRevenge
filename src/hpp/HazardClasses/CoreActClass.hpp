#ifndef HAZARD_COREACTCLASS_HPP
#define HAZARD_COREACTCLASS_HPP

#include "HazardStructs/ActContent.hpp"
#include "HazardTypedef.hpp"

struct ActContent;
struct ImageVectorWithHeader;
struct SpriteMapPair;
struct ActSummary;

class CoreActClass {

public:
  CoreActClass(char* actName);
  ~CoreActClass();

  int32_t GetActionIndexByName(char*);
  ImageVectorWithHeader* GetShadowSpriteForAction(int32_t param_1, uint16_t param_2, unsigned char param_3);
  int32_t GetFrameCountForAction(int32_t);
  void LoadActSpriteData(char* sprFilename, int32_t dimension1, int32_t dimension2);

  ActContent* txtContent;
  ImageVectorWithHeader** solidSpriteMap;
  ImageVectorWithHeader** shadowSpriteMap;
  int32_t numberSprFrames;
  int32_t numberActLines;

  __forceinline int32_t __InlineGetActionIndexFromName(char* actionName) {
    int32_t index = this->GetActionIndexByName(actionName);
    if (index == -1) {
      return 0;
    }
    return *this->txtContent[index].ptrFrameStart;
  }
};

#endif
