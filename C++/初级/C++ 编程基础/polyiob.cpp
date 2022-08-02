#include <iostream>
#include <fstream>
#include "Vec.h"
#include "itemc.h"
using namespace std;

int main()
{
    StockItem* x;
    StockItem* y;

    ifstream ShopInfo("polyiob.in");

    ShopInfo >> x;

    ShopInfo >> y;

    cout << "A StockItem: " << endl;
    cout << x;

    cout << endl;

    cout << "A DatedStockItem: " << endl;
    cout << y;

    delete x;
    delete y;

    return 0;
}
