#include <iostream>
#include <string>
#include "itemp.h"
using namespace std;

int main()
{
    StockItem item1("cups",32,129,10,5,"Bob's Dist.",
        "2895657951"); // create an undated object

    StockItem item2("Hot Chicken",48,158,15,12,"Joe's Dist.",
        "987654321", "19960824"); // create a dated object

    StockItem item3 = item1; // copy constructor
    item1 = item2; // assignment operator

    item1.FormattedDisplay(cout); // display an object with labels

    return 0;
}
