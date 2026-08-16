#include <stdio.h>
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardExterns/CoreGameClass.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ItemRawCollection.hpp"
#include "HazardStructs/ItemRawStruct.hpp"
#include "HazardStructs/ItemReferenceCollection.hpp"
#include "HazardStructs/ItemReferenceStruct.hpp"
#include "HazardStructs/ItemStatsTemplate.hpp"

void LoadItemTxtAndAct(void) {
  char currentChar;
  UnpackedFileBase* itemTxt;
  uint32_t readByteResult;
  int32_t itemIndex;
  int32_t stringLength;
  int32_t counter;
  ItemRawStruct* itemPtr;
  ItemRawStruct* itemPtr2;
  char* nameBufferPtr;

  char nameBuffer[20];
  int32_t itemId;

  if (Item00Act == nullptr) {
    itemTxt = UnpackedFileBase::LoadFileFromArchive(s_item00_txt, 0x20000);
    RawItemCollection62k = new ItemRawCollection();

    itemPtr2 = (ItemRawStruct*)RawItemCollection62k;
    memset(itemPtr2, 0, sizeof(ItemRawStruct));

    for (itemIndex = 0; ReadInterpolatableString(itemTxt, s__d, &RawItemCollection62k->rawItemArray[itemIndex].ItemId), (RawItemCollection62k->rawItemArray[itemIndex].ItemId) != 0; itemIndex = itemIndex + 1) {
      ReadInterpolatableString(itemTxt, s__s__d, nameBuffer, &RawItemCollection62k->rawItemArray[itemIndex].Price);
      stringLength = -1;
      nameBufferPtr = nameBuffer;
      do {
        if (stringLength == 0) {
          break;
        }
        stringLength = stringLength + -1;
        currentChar = *nameBufferPtr;
        nameBufferPtr = nameBufferPtr + 1;
      } while (currentChar != '\0');
      if (stringLength != -0x15) {
        WrapperMessageBoxA(nameBuffer, s_item00_error);
      }
      stringLength = 0;
      counter = 1;
      (RawItemCollection62k->rawItemArray[itemIndex].EquipmentFlags) = 0;
      do {
        (RawItemCollection62k->rawItemArray[itemIndex].EquipmentFlags) = (RawItemCollection62k->rawItemArray[itemIndex].EquipmentFlags) + ((nameBuffer[stringLength] + -48) * counter);
        counter = counter * (stringLength == 8 ? 8 : 2);
        stringLength = stringLength + 1;
      } while (stringLength < 19);

      sprintf(RawItemCollection62k->rawItemArray[itemIndex].actKeyword, s___d, RawItemCollection62k->rawItemArray[itemIndex].ItemId);
      readByteResult = itemTxt->readByte();
      while (readByteResult != L'"') {
        readByteResult = itemTxt->readByte();
      }
      stringLength = 0;
      readByteResult = itemTxt->readByte();
      RawItemCollection62k->rawItemArray[itemIndex].Name[0] = (char)readByteResult;
      currentChar = RawItemCollection62k->rawItemArray[itemIndex].Name[0];
      while (currentChar != '\"') {
        stringLength = stringLength + 1;
        readByteResult = itemTxt->readByte();
        RawItemCollection62k->rawItemArray[itemIndex].Name[stringLength] = (char)readByteResult;
        currentChar = RawItemCollection62k->rawItemArray[itemIndex].Name[stringLength];
      }
      RawItemCollection62k->rawItemArray[itemIndex].Name[stringLength] = '\0';
      readByteResult = itemTxt->readByte();
      while (readByteResult != L'"') {
        readByteResult = itemTxt->readByte();
      }
      stringLength = 0;
      readByteResult = itemTxt->readByte();
      RawItemCollection62k->rawItemArray[itemIndex].Description[0] = (char)readByteResult;
      currentChar = RawItemCollection62k->rawItemArray[itemIndex].Description[0];
      while (currentChar != '\"') {
        stringLength = stringLength + 1;
        readByteResult = itemTxt->readByte();
        RawItemCollection62k->rawItemArray[itemIndex].Description[stringLength] = (char)readByteResult;
        currentChar = RawItemCollection62k->rawItemArray[itemIndex].Description[stringLength];
      }
      RawItemCollection62k->rawItemArray[itemIndex].Description[stringLength] = '\0';
      readByteResult = itemTxt->readByte();
      while (readByteResult != L'"') {
        readByteResult = itemTxt->readByte();
      }
      readByteResult = itemTxt->readByte();
      while (readByteResult != L'"') {
        readByteResult = itemTxt->readByte();
      }
      stringLength = 0;
      memset(RawItemCollection62k->rawItemArray[itemIndex].StatsArray, 0, sizeof(int32_t[16]));
      for (counter = 0; ReadInterpolatableString(itemTxt, s__d, &RawItemCollection62k->rawItemArray[itemIndex].StatsArray[counter]), (RawItemCollection62k->rawItemArray[itemIndex].StatsArray[counter]) != 999; counter = counter + 1) {
        stringLength = stringLength + 1;
      }
      RawItemCollection62k->rawItemArray[itemIndex].StatsArray[stringLength] = 0;
    }
    if (itemTxt != nullptr) {
      delete itemTxt;
    }
    Item00Act = new CoreActClass(s_item00_act);
    if (ItemStruct12k == nullptr) {
      ItemStruct12k = new ItemReferenceCollection();
    }
    itemId = RawItemCollection62k->rawItemArray[0].ItemId;
    if (itemId != 0) {
      itemPtr = RawItemCollection62k->rawItemArray;
      itemIndex = 0;
      do {
        ItemStruct12k->itemArray[itemId].equipFlags = itemPtr->EquipmentFlags;
        stringLength = Item00Act->GetActionIndexByName(RawItemCollection62k->rawItemArray[itemIndex].actKeyword);
        ItemStruct12k->itemArray[RawItemCollection62k->rawItemArray[itemIndex].ItemId].actOffset = stringLength;
        ItemStruct12k->itemArray[RawItemCollection62k->rawItemArray[itemIndex].ItemId].name = RawItemCollection62k->rawItemArray[itemIndex].Name;
        ItemStruct12k->itemArray[RawItemCollection62k->rawItemArray[itemIndex].ItemId].description = RawItemCollection62k->rawItemArray[itemIndex].Description;
        ItemStruct12k->itemArray[RawItemCollection62k->rawItemArray[itemIndex].ItemId].price = RawItemCollection62k->rawItemArray[itemIndex].Price;
        ItemStruct12k->itemArray[RawItemCollection62k->rawItemArray[itemIndex].ItemId].stats = (ItemStatsTemplate*)(&RawItemCollection62k->rawItemArray[itemIndex].StatsArray);
        itemId = RawItemCollection62k->rawItemArray[itemIndex + 1].ItemId;
        itemPtr = &RawItemCollection62k->rawItemArray[itemIndex + 1];
        itemIndex = itemIndex + 1;
      } while (itemId != 0);
    }
  }
}
