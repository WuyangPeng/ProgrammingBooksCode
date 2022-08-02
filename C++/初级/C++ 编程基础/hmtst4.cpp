#include <iostream>
#include <fstream>

#include "Vec.h"
#include "hmit4.h"
#include "hmin4.h"
using namespace std;

int main()
{
    ifstream HomeInfo("home3.in");
    HomeInventory MyInventory;
    HomeItem TempItem;
    string Name;

    MyInventory.LoadInventory(HomeInfo);

    TempItem = MyInventory.AddItem();
    Name = TempItem.GetName();
    HomeItem test2 = MyInventory.FindItemByName(Name);
    cout << endl << "Here is the item you added" << endl;
    test2.FormattedDisplay(cout);

    HomeItem test1 = MyInventory.FindItemByName("Relish");
    cout << endl << "Here is an item from the file" << endl;
    test1.FormattedDisplay(cout);

    return 0;
}
