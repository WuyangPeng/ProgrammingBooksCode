// Soln7_05.cpp

#include <iostream>                   // For stream input/output

using std::cout;
using std::endl;

static const int MAX{ 10 };            // Maximum stack size

class CStack
{
public:
   void push(int i);
   int pop();
   void print();
private:
  int list[MAX];
  size_t next{};

};

// Push a value on to the stack
void CStack::push(int i)
{
   if (next < MAX)
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
   int index(next);
   while(index)
     cout << " " << list[--index];
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
}

