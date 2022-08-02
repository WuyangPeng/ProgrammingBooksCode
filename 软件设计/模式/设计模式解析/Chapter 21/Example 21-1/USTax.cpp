#include "USTax.h"
USTax* USTax::myInstance = 0;
USTax* USTax::Instance ()
{
 if (myInstance == 0) {
 myInstance = new USTax;
 }
 return myInstance;
}
 