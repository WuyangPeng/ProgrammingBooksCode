// Soln10_05.cpp
// Storing phone numbers in a multimap
#include "stdafx.h"
#include "Person.h"
#include <cliext/map>

using namespace System;
using namespace cliext;

// Read a person from standard input
Person^ getPerson()
{
  String^ first;
  String^ second;
  Console::Write(L"Enter a first name: ") ;
  first = Console::ReadLine();
  Console::Write(L"Enter a second name: ") ;
  second = Console::ReadLine();
  return gcnew Person(first->Trim(), second->Trim());
}

// Add a new entry to a phone book
void addEntry(multimap<Person^, String^>^ book)
{
  multimap<Person^, String^>::value_type entry;              // Stores a phone book entry
  String^ number;
  Person^ person = getPerson();

  Console::Write(L"Enter the phone number for {0}: ", person);
  number = Console::ReadLine()->Trim();

  entry = book->make_value(person, number);
  multimap<Person^,String^>::iterator iter = book->lower_bound(person);
  if(iter == book->end())
    book->insert(entry);
  else
    book->insert(iter, entry);
  Console::WriteLine(L"Entry successful.");
}

// List the contents of a phone book
void listEntries(multimap<Person^, String^>^ book)
{
  if(book->empty())
  {
    Console::WriteLine(L"The phone book is empty.");
    return;
  }
  multimap<Person^, String^>::iterator iter;
  for(iter = book->begin() ; iter != book->end() ; iter++)
    Console::WriteLine(L"{0, -30}{1,-12}", iter->first, iter->second); 
}

// Retrieve an entry from a phone book
void getEntry(multimap<Person^, String^>^ book)
{
  Person^ person = getPerson();
  multimap<Person^, String^>::const_iterator iter = book->lower_bound(person);
  if(iter == book->end())
    Console::WriteLine(L"No entry found for {0}", person);
  else
  {
    Console::WriteLine(L"The numbers for {0} are:", person);
    for(; iter != book->end() ; ++iter)
      if(iter->first == person)
        Console::WriteLine(iter->second);
  }
}

// Delete an entry from a phone book
void deleteEntry(multimap<Person^, String^>^ book)
{
  Person^ person = getPerson();
  multimap<Person^, String^>::iterator iter = book->lower_bound(person);
  String^ answer;
  if(iter == book->end())
    Console::WriteLine(L"No entry found for {0}", person);
  else
    for(; iter != book->upper_bound(person) ; ++iter)
    {
      Console::Write(L"Do you want to erase {0} for {1}?(y or n): ", iter->second, person);
      answer = Console::ReadLine()->Trim();
      if(Char::ToUpper(answer[0]) == L'Y')
      {
        String^ number = iter->second;
        book->erase(iter);
        Console::WriteLine(L"{0} for {1} erased.", number, person);
        break;
      }
    }
}

int main(array<System::String ^> ^args)
{
  multimap<Person^, String^>^ phonebook = gcnew multimap<Person^, String^>();
  String^ answer;

  while(true)
  {
    Console::Write(L"Do you want to enter a phone book entry(Y or N): ") ;
    answer = Console::ReadLine()->Trim();
    if(Char::ToUpper(answer[0]) == L'N')
      break;
    addEntry(phonebook);
  }

  // Query the phonebook
  while(true)
  {
    Console::WriteLine(L"\nChoose from the following options:");
    Console::WriteLine(L"A  Add an entry   D Delete an entry   G  Get an entry");
    Console::WriteLine(L"L  List entries   Q  Quit"); 
    answer = Console::ReadLine()->Trim();
    
    switch(Char::ToUpper(answer[0]))
    {
      case L'A':
        addEntry(phonebook);
        break;
      case L'G':
        getEntry(phonebook);
        break;
      case L'D':
        deleteEntry(phonebook);
        break;
      case L'L':
        listEntries(phonebook);
        break;
      case L'Q':
        return 0;
      default:
        Console::WriteLine(L"Invalid selection. Try again.");
        break;
    }
  }
  return 0;
}
