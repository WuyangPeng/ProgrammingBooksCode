// Fig. 7.16: GradeBook.cpp
// Member-function definitions for class GradeBook that
// uses an array to store test grades.
#include <iostream>
#include <iomanip>
#include "GradeBook.h" // GradeBook class definition
using namespace std;

// constructor initializes courseName and grades array
GradeBook::GradeBook( string name, const int gradesArray[] )
{
   setCourseName( name ); // initialize courseName

   // copy grades from gradeArray to grades data member
   for ( int grade = 0; grade < students; grade++ )
      grades[ grade ] = gradesArray[ grade ];
} // end GradeBook constructor

// function to set the course name
void GradeBook::setCourseName( string name )
{
   courseName = name; // store the course name
} // end function setCourseName

// function to retrieve the course name
string GradeBook::getCourseName()
{
   return courseName;
} // end function getCourseName

// display a welcome message to the GradeBook user
void GradeBook::displayMessage()
{
   // this statement calls getCourseName to get the 
   // name of the course this GradeBook represents
   cout << "Welcome to the grade book for\n" << getCourseName() << "!" 
      << endl;
} // end function displayMessage

// perform various operations on the data
void GradeBook::processGrades()
{
   // output grades array
   outputGrades();

   // call function getAverage to calculate the average grade
   cout << "\nClass average is " << setprecision( 2 ) << fixed <<
      getAverage() << endl;

   // call functions getMinimum and getMaximum
   cout << "Lowest grade is " << getMinimum() << "\nHighest grade is "
      << getMaximum() << endl;

   // call function outputBarChart to print grade distribution chart
   outputBarChart();
} // end function processGrades

// find minimum grade
int GradeBook::getMinimum()
{
   int lowGrade = 100; // assume lowest grade is 100

   // loop through grades array
   for ( int grade = 0; grade < students; grade++ )
   {
      // if current grade lower than lowGrade, assign it to lowGrade
      if ( grades[ grade ] < lowGrade )
         lowGrade = grades[ grade ]; // new lowest grade
   } // end for

   return lowGrade; // return lowest grade
} // end function getMinimum

// find maximum grade
int GradeBook::getMaximum()
{
   int highGrade = 0; // assume highest grade is 0

   // loop through grades array
   for ( int grade = 0; grade < students; grade++ )
   {
      // if current grade higher than highGrade, assign it to highGrade
      if ( grades[ grade ] > highGrade )
         highGrade = grades[ grade ]; // new highest grade
   } // end for

   return highGrade; // return highest grade
} // end function getMaximum     

// determine average grade for test
double GradeBook::getAverage()
{
   int total = 0; // initialize total

   // sum grades in array
   for ( int grade = 0; grade < students; grade++ )
      total += grades[ grade ];

   // return average of grades
   return static_cast< double >( total ) / students;
} // end function getAverage

// output bar chart displaying grade distribution
void GradeBook::outputBarChart()
{
   cout << "\nGrade distribution:" << endl;

   // stores frequency of grades in each range of 10 grades
   const int frequencySize = 11;
   int frequency[ frequencySize ] = {}; // initialize elements to 0

   // for each grade, increment the appropriate frequency
   for ( int grade = 0; grade < students; grade++ )
      frequency[ grades[ grade ] / students ]++;

   // for each grade frequency, print bar in chart
   for ( int count = 0; count < frequencySize; count++ ) 
   {
      // output bar labels ("0-9:", ..., "90-99:", "100:" )
      if ( count == 0 )
         cout << "  0-9: ";
      else if ( count == 10 )
         cout << "  100: ";
      else
         cout << count * 10 << "-" << ( count * 10 ) + 9 << ": ";
      
      // print bar of asterisks
      for ( int stars = 0; stars < frequency[ count ]; stars++ ) 
         cout << '*';

      cout << endl; // start a new line of output
   } // end outer for
} // end function outputBarChart

// output the contents of the grades array
void GradeBook::outputGrades()
{
   cout << "\nThe grades are:\n\n";

   // output each student's grade
   for ( int student = 0; student < students; student++ )
      cout << "Student " << setw( 2 ) << student + 1 << ": " << setw( 3 )
         << grades[ student ] << endl;
} // end function outputGrades


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
