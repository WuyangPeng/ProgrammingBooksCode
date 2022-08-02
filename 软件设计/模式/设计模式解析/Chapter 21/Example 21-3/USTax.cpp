// Simplified - In the real world, much detail 
// would be added around the multithreading/Lock mechanics
#include "USTax.h"
USTax* USTax::myInstance = 0;
USTax::USTax(void)
{
}
USTax::~USTax(void)
{
}
USTax* USTax::Instance() {
 // 1st test
 if (myInstance == 0) 
 { 
 // acquire lock (simplified)
 Guard guard (lock);
 // 2nd test
 if (myInstance == 0) 
 { 
 myInstance = new USTax;
 }
 // release guard/lock (via destructor)
 }
 return myInstance;
} 