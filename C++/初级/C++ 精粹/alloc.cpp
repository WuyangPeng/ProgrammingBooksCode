/*********************************************************************

  Filename:  alloc.cpp
  Section:   8.10   new and delete Expressions
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//alloc.cpp  Section 8 - show elementary use of new
#include <iostream>
#include <assert>

int main()
{
   int*  data;
   int   size;
   bool  run_flag = true;

   while (run_flag) {
      cout << "\nEnter array size: ";
      cin >> size;

      data = new int[size];  //return int* expression
      assert (data != 0);    //assure memory obtained
      for (int i = 0; i < size; ++i)      //main computation
         cout << (data[i] = i) << '\t';
      cout << endl;
      delete []data;         //deallocate memory
      cout << "keep running  NO = 0, YES = 1:" << endl;
      cin >> run_flag;
   }
}
