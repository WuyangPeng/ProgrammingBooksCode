// Ex10_04.cpp
// A phone book that allows multiple numbers per name and permits retrieving
// the numbers for a name or the name for a number.
// I assumed that there is only one nmae corresponding to each number although it
// is not difficult to allow multiple names per number.
#include <iostream>
#include <cstring>
#include "PhoneBook.h"

using std::cin;
using std::cout;
using std::endl;

int main()
{
  PhoneBook phonebook;
  char answer{};

  while (true)
  {
    std::cout << "Do you want to enter a phone book entry(Y or N): ";
    std::cin >> answer;
    std::cin.ignore();                      // Ignore newline in buffer
    if (toupper(answer) == 'N')
      break;
    if (toupper(answer) != 'Y')
    {
      std::cout << "Invalid response. Try again." << std::endl;
      continue;
    }
    phonebook.addEntry();
  }

  // Query the phonebook
  while (true)
  {
    std::cout << "\nChoose from the following options:\n"
      << "A  Add an entry   D Delete an entry for a name   G  Get entries for a name\n"
      << "L  List entries   d Delete an entry for a number g  Get the entry for a number\n"
      << "Q  Quit" << std::endl;
    std::cin >> answer;
    cin.ignore();                      // Ignore newline in buffer

    switch (answer)
    {
    case 'A': case 'a':
      phonebook.addEntry();
      break;
    case 'G':
      phonebook.getNumber();
      break;
    case 'g':
      phonebook.getName();
      break;
    case 'D':
      phonebook.deleteNameEntry();
      break;
    case 'd':
      phonebook.deleteNumberEntry();
      break;
    case 'L': case 'l':
      phonebook.listEntries();
      break;
    case 'Q': case 'q':
      return 0;
    default:
      std::cout << "Invalid selection. Try again." << std::endl;
      break;
    }
  }
}
