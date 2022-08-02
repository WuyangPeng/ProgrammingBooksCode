#include <iostream>
#include <fstream>
#include "Vec.h"
#include "item20.h"
#include "invent20.h"
using namespace std;

Inventory::Inventory()
: m_Stock (Vec<StockItem>(100)),
  m_StockCount(0)
{
}

short Inventory::LoadInventory(istream& is)
{
  short i;

  for (i = 0; i < 100; i ++)
    {
    is >> m_Stock[i];
    if (is.fail())
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
    m_Stock[i] = Item;
    
  return Found;
  
}

void Inventory::StoreInventory(ostream& os)
{
  short i;

  for (i = 0; i < m_StockCount; i ++)
    os << m_Stock[i];
}

void Inventory::ReorderItems(ostream& os)
{
  short i;

  for (i = 0; i < m_StockCount; i ++)
    m_Stock[i].Reorder(os);
}
