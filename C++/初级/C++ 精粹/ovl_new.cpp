/*********************************************************************

  Filename:  ovl_new.cpp
  Section:   8.10.1 Placement Syntax and Overloading
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

#include <iostream.h>
#include <string.h>


//overloaded new as found in <new.h>
void* operator new(size_t size, void* ptr)
{ return ptr; }

char* buf1 = new char[1000];  //global memory
char* buf2 = new char[2000];  //more global memory

class sma_ob {               //needs only a few bytes
public:
   char a;
   char b;
};

// This program will use new to get memory from buf1 or buf2
int main()
{
   strcpy(buf1, "ABCDEFGHIJK");    // init memory so we can see alloc
   strcpy(buf2, "1234567890");

   sma_ob *p = new(buf1) sma_ob;   //place at begin buf1[]
   sma_ob *q = new(buf2) sma_ob;   //place at begin buf2[]
   sma_ob *r = new(buf2 + sizeof(sma_ob)) sma_ob;
   cout << "p points at " << p -> a << p -> b << endl;
   cout << "q points at " << q -> a << q -> b << endl;
   cout << "r points at " << r -> a << r -> b << endl;
}

