// Ex10_09.cpp
// Exercising a priority queue container
#include <vector>
#include <queue>
#include <functional>
#include "Person.h"

int main()
{
  std::priority_queue<Person, std::vector<Person>, std::greater<>> people;
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

  std::cout << "\nThere are " << people.size() << " people in the queue." << std::endl;

  std::cout << "\nThe names that you entered are:" << std::endl;
  while (!people.empty())
  {
    people.top().showPerson();
    people.pop();
  }
}
