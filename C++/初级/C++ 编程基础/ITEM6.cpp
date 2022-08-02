#include <iostream>
#include <fstream>
#include <string>
#include "vec.h"
#include "item6.h"
using namespace std;

StockItem::StockItem()
: m_InStock(0), m_Price(0), m_Name(), 
  m_Distributor(), m_UPC()
{
}

StockItem::StockItem(string Name, short InStock, 
short Price, string Distributor, string UPC)
: m_InStock(InStock), m_Price(Price), m_Name(Name), 
  m_Distributor(Distributor), m_UPC(UPC)
{
}

void StockItem::Display()
{
    cout << "Name: ";
    cout << m_Name << endl;
    cout << "Number in stock: ";
    cout << m_InStock << endl;
    cout << "Price: ";
    cout << m_Price << endl;
    cout << "Distributor: ";
    cout << m_Distributor << endl;
    cout << "UPC: ";
    cout << m_UPC << endl;
    cout << endl;
}

void StockItem::Read(istream& is)
{
  getline(is,m_Name);
  is >> m_InStock;
  is >> m_Price;
  is.ignore();
  getline(is,m_Distributor);
  getline(is,m_UPC);
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

//function added for inventory update
void StockItem::Write(ofstream& os)
{
    os << m_Name << endl;
    os << m_InStock << endl;
    os << m_Price << endl;
    os << m_Distributor << endl;
    os << m_UPC << endl;
    return;
}

