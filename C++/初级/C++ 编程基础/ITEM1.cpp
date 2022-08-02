#include <iostream>
#include <string>
#include "item1.h"
using namespace std;

StockItem::StockItem()
: m_Name(), m_InStock(0), m_Price(0), m_Distributor(), m_UPC()
{
}

StockItem::StockItem(string Name, short InStock, 
short Price, string Distributor, string UPC)
: m_Name(Name), m_InStock(InStock), m_Price(Price), 
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
}