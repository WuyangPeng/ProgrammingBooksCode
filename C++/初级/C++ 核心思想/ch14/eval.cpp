#include <iostream>
#include <cctype>

using namespace std;

int term_value();
int factor_value();

/**
   Evaluates the next expression found in cin
   @return the value of the expression.
*/
int expression_value()
{
   int result = term_value();
   bool more = true;
   while (more)
   {
      char op = cin.peek();
      if (op == '+' || op == '-')
      {
         cin.get();
         int value = term_value();
         if (op == '+') result = result + value;
         else result = result - value;
      }
      else more = false;
   }
   return result;
}

/**
   Evaluates the next term found in cin
   @return the value of the term.
*/
int term_value()
{
   int result = factor_value();
   bool more = true;
   while (more)
   {
      char op = cin.peek();
      if (op == '*' || op == '/')
      {
         cin.get();
         int value = factor_value();
         if (op == '*') result = result * value;
         else result = result / value;
      }
      else more = false;
   }
   return result;
}

/**
   Evaluates the next factor found in cin
   @return the value of the factor.
*/
int factor_value()
{
   int result = 0;
   char c = cin.peek();
   if (c == '(')
   {
      cin.get();
      result = expression_value();
      cin.get(); // read ")"
   }
   else // assemble number value from digits
   {
      while (isdigit(c))
      {
         result = 10 * result + c - '0';
         cin.get();
         c = cin.peek();
      } 
   }
   return result;
}

int main()
{
   cout << "Enter an expression: ";
   cout << expression_value() << "\n";
   return 0;
}
