//hmin8.cc

#include <iostream>
#include <fstream>
#include <conio.h>


#include "windos\pc.h"
#include "windos\keys.h"

#include "Vec.h"
#include "xstring.h"
#include "hmit8.h"
#include "hmin8.h"
#include "hmutil1.h"
using namespace std;

HomeInventory::HomeInventory()
: m_Home (Vec<HomeItem>(0))
{
}

short HomeInventory::LoadInventory(ifstream& is)
{
  short i;
  short ElementCount;

  is >> ElementCount;
  is.ignore();

  m_Home.resize(ElementCount+1);

  for (i = 0; ; i ++)
    {
    is >> m_Home[i];

    if (is.fail() != 0)
      break;
    }

  if (i < ElementCount)
    {
    cerr << "Not enough items in input file" << endl;
    exit(1);
    }

  m_Home.resize(ElementCount);

  SortInventoryByName();

  return i;
}

void HomeInventory::DumpInventory()
{
  short ItemCount = m_Home.size();

  for (short i = 0; i < ItemCount; i ++)
     cout << m_Home[i];
}

HomeItem HomeInventory::AddItem()
{
  HomeItem TempItem = HomeItem::NewItem();

  if (TempItem.IsNull())
    return TempItem;

  short OldCount = m_Home.size();

  m_Home.resize(OldCount + 1);

  m_Home[OldCount] = TempItem;

  SortInventoryByName();

  return TempItem;
}

Vec<short> HomeInventory::LocateItemByDescription(
  const xstring& Partial)
{
  short ItemCount = m_Home.size();
  xstring Description;
  short FoundCount = 0;

  for (short i = 0; i < ItemCount; i ++)
    {
    Description = m_Home[i].GetDescription();
    if (Description.find_nocase(Partial) >= 0)
      FoundCount ++;
    }

  Vec<short> Found(FoundCount);

  FoundCount = 0;

  for (short i = 0; i < ItemCount; i ++)
    {
    Description = m_Home[i].GetDescription();
    if (Description.find_nocase(Partial) >= 0)
      Found[FoundCount++] = i;
    }

  return Found;
}

Vec<short> HomeInventory::LocateItemByCategory(
  const xstring& Partial)
{
  short ItemCount = m_Home.size();
  xstring Category;
  short FoundCount = 0;

  for (short i = 0; i < ItemCount; i ++)
    {
    Category = m_Home[i].GetCategory();
    if (Category.find_nocase(Partial) >= 0)
      FoundCount ++;
    }

  Vec<short> Found(FoundCount);

  FoundCount = 0;

  for (short i = 0; i < ItemCount; i ++)
    {
    Category = m_Home[i].GetCategory();
    if (Category.find_nocase(Partial) >= 0)
      Found[FoundCount++] = i;
    }

  return Found;
}

Vec<short> HomeInventory::LocateItemByPartialName(
  const xstring& Partial)
{
  short ItemCount = m_Home.size();
  xstring Name;
  short FoundCount = 0;

  for (short i = 0; i < ItemCount; i ++)
    {
    Name = m_Home[i].GetName();
    if (Name.find_nocase(Partial) >= 0)
      FoundCount ++;
    }

  Vec<short> Found(FoundCount);

  FoundCount = 0;

  for (short i = 0; i < ItemCount; i ++)
    {
    Name = m_Home[i].GetName();
    if (Name.find_nocase(Partial) >= 0)
      Found[FoundCount++] = i;
    }

  return Found;
}

HomeItem HomeInventory::EditItem(short Index)
{
  bool NameChanged = false;

  HomeItem TempItem = m_Home[Index];

  TempItem.Edit();

  if (TempItem.GetName() != m_Home[Index].GetName())
    NameChanged = true;

  m_Home[Index] = TempItem;

  if (NameChanged)
    SortInventoryByName();

  return TempItem;
}


void HomeInventory::PrintNames(ostream& os)
{
  short ItemCount = m_Home.size();

  for (short i = 0; i < ItemCount; i ++)
    {
    os << m_Home[i].GetName() << endl;
    }

  os << '\f' << endl;
  os.flush();
}


void HomeInventory::PrintAll(ostream& os)
{
  short ItemCount = m_Home.size();

  for (short i = 0; i < ItemCount; i ++)
    {
    os << m_Home[i] << endl;
    }

  os << '\f' << endl;
  os.flush();
}


