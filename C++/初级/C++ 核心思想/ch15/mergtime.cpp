#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

#include "ccc_time.cpp"

/** 
   Merges two adjacent ranges in a vector
   @param a the vector with the elements to merge
   @param from the start of the first range
   @param mid the end of the first range
   @param to the end of the second range
*/
void merge(vector<int>& a, int from, int mid, int to)
{  
   int n = to - from + 1; /* size of the range to be merged */
   /* merge both halves into a temporary vector b */
   vector<int> b(n);

   int i1 = from;
      /* next element to consider in the first half */
   int i2 = mid + 1;
      /* next element to consider in the second half */
   int j = 0; /* next open position in b */

   /* 
      As long as neither i1 nor i2 is past the end, move the smaller
      element into b
   */
   while (i1 <= mid && i2 <= to)
   {  
      if (a[i1] < a[i2])
      {  
         b[j] = a[i1];
         i1++;
      }
      else
      {  
         b[j] = a[i2];
         i2++;
      }
      j++;
   }

   /* 
      Note that only one of the two while loops below is executed
   */

   /* Copy any remaining entries of the first half */
   while (i1 <= mid)
   {  
      b[j] = a[i1];
      i1++;
      j++;
   }
   /* Copy any remaining entries of the second half */
   while (i2 <= to)
   {  
      b[j] = a[i2];
      i2++;
      j++;
   }

   /* Copy back from the temporary vector */
   for (j = 0; j < n; j++)
      a[from + j] = b[j];
}

/**  
   Sorts the elements in a range of a vector.
   @param a the vector with the elements to sort
   @param from start of the range to sort
   @param to end of the range to sort
*/
void merge_sort(vector<int>& a, int from, int to)
{  
   if (from == to) return;
   int mid = (from + to) / 2;
   /* sort the first and the second half */
   merge_sort(a, from, mid);
   merge_sort(a, mid + 1, to);
   merge(a, from, mid, to);
}

/** 
   Prints all elements in a vector
   @param a the vector to print
*/
void print(vector<int> a)
{  
   for (int i = 0; i < a.size(); i++)
      cout << a[i] << " ";
   cout << "\n";
}

/**
   Sets the seed of the random number generator.
*/
void rand_seed()
{  
   int seed = static_cast<int>(time(0));
   srand(seed);
}

/** 
   Computes a random integer in a range.
   @param a the bottom of the range
   @param b the top of the range
   @return a random integer x, a <= x and x <= b
*/
int rand_int(int a, int b)
{  
   return a + rand() % (b - a + 1);
}

int main()
{  
   rand_seed();
   cout << "Enter vector size: ";
   int n;
   cin >> n;
   vector<int> v(n);
   for (int i = 0; i < v.size(); i++)
      v[i] = rand_int(1, 100);
   Time before;
   merge_sort(v, 0, v.size() - 1);
   Time after;

   cout << "Elapsed time = " << after.seconds_from(before)
      << " seconds\n";
   return 0;
}
