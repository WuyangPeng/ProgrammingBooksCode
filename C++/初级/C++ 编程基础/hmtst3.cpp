#include <iostream>
#include <fstream>

#include "Vec.h"
#include "hmit2.h"
#include "hmin2.h"
using namespace std;

int main()
{
    ifstream HomeInfo("home3.in");

    HomeInventory MyInventory;

    MyInventory.LoadInventory(HomeInfo);

    HomeItem test = MyInventory.FindItemByName("Relish");

    cout << test;

    return 0;
}


