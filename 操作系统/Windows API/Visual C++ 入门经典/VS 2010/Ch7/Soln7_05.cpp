// Soln7_05.cpp

#include <iostream>                   // For stream input/output

using std::cout;
using std::endl;

class CStack
{
public:
   CStack() : next(0) {}
   void push(int i);
   int pop();
   void print();
private:
   int list[100];
   int next;
};

// Push a value on to the stack
void CStack::push(int i)
{
   if (next < 99)
      list[next++] = i;
}

// Pop a value off the stack
int CStack::pop()
{
   return list[--next];
}

// Output the contents of the stack
void CStack::print()
{
   cout << '[';
   for(int i = next-1 ; i >= 0 ; i--)
      cout << ' '<< list[i];
   cout << " ]\n";
}

int main()
{
   CStack s;

   s.print();

   s.push(5);
   s.push(10);
   s.push(8);

   s.print();

   cout << "top of stack = " << s.pop() << endl;

   s.print();

   return 0;
}

