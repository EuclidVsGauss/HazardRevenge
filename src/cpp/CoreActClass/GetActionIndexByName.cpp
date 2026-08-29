#include "HazardClasses/CoreActClass.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActContent.hpp"

int32_t CoreActClass::GetActionIndexByName(char* actKeyword) {

  for (int32_t index = 0; index < this->numberActLines; index++) {
    int32_t compareResult = strcmp(actKeyword, this->txtContent[index].actionName);
    if (compareResult == 0) {
      return index;
    }
  }
  return -1;
}
