#include "V1Slot.h"
#include "V1.h"

V1Slot::V1Slot(int modelNumber, int ID)
{
    myModelNumber = modelNumber;
    myID = ID;
}

V1Slot::~V1Slot(void)
{
}

// myModelNumber and myID are private members containing
// information about the model and feature (in V1) this 
// feature corresponds to
double V1Slot::getX1 () 
{
    return V1::getX1forSlot( myModelNumber, myID);
}
double V1Slot::getX2 () 
{
    return V1::getX2forSlot( myModelNumber, myID);
}