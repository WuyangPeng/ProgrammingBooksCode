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
   int fold = 1;
   int fold2 = 1;
   int fnew;
   for (int i = 3; i <= n; i++)
   {  
      fnew = fold + fold2;
      fold2 = fold;
      fold = fnew;
   }
   return fnew;
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
