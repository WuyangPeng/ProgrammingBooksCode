/*  1 */ #include <iostream>
/*  2 */ 
/*  3 */ using namespace std;
/*  4 */ 
/*  5 */ /**
    6       Tests if an integer is a prime.
    7       @param n any positive integer
    8       @return true iff n is a prime
    9    */
/* 10 */ bool isprime(int n)
/* 11 */ {  
/* 12 */    if (n == 2) return true;
/* 13 */    if (n % 2 == 0) return false;
/* 14 */    int k = 3;
/* 15 */    while (k * k < n)
/* 16 */    {  
/* 17 */       if (n % k == 0) return false;
/* 18 */       k = k + 2;
/* 19 */    }
/* 20 */    return true;
/* 21 */ }
/* 22 */
/* 23 */ int main()
/* 24 */ {  
/* 25 */    int n;
/* 26 */    cout << "Please enter the upper limit: ";
/* 27 */    cin >> n;
/* 28 */    int i;
/* 29 */    for (i = 1; i <= n; i = i + 2)
/* 30 */    {  
/* 31 */       if (isprime(i))
/* 32 */       cout << i << "\n";
/* 33 */    }
/* 34 */    return 0;
/* 35 */ }
