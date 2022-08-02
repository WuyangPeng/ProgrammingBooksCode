#include <iostream>
#include <fstream>

#include "Vec.h"
#include "hmit5.h"
#include "hmin5.h"
using namespace std;

int main()
{
    ifstream HomeInfo("home3.in");
    HomeInventory MyInventory;
    HomeItem TempItem;
    string Name;

    MyInventory.LoadInventory(HomeInfo);

    TempItem = MyInventory.FindItemByName("Relish");
    cout << endl;

    TempItem.Edit();
    cout << endl;

    TempItem.FormattedDisplay(cout);
    cout << endl;

    return 0;
}
