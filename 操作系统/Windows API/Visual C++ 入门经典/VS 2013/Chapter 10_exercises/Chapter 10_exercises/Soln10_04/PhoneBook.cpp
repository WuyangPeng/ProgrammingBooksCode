// PhoneBook.cpp

#include "PhoneBook.h"
#include <iostream>
#include <iomanip>
using std::string;
using std::pair;
using std::make_pair;

// Helper function to read a person from cin
Person getPerson()
{
  string first;
  string second;
  std::cout << "Enter a first name: ";
  getline(std::cin, first);
  std::cout << "Enter a second name: ";
  getline(std::cin, second);
  return Person(first, second);
}

void PhoneBook::addEntry()
{
  pair<Person, string> nameEntry;                               // Stores a name book entry
  pair<string, Person> numberEntry;                             // Stores a number book entry
  string number;
  Person person = getPerson();

  std::cout << "Enter the phone number for " << person.getName() << ": ";
  getline(std::cin, number);

  namebook.emplace(make_pair(person, number));                  // Add an entry to namebook
  numberbook.emplace(make_pair(number, person));                // Add an entry to numberbook
}

// Retrieves the person for a given number
void PhoneBook::getName()
{
  string number;
  std::cout << "Enter the phone number: ";
  getline(std::cin, number);



  auto iter = numberbook.lower_bound(number);
  if (numberbook.count(number))
    std::cout << "The  name for " << number << " is "
    << numberbook.find(number)->second.getName() << std::endl;
  else
    std::cout << "No entry found for " << number << std::endl;
}

// Retrieves all the numbers for a given person
void PhoneBook::getNumber()
{
  Person person = getPerson();
  auto iter = namebook.lower_bound(person);
  if (iter == namebook.end())
    std::cout << "No entry found for " << person.getName() << std::endl;
  else
  {
    std::cout << "The following number(s) are listed for " << person.getName() << ":" << std::endl;
    for (; iter != namebook.upper_bound(person); iter++)
      std::cout << iter->second << std::endl;
  }
}

// List all the entries
void PhoneBook::listEntries()
{
  if (namebook.empty())
  {
    std::cout << "The phone book is empty." << std::endl;
    return;
  }
  std::cout << std::setiosflags(std::ios::left);                // Left justify output
  string name;
  string newName;
  for (auto iter = namebook.begin(); iter != namebook.end(); iter++)
  {
    newName = iter->first.getName();
    if (name != newName)
    {
      name = newName;
      std::cout << std::endl;
    }
    std::cout << std::setw(30) << name
      << std::setw(12) << iter->second << std::endl;
  }
  std::cout << std::resetiosflags(std::ios::right);             // Right justify output
}

// Delete an entry from a phone book
void PhoneBook::deleteNameEntry()
{
  Person person{ getPerson() };
  size_t entries{ namebook.count(person) };  // Get number of entries for person
  string number;

  if (entries == 0)
  { // There are no entries.
    std::cout << "No entry found for " << person.getName() << std::endl;
  }
  else if (entries > 1)
  { // Multiple entries - so ask which one to erase.
    std::cout << "The number(s) for " << person.getName() << " are: " << std::endl;
    for (auto iter = namebook.find(person); iter != namebook.upper_bound(person); ++iter)
      std::cout << std::setw(24) << iter->second << std::endl;

    std::cout << "Which one do you want to delete: ";
    getline(std::cin, number);
    for (auto iter = namebook.find(person); iter != namebook.upper_bound(person); ++iter)
    { // Find the number
      if (number == iter->second)
      {
        namebook.erase(iter);                                   // Found it so erase
        numberbook.erase(number);                               // Erase the number from number book
        break;
      }
    }

    std::cout << " The number " << number << " for " << person.getName() << " erased." << std::endl;
  }
  else
  { // Only one entry - so erase it.
    auto nameIter = namebook.find(person);
    number = nameIter->second;
    namebook.erase(nameIter);
    numberbook.erase(number);
    std::cout << " The entry for " << person.getName() << " erased." << std::endl;
  }
}

// Deletes  a person entry for a given number
void PhoneBook::deleteNumberEntry()
{
  string number;
  std::cout << "Enter the phone number you want to delete: ";
  getline(std::cin, number);

  auto numberIter = numberbook.lower_bound(number);
  Person person;

  if (numberIter == numberbook.end())
    std::cout << "No entry found for " << number << std::endl;
  else
  {
    Person person(numberIter->second);
    numberbook.erase(numberIter);
    // Find the number entry in the name book
    if (namebook.count(number) == 1)
    {
      namebook.erase(person);
    }
    else
    {
      for (auto iter = namebook.find(person); iter != namebook.upper_bound(person); ++iter)
      {
        if (number == iter->second)
        {
          namebook.erase(iter);
          std::cout << number << " for " << person.getName() << " deleted.";
          break;
        }
      }
    }
  }
}
