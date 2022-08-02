#include <iostream>
#include <fstream>
#include <string>
#include "Vec.h"
#include "item2.h"
using namespace std;

int main()
{
    ifstream ShopInfo("shop2.in");
    Vec<StockItem> AllItems(100);
    short i;
    short InventoryCount;

    for (i = 0; i < 100; i ++)
        {
        AllItems[i].Read(ShopInfo);
        if (ShopInfo.fail() != 0)
            break;
        }

    InventoryCount = i;

    for (i = 0; i < InventoryCount; i ++)
        {
        AllItems[i].Display();
        }

    return 0;
}
