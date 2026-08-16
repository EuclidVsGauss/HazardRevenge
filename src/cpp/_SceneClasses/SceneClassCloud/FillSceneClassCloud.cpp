#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/SceneClassCloud.hpp"
#include "HazardGlobals.hpp"

SceneClassCloud::SceneClassCloud(char* fileName, char* actName, int32_t startX, int32_t startY, int32_t endX, int32_t endY, int32_t maxFrame) {
  CoreActClass* actObject = new CoreActClass(fileName);
  this->fileObject = actObject;
  this->actObject = actObject->GetActionIndexByName(actName);

  int32_t startGridX_scaled = startX << 4;
  int32_t startGridY_scaled = startY << 4;
  int32_t endGridX_scaled = endX << 4;
  int32_t endGridY_scaled = endY << 4;

  this->startGridX = startGridX_scaled;
  this->startGridY = startGridY_scaled;
  this->targetGridX = endGridX_scaled;
  this->targetGridY = endGridY_scaled;

  this->toFloat_2 = (float)startGridX_scaled;
  this->toFloat_1 = (float)startGridY_scaled;

  this->maxFrame = maxFrame;
  this->currentFrame = 0;

  float divisor = (float)maxFrame;
  this->addToFloat_2 = (float)(endGridX_scaled - startGridX_scaled) / divisor;
  this->addToFloat_1 = (float)(endGridY_scaled - startGridY_scaled) / divisor;
}
