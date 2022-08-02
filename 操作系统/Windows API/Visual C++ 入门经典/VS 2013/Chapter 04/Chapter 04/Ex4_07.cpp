// Ex4_07.cpp
// Initializing pointers with strings
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
  const char* pstr1 { "Robert Redford" };
  const char* pstr2 { "Hopalong Cassidy" };
  const char* pstr3 { "Lassie" };
  const char* pstr4 { "Slim Pickens" };
  const char* pstr5 { "Boris Karloff" };
  const char* pstr6 { "Oliver Hardy" };
  const char* pstr { "Your lucky star is " };

   int dice {};

   cout << endl
        << "Pick a lucky star!"
        << "Enter a number between 1 and 6: ";
   cin >> dice;

   cout << endl;
   switch(dice)
   {
      case 1: cout << pstr << pstr1;
              break;
      case 2: cout << pstr << pstr2;
              break;
      case 3: cout << pstr << pstr3;
              break;
      case 4: cout << pstr << pstr4;
              break;
      case 5: cout << pstr << pstr5;
              break;
      case 6: cout << pstr << pstr6;
              break;
      
      default: cout << "Sorry, you haven't got a lucky star.";
   }
   
   cout << endl;
   return 0;
}
