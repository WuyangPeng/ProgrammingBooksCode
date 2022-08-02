// PhoneBook.h

#pragma once
#include <string>
#include <map>
#include <cstring>
#include "Person.h"


class PhoneBook
{
public:
  void addEntry();
  void getName();                                // Get a person for a number
  void getNumber();                              // Get a number for a person
  void listEntries();                            // List all entries
  void deleteNameEntry();                        // Delete an entry for a given person
  void deleteNumberEntry();                      // Delete an entry for a given number
private:
  std::multimap<Person, string> namebook;        // Stores numbers with person keys
  std::multimap<string, Person> numberbook;      // Stores Person objects with number keys
};
