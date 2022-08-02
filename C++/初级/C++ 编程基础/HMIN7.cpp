//hmin7.cc

#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>

#include "xstring.h"
#include "Vec.h"

#include "hmit7.h"
#include "hmin7.h"
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

void HomeInventory::DisplayNames(ostream& os)
{
    short ItemCount = m_Home.size();

    clrscr();

    for (short i = 0; i < ItemCount; i ++)
      {
      os << m_Home[i].GetName() << endl;
      }

    os << endl;
}    

short HomeInventory::LocateItemByPartialName(const xstring& Partial)
{
    short i;
    bool Found = false;
    short ItemCount = m_Home.size();
    xstring Name;

    for (i = 0; i < ItemCount; i ++)
      {
      Name = m_Home[i].GetName();
      if (Name.find_nocase(Partial) >= 0)
      {
      Found = true;
      break;
      }
    }

    if (Found)
      return i;

    return -1;
}


HomeItem HomeInventory::EditItem(short Index)
{
    HomeItem TempItem = m_Home[Index];

    TempItem.Edit();

    m_Home[Index] = TempItem;

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


void HomeInventory::StoreInventory(ofstream& OutputStream)
{
    short i;
    short ElementCount = m_Home.size();

    OutputStream << ElementCount << endl << endl;


    for (i = 0; i < ElementCount; i ++)
      {
      OutputStream << m_Home[i];
      OutputStream << endl;
      }
}

void HomeInventory::DisplayItem(short Index)
{
    clrscr();
    m_Home[Index].FormattedDisplay(cout);
}
