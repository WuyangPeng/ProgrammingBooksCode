/**
   @file intname.cpp
   @author Cay Horstmann
*/

#include <iostream>
#include <string>

using namespace std;

/**
   Turn a digit into its English name
   @param n an integer between 1 and 9
   @return the name of n ("one" . . . "nine")
*/
string digit_name(int n)
{  
   if (n == 1) return "one";
   if (n == 2) return "two";
   if (n == 3) return "three";
   if (n == 4) return "four";
   if (n == 5) return "five";
   if (n == 6) return "six";
   if (n == 7) return "seven";
   if (n == 8) return "eight";
   if (n == 9) return "nine";
   return "";
}

/**
   Turn a number between 10 and 19 into its English name
   @param n an integer between 10 and 19
   @return the name of n ("ten" . . . "nineteen")
*/
string teen_name(int n)
{  
   if (n == 10) return "ten";
   if (n == 11) return "eleven";
   if (n == 12) return "twelve";
   if (n == 13) return "thirteen";
   if (n == 14) return "fourteen";
   if (n == 15) return "fifteen";
   if (n == 16) return "sixteen";
   if (n == 17) return "seventeen";
   if (n == 18) return "eighteen";
   if (n == 19) return "nineteen";
   return "";
}

/**
   Give the English name of a multiple of 10
   @param n an integer between 2 and 9
   @return the name of 10 * n ("twenty" . . . "ninety")
*/
string tens_name(int n)
{  
   if (n == 2) return "twenty";
   if (n == 3) return "thirty";
   if (n == 4) return "forty";
   if (n == 5) return "fifty";
   if (n == 6) return "sixty";
   if (n == 7) return "seventy";
   if (n == 8) return "eighty";
   if (n == 9) return "ninety";
   return "";
}

/**
   Turn a number into its English name
   @param n a positive integer < 1,000,000
   @return the name of n (e.g. "two hundred seventy four")
*/
string int_name(int n)
{  int c = n; /* the part that still needs to be converted */
   string r; /* the return value */

   if (c >= 1000)
   {  
      r = int_name(c / 1000) + " thousand";
      c = c % 1000;
   }

   if (c >= 100)
   {  
      r = r + " " + digit_name(c / 100) + " hundred";
      c = c % 100;
   }

   if (c >= 20)
   {  
      r = r + " " + tens_name(c / 10);
      c = c % 10;
   }
   
   if (c >= 10)
   {  
      r = r + " " + teen_name(c);
      c = 0;
   }

   if (c > 0)
      r = r + " " + digit_name(c);

   return r;
}

int main()
{  
   int n;
   cout << "Please enter a positive integer: ";
   cin >> n;
   cout << int_name(n);
   return 0;
}


