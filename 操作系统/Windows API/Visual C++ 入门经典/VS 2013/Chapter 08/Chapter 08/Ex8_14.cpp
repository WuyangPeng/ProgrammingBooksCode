// Ex8_14.cpp
// Creating and joining string objects
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

// List names and ages
void listnames(string names[], string ages[], size_t count)
{
  cout << "The names you entered are: " << endl;
  for (size_t i{}; i < count && !names[i].empty(); ++i)
    cout << names[i] + " aged " + ages[i] + '.' << endl;
}

int main()
{
  const size_t count{ 100 };
  string names[count];
  string ages[count];
  string firstname;
  string secondname;

  for (size_t i{}; i<count; ++i)
  {
    cout << "Enter a first name or press Enter to end: ";
    std::getline(std::cin, firstname, '\n');
    if (firstname.empty())
    {
      listnames(names, ages, i);
      cout << "Done!!" << endl;
      return 0;
    }

    cout << "Enter a second name: ";
    std::getline(std::cin, secondname, '\n');

    names[i] = firstname + ' ' + secondname;
    cout << "Enter " + firstname + "'s age: ";
    std::getline(std::cin, ages[i], '\n');
  }
  cout << "No space for more names." << endl;
  listnames(names, ages, count);
  return 0;
}
