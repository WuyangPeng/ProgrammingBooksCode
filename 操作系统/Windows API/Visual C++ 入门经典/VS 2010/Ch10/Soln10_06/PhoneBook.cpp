// PhoneBook.cpp

#include "PhoneBook.h"

// Helper function to read a person from cin
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

void PhoneBook::addEntry()
{
  pair<Person, string> nameEntry;          // Stores a name book entry
  pair<string, Person> numberEntry;        // Stores a number book entry
  string number;
  Person person = getPerson();

  cout << "Enter the phone number for "
    << person.getName() << ": ";
    getline(cin, number);

    // Add an entry to namebook
    nameEntry = make_pair(person, number);
    multimap<Person,string>::iterator nameIter = namebook.lower_bound(person);
    if(nameIter == namebook.end())                 // Is there a previous entry for person?
      namebook.insert(nameEntry);                  // No, so just insert the pair
    else
      namebook.insert(nameIter, nameEntry);        // Yes, so insert the pair after this point


    // Add an entry to numberbook
    numberEntry = make_pair(number, person);
    multimap<string,Person>::iterator numberIter = numberbook.lower_bound(number);
    if(numberIter == numberbook.end())             // Is there a previous entry for number?
      numberbook.insert(numberEntry);              // No, so just insert the pair
    else
      numberbook.insert(numberIter, numberEntry);  // Yes, so insert the pair after this point

    cout << "Entry successful." << endl;
}

// Retrieves all persons for a given number
void PhoneBook::getName()
{
  string number;
  cout << "Enter the phone number: ";
  getline(cin, number);

  multimap<string, Person>::iterator iter = numberbook.lower_bound(number);
  if(iter == numberbook.end())
    cout << "No entry found for " << number << endl;
  else
  {
    cout << "The following names are listed for " << number << ":" << endl;
    for(  ;  iter != numberbook.upper_bound(number) ; iter++)
      cout << iter->second.getName() << endl;
  }
}

// Retrieves all the numbers for a given person
void PhoneBook::getNumber()
{
  Person person = getPerson();
  multimap<Person, string>::iterator iter = namebook.lower_bound(person);
  if(iter == namebook.end())
    cout << "No entry found for " << person.getName() << endl;
  else
  {
    cout << "The following numbers are listed for " << person.getName() << ":" << endl;
    for(  ;  iter != namebook.upper_bound(person) ; iter++)
      cout << iter->second << endl;
  }
}

// List all the entries
void PhoneBook::listEntries()
{
  if(namebook.empty())
  {
    cout << "The phone book is empty." << endl;
    return;
  }
  multimap<Person, string>::iterator iter;
  cout << setiosflags(ios::left);              // Left justify output
  for(iter = namebook.begin() ; iter != namebook.end() ; iter++)
  {
    cout << setw(30) << iter->first.getName() 
         << setw(12) << iter->second << endl; 
  }
  cout << resetiosflags(ios::right);           // Right justify output
}

// Allows the deletion of a number for a given person
// Note that the erase() function increments the iterator you pass as the 
// argument so it is important to exit the loop after calling erase() to
// avoid the possibility of attempting to increment the iterator when it
// is already pointing to one beyond the end of the container.
void PhoneBook::deleteNameEntry()
{
  Person person = getPerson();
  multimap<Person, string>::iterator nameIter = namebook.lower_bound(person);
  multimap<string, Person>::iterator numberIter;
  string number;
  char answer;

  if(nameIter == namebook.end())
    cout << "No entry found in name book for " << person.getName() << endl;
  else
    for(  ;  nameIter != namebook.upper_bound(person) ; nameIter++)
    {
      cout << "Do you want to erase " << nameIter->second << " for "
           << person.getName() << "? (y or n): ";
      cin >> answer;
      if(tolower(answer) == 'y')
      {
        // Find the corresponding entry in the numberbook before erasing namebook entry
        number = nameIter->second;
        numberIter = numberbook.lower_bound(number);
        if(numberIter == numberbook.end())
          cout << "No entry found in number book for " << number << endl;
        else
        {
          for(  ;  numberIter != numberbook.upper_bound(number) ; numberIter++)
            if(numberIter->second.getName().compare(person.getName()) == 0)
            {
              numberbook.erase(numberIter);
              cout << "Deleted number entry" << endl;
              break;
            }

          namebook.erase(nameIter);        
          cout << person.getName() << " erased." << endl;
          break;                                 // Exit the loop
        }
      }
      else
        continue;
  }
}

// Allows the deletion of a person for a given number
void PhoneBook::deleteNumberEntry()
{
  string number;
  cout << "Enter the phone number you want to delete: ";
  getline(cin, number);

  multimap<string, Person>::iterator numberIter = numberbook.lower_bound(number);
  multimap<Person, string>::iterator nameIter;
  Person person;
  char answer;

  if(numberIter == numberbook.end())
    cout << "No entry found for " << number << endl;
  else
    for(  ;  numberIter != numberbook.upper_bound(number) ; numberIter++)
    {
      person = numberIter->second;
      cout << "Do you want to erase " << person.getName() << " for "
           << number << "? (y or n): ";
      cin >> answer;
      if(tolower(answer) == 'y')
      {
        // Find the corresponding entry in the namebook before erasing numberbook entry
        nameIter = namebook.lower_bound(person);
        if(nameIter == namebook.end())
          cout << "No entry found in namebook for " << person.getName() << endl;
        else
          for(  ;  nameIter != namebook.upper_bound(person) ; nameIter++)
            if(number.compare(nameIter->second) == 0)
            {
              namebook.erase(nameIter);
              cout << "Deleted name entry." << endl;
              break;
            }
        numberbook.erase(numberIter);
        cout << number << " erased." << endl;
        break;                                       // Exit the loop
      }
      else
        continue;
  }
}
