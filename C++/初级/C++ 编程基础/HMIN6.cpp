//hmin6.cc

#include <iostream>
#include <fstream>
#include <string>

#include "xstring.h"
#include "Vec.h"

#include "hmit6.h"
#include "hmin6.h"
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

  return i;
}

void HomeInventory::DumpInventory()
{
  short ItemCount = m_Home.size();

  for (short i = 0; i < ItemCount; i ++)
     cout << m_Home[i];
}

HomeItem HomeInventory::FindItemByName(const xstring& Name)
{
  short i;
  bool Found = false;
  short ItemCount = m_Home.size();

  for (i = 0; i < ItemCount; i ++)
    {
    if (m_Home[i].GetName() == Name)
      {
      Found = true;
      break;
      }
    }

  if (Found)
    return m_Home[i];

  return HomeItem();
}


short HomeInventory::LocateItemByName(const xstring& Name)
{
  short i;
  bool Found = false;
  short ItemCount = m_Home.size();

  for (i = 0; i < ItemCount; i ++)
    {
    if (m_Home[i].GetName() == Name)
      {
      Found = true;
      break;
      }
    }

  if (Found)
    return i;

  return -1;
}


HomeItem HomeInventory::AddItem()
{
  HomeItem TempItem = HomeItem::NewItem();

  short OldCount = m_Home.size();

  m_Home.resize(OldCount + 1);

  m_Home[OldCount] = TempItem;

  return TempItem;
}


HomeItem HomeInventory::EditItem(const xstring& Name)
{
  short ItemNumber = LocateItemByName(Name);

  HomeItem TempItem = m_Home[ItemNumber];

  TempItem.Edit();

  m_Home[ItemNumber] = TempItem;

  return TempItem;
}


HomeItem HomeInventory::FindItemByDescription(
  const xstring& Partial)
{
  short i;
  xstring Description;
  bool Found = false;
  short ItemCount = m_Home.size();
  
  for (i = 0; i < ItemCount; i ++)
    {
    Description = m_Home[i].GetDescription();
    if (Description.find_nocase(Partial) >= 0)
      {
      Found = true;
      break;
      }
    }

  if (Found)
    return m_Home[i];

  return HomeItem();
}


short HomeInventory::LocateItemByDescription(
  const xstring& Partial)
{
  short i;
  xstring Description;
  bool Found = false;
  short ItemCount = m_Home.size();

  for (i = 0; i < ItemCount; i ++)
    {
    Description = m_Home[i].GetDescription();
    if (Description.find_nocase(Partial) >= 0)
      {
      Found = true;
      break;
      }
    }

  if (Found)
    return i;

  return -1;
}
