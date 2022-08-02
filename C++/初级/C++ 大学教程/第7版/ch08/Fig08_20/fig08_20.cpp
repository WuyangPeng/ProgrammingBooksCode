// Fig. 8.20: fig08_20.cpp
// Multipurpose sorting program using function pointers.
#include <iostream>
#include <iomanip>
using namespace std;

// prototypes
void selectionSort( int [], const int, bool (*)( int, int ) );
void swap( int * const, int * const );   
bool ascending( int, int ); // implements ascending order
bool descending( int, int ); // implements descending order

int main()
{
   const int arraySize = 10;
   int order; // 1 = ascending, 2 = descending
   int counter; // array index
   int a[ arraySize ] = { 2, 6, 4, 8, 10, 12, 89, 68, 45, 37 };

   cout << "Enter 1 to sort in ascending order,\n" 
      << "Enter 2 to sort in descending order: ";
   cin >> order;
   cout << "\nData items in original order\n";
   
   // output original array
   for ( counter = 0; counter < arraySize; counter++ )
      cout << setw( 4 ) << a[ counter ];

   // sort array in ascending order; pass function ascending 
   // as an argument to specify ascending sorting order
   if ( order == 1 ) 
   {
      selectionSort( a, arraySize, ascending );
      cout << "\nData items in ascending order\n";
   } // end if

   // sort array in descending order; pass function descending
   // as an argument to specify descending sorting order
   else 
   {
      selectionSort( a, arraySize, descending );
      cout << "\nData items in descending order\n";
   } // end else part of if...else

   // output sorted array
   for ( counter = 0; counter < arraySize; counter++ )
      cout << setw( 4 ) << a[ counter ];

   cout << endl;
} // end main

// multipurpose selection sort; the parameter compare is a pointer to
// the comparison function that determines the sorting order
void selectionSort( int work[], const int size,
                    bool (*compare)( int, int ) )
{
   int smallestOrLargest; // index of smallest (or largest) element

   // loop over size - 1 elements
   for ( int i = 0; i < size - 1; i++ )
   {
      smallestOrLargest = i; // first index of remaining vector

      // loop to find index of smallest (or largest) element
      for ( int index = i + 1; index < size; index++ )
         if ( !(*compare)( work[ smallestOrLargest ], work[ index ] ) )
            smallestOrLargest = index;

      swap( &work[ smallestOrLargest ], &work[ i ] );
   } // end if
} // end function selectionSort

// swap values at memory locations to which 
// element1Ptr and element2Ptr point
void swap( int * const element1Ptr, int * const element2Ptr )
{
   int hold = *element1Ptr;
   *element1Ptr = *element2Ptr;
   *element2Ptr = hold;
} // end function swap

// determine whether element a is less than 
// element b for an ascending order sort
bool ascending( int a, int b )
{
   return a < b; // returns true if a is less than b
} // end function ascending

// determine whether element a is greater than 
// element b for a descending order sort
bool descending( int a, int b )
{
   return a > b; // returns true if a is greater than b
} // end function descending

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
