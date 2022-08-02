#include <iostream>
#include <fstream>
#include "Vec.h"
#include <string>

#include "hmit4.h"
#include "hmin4.h"
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


HomeItem HomeInventory::AddItem()
{
    HomeItem TempItem = HomeItem::NewItem();

    short OldCount = m_Home.size();

    m_Home.resize(OldCount + 1);

    m_Home[OldCount] = TempItem;

    return TempItem;
}
