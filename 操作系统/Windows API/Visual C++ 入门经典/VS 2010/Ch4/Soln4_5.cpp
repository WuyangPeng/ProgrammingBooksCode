// Soln4_5.cpp : main project file.

#include "stdafx.h"
 
using namespace System;

int main(array<System::String ^> ^args)
{
  Random^ generator = gcnew Random;
  int number = generator->Next(1000, Int32::MaxValue);
  Console::WriteLine(L"The value is {0}", number);

  array<String^>^ digitWord = {L" zero", L" one", L" two", L" three", L" four",
                           L" five", L" six", L" seven", L" eight", L" nine"};
  String^ inWords = L"";

  while(number > 0)
  {
    // Use the rightmost digit in number to index the digitWord array
    // and prefix the select word to inWords.
    inWords = digitWord[number % 10] + inWords;
    number /= 10;                 // Remove the rightmost decimal digit
  }
  Console::WriteLine(inWords);
  return 0;
}
