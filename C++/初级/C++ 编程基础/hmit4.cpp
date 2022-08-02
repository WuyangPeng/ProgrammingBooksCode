// hmit4.cc

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#include "Vec.h"

#include "hmit4.h"
#include "hmiti4.h"
#include <dos.h>
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
  bool Interactive = (&is == &cin);

  while (Type == "")
    {
    if (Interactive)
      cout << "Type (Basic, Music) ";
    getline(is,Type);
    if (is.fail() != 0)
      {
      Item = HomeItem();
      return is;
      }
    }

  if (Interactive)
    cout << "Name ";
  getline(is,Name);

  if (Interactive)
    cout << "Purchase Price ";
  is >> PurchasePrice;

  if (Interactive)
    cout << "Purchase Date ";
  is >> PurchaseDate;
  is.ignore();

  if (Interactive)
    cout << "Description ";
  getline(is,Description);

  if (Interactive)
    cout << "Category ";
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

    if (Interactive)
      cout << "Artist ";
    getline(is,Artist);

    if (Interactive)
      cout << "TrackCount ";
    is >> TrackCount;
    is.ignore();

    Vec<string> Track(TrackCount);
    for (short i = 0; i < TrackCount; i ++)
      {
      if (Interactive)
        cout << "Track # " << i + 1 << ": ";
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

string HomeItem::GetName()
{
  return m_Worker->GetName();
}

void HomeItem::Write(ostream&)
{
}

void HomeItem::FormattedDisplay(ostream& os)
{
  m_Worker->FormattedDisplay(os);
}

HomeItem HomeItem::NewItem()
{
  HomeItem TempItem;

  cin >> TempItem;

  return TempItem;
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

void HomeItemBasic::FormattedDisplay(ostream& os)
{
  os << "Type: ";
  os << GetType() << endl;
  os << "Name: ";
  os << m_Name << endl;
  os << "Purchase price: ";
  os << m_PurchasePrice << endl;
  os << "Purchase date: ";
  os << m_PurchaseDate << endl;
  os << "Description: ";
  os << m_Description << endl;
  os << "Category: ";
  os << m_Category << endl;
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

string HomeItemBasic::GetName()
{
  return m_Name;
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

  short TrackCount = m_Track.size();

  os << m_Artist << endl;
  os << TrackCount << endl;

  for (short i = 0; i < TrackCount; i ++)
    {
    os << m_Track[i] << endl;
    }
}

void HomeItemMusic::FormattedDisplay(ostream& os)
{
  HomeItemBasic::FormattedDisplay(os);

  os << "Artist: ";
  os << m_Artist << endl;
  os << "Tracks: ";

  int TrackCount = m_Track.size();
  os << TrackCount << endl;
  for (short i = 0; i < TrackCount; i ++)
    os << m_Track[i] << endl;
}

string HomeItemMusic::GetType()
{
  return "Music";
}
