#include <iostream>
#include <fstream>
#include <string>
#include "Vec.h"
#include "item4.h"
using namespace std;

int main()
{
    ifstream ShopInfo("shop2.in");
    Vec<StockItem> AllItems(100);
    short i;
    short InventoryCount;
    short OldInventory;
    short NewInventory;
    string PurchaseUPC;
    string ItemName;
    short PurchaseCount;
    bool Found;

    for (i = 0; i < 100; i ++)
        {
        AllItems[i].Read(ShopInfo);
        if (ShopInfo.fail() != 0)
            break;
        }

    InventoryCount = i;
    cout << "What is the UPC of the item? ";
    cin >> PurchaseUPC;
    Found = false;

    for (i = 0; i < InventoryCount; i ++)
        {
        if (AllItems[i].CheckUPC(PurchaseUPC))
            {
            Found = true;
            break;
            }
        }

    if (Found)
        {
        OldInventory = AllItems[i].GetInventory();
        ItemName = AllItems[i].GetName();

        cout << "There are currently " << OldInventory << " units of "
        << ItemName << " in stock." << endl;
        cout << "How many items were sold? ";
        cin >> PurchaseCount;

        AllItems[i].DeductSaleFromInventory(PurchaseCount);
        cout << "The inventory has been updated." << endl;

        NewInventory = AllItems[i].GetInventory();
        cout << "There are now " << NewInventory << " units of "
        << ItemName << " in stock." << endl;
        }
    else
        cout << "Can't find that item. Please check UPC" << endl;

    return 0;
}
