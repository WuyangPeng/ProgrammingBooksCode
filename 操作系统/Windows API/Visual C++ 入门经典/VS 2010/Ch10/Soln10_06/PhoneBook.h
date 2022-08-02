// PhoneBook.h

#pragma once
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
  multimap<Person, string> namebook;             // Stores numbers with person keys
  multimap<string, Person> numberbook;           // Stores Person objects with number keys
};
