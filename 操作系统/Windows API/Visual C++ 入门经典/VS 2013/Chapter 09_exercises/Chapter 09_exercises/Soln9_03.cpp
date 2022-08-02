// Soln 9_03.cpp
/*
  CBase is an abstract class because it contains the pure virtual function print().
*/
#include <iostream>

class CBase
{
protected:
   int m_anInt;
public:
  CBase(int n) : m_anInt{ n } { std::cout << "Base constructor\n"; }
   virtual void print() const = 0;
};

class CDerived : public CBase
{
public:
  CDerived(int n) : CBase{ n } { std::cout << "Derived constructor\n"; }
  void print() const override { std::cout << "value is " << m_anInt << std::endl; }
};

int main()
{
  CDerived d{ 3 };

   d.print();
}
