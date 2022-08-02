// Soln2_6.cpp : main project file.

#include "stdafx.h"

using namespace System;
// Define the enumeration at global scope
enum class Month{January=1,   February, March,    April,
                 May,       June,     July,     August,
                 September, October,  November, December};

int main(array<System::String ^> ^args)
{
  Month month = Month::January;
  Console::WriteLine(L"Month is {0} and the value is {1} ", month, safe_cast<int>(month));
  month = Month::February;
  Console::WriteLine(L"Month is {0} and the value is {1} ", month, safe_cast<int>(month));
  month = Month::March;
  Console::WriteLine(L"Month is {0} and the value is {1} ", month, safe_cast<int>(month));
  month = Month::April;
  Console::WriteLine(L"Month is {0} and the value is {1} ", month, safe_cast<int>(month));
  month = Month::May;
  Console::WriteLine(L"Month is {0} and the value is {1} ", month, safe_cast<int>(month));
  month = Month::June;
  Console::WriteLine(L"Month is {0} and the value is {1} ", month, safe_cast<int>(month));
  month = Month::July;
  Console::WriteLine(L"Month is {0} and the value is {1} ", month, safe_cast<int>(month));
  month = Month::August;
  Console::WriteLine(L"Month is {0} and the value is {1} ", month, safe_cast<int>(month));
  month = Month::September;
  Console::WriteLine(L"Month is {0} and the value is {1} ", month, safe_cast<int>(month));
  month = Month::October;
  Console::WriteLine(L"Month is {0} and the value is {1} ", month, safe_cast<int>(month));
  month = Month::November;
  Console::WriteLine(L"Month is {0} and the value is {1} ", month, safe_cast<int>(month));
  month = Month::December;
  Console::WriteLine(L"Month is {0} and the value is {1} ", month, safe_cast<int>(month));
  return 0;
}
