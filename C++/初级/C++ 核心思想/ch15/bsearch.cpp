#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

/**
   Finds an element in a sorted vector.
   @param v the sorted vector with the elements to search
   @param from the start of the range to search
   @param to the end of the range to search
   @param a the value to search for
   @return the index of the first match, or -1 if not found
*/
int binary_search(vector<int> v, int from, int to, int a)
{  
   if (from > to)
      return -1;
   int mid = (from + to) / 2;
   if (v[mid] == a)
      return mid;
   else if (v[mid] < a)
      return binary_search(v, mid + 1, to, a);
   else
      return binary_search(v, from, mid - 1, a);
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
   v[0] = 1;
   for (int i = 1; i < v.size(); i++)
      v[i] = v[i - 1] + rand_int(1, 10);

   print(v);
   cout << "Enter number to search for: ";
   int n;
   cin >> n;
   int j = binary_search(v, 0, v.size() - 1, n);
   cout << "Found in position " << j << "\n";
   return 0;
}
