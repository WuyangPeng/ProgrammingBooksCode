#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <dos.h>
#include "item21.h"
using namespace std;

StockItem::StockItem()
: m_InStock(0), m_Price(0), m_MinimumStock(0), 
  m_MinimumReorder(0), m_Name(), m_Distributor(),
  m_UPC()
{
}

StockItem::StockItem(string Name, short InStock, 
  short Price, short MinimumStock, short MinimumReorder, 
  string Distributor, string UPC)
: m_InStock(InStock), m_Price(Price), 
  m_MinimumStock(MinimumStock), 
  m_MinimumReorder(MinimumReorder), m_Name(Name),
  m_Distributor(Distributor), m_UPC(UPC)
{
}

void StockItem::FormattedDisplay(ostream& os)
{
  os << "Name: ";
  os << m_Name << endl;
  os << "Number in stock: ";
  os << m_InStock << endl;
  os << "Price: ";
  os << m_Price << endl;
  os << "Minimum stock: ";
  os << m_MinimumStock << endl;
  os << "Minimum Reorder quantity: ";
  os << m_MinimumReorder << endl;
  os << "Distributor: ";
  os << m_Distributor << endl;
  os << "UPC: ";
  os << m_UPC << endl;
}

ostream& operator << (ostream& os, const StockItem& Item)
{
  os << Item.m_Name << endl;
  os << Item.m_InStock << endl;
  os << Item.m_Price << endl;
  os << Item.m_MinimumStock << endl;
  os << Item.m_MinimumReorder << endl;
  os << Item.m_Distributor << endl;
  os << Item.m_UPC << endl;

  return os;
}

istream& operator >> (istream& is, StockItem& Item)
{
  getline(is,Item.m_Name);
  is >> Item.m_InStock;
  is >> Item.m_Price;
  is >> Item.m_MinimumStock;
  is >> Item.m_MinimumReorder;
  is.ignore();
  getline(is,Item.m_Distributor);
  getline(is,Item.m_UPC);
  return is;
}

bool StockItem::CheckUPC(string ItemUPC)
{
  if (m_UPC == ItemUPC)
    return true;

  return false;
}

void StockItem::DeductSaleFromInventory(short QuantitySold)
{
  m_InStock -= QuantitySold;
}

short StockItem::GetInventory()
{
  return m_InStock;
}

string StockItem::GetName()
{
  return m_Name;
}

string StockItem::GetUPC()
{
  return m_UPC;
}

bool StockItem::IsNull()
{
  if (m_UPC == "")
    return true;

  return false;
}

short StockItem::GetPrice()
{
  return m_Price;
}

void StockItem::Reorder(ostream& os)
{
  short ActualReorderQuantity;

  if (m_InStock < m_MinimumStock)
    {
    ActualReorderQuantity = m_MinimumStock - m_InStock;
    if (m_MinimumReorder > ActualReorderQuantity)
      ActualReorderQuantity = m_MinimumReorder;
    os << "Reorder " << ActualReorderQuantity;
    os <<  " units of " << m_Name;
    os << " with UPC " << m_UPC;
    os << " from " << m_Distributor << endl;
    }
}

DatedStockItem::DatedStockItem()
: m_Expires()
{
}

string DatedStockItem::Today()
{
  date d;
  short year;
  char day;
  char month;
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
  short Price, short MinimumStock, short MinimumReorder, 
  string Distributor, string UPC, string Expires)
: StockItem(Name, InStock, Price, MinimumStock,
  MinimumReorder, Distributor, UPC), 
  m_Expires(Expires)
{
}

void DatedStockItem::Reorder(ostream& os)
{
  if (m_Expires < Today())
    {
    os << "Return " << m_InStock;
    os << " units of " << m_Name;
    os << " with UPC " << m_UPC;
    os << " to " << m_Distributor << endl;
    m_InStock = 0;
    }

  StockItem::Reorder(os);
}

void DatedStockItem::FormattedDisplay(ostream& os)
{
  os << "Expiration Date: ";
  os << m_Expires << endl;
  StockItem::FormattedDisplay(os);
}

ostream& operator << (ostream& os, const DatedStockItem& Item)
{
  os << Item.m_Expires << endl;
  os << Item.m_Name << endl;
  os << Item.m_InStock << endl;
  os << Item.m_Price << endl;
  os << Item.m_MinimumStock << endl;
  os << Item.m_MinimumReorder << endl;
  os << Item.m_Distributor << endl;
  os << Item.m_UPC << endl;

  return os;
}

istream& operator >> (istream& is, DatedStockItem& Item)
{
  getline(is,Item.m_Expires);
  getline(is,Item.m_Name);
  is >> Item.m_InStock;
  is >> Item.m_Price;
  is >> Item.m_MinimumStock;
  is >> Item.m_MinimumReorder;
  is.ignore();
  getline(is,Item.m_Distributor);
  getline(is,Item.m_UPC);
  return is;
}
