// Soln4_6.cpp : main project file.

#include "stdafx.h"

using namespace System;
// This tests strings for being palindromes by extracting just the letters 
// from each string and assembling them into a new string as lowercase.
// Successive letters from either end of the new string are compared
// and if any pair does not match, the string is not a palindrome.

int main(array<System::String ^> ^args)
{
  array<String^>^ phrases = {L" Madam I'm Adam",
                             L" Don't cry for me, Marge and Tina",
                             L" Lid off a daffodil",
                             L" Red lost soldier",
                             L" Cigar? Toss it in a can. It is so tragic"};
  String^ letters;           // Stores handle to letters-only phrase
  bool isPalindrome;         // Indicates palindrome or not
  for each(String^ phrase in phrases)
  {
    // Extract letters and make lowercase
    letters = L"";
    for each(wchar_t ch in phrase)
      if(Char::IsLetter(ch))
        letters += Char::ToLower(ch);
 
   // Test for palindrome - compare characts from each end
   isPalindrome = true;
   for(int i = 0 ; i<letters->Length/2 ; i++)
      if(letters[i] != letters[letters->Length-i-1])
      {
        isPalindrome = false;
        break;
      }
    Console::WriteLine(L"\"" + phrase + L"\" " 
                 + (isPalindrome ? "is" : "is not") + L" a palindrome.");
  }

  return 0;
}
