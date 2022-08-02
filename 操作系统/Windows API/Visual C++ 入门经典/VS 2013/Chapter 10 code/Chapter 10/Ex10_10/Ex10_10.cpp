// Ex10_10.cpp
// Exercising a stack container
#include <iostream>
#include <stack>
#include <list>
#include "Person.h"

int main()
{
  std::stack<Person, std::list<Person>> people;

  std::string first, second;
  while (true)
  {
    std::cout << "Enter a first name or press Enter to end: ";
    std::getline(std::cin, first);
    if (first.empty())
      break;

    std::cout << "Enter a second name: ";
    std::getline(std::cin, second);
    people.push(Person{ first, second });
  }

  std::cout << "\nThere are " << people.size() << " people in the stack." << std::endl;
  std::cout << "\nThe names that you entered are:" << std::endl;
  while (!people.empty())
  {
    people.top().showPerson();
    people.pop();
  }
}
