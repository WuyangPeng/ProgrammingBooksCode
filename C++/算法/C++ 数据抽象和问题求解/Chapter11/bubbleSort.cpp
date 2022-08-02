//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// Listing 11-2.

#include <iostream>
#include <string>

using namespace std;
template<class ItemType>

/** Sorts the items in an array into ascending order.
 @pre  None.
 @post  theArray is sorted into ascending order; n is unchanged.
 @param theArray  The given array.
 @param n  The size of theArray. */
void bubbleSort(ItemType theArray[], int n)
{
   bool sorted = false; // False when swaps occur
   int pass = 1;
   while (!sorted && (pass < n))
   {
      // At this point, theArray[n+1-pass..n-1] is sorted
      // and all of its entries are > the entries in theArray[0..n-pass]
      sorted = true; // Assume sorted
      for (int index = 0; index < n - pass; index++)
      {
         // At this point, all entries in theArray[0..index-1]
         // are <= theArray[index]
         int nextIndex = index + 1;
         if (theArray[index] > theArray[nextIndex])
         {
            // Exchange entries
            std::swap(theArray[index], theArray[nextIndex]);
            sorted = false; // Signal exchange
         } // end if
      }  // end for
      // Assertion: theArray[0..n-pass-1] < theArray[n-pass]
      
      pass++;
   }  // end while
}  // end bubbleSort

int main()
{
   string a[6] = {"Z", "X", "R", "K", "F", "B"};
   bubbleSort(a, 6);
   for (int i = 0; i < 6; i++)
      cout << a[i] << " ";
   cout << endl;   
}  // end main

/*

 B F K R X Z 
 
*/
