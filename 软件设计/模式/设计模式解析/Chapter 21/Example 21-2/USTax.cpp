#include "USTax.h"
// USTax* USTax::myInstance = 0;
USTax* USTax::getInstance ()
{
 if (myInstance == 0) {
 myInstance = new USTax;
 }
 return myInstance;
}
double USTax::calcTax(double a,double b){
 return 0; //Obviously needing a real implementation
}