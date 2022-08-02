#include <iostream>
#include <fstream>
#include <string>

#include "Vec.h"
#include "xstring.h"
#include "hmit6.h"
#include "hmin6.h"
using namespace std;

int main()
{
    ifstream HomeInfo("home3.in");
    HomeInventory MyInventory;
    HomeItem TempItem;
    xstring Name;
    xstring Description;

    MyInventory.LoadInventory(HomeInfo);

    TempItem = MyInventory.FindItemByName("Relish");
    cout << endl;

    TempItem.Edit();
    cout << endl;

    TempItem.FormattedDisplay(cout);
    cout << endl;

    cout << "Please enter a search string: ";
    cin >> Description;

    TempItem = MyInventory.FindItemByDescription(Description);

    if (TempItem.IsNull())
      cout << "Sorry, I couldn't locate that item." << endl;
    else
      TempItem.FormattedDisplay(cout);
    cout << endl;

    return 0;
}
