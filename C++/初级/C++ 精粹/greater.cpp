/*********************************************************************

  Filename:  greater.cpp
  Section:   10.2   Call-by-reference
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//  Title: greater

#include <iostream.h>

//greater() using call-by-reference parameters
int greater(int& a, int& b)
{
   if (a > b) {      //exchange
      int temp = a;
      a = b;
      b = temp;
      return 1;
   }
   else
      return 0;
}



/* C greater  */
int greater2(int* a, int* b)
{
   if (*a > *b) {
      int temp = *a;
      *a = *b;
      *b = temp;
      return 1;
   }
   else
      return 0;
}

int main()
{
   int i, j;

   i = 5;
   j = 10;
   cout << "\nBefore Greater  i is " << i << "  and j is " << j << endl;
   greater(i, j);   //C++ style
   cout << "After  Greater  i is " << i << "  and j is " << j << endl;
   i = 6;
   j = 11;
   cout << "Before Greater2 i is " << i << "  and j is " << j << endl;
   greater2(&i, &j);
   cout << "After  Greater2 i is " << i << "  and j is " << j << endl;

   i = 15;
   j = 10;
   cout << "Before Greater  i is " << i << "  and j is " << j << endl;
   greater(i, j);   //C++ style
   cout << "After  Greater  i is " << i << "  and j is " << j << endl;
   i = 16;
   j = 11;
   cout << "Before Greater2 i is " << i << "  and j is " << j << endl;
   greater2(&i, &j);
   cout << "After  Greater2 i is " << i << "  and j is " << j << endl;
}



