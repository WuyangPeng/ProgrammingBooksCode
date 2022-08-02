#include <iostream>
#include <fstream>
#include <string>
#include "Vec.h"
#include "itemp.h"
using namespace std;

int main()
{
    StockItem x("test1",1,2,3,4,"abc","1234");
    StockItem y("test2",11,12,13,14,"def","5678","19990101");

    cout << "A StockItem: " << endl;
    cout << x;

    cout << endl;

    cout << "A DatedStockItem: " << endl;
    cout << y;

    x.Reorder(cout);
    y.Reorder(cout);

    return 0;
}
