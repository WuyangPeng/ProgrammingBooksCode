// Soln8_06.cpp
// We must add a destructor to release memory when a CStack object is destroyed.
/// I added code to increase the size of the stack when necessary.

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
  int peek();
  void print();

private:
  int* pList{};
  size_t size{};
  size_t next{};
};

CStack::CStack(int n) : size{ n }
{
  pList = new int[size];
}

CStack::~CStack()
{
  delete[] pList;
}

void CStack::push(int i)
{
  if (next >= size)
  { // Stack full so create a bigger one
    cout << "Enlarging stack." << endl;
    size_t newSize{ size + size / 4 + 1 };        // About 25% larger...
    int* pNewList{ new int[newSize] };
    for (size_t i{}; i < size; ++i)               // Copy the old list
      pNewList[i] = pList[i];
    size = newSize;
    delete[] pList;
    pList = pNewList;
  }
  pList[next++] = i;
}

int CStack::pop()
{
  if (next)
  {
    return pList[--next];
  }
  else
  {
    cout << "Stack empty." << endl;
    return 0;
  }
}

int CStack::peek()
{
  if (next)
  {
    return pList[next - 1];
  }
  else
  {
    cout << "Stack empty." << endl;
    return 0;
  }
}

void CStack::print()
{
  cout << '[';
  size_t index{ next };
  while (index)
    cout << " " << pList[--index];
  cout << " ]\n";
}

int main()
{
  CStack s{ 4 };

  s.print();

  s.push(5);
  s.push(10);
  s.push(8);
  s.print();

  s.push(18);
  s.push(44);
  s.push(3);
  s.print();

  cout << "top of stack popped = " << s.pop() << endl;
  cout << "top of stack peeked = " << s.peek() << endl;

  s.print();
}

