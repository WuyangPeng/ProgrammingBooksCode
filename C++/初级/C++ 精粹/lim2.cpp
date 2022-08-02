/*********************************************************************

  Filename:  lim2.cpp
  Section:   6      Types
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//Display limits on constants
//Author: Ira Pohl. version 2.
//Organization: Cottage Consultants, Aptos, CA
//Section 3 constants
//New style uses template classes and static members to
//return information on a given data type,  eg.
//   numeric_limits<TYPE>::max() ---gives max value

#include<iostream>
#include <limits>    //integer constants
using namespace std;

int main()
{
     cout << "\nDisplay constants: ";

     cout << "shorts " << numeric_limits<short>::max() << " <  "
        << numeric_limits<short>::min()  << endl;
     cout << "wchar_t " <<  numeric_limits<wchar_t>::max() << " <  "
        << numeric_limits<wchar_t>::min()  << endl;
     cout << "doubles max exponent base 10  "
        << numeric_limits<double>::max_exponent10 << endl;
     cout << "doubles epsilon =  "
        << numeric_limits<double>::epsilon() << " round error = "
        << numeric_limits<double>::round_error()<< endl;
}
