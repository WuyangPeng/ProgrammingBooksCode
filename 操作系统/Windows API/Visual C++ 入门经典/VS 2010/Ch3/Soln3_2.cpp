// Soln3_2.cpp

/*
  nVowels records the count of vowels and nChars records the total number of
  characters that are entered including vowels.
*/

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
   char c;
   int nVowels(0), nChars(0);       // Initialized with zero using functional notation       

   cout << "Enter characters and enter 'Q' or 'q' to end:"
        << endl;
   for (;;)
   {
      cin >> c;

      if (c == 'q' || c == 'Q')
         break;

      switch(c)
      {
      case 'A': case 'a':
      case 'E': case 'e':
      case 'I': case 'i':
      case 'O': case 'o':
      case 'U': case 'u':
         nVowels++;         // This executes only when c is a vowel.
                            // Because there is no break statement here execution
		                        // continues with the default case.
      default:
         nChars++;          // This is always executed
      }
   }

   cout << "Total chars=" << nChars << ", vowels=" << nVowels;
   cout << endl;
   return 0;
}
