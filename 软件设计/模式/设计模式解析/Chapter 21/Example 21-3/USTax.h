#pragma once
// Code Fragments
// Multithreading/Lock Detail Beyond Scope Here
#include <Thread.h>
#include <Mutex.h>
#include <Guard.h>
class USTax
{
public:
 static USTax* Instance();
protected:
 USTax(void);
 virtual ~USTax(void);
private:
 static Mutex lock;
 static USTax * myInstance;
}; 