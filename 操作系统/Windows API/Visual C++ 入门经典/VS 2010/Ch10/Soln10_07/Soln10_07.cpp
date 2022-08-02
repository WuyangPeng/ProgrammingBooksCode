// Soln10_07.cpp
// Storing phone numbers in a multimap - in fact two multimaps as in the previous exercise solution.
#include "Person.h"
#include <cliext/map>
using namespace cliext;

typedef  multimap<Person^, String^>^ ByName;         
typedef  multimap<String^, Person^>^ ByNumber;         

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

void addEntry(ByName namebook, ByNumber numberbook)
{
  multimap<Person^, String^>::value_type nameEntry;              // Stores a namebook entry
  multimap<String^, Person^>::value_type numberEntry;            // Stores a numberbook entry
  String^ number;
  Person^ person = getPerson();
  Console::Write(L"Enter the phone number for {0}: ", person);
  number = Console::ReadLine()->Trim();

  // Add an entry to namebook
  nameEntry = namebook->make_value(person, number);
  multimap<Person^,String^>::iterator nameIter = namebook->lower_bound(person);
  if(nameIter == namebook->end())
    namebook->insert(nameEntry);
  else
    namebook->insert(nameIter, nameEntry);

  // Add an entry to numberbook
  numberEntry = numberbook->make_value(number, person);
  multimap<String^, Person^>::iterator numberIter = numberbook->lower_bound(number);
  if(numberIter == numberbook->end())
    numberbook->insert(numberEntry);
  else
    numberbook->insert(numberIter, numberEntry);

  Console::WriteLine(L"Entry successful.");
}

// Retrieves all persons for a given number
void getName(ByNumber numberbook)
{
  Console::Write(L"Enter the phone number: ");
  String^ number = Console::ReadLine()->Trim();

  multimap<String^, Person^>::iterator numberIter = numberbook->lower_bound(number);
  if(numberIter == numberbook->end())
    Console::WriteLine(L"No entry found for {0}.", number);
  else
  {
    Console::WriteLine(L"The following names are listed for {0}:", number);
    for(  ;  numberIter != numberbook->upper_bound(number) ; numberIter++)
      Console::WriteLine(numberIter->second);
  }
}

// Retrieves all the numbers for a given person
void getNumber(ByName namebook)
{
  Person^ person = getPerson();
  multimap<Person^, String^>::iterator nameIter = namebook->lower_bound(person);
  if(nameIter == namebook->end())
    Console::WriteLine(L"No entry found for {0}.", person);
  else
  {
    Console::WriteLine(L"The following numbers are listed for {0}:", person);
    for(  ;  nameIter != namebook->upper_bound(person) ; nameIter++)
      Console::WriteLine(nameIter->second);
  }
}

// List all the entries
void listEntries(ByName namebook)
{
  if(namebook->empty())
  {
    Console::WriteLine(L"The phone book is empty.");
    return;
  }
  multimap<Person^, String^>::iterator iter;
  for(iter = namebook->begin() ; iter != namebook->end() ; iter++)
    Console::WriteLine(L"{0, -30}{1,-12}", iter->first, iter->second); 
}

// Allows the deletion of a number for a given person
void deleteNameEntry(ByName namebook, ByNumber numberbook)
{
  Person^ person = getPerson();
  multimap<Person^, String^>::iterator nameIter = namebook->lower_bound(person);
  multimap<String^, Person^>::iterator numberIter;
  String^ number;
  String^ answer;

  if(nameIter == namebook->end())
    Console::WriteLine(L"No entry found in name book for {0}.", person);
  else
    for(  ;  nameIter != namebook->upper_bound(person) ; nameIter++)
    {
      Console::WriteLine(L"Do you want to erase {0} for {1}? (y or n): ",
                         nameIter->second, person);
      answer = Console::ReadLine()->Trim();
      if(Char::ToUpper(answer[0]) == L'Y')
      {
        // Find the corresponding entry in the numberbook before erasing namebook entry
        number = nameIter->second;
        numberIter = numberbook->lower_bound(number);
        if(numberIter == numberbook->end())
          Console::WriteLine(L"No entry found in number book for {0}.", number);
        else
        {
          for(  ;  numberIter != numberbook->upper_bound(number) ; numberIter++)
            if(numberIter->second == person)
            {
              numberbook->erase(numberIter);
              Console::WriteLine(L"Deleted number entry for {0}.", person);
              break;
            }

          namebook->erase(nameIter);        
          Console::WriteLine(L"{0} erased.", person);
          break;                                 // Exit the loop
        }
      }
      else
        continue;
  }
}

