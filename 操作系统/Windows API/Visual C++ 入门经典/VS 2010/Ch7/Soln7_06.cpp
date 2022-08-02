// Soln7_06.cpp

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
   int peek();
private:
   int list[100];
   int next;
};

// Push a value on to the stack
void CStack::push(int i)
{
   if (next < 99)
      list[next++] = i;
   else
      cout << "Error! Stack overflow" << endl;
}

// Pop a value off the stack
int CStack::pop()
{
   if (next == 0)
   {
      cout << "Error! Stack underflow" << endl;
      return 0;
   }
   else
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

// Inspect the top of the stack
int CStack::peek()
{
   if (next == 0)
   {
      cout << "Error! Stack underflow" << endl;
      return 0;
   }
   else
      return list[next-1];
}

int main()
{
   CStack s;

   s.print();

   s.push(5);
   s.push(10);
   s.push(8);

   s.print();

   cout << "peek at top of stack = " << s.peek() << endl;
   s.print();
   cout << "pop top of stack = " << s.pop() << endl;
   cout << "pop top of stack = " << s.pop() << endl;
   s.print();
   cout << "pop top of stack = " << s.pop() << endl;
   cout << "pop top of stack = " << s.pop() << endl;

   return 0;
}

