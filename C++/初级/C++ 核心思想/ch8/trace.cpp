/****************************************************************************
** COPYRIGHT (C):    1996 Cay S. Horstmann. All Rights Reserved.
** PROJECT:          Computing Concepts with C++
** FILE:             trace.cpp
** NOTE TO STUDENTS: This file has been edited to be compatible with older
** compilers. If your compiler fully supports the ANSI/ISO C++
** standard, remove the line #include "ccc_ansi.cpp". You can also remove
** the lines #ifndef CCC_ANSI_H and #endif
****************************************************************************/

   #include "ccc_ansi.cpp"
   #ifndef CCC_ANSI_H

#include <iostream>
#include <string>

using namespace std;

   #endif
 
string digit_name(int n)
/* PURPOSE:  turn a digit into its English name
   RECEIVES: n - an integer between 1 and 9
   RETURNS:  the name of n ("one" . . . "nine")
*/
{  cout << "Entering digit_name. n = " << n << "\n";
   string r;
   if (n == 1) r = "one";
   else if (n == 2) r = "two";
   else if (n == 3) r = "three";
   else if (n == 4) r = "four";
   else if (n == 5) r = "five";
   else if (n == 6) r = "six";
   else if (n == 7) r = "seven";
   else if (n == 8) r = "eight";
   else if (n == 9) r = "nine";
   else r = "";
   cout << "Exiting digit_name. Return value = " << r << "\n";
   return r;
}

string teen_name(int n)
/* PURPOSE:  turn a number between 10 and 19 into its English name
   RECEIVES: n - an integer between 10 and 19
   RETURNS:  the name of n ("ten" . . . "nineteen")
*/
{  cout << "Entering teen_name. n = " << n << "\n";
   string r;
   if (n == 10) r = "ten";
   else if (n == 11) r = "eleven";
   else if (n == 12) r = "twelve";
   else if (n == 13) r = "thirteen";
   else if (n == 14) r = "fourteen";
   else if (n == 15) r = "fifteen";
   else if (n == 16) r = "sixteen";
   else if (n == 17) r = "seventeen";
   else if (n == 18) r = "eighteen";
   else if (n == 19) r = "nineteen";
   else r = "";
   cout << "Exiting teen_name. Return value = " << r << "\n";
   return r;
}

string tens_name(int n)
/* PURPOSE:  give the English name of a multiple of 10
   RECEIVES: n - an integer between 2 and 9
   RETURNS:  the name of 10 * n ("twenty" . . . "ninety")
*/
{  cout << "Entering tens_name. n = " << n << "\n";
   string r;
   if (n == 2) r = "twenty";
   else if (n == 3) r = "thirty";
   else if (n == 4) r = "forty";
   else if (n == 5) r = "fifty";
   else if (n == 6) r = "sixty";
   else if (n == 7) r = "seventy";
   else if (n == 8) r = "eighty";
   else if (n == 9) r = "ninety";
   else r = "";
   cout << "Exiting tens_name. Return value = " << r << "\n";
   return r;
}

string int_name(int n)
/* PURPOSE:  turn a number into its English name
   RECEIVES: n - a positive integer < 1,000,000
   RETURNS:  the name of n (e.g. "two hundred seventy four")
*/
{  cout << "Entering int_name. n = " << n << "\n";
   int c = n; /* the part that still needs to be converted */
   string r; /* the return value */

   if (c >= 1000)
   {  cout << "Inside int_name. Thousands\n";
      r = int_name(c / 1000) + " thousand";
      c = c % 1000;
   }

   if (c >= 100)
   {  cout << "Inside int_name. Hundreds\n";
      r = r + " " + digit_name(c / 100) + " hundred";
      c = c % 100;
   }

   if (c >= 20)
   {  cout << "Inside int_name. Tens\n";
      r = r + " " + tens_name(c / 10);
      c = c % 10;
   }
   else if (c >= 10)
   {  cout << "Inside int_name. Teens\n";
      r = r + " " + teen_name(c);
      c = 0;
   }

   if (c > 0)
   {  cout << "Inside int_name. Ones\n";
      r = r + " " + digit_name(c);
   }

   cout << "Exiting digit_name. Return value = " << r << "\n";
   return r;
}

int main()
{  int n;
   cout << "Please enter a positive integer: ";
   cin >> n;
   cout << int_name(n);
   return 0;
}


