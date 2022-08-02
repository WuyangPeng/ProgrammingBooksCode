/*********************************************************************

  Filename:  swap.cpp
  Section:   13.1   Function Templates
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//generic swap
//templates are used for generic programming

#include <iostream.h>

template <class T>
void swap(T& x, T& y)
{
  T  temp;

  temp = x;
  x = y;
  y = temp;
}

int main()
{
   int i = 5, j = 9;
   enum color { black, green, red} c1 = red, c2 = black;
   char c[10] = "ABCDEFGHI";

   cout << "before int swap " << i << ", " << j << endl;
   swap(i, j);
   cout << "after int swap " << i << ", " << j << endl;
   swap(c1, c2);
   cout << "after color swap " << c1 << ", " << c2 << endl;
   swap(i, static_cast<int>(c[6])); //creates a temporary
   cout << "after int with cast swap " << i << ", " << c[6] << endl;
   //prints 71 G  c[6] remains G
   swap<char>(i, j);//allowed under ANSI explicit use of swap(char&, char&)
   cout << "after char cast " << i << ", " << j << endl;
   swap(i, reinterpret_cast<int&>(c[4]));
   cout << "after int with cast swap " << i << ", " << c[4] << endl;
}
