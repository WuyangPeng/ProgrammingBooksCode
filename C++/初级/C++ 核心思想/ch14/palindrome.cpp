#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
   Tests whether a string is a palindrome. A palindrome
   is equal to its reverse, for example "rotor" or "racecar".
   @param s a string
   @return true if s is a palindrome
*/
bool is_palindrome(string s)
{
   // separate case for shortest strings
   if (s.length() <= 1) return true;

   // get first and last character, converted to lowercase   
   char first = s[0];
   char last = s[s.length() - 1];

   if (first == last)
   {
      string shorter = s.substr(1, s.length() - 2);
      return is_palindrome(shorter);
   }
   else
      return false;
}

int main()
{
   cout << "Enter a string: ";
   string input;
   getline(cin, input);
   cout << input << " is ";
   if (!is_palindrome(input)) cout << "not ";
   cout << "a palindrome.\n";
   return 0;
}
