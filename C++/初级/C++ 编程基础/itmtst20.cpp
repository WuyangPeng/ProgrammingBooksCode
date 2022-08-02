#include <iostream>
#include <fstream>
#include "Vec.h"
#include "item20.h"
#include "invent20.h"
using namespace std;

int main()
{
  ifstream ShopInfo("shop20.in");
  ofstream ReorderInfo("shop20.reo");

  Inventory MyInventory;

  MyInventory.LoadInventory(ShopInfo);

  MyInventory.ReorderItems(ReorderInfo);

  return 0;
}
