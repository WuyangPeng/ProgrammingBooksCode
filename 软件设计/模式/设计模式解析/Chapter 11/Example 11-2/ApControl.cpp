#include "ApControl.h"

ApControl::ApControl(void)
{
    ResFactory *myResFactory= ResFactory::getFactory();
    myDisplayDriver= myResFactory->getDispDrvr();
    myPrintDriver= myResFactory->getPrtDrvr();
}

ApControl::~ApControl(void)
{
}

void ApControl::doDraw(void)
{
//    . . .
    myDisplayDriver->draw();
}

void ApControl::doPrint(void)
{
//    . . .
    myPrintDriver->print();
}