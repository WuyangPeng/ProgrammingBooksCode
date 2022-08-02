#include "V1Hole.h"
#include "V1.h"

V1Hole::V1Hole(int modelNumber, int ID)
{
    myModelNumber = modelNumber;
    myID = ID;
}
V1Hole::~V1Hole(void)
{
}
// myModelNumber and myID are private members containing
// information about the model and feature (in V1) this 
// feature corresponds to

double V1Hole::getX()
{
    return V1::getXforHole( myModelNumber, myID);
}