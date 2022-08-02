// Fig 19.06: MergeSort.cpp
// Class MergeSort member-function definition.
#include <iostream>
#include <vector>
#include <cstdlib> // prototypes for functions srand and rand
#include <ctime> // prototype for function time
#include "MergeSort.h" // class MergeSort definition
using namespace std;

// constructor fill vector with random integers
MergeSort::MergeSort( int vectorSize )
{
   size = ( vectorSize > 0 ? vectorSize : 10 ); // validate vectorSize
   srand( time( 0 ) ); // seed random number generator using current time

   // fill vector with random ints in range 10-99
   for ( int i = 0; i < size; i++ )
      data.push_back( 10 + rand() % 90 );
} // end MergeSort constructor

// split vector, sort subvectors and merge subvectors into sorted vector
void MergeSort::sort()
{
   sortSubVector( 0, size - 1 ); // recursively sort entire vector
} // end function sort

// recursive function to sort subvectors                
void MergeSort::sortSubVector( int low, int high )
{                                                 
   // test base case; size of vector equals 1
   if ( ( high - low ) >= 1 ) // if not base case
   {
      int middle1 = ( low + high ) / 2; // calculate middle of vector
      int middle2 = middle1 + 1; // calculate next element over

      // output split step                                          
      cout << "split:   ";                                          
      displaySubVector( low, high );                                 
      cout << endl << "         ";                                  
      displaySubVector( low, middle1 );                              
      cout << endl << "         ";                                  
      displaySubVector( middle2, high );                             
      cout << endl << endl;                                         

      // split vector in half; sort each half (recursive calls)
      sortSubVector( low, middle1 ); // first half of vector      
      sortSubVector( middle2, high ); // second half of vector    

      // merge two sorted vectors after split calls return
      merge( low, middle1, middle2, high );
   } // end if
} // end function sortSubVector

// merge two sorted subvectors into one sorted subvector
void MergeSort::merge( int left, int middle1, int middle2, int right ) 
{
   int leftIndex = left; // index into left subvector              
   int rightIndex = middle2; // index into right subvector         
   int combinedIndex = left; // index into temporary working vector
   vector< int > combined( size ); // working vector              

   // output two subvectors before merging
   cout << "merge:   ";                  
   displaySubVector( left, middle1 );     
   cout << endl << "         ";          
   displaySubVector( middle2, right );    
   cout << endl;                         
      
   // merge vectors until reaching end of either
   while ( leftIndex <= middle1 && rightIndex <= right )
   {
      // place smaller of two current elements into result
      // and move to next space in vector
      if ( data[ leftIndex ] <= data[ rightIndex ] )
         combined[ combinedIndex++ ] = data[ leftIndex++ ]; 
      else 
         combined[ combinedIndex++ ] = data[ rightIndex++ ];
   } // end while
   
   if ( leftIndex == middle2 ) // if at end of left vector          
   {                                                               
      while ( rightIndex <= right ) // copy in rest of right vector
         combined[ combinedIndex++ ] = data[ rightIndex++ ];       
   } // end if                                                     
   else // at end of right vector                                   
   {                                                               
      while ( leftIndex <= middle1 ) // copy in rest of left vector
         combined[ combinedIndex++ ] = data[ leftIndex++ ];        
   } // end else                                                   

   // copy values back into original vector
   for ( int i = left; i <= right; i++ )   
      data[ i ] = combined[ i ];           

   // output merged vector         
   cout << "         ";            
   displaySubVector( left, right );
   cout << endl << endl;           
} // end function merge

// display elements in vector
void MergeSort::displayElements() const
{
   displaySubVector( 0, size - 1 );
} // end function displayElements

// display certain values in vector
void MergeSort::displaySubVector( int low, int high ) const
{
   // output spaces for alignment
   for ( int i = 0; i < low; i++ )
      cout << "   ";

   // output elements left in vector
   for ( int i = low; i <= high; i++ )
      cout << " " << data[ i ];
} // end function displaySubVector



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
 *************************************************************************/
