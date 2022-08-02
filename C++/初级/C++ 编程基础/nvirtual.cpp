#include <iostream>
#include "itema.h"
using namespace std;

int main()
{
    StockItem StockItemObject("soup",32,100);
    StockItem* StockItemPointer;
    DatedStockItem DatedStockItemObject("milk",
      10,15,"19950110");

    DatedStockItem* DatedStockItemPointer;

    StockItemObject.Reorder(cout);
    cout << endl;
    DatedStockItemObject.Reorder(cout);
    cout << endl;

    StockItemPointer = new StockItem("beans",40,110);
    StockItemPointer->Reorder(cout);
    cout << endl;

    DatedStockItemPointer = new DatedStockItem("ham",
      22,30,"19970110");
    DatedStockItemPointer->Reorder(cout);
    cout << endl;

    StockItemPointer = new DatedStockItem("steak",
      90,95,"19960110");
    StockItemPointer->Reorder(cout);
    cout << endl;
}
