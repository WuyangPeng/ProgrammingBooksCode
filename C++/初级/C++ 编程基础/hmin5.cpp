//hmin5.cc

#include <iostream>
#include <fstream>
#include "Vec.h"
#include <string>

#include "hmit5.h"
#include "hmin5.h"
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

HomeItem HomeInventory::FindItemByName(string Name)
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


short HomeInventory::LocateItemByName(string Name)
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


HomeItem HomeInventory::EditItem(string Name)
{
    short ItemNumber = LocateItemByName(Name);

    HomeItem TempItem = m_Home[ItemNumber];

    TempItem.Edit();

    m_Home[ItemNumber] = TempItem;

    return TempItem;
}

