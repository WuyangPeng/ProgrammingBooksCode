// Ex10_08.cpp
// Exercising a queue container

#include <iostream>
#include <queue>
#include <string>

int main()
{
  std::queue<std::string> sayings;
  std::string saying;
  std::cout << "Enter one or more sayings. Press Enter to end." << std::endl;
  while (true)
  {
    std::getline(std::cin, saying);
    if (saying.empty())
      break;
    sayings.push(saying);
  }

  std::cout << "There are " << sayings.size() << " sayings in the queue.\n" << std::endl;
  std::cout << "The sayings that you entered are:" << std::endl;
  while (!sayings.empty())
  {
    std::cout << sayings.front() << std::endl;
    sayings.pop();
  }
}
