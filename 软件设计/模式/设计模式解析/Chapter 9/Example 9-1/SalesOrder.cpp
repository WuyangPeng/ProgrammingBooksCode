#include "SalesOrder.h"

SalesOrder::SalesOrder(void)
{
}

SalesOrder::~SalesOrder(void)
{
}

void SalesOrder::process (CalcTax *taxToUse)
{
    long itemNumber= 0;
    double price= 0;

    // given the tax object to use

    // . . .

    // calculate tax
    double tax= taxToUse->taxAmount( itemNumber, price);
}