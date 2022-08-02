// Ex4_08.cpp
// Initializing pointers with strings
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
   const char* pstr[] { "Robert Redford",                   // Initializing a pointer array
                        "Hopalong Cassidy",
                        "Lassie",
                        "Slim Pickens",
                        "Boris Karloff",
                        "Oliver Hardy"
                      };
   const char* pstart { "Your lucky star is " };

   int dice {};

   cout << endl
        << "Pick a lucky star!"
        << "Enter a number between 1 and " << _countof(pstr) << ": ";
   cin >> dice;

   cout << endl;
   if (dice >= 1 && dice <= _countof(pstr))           // Check input validity
      cout << pstart << pstr[dice - 1];               // Output star name
   else
      cout << "Sorry, you haven't got a lucky star."; // Invalid input

   cout << endl;
   return 0;
}
