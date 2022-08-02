// Soln7_07.cpp : main project file.

#include "stdafx.h"

using namespace System;

ref class Record
{
public:
  int getRecord()
  {
    Console::Write(L"Enter a number: ");
    number = Int32::Parse(Console::ReadLine());

     if (number)
     {
        Console::Write(L"And a name: ");
        name = Console::ReadLine();
     }
     return number;
  }

  void putRecord()
  {
    Console::WriteLine(L"The number and name are {0} and \"{1}\"",
                                                    number, name);
  }

private:
   int number;
   String^ name;
};


int main(array<System::String ^> ^args)
{
  while (true)
  {
    Record^ record = gcnew Record;
    if(!record->getRecord())
      break;
    record->putRecord();
  }
   
  return 0;
}
