// Soln7_06.cpp

#include <iostream>                    // For stream input/output

using std::cout;
using std::cerr;
using std::endl;

static const int MAX{ 10 };            // Maximum stack size

class CStack
{
public:
   void push(int i);
   int pop();
   void print();
   int peek();

private:
  int list[MAX];
  size_t next{};

};

// Push a value on to the stack
void CStack::push(int i)
{
   if (next < MAX)
      list[next++] = i;
   else
      cerr << "Error! Stack overflow" << endl;
}

// Pop a value off the stack
int CStack::pop()
{
  if(next)
  {
    return list[--next];
  }
  else
  {
    cerr << "Error! Stack empty" << endl;
    return 0;
  }
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

// Inspect the top of the stack
int CStack::peek()
{
   if (next)
   {
      return list[next - 1];
   }
   else
   {
      cerr << "Error! Stack empty" << endl;
      return 0;
   }
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
}

