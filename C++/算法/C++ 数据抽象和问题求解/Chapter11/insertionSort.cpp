//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// Listing 11-3.

#include <iostream>
#include <string>

using namespace std;
template<class ItemType>

/** Sorts the items in an array into ascending order.
 @pre  None.
 @post  theArray is sorted into ascending order; n is unchanged.
 @param theArray  The given array.
 @param n  The size of theArray. */
void insertionSort(ItemType theArray[], int n)
{
   // unsorted = first index of the unsorted region,
   // loc = index of insertion in the sorted region,
   // nextItem = next item in the unsorted region.
   // Initially, sorted region is theArray[0],
   // unsorted region is theArray[1..n-1].
   // In general, sorted region is theArray[0..unsorted-1],
   // unsorted region theArray[unsorted..n-1]
   for (int unsorted = 1; unsorted < n; unsorted++)
   {
      // At this point, theArray[0..unsorted-1] is sorted.
      // Find the right position (loc) in theArray[0..unsorted]
      // for theArray[unsorted], which is the first entry in the
      // unsorted region; shift, if necessary, to make room
      ItemType nextItem = theArray[unsorted];
      int loc = unsorted;
      while ((loc > 0) && (theArray[loc - 1] > nextItem))
      {
         // Shift theArray[loc - 1] to the right
         theArray[loc] = theArray[loc - 1];
         loc--;
      }  // end while
      
      // At this point, theArray[loc] is where nextItem belongs
      theArray[loc] = nextItem; // Insert nextItem into sorted region
   }  // end for
}  // end insertionSort

int main()
{
   string a[6] = {"Z", "X", "R", "K", "F", "B"};
   insertionSort(a, 6);
   for (int i = 0; i < 6; i++)
      cout << a[i] << " ";
   cout << endl;
}  // end main

/*
 
 B F K R X Z
 
 */
