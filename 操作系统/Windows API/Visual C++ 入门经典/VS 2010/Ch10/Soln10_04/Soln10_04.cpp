// Soln10_04.cpp
// Using a multimap container

#include <iostream>
#include <cstdio>
#include <iomanip>
#include <string>
#include <map>
#include <cstring>
#include "Person.h"

using std::cin;
using std::cout;
using std::endl;
using std::setw;
using std::ios;
using std::string;
using std::pair;
using std::multimap;
using std::make_pair;

// Read a person from cin
Person getPerson()
{
  string first;
  string second;
  cout << "Enter a first name: " ;
  getline(cin, first);
  cout << "Enter a second name: " ;
  getline(cin, second);
  return Person(first, second);
}

// Add a new entry to a phone book
void addEntry(multimap<Person, string>& book)
{
  pair<Person, string> entry;          // Stores a phone book entry
  string number;
  Person person = getPerson();

  cout << "Enter the phone number for "
    << person.getName() << ": ";
    getline(cin, number);
    entry = make_pair(person, number);
    multimap<Person,string>::iterator iter = book.lower_bound(person);
    if(iter == book.end())       // Is there a previous entry for person?
      book.insert(entry);        // No, so just intert the pair
    else
      book.insert(iter, entry);  // Yes, so insert the pair after this point

    cout << "Entry successful." << endl;
}

// List the contents of a phone book
void listEntries(multimap<Person, string>& book)
{
  if(book.empty())
  {
    cout << "The phone book is empty." << endl;
    return;
  }
  multimap<Person, string>::iterator iter;
  cout << setiosflags(ios::left);              // Left justify output
  for(iter = book.begin() ; iter != book.end() ; iter++)
  {
    cout << setw(30) << iter->first.getName() 
         << setw(12) << iter->second << endl; 
  }
  cout << resetiosflags(ios::right);           // Right justify output
}

// Retrieve an entry from a phone book
void getEntry(multimap<Person, string>& book)
{
  Person person = getPerson();
  multimap<Person, string>::iterator iter = book.lower_bound(person);
  if(iter == book.end())
    cout << "No entry found for " << person.getName() << endl;
  else
  {
    cout << "The following numbers are listed for " << person.getName() << ":" << endl;
    for(  ;  iter != book.upper_bound(person) ; iter++)
      cout << iter->second << endl;
  }
}

// Delete an entry from a phone book
void deleteEntry(multimap<Person, string>& book)
{
  Person person = getPerson();
  multimap<Person, string>::iterator iter = book.lower_bound(person);
  char answer;
  if(iter == book.end())
    cout << "No entry found for " << person.getName() << endl;
  else
    for(  ;  iter != book.upper_bound(person) ; iter++)
    {
      cout << "Do you want to erase " << iter->second << " for "
           << person.getName() << "? (y or n): ";
      cin >> answer;
      if(tolower(answer) == 'y')
      {
        string number = iter->second;
        book.erase(iter);
        cout << number << " for " << person.getName() << " erased." << endl;
        break;
      }
      else
        continue;
  }
}

int main()
{  
  multimap<Person, string> phonebook;
  char answer = 0;

  while(true)
  {
    cout << "Do you want to enter a phone book entry(Y or N): " ;
    cin >> answer;
    cin.ignore();                      // Ignore newline in buffer
    if(toupper(answer) == 'N')
      break;
    if(toupper(answer) != 'Y')
    {
      cout << "Invalid response. Try again." << endl;
      continue;
    }
    addEntry(phonebook);
  }

  // Query the phonebook
  while(true)
  {
    cout << endl << "Choose from the following options:" << endl
         << "A  Add an entry   D Delete an entry   G  Get an entry" << endl
         << "L  List entries   Q  Quit" << endl; 
    cin >> answer;
    cin.ignore();                      // Ignore newline in buffer
    
    switch(toupper(answer))
    {
      case 'A':
        addEntry(phonebook);
        break;
      case 'G':
        getEntry(phonebook);
        break;
      case 'D':
        deleteEntry(phonebook);
        break;
      case 'L':
        listEntries(phonebook);
        break;
      case 'Q':
        return 0;
      default:
        cout << "Invalid selection. Try again." << endl;
        break;
    }
  }
  return 0;
}
