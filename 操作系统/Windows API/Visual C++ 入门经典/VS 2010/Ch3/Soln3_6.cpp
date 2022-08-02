// Soln3_6.cpp : main project file.
// Analyzing a string using a for each loop

#include "stdafx.h"

using namespace System;


int main(array<System::String ^> ^args)
{
  int vowels(0);
  int consonants(0);
  int nonAlpha(0);
  int totalChars(0);

  String^ string(L"\"Hello!\" he shouted, \"Are we going now?\".");
  for each(wchar_t ch in string)
  {
    ++totalChars;
    if(Char::IsLetter(ch))
    {
      ch = Char::ToLower(ch);      // Convert to lowercase
      switch(ch)
      {
      case 'a': case 'e': case 'i':
      case 'o': case 'u':
        ++vowels;
        break;
      default:
        ++consonants;
        break;
      }
    }
    else
      ++nonAlpha;
  }
  Console::WriteLine(string);
  Console::WriteLine(L"The string contains {0} vowels, {1} consonants,",
                                                              vowels, consonants);
  Console::WriteLine(L"{0} non-alphabetic characters, which is {1} in total.",
                                                              nonAlpha, totalChars);

    return 0;
}
