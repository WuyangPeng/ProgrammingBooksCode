// Ex10_02.cpp
// Storing objects in a vector

#include <iostream>
#include <vector>
#include "Person.h"

using std::vector;

int main()
{
  vector<Person> people;               // Vector of Person objects
  const size_t maxlength{ 50 };
  char firstname[maxlength];
  char secondname[maxlength];

  // Input all the people
  while (true)
  {
    std::cout << "Enter a first name or press Enter to end: ";
    std::cin.getline(firstname, maxlength, '\n');
    if (strlen(firstname) == 0)
      break;
    std::cout << "Enter the second name: ";
    std::cin.getline(secondname, maxlength, '\n');
    people.emplace_back(firstname, secondname);
  }
  // Output the contents of the vector using an iterator
  std::cout << std::endl;
  auto iter = cbegin(people);
  while (iter != cend(people))
  {
    iter->showPerson();
    ++iter;
  }

  //  Simpler alternative to output code above
  //for (auto& p : people)
  //  p.showPerson();
}
