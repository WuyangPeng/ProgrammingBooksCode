// Fig. 22.40: Fig22_40.cpp                                
// Using a bitset to demonstrate the Sieve of Eratosthenes.
#include <iostream>
#include <iomanip>
#include <cmath> // sqrt prototype
#include <bitset> // bitset class definition
using namespace std;

int main()
{
   const int SIZE = 1024;
   int value;
   bitset< SIZE > sieve; // create bitset of 1024 bits
   sieve.flip(); // flip all bits in bitset sieve
   sieve.reset( 0 ); // reset first bit (number 0)         
   sieve.reset( 1 ); // reset second bit (number 1)        

   // perform Sieve of Eratosthenes
   int finalBit = sqrt( static_cast< double >( sieve.size() ) ) + 1;

   // determine all prime numbers from 2 to 1024
   for ( int i = 2; i < finalBit; i++ )
   {
      if ( sieve.test( i ) ) // bit i is on
      {
         for ( int j = 2 * i; j < SIZE; j += i ) 
            sieve.reset( j ); // set bit j off
      } // end if
   } // end for

   cout << "The prime numbers in the range 2 to 1023 are:\n";

   // display prime numbers in range 2-1023
   for ( int k = 2, counter = 1; k < SIZE; k++ )
   {
      if ( sieve.test( k ) ) // bit k is on
      {
         cout << setw( 5 ) << k;

         if ( counter++ % 12 == 0 ) // counter is a multiple of 12
            cout << '\n';
      } // end if          
   } // end for    
   
   cout << endl;

   // get value from user 
   cout << "\nEnter a value from 2 to 1023 (-1 to end): ";
   cin >> value;

   // determine whether user input is prime
   while ( value != -1 ) 
   {
      if ( sieve[ value ] ) // prime number
         cout << value << " is a prime number\n";
      else // not a prime number
         cout << value << " is not a prime number\n";
      
      cout << "\nEnter a value from 2 to 1023 (-1 to end): ";
      cin >> value;
   } // end while
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
