/*********************************************************************

  Filename:  stack_p.cpp
  Chapter:   Quick  Reference Guide
  Section:   8.1    Template Class Stack
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//template stack implementation
//  Title: stack_parameterized

#include <iostream.h>

//template stack implementation
template <class T>
class stack {
public:
   stack() : max_len(1000), top(EMPTY)
      { s = new T[1000]; }
   stack(int size) : max_len(size), top(EMPTY)
      { s = new T[size]; }
   ~stack() { delete []s; }
   void  reset() { top = EMPTY; }
   void  push(T c) { s[++top] = c; }
   T  pop() { return s[top--]; }
   T  top_of() const { return s[top]; }
   bool  empty() const {return bool(top == EMPTY);}
   bool  full() const
      { return bool(top == max_len - 1); }
private:
   enum   { EMPTY = -1 };
   T*  s;
   int    max_len;
   int    top;
};

//Reversing a series of char* represented strings
void reverse(char* str[], int n)
{
   stack<char*>  stk(n);

   for (int i = 0; i < n; ++i)
      stk.push(str[i]);
   for (int i = 0; i < n; ++i)
      str[i] = stk.pop();
}

int main()
{

   stack<char>     stk_ch;           // 1000 char stack
   stack<char*>    str_stack(100);   // 100 char* stack
   char*           str_series[] = {"first string ", "second string ",
                                 "third string ", "last string "};

   cout << "\ntemplate stack popped is ";
   stk_ch.push('A');
   cout << stk_ch.pop();
   str_stack.push("BCD");
   str_stack.push("ANOTHER");
   cout << str_stack.pop();
   cout << endl;
   reverse(str_series, 3); //reverse 1st 3 strings, leave last in place
   cout << str_series[0] << str_series[1]
        << str_series[2] << str_series[3] << endl;
}
