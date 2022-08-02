#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "itemp.h"
#include "itempi.h"
#include <dos.h>
using namespace std;

//friend functions of StockItem

ostream& operator << (ostream& os, const StockItem& Item)
{
  return Item.m_Worker->Write(os);
}

istream& operator >> (istream& is, StockItem& Item)
{
  string Expires;
  string Name;
  short InStock;
  short Price;
  short MinimumStock;
  short MinimumReorder;
  string Distributor;
  string UPC;

  getline(is,Expires);
  getline(is,Name);
  is >> InStock;
  is >> MinimumStock;
  is >> Price;
  is >> MinimumReorder;
  is.ignore();
  getline(is,Distributor);
  getline(is,UPC);

  if (Expires == "0")
    {
    Item = StockItem(Name, InStock, Price, MinimumStock,
          MinimumReorder, Distributor, UPC);
    }
  else
    {
    Item = StockItem(Name, InStock, Price, MinimumStock,
          MinimumReorder, Distributor, UPC, Expires);
    }
  
  return is;

}


// StockItem member functions

StockItem::StockItem()
: m_Count(0), m_Worker(new UndatedStockItem)
{
  m_Worker->m_Count = 1;
}

StockItem::StockItem(const StockItem& Item)
: m_Count(0), m_Worker(Item.m_Worker)
{
  m_Worker->m_Count ++;
}

StockItem& StockItem::operator = (const StockItem& Item)
{
  StockItem* temp = m_Worker;
  
  m_Worker = Item.m_Worker;
  m_Worker->m_Count ++;
  
  temp->m_Count --;
  if (temp->m_Count <= 0)
    delete temp;

  return *this;
}

StockItem::~StockItem()
{
  if (m_Worker == 0)
    return;

  m_Worker->m_Count --;
  if (m_Worker->m_Count <= 0)
    delete m_Worker;
}

StockItem::StockItem(string Name, short InStock, // Undated
  short Price, short MinimumStock, short MinimumReorder, 
  string Distributor, string UPC)
: m_Count(0),
  m_Worker(new UndatedStockItem(Name, InStock, Price, 
  MinimumStock, MinimumReorder, Distributor, UPC))
{
  m_Worker->m_Count = 1;
}

StockItem::StockItem(int)
: m_Worker(0)
{
}

StockItem::StockItem(string Name, short InStock, // Dated
  short Price, short MinimumStock, short MinimumReorder, 
  string Distributor, string UPC, string Expires)
: m_Count(0),
  m_Worker(new DatedStockItem(Name, InStock, Price, 
  MinimumStock, MinimumReorder, Distributor, UPC, Expires))
{
  m_Worker->m_Count = 1;
}

bool StockItem::CheckUPC(string UPC)
{
  return m_Worker->CheckUPC(UPC);
}

short StockItem::GetInventory()
{
  return m_Worker->GetInventory();
}

void StockItem::DeductSaleFromInventory(short QuantitySold)
{
  m_Worker->DeductSaleFromInventory(QuantitySold);
}

string StockItem::GetName()
{
  return m_Worker->GetName();
}

ostream& StockItem::Write(ostream& os)
{
  exit(1); // should never get here
  return os;
}

void StockItem::Reorder(ostream& os)
{
  m_Worker->Reorder(os);
}


void StockItem::FormattedDisplay(ostream& os)
{
  m_Worker->FormattedDisplay(os);
}


// UndatedStockItem member functions

UndatedStockItem::UndatedStockItem()
: StockItem(1),
  m_InStock(0),
  m_Price(0),
  m_MinimumStock(0),
  m_MinimumReorder(0),
  m_Name(),
  m_Distributor(),
  m_UPC()
{
}

UndatedStockItem::UndatedStockItem(string Name, 
  short InStock, short Price, short MinimumStock,
  short MinimumReorder, string Distributor, string UPC)
: StockItem(1),
  m_InStock(InStock),
  m_Price(Price),
  m_MinimumStock(MinimumStock),
  m_MinimumReorder(MinimumReorder),
  m_Name(Name),
  m_Distributor(Distributor),
  m_UPC(UPC)
{
}

