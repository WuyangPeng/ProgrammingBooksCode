// Soln 9_03.cpp
/*
  CBase is an abstract class because it contains the pure virtual function Print().
*/
#include <iostream>
using std::cout;
using std::endl;

class CBase
{
protected:
   int m_anInt;
public:
   CBase(int n) : m_anInt(n) { cout << "Base constructor" << endl; }
   virtual void Print() = 0;
};

class CDerived : public CBase
{
public:
   CDerived(int n) : CBase(n) { cout << "Derived constructor" << endl; }
   void Print() { cout << "value is " << m_anInt << endl; }
};

int main()
{
   CDerived d(3);

   d.Print();

   return 0;
}
