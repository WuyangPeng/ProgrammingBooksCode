/*********************************************************************

  Filename:  mix_io.cpp
  Section:   16.9   Mixing I/O Libraries
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//The mix_io program with syncronized IO.

//The mix_io program with syncronized IO.
#include  <stdio.h>
#include  <iostream.h>

unsigned long fact(int n)
{
   unsigned long  f = 1;
   for (int i = 2; i <= n; ++i)
      f *= i;
   return f;
}

int main()
{
   int n;

   ios::sync_with_stdio();
   do {
      cout << "\nEnter n positive or 0 to halt: ";
      scanf("%d", &n);
      printf("\n fact(%d) = %ld", n, fact(n));
   } while (n > 0);
   cout << "\nend of session" << endl;
}

