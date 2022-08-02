#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "itema.h"
#include <dos.h>
using namespace std;

StockItem::StockItem(string Name, short InStock, 
short MinimumStock)
: m_InStock(InStock), m_Name(Name), 
  m_MinimumStock(MinimumStock)
{
}

void StockItem::Reorder(ostream& os)
{
  short ActualReorderQuantity;

  if (m_InStock < m_MinimumStock)
    {
    ActualReorderQuantity = m_MinimumStock - m_InStock;
    os << "StockItem::Reorder says:" << endl;
    os << "Reorder " << ActualReorderQuantity << " units of ";
    os <<  m_Name << endl;
    }
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

void DatedStockItem::Reorder(ostream& os)
{

  if (m_Expires < Today())
    {
    os << "DatedStockItem::Reorder says:" << endl;
    short ReturnQuantity = m_InStock;
    m_InStock = 0;
    os << "Return " << ReturnQuantity <<  " units of ";
    os << m_Name << endl;
    }

  StockItem::Reorder(os);
}

DatedStockItem::DatedStockItem(string Name, short InStock, 
short MinimumStock, string Expires)
: StockItem(Name, InStock,MinimumStock),
  m_Expires(Expires)
{
}
