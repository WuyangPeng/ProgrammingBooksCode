#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

/**
   Finds an element in a vector
   @param v the vector with the elements to search
   @param a the value to search for
   @return the index of the first match, or -1 if not found
*/
int linear_search(vector<int> v, int a)
{  
   for (int i = 0; i < v.size(); i++)
   {  
      if (v[i] == a)
         return i;
   }
   return -1;
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
   cout << "Enter number to search for: ";
   int n;
   cin >> n;
   int j = linear_search(v, n);
   cout << "Found in position " << j << "\n";
   return 0;
}