void HomeInventory::StoreInventory(ofstream& ofs)
{
  short i;
  short ElementCount = m_Home.size();

  ofs << ElementCount << endl << endl;

  for (i = 0; i < ElementCount; i ++)
    {
    ofs << m_Home[i];
    ofs << endl;
    }
}

void HomeInventory::DisplayItem(short Index)
{
  m_Home[Index].FormattedDisplay(cout);
}

void HomeInventory::SortInventoryByName()
{
  short ItemCount = m_Home.size();
  Vec<HomeItem> m_HomeTemp = m_Home;
  Vec<xstring> Name(ItemCount);
  xstring HighestName = "zzzzzzzz";
  xstring FirstName;
  short FirstIndex;

  for (int i = 0; i < ItemCount; i ++)
      Name[i] = m_Home[i].GetName();

  for (int i = 0; i < ItemCount; i ++)
      {
      FirstName = HighestName;
      FirstIndex = 0;
      for (int k = 0; k < ItemCount; k ++)
          {
          if (Name[k].less_nocase(FirstName))
              {
              FirstName = Name[k];
              FirstIndex = k;
              }
          }
      m_HomeTemp[i] = m_Home[FirstIndex];
      Name[FirstIndex] = HighestName;
      }

  m_Home = m_HomeTemp;
}

short HomeInventory::GetCount()
{
  return m_Home.size();
}

short HomeInventory::SelectItemFromDescriptionList(
  const xstring& Partial)
{
  Vec<short> Found = LocateItemByDescription(Partial);

  Vec<xstring> Name(Found.size());

  for (unsigned i = 0; i < Found.size(); i ++)
     Name[i] = m_Home[Found[i]].GetName();

  short Result = HomeUtility::SelectItem(Found,Name) - 1;

  return Result;
}

short HomeInventory::SelectItemFromCategoryList(
  const xstring& Partial)
{
  Vec<short> Found = LocateItemByCategory(Partial);

  Vec<xstring> Name(Found.size());
  Vec<xstring> Category(Found.size());
  xstring Padding;
  unsigned PaddingLength;
  const unsigned ItemNumberLength = 7;

  unsigned MaxLength = 0;

  for (unsigned i = 0; i < Found.size(); i ++)
     {
     Category[i] = m_Home[Found[i]].GetCategory();
     Name[i] = m_Home[Found[i]].GetName();
     if (Name[i].size() > MaxLength)
       MaxLength = Name[i].size();
     }

  for (unsigned i = 0; i < Found.size(); i ++)
     {
     PaddingLength = MaxLength - Name[i].size();
     Padding = xstring(PaddingLength);
     Name[i] = Name[i] + Padding + "    " + Category[i];
     }

  MaxLength += ItemNumberLength;
  xstring Heading = "Item #  Name";
  unsigned HeadingLength = Heading.size();
  if (MaxLength > HeadingLength)
    PaddingLength = MaxLength - HeadingLength;
  else
    PaddingLength = 0;
  Padding = xstring(PaddingLength);
  Heading = Heading + Padding + "     Category";
  cout << Heading << endl << endl;

  short Result = HomeUtility::SelectItem(Found,Name) - 1;

  return Result;
}

short HomeInventory::SelectItemByPartialName(
const xstring& Partial)
{
  Vec<short> Found = LocateItemByPartialName(Partial);

  Vec<xstring> Name(Found.size());

  for (unsigned i = 0; i < Found.size(); i ++)
     Name[i] = m_Home[Found[i]].GetName();

  short Result = HomeUtility::SelectItem(Found,Name) - 1;

  return Result;
}

short HomeInventory::SelectItemFromNameList()
{
  short ItemCount = m_Home.size();

  Vec<short> Found(ItemCount);

  for (int i = 0; i < ItemCount; i ++)
      Found[i] = i;

  Vec<xstring> Name(Found.size());

  for (unsigned i = 0; i < Found.size(); i ++)
     Name[i] = m_Home[i].GetName();

  short Result = HomeUtility::SelectItem(Found,Name) - 1;

  return Result;
}

void HomeInventory::DeleteItem(short Index)
{
  short ItemCount = m_Home.size();

  for (short i = Index; i < ItemCount-1; i ++)
    m_Home[i] = m_Home[i+1];

  m_Home.resize(ItemCount-1);
}
