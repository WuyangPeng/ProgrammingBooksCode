#include <iostream>
#include <fstream>
#include "Vec.h"
#include "item21.h"
#include "invent21.h"
using namespace std;

int main()
{
  ifstream ShopInfo("shop21.in");
  ofstream ReorderInfo("shop21.reo");

  Inventory MyInventory;

  MyInventory.LoadInventory(ShopInfo);

  MyInventory.ReorderItems(ReorderInfo);

  return 0;
}
