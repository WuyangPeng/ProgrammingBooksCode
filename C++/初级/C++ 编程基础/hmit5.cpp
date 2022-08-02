// hmit5.cc

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#include "Vec.h"
#include "hmit5.h"
#include "hmiti5.h"
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

  if (Type == "Basic")
    { 
    // create empty Basic object to be filled in
    HomeItem Temp("",0.0,0,"",""); 
    Temp.Read(is);
    Item = Temp;
    }
  else if (Type == "Music")
    {
    // create an empty Music object to be filled in
    HomeItem Temp("",0.0,0,"","","",Vec<string>(0));
    Temp.Read(is);
    Item = Temp;
    }
  else
    {
    cerr << "Can't create object of type " << Type << endl;
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

short HomeItem::FormattedDisplay(ostream& os)
{
  return m_Worker->FormattedDisplay(os);
}

void HomeItem::Write(ostream& os)
{
  m_Worker->Write(os);
}

HomeItem HomeItem::NewItem()
{
  HomeItem TempItem;

  cin >> TempItem;

  return TempItem;
}

void HomeItem::Read(istream& is)
{
  if (m_Worker->m_Count > 1)
    {
    m_Worker->m_Count --;
    m_Worker = m_Worker->CopyData();
    m_Worker->m_Count = 1;
    }

  m_Worker->Read(is);
}

void HomeItem::Edit()
{
  if (m_Worker->m_Count > 1)
    {
    m_Worker->m_Count --;
    m_Worker = m_Worker->CopyData();
    m_Worker->m_Count = 1;
    }

  m_Worker->Edit();
}

HomeItem* HomeItem::CopyData()
{
  exit(1); // should never be called
  return 0;
}


// HomeItemBasic member functions

string HomeItemBasic::GetType()
{
  return "Basic";
}

string HomeItemBasic::GetName()
{
  return m_Name;
}

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

void HomeItemBasic::Read(istream& is)
{
  if (&is == &cin)
    ReadInteractive();
  else
    ReadFromFile(is);
}

void HomeItemBasic::Edit()
{
  short FieldNumber;

  FormattedDisplay(cout);
  cout << endl;

  cout << "Please enter field number to be changed: ";
  cin >> FieldNumber;
  cin.ignore();
  cout << endl;

  EditField(FieldNumber);
}

string HomeItemBasic::GetFieldName(short FieldNumber)
{
  static string Name[e_Category+1] = {"","Name",
    "Purchase Price","Purchase Date", "Description",
    "Category"};

  if ((FieldNumber > 0) && (FieldNumber <= e_Category))
    return Name[FieldNumber];

  return "";
}

bool HomeItemBasic::EditField(short FieldNumber)
{
  bool result = true;

  switch (FieldNumber)
    {
    case e_Name:
    cout << FieldNumber << ". ";
    cout << GetFieldName(FieldNumber) << ": ";
    getline(cin,m_Name);
    break;

    case e_PurchasePrice:
    cout << FieldNumber << ". ";
    cout << GetFieldName(FieldNumber) << ": ";
    cin >> m_PurchasePrice;
    break;

    case e_PurchaseDate:
    cout << FieldNumber << ". ";
    cout << GetFieldName(FieldNumber) << ": ";
    cin >> m_PurchaseDate;
    break;

    case e_Description:
    cout << FieldNumber << ". ";
    cout << GetFieldName(FieldNumber) << ": ";
    getline(cin,m_Description);
    break;

    case e_Category:
    cout << FieldNumber << ". ";
    cout << GetFieldName(FieldNumber) << ": ";
    getline(cin,m_Category);
    break;

    default:
    cout << "Sorry, that is not a valid field number." << endl;
    result = false;
    break;
    }

  return result;
}

short HomeItemBasic::ReadInteractive()
{
  short FieldNumber = e_Name;

  cout << FieldNumber << ". ";
  cout << GetFieldName(FieldNumber) << ": ";
  FieldNumber ++;
  getline(cin,m_Name);

  cout << FieldNumber << ". ";
  cout << GetFieldName(FieldNumber) << ": ";
  FieldNumber ++;
  cin >> m_PurchasePrice;

  cout << FieldNumber << ". ";
  cout << GetFieldName(FieldNumber) << ": ";
  FieldNumber ++;
  cin >> m_PurchaseDate;

  cout << FieldNumber << ". ";
  cout << GetFieldName(FieldNumber) << ": ";
  FieldNumber ++;
  getline(cin,m_Description);

  cout << FieldNumber << ". ";
  cout << GetFieldName(FieldNumber) << ": ";
  FieldNumber ++;
  getline(cin,m_Category);

  return FieldNumber;
}

short HomeItemBasic::ReadFromFile(istream& is)
{
  getline(is,m_Name);
  is >> m_PurchasePrice;
  is >> m_PurchaseDate;
  is.ignore();
  
  getline(is,m_Description);
  getline(is,m_Category);
  
  return 0;
}

short HomeItemBasic::FormattedDisplay(ostream &os)
{
  short FieldNumber = e_Name;

  os << "Type: " << GetType() << endl;

  os << FieldNumber << ". ";
  os << GetFieldName(FieldNumber) << ": ";
  FieldNumber ++;
  os << m_Name << endl;

  os << FieldNumber << ". ";
  os << GetFieldName(FieldNumber) << ": ";
  FieldNumber ++;
  os << m_PurchasePrice << endl;

  os << FieldNumber << ". ";
  os << GetFieldName(FieldNumber) << ": ";
  FieldNumber ++;
  os << m_PurchaseDate << endl;

  os << FieldNumber << ". ";
  os << GetFieldName(FieldNumber) << ": ";
  FieldNumber ++;
  os << m_Description << endl;

  os << FieldNumber << ". ";
  os << GetFieldName(FieldNumber) << ": ";
  FieldNumber ++;
  os << m_Category << endl;

  return FieldNumber;
}

void HomeItemBasic::Write(ostream &os)
{
  os << GetType() << endl;
  os << m_Name << endl;
  os << m_PurchasePrice << endl;
  os << m_PurchaseDate << endl;
  os << m_Description << endl;
  os << m_Category << endl;
}

HomeItem* HomeItemBasic::CopyData()
{
  HomeItem* TempItem = new HomeItemBasic(m_Name,
  m_PurchasePrice, m_PurchaseDate, m_Description, m_Category);
  
  return TempItem;
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

void HomeItemMusic::Write(ostream &os)
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

short HomeItemMusic::FormattedDisplay(ostream &os)
{
  short FieldNumber = HomeItemBasic::FormattedDisplay(os);

  short TrackCount = m_Track.size();

  os << FieldNumber << ". ";
  os << GetFieldName(FieldNumber) << ": ";
  FieldNumber ++;
  os << m_Artist << endl;

  os << FieldNumber << ". ";
  os << GetFieldName(FieldNumber) << ": ";
  FieldNumber ++;
  os << TrackCount << endl;

  for (short i = 0; i < TrackCount; i ++)
    {
    os << FieldNumber << ". ";
    os << GetFieldName(FieldNumber) << i + 1 << ": ";
    FieldNumber ++;
    os << m_Track[i] << endl;
    }

  return FieldNumber;
}

string HomeItemMusic::GetType()
{
  return "Music";
}

string HomeItemMusic::GetFieldName(short FieldNumber)
{
  static string Name[e_TrackNumber - e_Category] = 
    {"Artist","Track Count","Track #"};

  if ((FieldNumber > 0) && (FieldNumber <= e_Category))
    return HomeItemBasic::GetFieldName(FieldNumber);

  if ((FieldNumber > e_Category) && (FieldNumber <= e_TrackNumber))
    return Name[FieldNumber - e_Artist];

  if (FieldNumber > e_TrackNumber)
    return Name[e_TrackNumber - e_Artist];
    
  return "";
}


bool HomeItemMusic::EditField(short FieldNumber)
{
  if (FieldNumber < e_Artist)
    {
    return HomeItemBasic::EditField(FieldNumber);
    }

  short TrackCount = m_Track.size();

  switch (FieldNumber)
    {
    case e_Artist:
    cout << FieldNumber << ". ";
    cout << GetFieldName(FieldNumber) << ": ";
    getline(cin,m_Artist);
    return true;

    case e_TrackCount:
    cout << FieldNumber << ". ";
    cout << GetFieldName(FieldNumber) << ": ";
    cin >> TrackCount;
    m_Track.resize(TrackCount);
    return true;
    }

  if (FieldNumber > (e_TrackCount + TrackCount))
    {
    cout << "Sorry, that is not a valid field number." << endl;
    return false;
    }

  cout << FieldNumber << ". ";
  cout << GetFieldName(FieldNumber);
  cout << FieldNumber - e_TrackCount << ": ";

  getline(cin,m_Track[FieldNumber - e_TrackNumber]);

  return true;
}

short HomeItemMusic::ReadInteractive()
{
  short TrackCount;

  short FieldNumber = HomeItemBasic::ReadInteractive();

  cout << FieldNumber << ". ";
  cout << GetFieldName(FieldNumber) << ": ";
  FieldNumber ++;
  getline(cin,m_Artist);

  cout << FieldNumber << ". ";
  cout << GetFieldName(FieldNumber) << ": ";
  FieldNumber ++;
  cin >> TrackCount;
  m_Track.resize(TrackCount);

  for (short i = 0; i < TrackCount; i ++)
    {
    cout << FieldNumber << ". ";
    cout << GetFieldName(FieldNumber) << i + 1 << ": ";
    FieldNumber ++;
    getline(cin,m_Track[i]);
    }

  return FieldNumber;
}

short HomeItemMusic::ReadFromFile(istream& is)
{
  short TrackCount;

  HomeItemBasic::ReadFromFile(is);

  getline(is,m_Artist);
  is >> TrackCount;
  is.ignore();

  m_Track.resize(TrackCount);
  for (short i = 0; i < TrackCount; i ++)
    {
    getline(is,m_Track[i]);
    }
    
  return 0;
}

HomeItem* HomeItemMusic::CopyData()
{
  HomeItem* TempItem = new HomeItemMusic(m_Name, m_PurchasePrice, 
  m_PurchaseDate, m_Description, m_Category, m_Artist, 
  m_Track);
  
  return TempItem;
}

