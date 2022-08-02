#include <iostream>
#include <fstream>
#include <string>

#include "Vec.h"

#include "hmit2.h"
#include "hmin2.h"
using namespace std;


HomeInventory::HomeInventory()
: m_Home (Vec<HomeItem>(0))
{
}

short HomeInventory::LoadInventory(ifstream& is)
{
    short i;

    for (i = 0; ; i ++)
      {
      m_Home.resize(i+1);

      is >> m_Home[i];
      if (is.fail() != 0)
        break;
      }

    m_Home.resize(i);
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
