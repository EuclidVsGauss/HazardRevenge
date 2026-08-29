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

  __forceinline ImageVectorWithHeader* __InlineGetSolidSpriteFrameForAction(int32_t actionId, int32_t currentFrame) {
    ImageVectorWithHeader* sprite;
    if (actionId >= 0) {
      ActContent* currentTxtContent = this->txtContent;
      ActContent* pContent = &currentTxtContent[actionId];
      int32_t frameCount = pContent->numberFrames;
      if (frameCount > 0) {
        uint16_t count = currentFrame;
        sprite = this->solidSpriteMap[pContent->ptrFrameStart[count % frameCount]];
      }
      else {
        sprite = nullptr;
      }
    }
    else {
      sprite = nullptr;
    }
    return sprite;
  }

  __forceinline ImageVectorWithHeader* __InlineGetShadowSpriteFrameForAction(int32_t actionId, int32_t currentFrame) {
    ImageVectorWithHeader* sprite;
    if (actionId >= 0) {
      ActContent* currentTxtContent = this->txtContent;
      ActContent* pContent = &currentTxtContent[actionId];
      int32_t frameCount = pContent->numberFrames;
      if (frameCount > 0) {
        uint16_t count = currentFrame;
        sprite = this->shadowSpriteMap[pContent->ptrFrameStart[count % frameCount]];
      }
      else {
        sprite = nullptr;
      }
    }
    else {
      sprite = nullptr;
    }
    return sprite;
  }

  __forceinline ImageVectorWithHeader* __InlineGetSolidSpriteFrameForActionWithOrientation(int32_t actionId, byte orientation, uint16_t currentFrame) {
    ImageVectorWithHeader* sprite;
    int32_t maxNumberFrames;
    if (actionId >= 0) {
      maxNumberFrames = this->txtContent[actionId].numberFrames;
      if (maxNumberFrames > 0) {
        int32_t directionalOffset = (orientation & 7) * this->numberSprFrames;
        int32_t frameOffset = this->txtContent[actionId].ptrFrameStart[currentFrame % maxNumberFrames];
        sprite = this->solidSpriteMap[frameOffset + directionalOffset];
      }
      else {
        sprite = nullptr;
      }
    }
    else {
      sprite = nullptr;
    }
    return sprite;
  }

  __forceinline ImageVectorWithHeader* __InlineGetShadowSpriteFrameForActionWithOrientation(int32_t actionId, byte orientation, uint16_t currentFrame) {
    ImageVectorWithHeader* sprite;
    int32_t maxNumberFrames;
    if (actionId >= 0) {
      maxNumberFrames = this->txtContent[actionId].numberFrames;
      if (maxNumberFrames > 0) {
        int32_t directionalOffset = (orientation & 7) * this->numberSprFrames;
        int32_t frameOffset = this->txtContent[actionId].ptrFrameStart[currentFrame % maxNumberFrames];
        sprite = this->shadowSpriteMap[frameOffset + directionalOffset];
      }
      else {
        sprite = nullptr;
      }
    }
    else {
      sprite = nullptr;
    }
    return sprite;
  }
};

#endif
