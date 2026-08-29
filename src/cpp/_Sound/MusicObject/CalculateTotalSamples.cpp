#include "HazardGlobals.hpp"

int32_t MusicObject::CalculateTotalSamples(int32_t) {
  return this->usedAsNumerator / (this->channelCount * this->audioFrequency * 2);
}
