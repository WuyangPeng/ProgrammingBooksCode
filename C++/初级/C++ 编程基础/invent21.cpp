#include <iostream>
#include <fstream>
#include "Vec.h"
#include "item21.h"
#include "invent21.h"
using namespace std;

Inventory::Inventory()
: m_Stock (Vec<DatedStockItem>(100)),
  m_StockCount(0)
{
}

short Inventory::LoadInventory(ifstream& is)
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

DatedStockItem Inventory::FindItem(string UPC)
{
  short i;
  short Found = 0;

  for (i = 0; i < m_StockCount; i ++)
    {
    if (m_Stock[i].GetUPC() == UPC)
      {
      Found = 1;
      break;
      }
    }

  if (Found == 1)
    return m_Stock[i];

  return DatedStockItem();
}

bool Inventory::UpdateItem(DatedStockItem Item)
{
  string UPC = Item.GetUPC();

  short i;
  short Found = false;

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

void Inventory::StoreInventory(ofstream& OutputStream)
{
  short i;

  for (i = 0; i < m_StockCount; i ++)
    OutputStream << m_Stock[i];
}

void Inventory::ReorderItems(ofstream& OutputStream)
{
  short i;

  for (i = 0; i < m_StockCount; i ++)
    m_Stock[i].Reorder(OutputStream);
}
