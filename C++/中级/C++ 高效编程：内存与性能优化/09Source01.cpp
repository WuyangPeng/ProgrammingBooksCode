#include "BookTools.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <iomanip.h>

const int N = 5000;

class A   // just a class  
{
        int data;
        A* next;

        public:
        A()  {};
        ~A() {};
};

class B  // same as class A but with "new" and "delete" overloaded
{
        int data;
        B* next;

        static B* freelist;             // pointer to free list

        public:
        B()  {};
        ~B() {};
                
        inline void* operator new(size_t);     // overloaded new()
        inline void operator delete(void*);    // overloaded delete()
};

class C :public B // exactly equal to class A but inherits from class B
{
        int data;
        C* next;

        public:
        C()  {};
        ~C() {};
};

A* aptr[N];
B* bptr[N];
C* cptr[N];

B* B::freelist = 0;

inline void* B::operator new(size_t sz)
{
  if (freelist)   // get free node from freelist if any
  {
         B* p = freelist;
         freelist = freelist->next;
         return p;
  }
  return malloc(sz);  // call malloc() otherwise
}

inline void B::operator delete(void* vp)
{
    B* p = (B*)vp;
    // link freed node onto freelist
    p->next = freelist;
    freelist = p;
}


long Org()
{
	// Original Benchmark
    int i;
    int j;

	for (i = 1; i <= N; i++) 
    {
         for (j = 0; j < N; j++)
           aptr[j] = new A();
         for (j = 0; j < N; j++)
           delete aptr[j];
    }

	return(0);
}

long Opt()
{	 
    // New Optimized Benchmark
    int i;
    int j;
    for (i = 1; i <= N; i++) 
    {
         for (j = 0; j < N; j++)
            bptr[j] = new B();
         for (j = 0; j < N; j++)
            delete bptr[j];
    }
	return(0);
}

long Inh()
{
      // New Optimized Benchmark (Inherited)
    int i;
    int j;
    for (i = 1; i <= N; i++) 
    {
         for (j = 0; j < N; j++)
            cptr[j] = new C();
         for (j = 0; j < N; j++)
            delete cptr[j];
    }
	return(0);
}



void main(int argc, char **argv)
{

	for (;;)
	{
		cout << "Timing Freelist Implementations" << endl;
		cout << "Original Benchmark      " << time_fn(Org) << endl;	
		cout << "New Optimized Benchmark " << time_fn(Opt) << endl;	
		cout << "New Inherited Benchmark " << time_fn(Inh) << endl;	
	}

}
