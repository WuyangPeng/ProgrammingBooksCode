// Ex10_12.cpp
// Using a map container
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <limits>
#include <string>
#include <map>
#include "Person.h"

using std::string;
using PhoneBook = std::map<Person, string>;
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

// Add a new entry to a phone book
void addEntry(PhoneBook& book)
{
  auto pr = book.insert(inputEntry());

  if (pr.second)
    std::cout << "Entry successful." << std::endl;
  else
  {
    std::cout << "Entry exists for " << pr.first->first.getName()
      << ". The number is " << pr.first->second << std::endl;
  }
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
  for (const auto& entry : book)
  {
    std::cout << std::setw(30) << entry.first.getName()
      << std::setw(12) << entry.second << std::endl;
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
    std::cout << "The number for " << person.getName()
    << " is " << iter->second << std::endl;
}

// Delete an entry from a phone book
void deleteEntry(PhoneBook& book)
{
  Person person{ getPerson() };
  auto iter = book.find(person);
  if (iter == book.end())
    std::cout << "No entry found for " << person.getName() << std::endl;
  else
  {
    book.erase(iter);
    std::cout << person.getName() << " erased." << std::endl;
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
  return 0;
}
