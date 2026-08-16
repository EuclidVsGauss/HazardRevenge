#include "HazardClasses/CoreActClass.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActContent.hpp"

int32_t CoreActClass::GetActionIndexByName(char* actKeyword) {
  int32_t index = 0;
  if (this->numberActLines > 0) {
    ActContent* currentActContent = this->txtContent;
    ActContent* actContentIter;
    const char* keywordIter;
    int32_t compareResult;

    actContentIter = currentActContent;
    keywordIter = actKeyword;

  label_compare_next_two:
    unsigned char c1 = *(unsigned char*)keywordIter;
    unsigned char c2 = *(unsigned char*)actContentIter->actionName;
    if (c1 != c2) {
      compareResult = (c1 < c2) ? -1 : 1;
    }
    else {
      if (c1 == 0) {
        compareResult = 0;
      }
      else {
        c1 = *(unsigned char*)(keywordIter + 1);
        c2 = *(unsigned char*)(actContentIter->actionName + 1);
        if (c1 != c2) {
          compareResult = (c1 < c2) ? -1 : 1;
        }
        else {
          if (c1 == 0) {
            compareResult = 0;
          }
          else {
            keywordIter += 2;
            actContentIter = (ActContent*)(actContentIter->actionName + 2);
            goto label_compare_next_two;
          }
        }
      }
    }

    if (compareResult == 0) {
      return index;
    }

    index++;
    currentActContent++;
    if (index < this->numberActLines) {
      actContentIter = currentActContent;
      keywordIter = actKeyword;
      goto label_compare_next_two;
    }
  }
  return -1;
}
