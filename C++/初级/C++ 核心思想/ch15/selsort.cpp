#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

/**
   Swaps two integers.
   @param x the first integer to swap
   @param y the second integer to swap
*/
void swap(int& x, int& y)
{  
   int temp = x;
   x = y;
   y = temp;
}

/** 
    Gets the position of the smallest element in a vector range.
    @param a the vector
    @param from the beginning of the range
    @param to the end of the range
    @return the position of the smallest element in 
    the range a[from]...a[to]
*/
int min_position(vector<int>& a, int from, int to)
{  
   int min_pos = from;
   int i;
   for (i = from + 1; i <= to; i++)
      if (a[i] < a[min_pos]) min_pos = i;
   return min_pos;
}

/** 
   Sorts a vector using the selection sort algorithm
   @param a the vector to sort
*/
void selection_sort(vector<int>& a)
{  
   int next; /* the next position to be set to the minimum */

   for (next = 0; next < a.size() - 1; next++)
   {  
      /* find the position of the minimum */
      int min_pos = min_position(a, next, a.size() - 1);
      if (min_pos != next)
         swap(a[min_pos], a[next]);
   }
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
   vector<int> v(20);
   for (int i = 0; i < v.size(); i++)
      v[i] = rand_int(1, 100);
   print(v);
   selection_sort(v);
   print(v);
   return 0;
}
