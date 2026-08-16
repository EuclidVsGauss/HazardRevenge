#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/RenderArrays.hpp"
#include "HazardExterns/GameWindow.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/RenderListEntry.hpp"

void GameWindow::RenderWithDirectDrawSurface() {
  int16_t leftBoundCandidate;
  int16_t rightBoundCandidate;
  int16_t boundaryCompare;
  HRESULT surfaceLostStatus;
  int32_t nextSegmentX;
  uint16_t* pixelBuffer;
  int16_t startBound;
  uint32_t byteLength;
  int32_t nPixelUpdates;
  RenderListEntry* shadowList;
  RenderListEntry* solidList;
  int16_t* sourcePtr;
  byte* destSurfacePtr;
  int32_t currentX;
  RenderListEntry* solidListIterator;
  int32_t pitchOffset;
  int32_t currentHeight;
  RECT windowArea;
  DDSURFACEDESC surfaceDesc;
  RenderListEntry* shadowEntry;
  RenderListEntry* shadowListIterator;
  uint16_t copyRgbMask;

  pitchOffset = 0;
  windowArea.left = this->copyOrigin1;
  windowArea.right = this->copyWindowWidth + windowArea.left;
  windowArea.top = this->copyOrigin2;
  windowArea.bottom = this->copyWindowHeight + windowArea.top;

  surfaceLostStatus = DirectDrawSurface->IsLost();
  if (surfaceLostStatus == -0x7789fe3e) {
    DirectDrawSurface->Restore();
    PauseState = 2;
  }
  surfaceDesc.dwSize = 108;
  DirectDrawSurface->Lock(&windowArea, &surfaceDesc, 0x21, (HANDLE) nullptr);
  currentHeight = 0;

  if (0 < this->copyWindowHeight) {
    shadowList = nullptr;
    do {

      if (PauseState == 0) {
        shadowList = (*this->arrayHeight2_copyTo)[currentHeight];

        for (shadowEntry = (*this->arrayHeight2_shadows_copyFrom)[currentHeight]; shadowEntry != nullptr; shadowEntry = shadowEntry->next) {
          if ((((shadowList == nullptr) || (shadowEntry->rightBound != shadowList->rightBound)) || (shadowEntry->leftBound != shadowList->leftBound)) || (shadowEntry->pixelTable != shadowList->pixelTable)) {
            if (shadowEntry != nullptr) {
              goto label_release_surface;
            }
            break;
          }
          shadowList = shadowList->next;
        }
        if (shadowList != nullptr) {
          goto label_release_surface;
        }
        shadowList = (*this->arrayHeight1_copyTo)[currentHeight];
        for (solidListIterator = (*this->arrayHeight1_solids_copyFrom)[currentHeight]; solidListIterator != nullptr; solidListIterator = solidListIterator->next) {
          if ((solidListIterator->pixelTable != shadowList->pixelTable) || (solidListIterator->leftBound != shadowList->leftBound)) {
            if (solidListIterator != nullptr) {
              goto label_release_surface;
            }
            break;
          }
          shadowList = shadowList->next;
        }
      }
      else {
      label_release_surface:
        if ((((*this->arrayHeight2_shadows_copyFrom)[currentHeight] == nullptr) && ((*this->arrayHeight2_copyTo)[currentHeight] == nullptr)) && (PauseState == 0)) {
          if (solidListIterator->pixelTable == shadowList->pixelTable) {
            boundaryCompare = solidListIterator->leftBound;
            if (shadowList->leftBound <= solidListIterator->leftBound) {
              boundaryCompare = shadowList->leftBound;
            }
          }
          else {
            boundaryCompare = solidListIterator->rightBound;
          }
          currentX = (int32_t)boundaryCompare;
          solidList = solidListIterator;
          do {
            if (currentX == solidList->leftBound) {
              solidList = solidList->next;
              solidListIterator = solidList;
            }
            if (currentX == shadowList->leftBound) {
              shadowList = shadowList->next;
            }

            if (solidList->pixelTable - solidList->rightBound == shadowList->pixelTable - shadowList->rightBound) {
              boundaryCompare = shadowList->leftBound;
              if (solidList->leftBound <= shadowList->leftBound) {
                boundaryCompare = solidList->leftBound;
              }
              nextSegmentX = (int32_t)boundaryCompare;
            }
            else {
              boundaryCompare = shadowList->leftBound;
              if (solidList->leftBound <= shadowList->leftBound) {
                boundaryCompare = solidList->leftBound;
              }
              nextSegmentX = (int32_t)boundaryCompare;
              byteLength = (nextSegmentX - currentX) * 2;

              sourcePtr = (solidList->pixelTable + (currentX - solidList->rightBound));
              destSurfacePtr = ((byte*)surfaceDesc.lpSurface + pitchOffset + (currentX * 2));

              memcpy(destSurfacePtr, sourcePtr, byteLength);
            }
            currentX = nextSegmentX;
          } while (nextSegmentX < this->copyWindowWidth);
        }
        else {
          for (solidList = (*this->arrayHeight1_solids_copyFrom)[currentHeight]; solidList != nullptr; solidList = solidList->next) {
            byteLength = ((int32_t)solidList->leftBound - (int32_t)solidList->rightBound) * 2;
            memcpy(SingleRowPixels640 + solidList->rightBound, solidList->pixelTable, byteLength);
          }

          for (
              shadowListIterator = (*this->arrayHeight2_shadows_copyFrom)[currentHeight];
              shadowListIterator != nullptr;
              shadowListIterator = shadowListIterator->next) {

            copyRgbMask = RgbMask;
            for (
                shadowList = (*this->arrayHeight1_solids_copyFrom)[currentHeight];
                RgbMask = copyRgbMask,
               shadowList != nullptr;
                shadowList = shadowList->next) {

              boundaryCompare = shadowList->rightBound;
              leftBoundCandidate = shadowListIterator->leftBound;
              if (leftBoundCandidate <= boundaryCompare) {
                break;
              }
              rightBoundCandidate = shadowListIterator->rightBound;
              startBound = shadowList->leftBound;

              if ((rightBoundCandidate < startBound) && (shadowList->layerIndex <= shadowListIterator->layerIndex)) {
                if (boundaryCompare <= rightBoundCandidate) {
                  boundaryCompare = rightBoundCandidate;
                }
                currentX = (int32_t)boundaryCompare;
                if (leftBoundCandidate <= startBound) {
                  startBound = leftBoundCandidate;
                }
                if (currentX < startBound) {
                  nextSegmentX = (currentX - rightBoundCandidate) * 2;
                  nPixelUpdates = startBound - currentX;
                  pixelBuffer = (uint16_t*)(SingleRowPixels640 + currentX);
                  do {

                    *pixelBuffer = ((*(uint16_t*)(shadowListIterator->pixelTable + (nextSegmentX / sizeof(int16_t))) & copyRgbMask) >> 1) + ((*pixelBuffer & copyRgbMask) >> 1);
                    nextSegmentX = nextSegmentX + 2;
                    nPixelUpdates = nPixelUpdates + -1;
                    pixelBuffer = pixelBuffer + 1;
                  } while (nPixelUpdates != 0);
                }
              }
              copyRgbMask = RgbMask;
            }
          }
          byteLength = this->copyWindowWidth << 1;
          memcpy(pitchOffset + (byte*)surfaceDesc.lpSurface, SingleRowPixels640, byteLength);
          solidListIterator = nullptr;
        }
      }
      pitchOffset = pitchOffset + surfaceDesc.lPitch;
      currentHeight = currentHeight + 1;
    } while (currentHeight < this->copyWindowHeight);
  }
  PauseState = PauseState - (uint32_t)(0 < PauseState);
  DirectDrawSurface->Unlock(nullptr);
}
