#include <iostream>
#include <fstream>
#include <string>
#include "Vec.h"
#include "item6.h"
#include "invent2.h"
using namespace std;

Inventory::Inventory()
: m_Stock (Vec<StockItem>(100)),
  m_StockCount(0)
{
}

short Inventory::LoadInventory(ifstream& is)
{
    short i;

    for (i = 0; i < 100; i ++)
        {
        m_Stock[i].Read(is);
        if (is.fail() != 0)
            break;
        }

    m_StockCount = i;
    return m_StockCount;
}

StockItem Inventory::FindItem(string UPC)
{
    short i;
    bool Found = false;

    for (i = 0; i < m_StockCount; i ++)
        {
        if (m_Stock[i].GetUPC() == UPC)
            {
            Found = true;
            break;
            }
        }

    if (Found)
        return m_Stock[i];

    return StockItem();
}

bool Inventory::UpdateItem(StockItem Item)
{
    string UPC = Item.GetUPC();

    short i;
    bool Found = true;

    for (i = 0; i < m_StockCount; i ++)
        {
        if (m_Stock[i].GetUPC() == UPC)
            {
            Found = true;
            break;
            }
        }

    if (Found)
        m_Stock[i] = Item;
        
    return Found;
    
}

//function added for inventory update
void Inventory::StoreInventory(ofstream& os)
{
    short i;

    for (i = 0; i < m_StockCount; i ++)
        m_Stock[i].Write(os);
}