// Allows the deletion of a person for a given number
void deleteNumberEntry(ByName namebook, ByNumber numberbook)
{
  Console::WriteLine(L"Enter the phone number you want to delete: ");
  String^ number = Console::ReadLine()->Trim();

  multimap<String^, Person^>::iterator numberIter = numberbook->lower_bound(number);
  multimap<Person^, String^>::iterator nameIter;
  Person^ person;
  String^ answer;

  if(numberIter == numberbook->end())
    Console::WriteLine(L"No entry found for {0}.", number);
  else
    for(  ;  numberIter != numberbook->upper_bound(number) ; numberIter++)
    {
      person = numberIter->second;
      Console::WriteLine(L"Do you want to erase {0} for {1}? (y or n): ", person, number);
      answer = Console::ReadLine()->Trim();
      if(Char::ToUpper(answer[0]) == L'Y')
      {
        // Find the corresponding entry in the namebook before erasing numberbook entry
        nameIter = namebook->lower_bound(person);
        if(nameIter == namebook->end())
          Console::WriteLine(L"No entry found in namebook for {0}.", person);
        else
          for(  ;  nameIter != namebook->upper_bound(person) ; nameIter++)
            if(String::Compare(number, nameIter->second) == 0)
            {
              namebook->erase(nameIter);
              Console::WriteLine(L"Deleted {0} name entry for {1}.", person, number);
              break;
            }
        numberbook->erase(numberIter);
        Console::WriteLine(L"{0} for {1} erased.", number, person);
        break;                                       // Exit the loop
      }
      else
        continue;
  }
}

int main(array<System::String ^> ^args)
{
  ByName namebook = gcnew multimap<Person^, String^>();          // Stores numbers with Person references as keys
  ByNumber numberbook = gcnew multimap<String^, Person^>();        // Stores Person object references with number keys
  String^ answer;

  while(true)
  {
    Console::Write(L"Do you want to enter a phone book entry(Y or N): ") ;
    answer = Console::ReadLine()->Trim();
    if(Char::ToUpper(answer[0]) == L'N')
      break;
    addEntry(namebook, numberbook);
  }

  // Query the phonebook
  while(true)
  {
    Console::WriteLine(L"\nChoose from the following options:");
    Console::WriteLine(L"A  Add an entry   D Delete an entry for a name   G  Get entries for a name");
    Console::WriteLine(L"L  List entries   d Delete an entry for a number g  Get entries for a number"); 
    Console::WriteLine(L"Q  Quit");
    answer = Console::ReadLine()->Trim();
    
    switch(answer[0])
    {
    case 'A': case 'a':
        addEntry(namebook, numberbook);
        break;
      case 'G':
        getNumber(namebook);
        break;
      case 'g':
        getName(numberbook);
        break;
      case 'D':
        deleteNameEntry(namebook, numberbook);
        break;
      case 'd':
        deleteNumberEntry(namebook, numberbook);
        break;
      case 'L': case 'l':
        listEntries(namebook);
        break;
      case 'Q': case 'q':
        return 0;
      default:
        Console::WriteLine(L"Invalid selection. Try again.");
        break;
    }
  }
  
  return 0;
}
