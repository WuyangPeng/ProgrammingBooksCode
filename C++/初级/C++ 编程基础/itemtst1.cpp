#include <iostream>
#include <string>
#include "item1.h"
using namespace std;

int main()
{
    StockItem soup;

    soup = StockItem("Chunky Chicken",32,129,
    "Bob's Distribution","123456789");

    soup.Display();

    return 0;
}
