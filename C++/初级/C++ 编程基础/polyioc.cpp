#include <iostream>
#include <fstream>

#include "Vec.h"
#include "itemp.h"
using namespace std;

int main()
{
    StockItem x;
    StockItem y;

    ifstream ShopInfo("shop22.in");

    ShopInfo >> x;

    ShopInfo >> y;

    cout << "A StockItem: " << endl;
    cout << x;

    cout << endl;

    cout << "A DatedStockItem: " << endl;
    cout << y;

    return 0;
}
