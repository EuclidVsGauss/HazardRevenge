#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardGlobals.hpp"

void GameWindowBase::UpdateObjectOnGrid(int32_t newPositionX, int32_t newPositionY) {
  GameWindowBase* sceneObject;
  int32_t newGridX;
  int32_t newGridY;
  GameWindowBase* nextObj;
  GameWindowBase* prevObj;
  GameWindowBase** existingObjectInArray;

  this->matrixIndexXTimes16 = newPositionX >> 4;
  this->matrixIndexYTimes16 = newPositionY >> 4;
  newGridX = ((uint32_t)newPositionX >> 8) & 127;
  newGridY = ((uint32_t)newPositionY >> 8) & 127;
  if (((this->matrixIndexX != newGridX) || (this->matrixIndexY != newGridY)) && (this->mainSceneHandler != nullptr)) {
    existingObjectInArray = &this->mainSceneHandler->matrix_128x128[this->matrixIndexY][this->matrixIndexX];
    if (*existingObjectInArray == this) {
      *existingObjectInArray = this->previousObject;
    }
    nextObj = this->nextObject;
    prevObj = this->previousObject;
    if (nextObj != nullptr) {
      nextObj->previousObject = prevObj;
    }
    if (prevObj != nullptr) {
      prevObj->nextObject = nextObj;
    }
    this->matrixIndexY = newGridY;
    this->matrixIndexX = newGridX;
    this->nextObject = nullptr;
    sceneObject = this->mainSceneHandler->matrix_128x128[newGridY][newGridX];
    if (this != nullptr) {
      this->previousObject = sceneObject;
    }
    if (sceneObject != nullptr) {
      sceneObject->nextObject = this;
    }
    this->mainSceneHandler->matrix_128x128[this->matrixIndexY][this->matrixIndexX] = this;
  }
}
