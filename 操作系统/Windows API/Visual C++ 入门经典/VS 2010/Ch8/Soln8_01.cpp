// Soln8_01.cpp
/*
No assignment operator needs to be defined for CEstimatedInteger object because the
default operator works fine.
I have not included implementations for * and / operations but these are easy to add
being very similar to the operator+() functions.
*/
#include <iostream>                   // For stream input/output

using std::cout;
using std::endl;

class CEstimatedInteger
{
private:
   int value;      
   bool estimated;     // true indicates estimated

public:
  CEstimatedInteger(int i=0, bool e=false) : value(i), estimated(e){}

   void print();

   CEstimatedInteger operator+(const CEstimatedInteger& n) const
   {
     return CEstimatedInteger(value+n.value, estimated || n.estimated);
   }

   CEstimatedInteger operator+(const int& n) const
   {
     return CEstimatedInteger(value+n, estimated);
   }

};

void CEstimatedInteger::print()
{
   if (estimated)
      cout << 'E';
   cout << value;
}


CEstimatedInteger operator+(const int& a, const CEstimatedInteger& b)
{
   return b+a;
}

int main()
{
   CEstimatedInteger a=3, c;
   CEstimatedInteger b(5,true);

   cout << "a = ";
   a.print();
   cout << endl;

   cout << "b = ";
   b.print();
   cout << endl;

   c = a + b;
   cout << "a + b = ";
   c.print();
   cout << endl;

   c = 7 + b;
   cout << "7 + b = ";
   c.print();
   cout << endl;

   c = a + 9;
   cout << "a + 9 = ";
   c.print();
   cout << endl;

   c = 8 + a + 9 + b;
   cout << "8 + a + 9 + b = ";
   c.print();
   cout << endl;

   return 0;
}
