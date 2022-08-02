// Soln10_03.cpp : main project file.
/*
  The way in which you create an instance of the priority_queue<T> adapter template is slightly
  different from standard STL. The first template argument is the type of element to be stored.
  The optional second template argument is the underlying container to be used. You can specify the
  optional ordering predicate in the way shown below.

  The stream iterators are not available with STL/CLR so you must use a Console class
  function to handle the input. The Console::Read() function returns a character read
  from the input as a code value of type int. When Ctrl+Z is entered this signifies 
  end-of-file on the input stream and the function returns -1.
*/
#include "stdafx.h"
#include "cliext/queue"
#include "cliext/vector"
#include "cliext/iterator"

using namespace System;
using namespace cliext;

int main(array<System::String ^> ^args)
{
  // Define a priority queue to store characters of type wchar_t using 
  // a vector as the underlying container and using the greater<T> predicate
  // to order the characters in ascending sequence.
  priority_queue<wchar_t, vector<wchar_t>> characters = greater<wchar_t>();

  Console::WriteLine(L"Enter characters then Enter followed by Ctrl+Z to end:");
  int ch = 0;
  while((ch=Console::Read()) != -1)
    characters.push(safe_cast<wchar_t>(ch));
 
  // Output the contents of the container
  Console::WriteLine(L"You entered the following characters:");
  while(!characters.empty())
  {
    Console::Write(L"{0} ", characters.top());
    characters.pop();
  }
  Console::WriteLine();
  Console::WriteLine(L"Press Enter to end.");
  Console::ReadLine();

  return 0;
}