void UndatedStockItem::FormattedDisplay(ostream& os)
{
  os << "Name: ";
  os << m_Name << endl;
  os << "Number in stock: ";
  os << m_InStock << endl;
  os << "Price: ";
  os << m_Price << endl;
  os << "Minimum stock: ";
  os << m_MinimumStock << endl;
  os << "Reorder quantity: ";
  os << m_MinimumReorder << endl;
  os << "Distributor: ";
  os << m_Distributor << endl;
  os << "UPC: ";
  os << m_UPC << endl;
  os << endl;
}

ostream& UndatedStockItem::Write(ostream& os)
{
  os << 0 << endl;
  os << m_Name << endl;
  os << m_InStock << endl;
  os << m_Price << endl;
  os << m_MinimumStock << endl;
  os << m_MinimumReorder << endl;
  os << m_Distributor << endl;
  os << m_UPC << endl;

  return os;
}

void UndatedStockItem::Reorder(ostream& os)
{
  short ReorderAmount;

  if (m_InStock < m_MinimumStock)
    {
    ReorderAmount = m_MinimumStock-m_InStock;
      if (ReorderAmount < m_MinimumReorder)
        ReorderAmount = m_MinimumReorder;
    os << "Reorder " << ReorderAmount;
    os << " units of " << m_Name << " with UPC ";
    os << m_UPC << " from " << m_Distributor << endl;
    }
}

bool UndatedStockItem::CheckUPC(string UPC)
{
  return (UPC == m_UPC);
}

short UndatedStockItem::GetInventory()
{
  return m_InStock;
}

void UndatedStockItem::DeductSaleFromInventory(
short QuantitySold)
{
  m_InStock -= QuantitySold;
}

string UndatedStockItem::GetName()
{
  return m_Name;
}


// DatedStockItem member functions

DatedStockItem::DatedStockItem(string Name, short InStock,
short Price, short MinimumStock, short MinimumReorder, 
string Distributor, string UPC, string Expires)
: UndatedStockItem(Name,InStock,Price,MinimumStock,
  MinimumReorder,Distributor,UPC),
  m_Expires(Expires)
{
}

ostream& DatedStockItem::Write(ostream& os)
{
  os << m_Expires << endl;
  os << m_Name << endl;
  os << m_InStock << endl;
  os << m_Price << endl;
  os << m_MinimumStock << endl;
  os << m_MinimumReorder << endl;
  os << m_Distributor << endl;
  os << m_UPC << endl;

  return os;
}

void DatedStockItem::FormattedDisplay(ostream& os)
{
  os << "Expiration date: ";
  os << m_Expires << endl;
  os << "Name: ";
  os << m_Name << endl;
  os << "Number in stock: ";
  os << m_InStock << endl;
  os << "Price: ";
  os << m_Price << endl;
  os << "Minimum stock: ";
  os << m_MinimumStock << endl;
  os << "Reorder quantity: ";
  os << m_MinimumReorder << endl;
  os << "Distributor: ";
  os << m_Distributor << endl;
  os << "UPC: ";
  os << m_UPC << endl;
  os << endl;
}

string DatedStockItem::Today()
{
   struct date d;
   unsigned short year;
   unsigned short day;
   unsigned short month;
   string TodaysDate;
   stringstream FormatStream;

   getdate(&d);
   year = d.da_year;
   day = d.da_day;
   month = d.da_mon;

   FormatStream << setfill('0') << setw(4) << year << 
     setw(2) << month << setw(2) << day;
   FormatStream.seekg(0);
   FormatStream >> TodaysDate;

   return TodaysDate;
}

void DatedStockItem::Reorder(ostream& os)
{
  if (m_Expires < Today())
    {
    os << "Return " << m_InStock << " units of " << m_Name;
    os << " with UPC " << m_UPC;
    os << " to " << m_Distributor << endl;
    m_InStock = 0;
    }

  UndatedStockItem::Reorder(os);
}
