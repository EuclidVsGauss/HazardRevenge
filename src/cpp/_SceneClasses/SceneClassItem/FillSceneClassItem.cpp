#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneClassItem.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"
#include "HazardStructs/ItemReferenceCollection.hpp"
#include "HazardStructs/ItemReferenceStruct.hpp"

SceneClassItem::SceneClassItem(int32_t position1, int32_t position2, int32_t itemIndex, uint16_t size_9600) {

  ImageVectorWithHeader* solidSprite;

  solidSprite = __InlineGetSolidSpriteFrameForAction(ItemStruct12k->itemArray[itemIndex].actOffset, Item00Act, 0);
  this->init0 = 0;
  this->init0_2 = 0;
  this->init0_3 = solidSprite;
  this->itemIndex = (int16_t)itemIndex;
  this->size_9600 = size_9600;
  this->UpdateObjectOnGrid(position1 << 4, position2 << 4);
}
