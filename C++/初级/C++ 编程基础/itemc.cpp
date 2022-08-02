#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "itemc.h"
#include <dos.h>
using namespace std;

StockItem::StockItem(string Name, short InStock, 
short MinimumStock)
: m_InStock(InStock), m_Name(Name), 
  m_MinimumStock(MinimumStock)
{
}

StockItem::~StockItem()
{
}

void StockItem::Reorder(ostream& os)
{
  short ReorderAmount;

  if (m_InStock < m_MinimumStock)
    {
    ReorderAmount = m_MinimumStock-m_InStock;
    os << "Reorder " << ReorderAmount << " units of " << m_Name;
    }
}

ostream& operator << (ostream& os, StockItem* Item)
{
    Item->Write(os);
    return os;
}

void StockItem::Write(ostream& os)
{
    os << 0 << endl;
    os << m_Name << endl;
    os << m_InStock << endl;
    os << m_MinimumStock << endl;
}

istream& operator >> (istream& is, StockItem*& Item)
{
    string Expires;
    short InStock;
    short MinimumStock;
    string Name;

    getline(is,Expires);
    getline(is,Name);
    is >> InStock;
    is >> MinimumStock;
    is.ignore();

    if (Expires == "0")
        Item = new StockItem(Name,InStock,MinimumStock);
    else
        Item = new DatedStockItem(Name,InStock,
        MinimumStock,Expires);

    return is;
}

void DatedStockItem::Reorder(ostream& os)
{
    if (m_Expires < Today())
        {
        os << "DatedStockItem::Reorder says:" << endl;
        os << "Return " << m_InStock <<  " units of ";
        os << m_Name << endl;
        m_InStock = 0;
        }

    StockItem::Reorder(os);
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
   FormatStream >> TodaysDate;

   return TodaysDate;
}

DatedStockItem::DatedStockItem(string Name, short InStock, 
short MinimumStock, string Expires)
: StockItem(Name, InStock,MinimumStock),
  m_Expires(Expires)
{
}

void DatedStockItem::Write(ostream& os)
{
    os << m_Expires << endl;
    os << m_Name << endl;
    os << m_InStock << endl;
    os << m_MinimumStock << endl;
}
