// Fig. 7.17: fig07_17.cpp
// Creates GradeBook object using an array of grades.
#include "GradeBook.h" // GradeBook class definition

// function main begins program execution
int main()
{
   // array of student grades
   int gradesArray[ GradeBook::students ] = 
      { 87, 68, 94, 100, 83, 78, 85, 91, 76, 87 }; 
   
   GradeBook myGradeBook( 
      "CS101 Introduction to C++ Programming", gradesArray );
   myGradeBook.displayMessage();
   myGradeBook.processGrades(); 
} // end main


/**************************************************************************
 * (C) Copyright 1992-2010 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 **************************************************************************/
