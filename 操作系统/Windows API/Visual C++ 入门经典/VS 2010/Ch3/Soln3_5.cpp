// Soln3_5.cpp : main project file.

/*
  Note that because this code uses the ReadKey() function,
  newline is recorded as a character. Enter the characters
  without pressing the Enter key if you don't want newline characters
  as part of the character count.
*/

#include "stdafx.h"

using namespace System;

int main(array<System::String ^> ^args)
{
   wchar_t ch;
   int nVowels(0), nChars(0);

   Console::WriteLine(L"Enter characters and enter 'Q' or 'q' to end:");
   for (;;)
   {
      ch = Console::ReadKey().KeyChar;

      if (ch == 'q' || ch == 'Q')
         break;

      switch(Char::ToLower(ch))
      {
      case 'a': case 'e': case 'i': case 'o': case 'u':
         nVowels++;

      default:
         nChars++;
      }
   }

   Console::WriteLine(L"\nTotal chars={0}, vowels={1}", nChars, nVowels);
  return 0;
}
