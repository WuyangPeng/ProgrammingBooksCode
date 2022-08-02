#include <iostream>

using namespace std;

/**
   Tests if an integer is a prime.
   @param n any positive integer
   @return true iff n is a prime
*/
bool isprime(int n)
{  
   if (n == 1) return false;
   if (n == 2) return true;
   if (n % 2 == 0) return false;
   int k = 3;
   while (k * k <= n)
   {  
      if (n % k == 0) return false;
      k = k + 2;
   }
   return true;
}

int main()
{  
   int n;
   cout << "Please enter the upper limit: ";
   cin >> n;
   int i;
   if (n >= 2) cout << "2\n";
   for (i = 3; i <= n; i = i + 2)
   {  
      if (isprime(i))
         cout << i << "\n";
   }
   return 0;
}
