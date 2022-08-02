#include <iostream>

using namespace std;

/**
   Computes a Fibonacci number.
   @param n an integer
   @return the nth Fibonacci number
*/
int fib(int n)
{  
   if (n <= 2) return 1;
   else return fib(n - 1) + fib(n - 2);
}

int main()
{  
   cout << "Enter n: ";
   int n;
   cin >> n;
   int f = fib(n);
   cout << "fib(" << n << ") = " << f << "\n";
   return 0;
}
