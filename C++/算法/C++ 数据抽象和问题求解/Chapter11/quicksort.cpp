//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// Listing 11-5.

template<class ItemType>

/** Sorts an array into ascending order. Uses the quick sort with
 median-of-three pivot selection for arrays of at least MIN_SIZE
 entries, and uses the insertion sort for other arrays.
 @pre  theArray[first..last] is an array.
 @post  theArray[first..last] is sorted.
 @param theArray  The given array.
 @param first  The first element to consider in theArray.
 @param last  The last element to consider in theArray. */
void quickSort(ItemType theArray[], int first, int last)
{
   if (last - first + 1 < MIN_SIZE)
   {
      insertionSort(theArray, first, last);
   }
   else
   {
      // Create the partition: S1 | Pivot | S2
      int pivotIndex = partition(theArray, first, last);
      
      // Sort subarrays S1 and S2
      quickSort(theArray, first, pivotIndex - 1);
      quickSort(theArray, pivotIndex + 1, last);
   }  // end if
}  // end quickSort
