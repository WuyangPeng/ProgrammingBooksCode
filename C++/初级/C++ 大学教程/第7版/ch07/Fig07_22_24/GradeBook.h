// Fig. 7.22: GradeBook.h
// Definition of class GradeBook that uses a 
// two-dimensional array to store test grades.
// Member functions are defined in GradeBook.cpp
#include <string> // program uses C++ Standard Library string class
using namespace std;

// GradeBook class definition
class GradeBook
{
public:
   // constants
   static const int students = 10; // number of students
   static const int tests = 3; // number of tests
 
   // constructor initializes course name and array of grades
   GradeBook( string, const int [][ tests ] );

   void setCourseName( string ); // function to set the course name
   string getCourseName(); // function to retrieve the course name
   void displayMessage(); // display a welcome message
   void processGrades(); // perform various operations on the grade data
   int getMinimum(); // find the minimum grade in the grade book
   int getMaximum(); // find the maximum grade in the grade book
   double getAverage( const int [], const int ); // get student's average
   void outputBarChart(); // output bar chart of grade distribution
   void outputGrades(); // output the contents of the grades array
private:
   string courseName; // course name for this grade book
   int grades[ students ][ tests ]; // two-dimensional array of grades
}; // end class GradeBook  

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
