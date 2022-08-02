#include <iostream>
#include "Vec.h"
#include "itemc.h"
using namespace std;

int main()
{
    Vec <StockItem*> x(2);

    x[0] = new StockItem("3-ounce cups",71,78);

    x[1] = new DatedStockItem("milk",76,87,"19970719");

    cout << "A StockItem: " << endl;
    cout << x[0] << endl;

    cout << "A DatedStockItem: " << endl;
    cout << x[1] << endl;

    delete x[0];
    delete x[1];

    return 0;
}
