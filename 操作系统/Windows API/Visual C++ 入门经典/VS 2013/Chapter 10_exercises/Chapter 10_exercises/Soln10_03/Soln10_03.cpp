// Soln10_03.cpp
// Using a multimap container to support multiple phone numbers per person
#include <iostream>
//#include <cstdio>
#include <iomanip>
#include <limits>
#include <string>
#include <map>
#include "Person.h"

using std::string;
using PhoneBook = std::multimap<Person, string>;
using Entry = std::pair<Person, string>;

// Read a person from cin
Person getPerson()
{
  string first, second;
  std::cout << "Enter a first name: ";
  getline(std::cin, first);
  std::cout << "Enter a second name: ";
  getline(std::cin, second);
  return Person{ std::move(first), std::move(second) };
}

// Read a phone book entry from standard input
Entry inputEntry()
{
  Person person{ getPerson() };

  string number;
  std::cout << "Enter the phone number for " << person.getName() << ": ";
  getline(std::cin, number);
  return std::make_pair(std::move(person), std::move(number));
}

// Add a new entry to a phone book - always possible
void addEntry(PhoneBook& book)
{
  book.emplace(inputEntry());
}

// List the contents of a phone book
void listEntries(const PhoneBook& book)
{
  if (book.empty())
  {
    std::cout << "The phone book is empty." << std::endl;
    return;
  }
  std::cout << setiosflags(std::ios::left);              // Left justify output
  string previousName;
  for (auto& entry : book)
  {
    if (previousName == entry.first.getName())
    {
      std::cout << std::setw(30) << " " << " : "
        << std::setw(12) << entry.second << std::endl;
    }
    else
    {
      previousName = entry.first.getName();
      std::cout << std::endl
        << std::setw(30) << previousName << " : "
        << std::setw(12) << entry.second << std::endl;
    }
  }
  std::cout << resetiosflags(std::ios::right);           // Right justify output
}

// Retrieve an entry from a phone book
void getEntry(const PhoneBook& book)
{
  Person person{ getPerson() };
  auto iter = book.find(person);
  if (iter == book.end())
    std::cout << "No entry found for " << person.getName() << std::endl;
  else
  { // At least one entry
    std::cout << "The number(s) for " << person.getName() << " are:\n";
    for (; iter != book.upper_bound(person); ++iter)
      std::cout << std::setw(24) << iter->second << std::endl;
  }
}

// Delete an entry from a phone book
void deleteEntry(PhoneBook& book)
{
  Person person = getPerson();
  size_t entries{ book.count(person) };  // Get number of entries for person

  if (entries == 0)
  { // There are no entries.
    std::cout << "No entry found for " << person.getName() << std::endl;
  }
  else if (entries > 1)
  { // Multiple entries - so ask which one to erase.
    string number;
    std::cout << "The number(s) for " << person.getName() << " are:\n";
    for (auto iter = book.find(person); iter != book.upper_bound(person); ++iter)
      std::cout << std::setw(24) << iter->second << std::endl;

    std::cout << "Which one do you want to delete: ";
    getline(std::cin, number);
    for (auto iter = book.find(person); iter != book.upper_bound(person); ++iter)
    { // Find the number
      if (number == iter->second)
      {
        book.erase(iter);              // Found it so erase
        break;
      }
    }
    std::cout << " The number " << number << " for " << person.getName() << " erased.\n";
  }
  else
  { // Only one entry - so erase it.
    book.erase(book.find(person));
    std::cout << " The entry for " << person.getName() << " erased.\n";
  }
}

int main()
{
  PhoneBook phonebook;
  char answer{};

  while (true)
  {
    std::cout << "Do you want to enter a phone book entry(Y or N): ";
    std::cin >> answer;
    while (std::cin.get() != '\n');                      // Ignore up to newline
    if (toupper(answer) == 'N')
      break;
    if (toupper(answer) != 'Y')
    {
      std::cout << "Invalid response. Try again." << std::endl;
      continue;
    }
    addEntry(phonebook);
  }

  // Query the phonebook
  while (true)
  {
    std::cout << "\nChoose from the following options:" << std::endl
      << "A  Add an entry   D Delete an entry   G  Get an entry" << std::endl
      << "L  List entries   Q  Quit" << std::endl;
    std::cin >> answer;
    while (std::cin.get() != '\n');                      // Ignore up to newline

    switch (toupper(answer))
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
      std::cout << "Invalid selection. Try again." << std::endl;
      break;
    }
  }
}
