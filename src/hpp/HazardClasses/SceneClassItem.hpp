#ifndef HAZARD_SCENECLASSITEM_HPP
#define HAZARD_SCENECLASSITEM_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardTypedef.hpp"

struct ImageVectorWithHeader;

class SceneClassItem : public GameWindowBase {

public:
  SceneClassItem(int32_t position1, int32_t position2, int32_t itemIndex, uint16_t size_9600);

  virtual void primarySwitchSingleParam(int32_t, intptr_t, intptr_t) override;

  int16_t init0_2;
  int16_t itemIndex;
  int16_t init0;
  int16_t size_9600;
  ImageVectorWithHeader* init0_3;

private:
  __forceinline void Case_0x7d11(intptr_t param2);
  __forceinline void Case_0x7d3b();
  __forceinline void Case_0x7d3c();
  __forceinline void Case_0x7d3e();
  __forceinline void Case_0x7d04(intptr_t param2);
};

#endif
