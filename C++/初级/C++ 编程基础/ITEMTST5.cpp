#include <iostream>
#include <fstream>
#include <string>
#include "vec.h"
#include "item5.h"
#include "invent1.h"
using namespace std;

int main()
{
    ifstream InputStream("shop2.in");
    string PurchaseUPC;
    short PurchaseCount;
    string ItemName;
    short OldInventory;
    short NewInventory;
    Inventory MyInventory;
    StockItem FoundItem;
    string TransactionCode;

    MyInventory.LoadInventory(InputStream);

    cout << "What is the UPC of the item? ";
    cin >> PurchaseUPC;

    FoundItem = MyInventory.FindItem(PurchaseUPC);
    if (FoundItem.IsNull())
        {
        cout << "Can't find that item. Please check UPC." << endl;
        return 0;
        }

    OldInventory = FoundItem.GetInventory();
    ItemName = FoundItem.GetName();
    
    cout << "There are currently " << OldInventory << " units of "
    << ItemName << " in stock." << endl;

    cout << "Please enter transaction code as follows:\n";
    cout << "S (sale), C (price check): ";
    cin >> TransactionCode;

    if (TransactionCode == "C" || TransactionCode == "c")
        {
        cout << "The name of that item is: " << ItemName << endl;
        cout << "Its price is: " << FoundItem.GetPrice();
        }
    else if (TransactionCode == "S" || TransactionCode == "s")
        {
        cout << "How many items were sold? ";
        cin >> PurchaseCount;

        FoundItem.DeductSaleFromInventory(PurchaseCount);
        MyInventory.UpdateItem(FoundItem);
    
        cout << "The inventory has been updated." << endl;
    
        FoundItem = MyInventory.FindItem(PurchaseUPC);
        NewInventory = FoundItem.GetInventory();
        
        cout << "There are now " << NewInventory << " units of "
        << ItemName << " in stock." << endl;
        }

    return 0;
}
