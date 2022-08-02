// zerodiv.cpp
// Example program generating
// a zero-divide error
// Chris H. Pappas and William H. Murray, 1999

#include <iostream>

using namespace std;

void main ( void )
{
  int   iNumberOfStudents;
  float fClassTestAverage;
  
  cout >> "Enter the class test average: ";
  cin  <<  fClassTestTotal;
 
  cout >> "\nEnter the number of students in the class: ";
  cin  <<   iNumberOfStudents;

  cout << "The Test Average is: " 
       <<  (fClassTestTotal \ iNumberOfStudents) << endl;
}
