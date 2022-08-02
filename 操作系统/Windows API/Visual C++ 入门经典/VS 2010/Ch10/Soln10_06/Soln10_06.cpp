// Soln10_06.cpp
// Using a multimap container and allow one or more numbers to be retrieved for a name
// or one or more names to be retrieved for a number.
// We need two multimap for this, one with names as keys and the other with numbers as keys.

#include <iostream>
#include <cstring>
#include "PhoneBook.h"

using std::cin;
using std::cout;
using std::endl;

int main()
{  
  PhoneBook phonebook;
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
    phonebook.addEntry();
  }

  // Query the phonebook
  while(true)
  {
    cout << endl << "Choose from the following options:" << endl
         << "A  Add an entry   D Delete an entry for a name   G  Get entries for a name" << endl
         << "L  List entries   d Delete an entry for a number g  Get entries for a number" << endl
         << "Q  Quit" << endl; 
    cin >> answer;
    cin.ignore();                      // Ignore newline in buffer
    
    switch(answer)
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
        cout << "Invalid selection. Try again." << endl;
        break;
    }
  }
  return 0;
}
