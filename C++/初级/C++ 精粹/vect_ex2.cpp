/*********************************************************************

  Filename:  vect_ex2.cpp
  Section:   14     Exceptions
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

#include <iostream.h>
#include <stdlib.h>     //for exit

class vect {
public:
   explicit vect(int n = 10);
   vect(vect& v);
   ~vect() { delete []p; }
private:
   int*  p;
   int   size;
};


vect::vect(int n)
{
   try {
      if (n < 1)
         throw (n);
      p = new int[n];
      if (p == 0)
         throw ("FREE STORE EXHAUSTED");
   }
   catch (int n)
   {
      cerr << "SIZE ERROR " << n << endl;
      abort();
   }
   catch (const char* error)    // catches if heap exhausted
   {
      cerr << error << endl;
      abort();
   }
}


vect::vect(vect& v)
{
   size = v.size;
   p = new int[size];
   for (int i = 0; i < size; ++i)
      p[i] = v.p[i];
}


int main()
{
   vect g(-10);         //show exception on bad parameter
}



