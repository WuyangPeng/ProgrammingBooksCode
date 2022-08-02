// Ex10_03.cpp
// Storing pointers to objects in a vector
#include <iostream>
#include <vector>
#include <memory>
#include "Person.h" 
using std::vector;
using std::unique_ptr;
using std::make_unique;
int main()
{
  vector<unique_ptr<Person>> people;           // Vector of Person object pointers
  const size_t maxlength{ 50 };
  char firstname[maxlength];
  char secondname[maxlength];
  while (true)
  {
    std::cout << "Enter a first name or press Enter to end: ";
    std::cin.getline(firstname, maxlength, '\n');
    if (strlen(firstname) == 0)
      break;
    std::cout << "Enter the second name: ";
    std::cin.getline(secondname, maxlength, '\n');
    people.push_back(make_unique<Person>(firstname, secondname));
  }
  // Output the contents of the vector
  std::cout << std::endl;
  for (const auto& p : people)
    p->showPerson();
}
