// Soln8_06.cpp
// We must add a destructor to release memory when a CStack object is destroyed.
#include <iostream>                   // For stream input/output

using std::cout;
using std::endl;

class CStack
{
public:
   CStack(int n = 10);
   ~CStack();
   void push(int i);
   int pop();
   void print();

private:
   int* pList;
   int size;
   int next;
};

CStack::CStack(int n) : next(0), size(n)
{
   pList = new int[size];
}

CStack::~CStack()
{
   delete [] pList;
}

void CStack::push(int i)
{
   if (next < 99)
      pList[next++] = i;
}

int CStack::pop()
{
   return pList[--next];
}

void CStack::print()
{
   cout << '[';
   for(int i=next-1 ; i>=0 ; i--)
      cout << ' '<< pList[i];
   cout << " ]\n";
}

int main()
{
   CStack s(20);

   s.print();

   s.push(5);
   s.push(10);
   s.push(8);

   s.print();

   cout << "top of stack=" << s.pop() << endl;

   s.print();

   return 0;
}

