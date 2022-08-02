// hmit1.cpp

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#include "Vec.h"

#include "hmit1.h"
#include "hmiti1.h"
using namespace std;


//friend functions of HomeItem

ostream& operator << (ostream& os, const HomeItem& Item)
{
  Item.m_Worker->Write(os);
  return os;
}

istream& operator >> (istream& is, HomeItem& Item)
{
  string Type;
  string Name;
  double PurchasePrice;
  long PurchaseDate;
  string Description;
  string Category;

  while (Type == "")
    {
    getline(is,Type);
    if (is.fail() != 0)
      {
      Item = HomeItem();
      return is;
      }
    }

  getline(is,Name);
  is >> PurchasePrice;
  is >> PurchaseDate;
  is.ignore();
  getline(is,Description);
  getline(is,Category);

  if (Type == "Basic")
    {
    Item = HomeItem(Name, PurchasePrice, PurchaseDate, 
           Description, Category);
    }
  else if (Type == "Music")
    {
    string Artist;
    short TrackCount;
    getline(is,Artist);
    is >> TrackCount;
    is.ignore();
    Vec<string> Track(TrackCount);
    for (short i = 0; i < TrackCount; i ++)
      {
      getline(is,Track[i]);
      }
    Item = HomeItem(Name, PurchasePrice, PurchaseDate, 
           Description, Category, Artist, Track);
    }
  else
    {
    cout << "Can't create object of type " << Type << endl;
    exit(1);
    }
  
  return is;
}


// HomeItem member functions

HomeItem::HomeItem()
: m_Count(0), m_Worker(new HomeItemBasic)
{
  m_Worker->m_Count = 1;
}

HomeItem::HomeItem(const HomeItem& Item)
: m_Count(0), m_Worker(Item.m_Worker)
{
  m_Worker->m_Count ++;
}

HomeItem& HomeItem::operator = (const HomeItem& Item)
{
  HomeItem* temp = m_Worker;
  m_Worker = Item.m_Worker;
  m_Worker->m_Count ++;
  temp->m_Count --;
  if (temp->m_Count <= 0)
    delete temp;

  return *this;
}

HomeItem::~HomeItem()
{
  if (m_Worker == 0)
    return;

  m_Worker->m_Count --;
  if (m_Worker->m_Count <= 0)
    delete m_Worker;
}

HomeItem::HomeItem(string Name, double PurchasePrice,
long PurchaseDate, string Description,
string Category)
: m_Count(0),
  m_Worker(new HomeItemBasic(Name, PurchasePrice, 
  PurchaseDate, Description, Category))
{
  m_Worker->m_Count = 1;
}

HomeItem::HomeItem(int)
: m_Worker(0)
{
}

HomeItem::HomeItem(string Name, double PurchasePrice,
long PurchaseDate, string Description,
string Category, string Artist, 
Vec<string> Track)
: m_Count(0),
  m_Worker(new HomeItemMusic(Name, PurchasePrice, 
  PurchaseDate, Description, Category, Artist, Track))
{
  m_Worker->m_Count = 1;
}


void HomeItem::Write(ostream& )
{
  exit(1); // error
}

// HomeItemBasic member functions

HomeItemBasic::HomeItemBasic()
: HomeItem(1),
  m_Name(),
  m_PurchasePrice(0),
  m_PurchaseDate(0),
  m_Description(),
  m_Category()
{
}

HomeItemBasic::HomeItemBasic(string Name, 
double PurchasePrice, long PurchaseDate, 
string Description, string Category)
: HomeItem(1),
  m_Name(Name),
  m_PurchasePrice(PurchasePrice),
  m_PurchaseDate(PurchaseDate),
  m_Description(Description),
  m_Category(Category)
{
}

void HomeItemBasic::Write(ostream& os)
{
  os << GetType() << endl;
  os << m_Name << endl;
  os << m_PurchasePrice << endl;
  os << m_PurchaseDate << endl;
  os << m_Description << endl;
  os << m_Category << endl;
}

string HomeItemBasic::GetType()
{
  return "Basic";
}


// HomeItemMusic member functions

HomeItemMusic::HomeItemMusic(string Name, 
double PurchasePrice, long PurchaseDate, 
string Description, string Category, 
string Artist, Vec<string> Track)
: HomeItemBasic(Name,PurchasePrice,PurchaseDate,
  Description, Category),
  m_Artist(Artist),
  m_Track(Track)
{
}

void HomeItemMusic::Write(ostream& os)
{
  HomeItemBasic::Write(os);

  os << m_Artist << endl;

  int TrackCount = m_Track.size();
  os << TrackCount << endl;
  for (short i = 0; i < TrackCount; i ++)
    os << m_Track[i] << endl;
}

string HomeItemMusic::GetType()
{
  return "Music";
}
