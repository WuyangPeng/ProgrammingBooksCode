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
    string PurchaseUPC;
    short PurchaseCount;
    bool Found;

    for (i = 0; i < 100; i ++)
        {
        AllItems[i].Read(ShopInfo);
        if (ShopInfo.fail() != 0)
            break;
        }

    InventoryCount = i;

    cout << "What is the UPC of the item?" << endl;
    cin >> PurchaseUPC;
    cout << "How many items were sold?" << endl;
    cin >> PurchaseCount;

    Found = false;
    for (i = 0; i < InventoryCount; i ++)
        {
        if (PurchaseUPC == AllItems[i].m_UPC)
            {
            Found = true;
            break;
            }
        }

    if (Found)
        {
        AllItems[i].m_InStock -= PurchaseCount;
        cout << "The inventory has been updated." << endl;
        }
    else
        cout << "Can't find that item. Please check UPC" << endl;

    return 0;
}
