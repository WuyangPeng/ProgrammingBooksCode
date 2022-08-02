// Ex10_06.cpp
// Working with a list
#include <iostream>
#include <list>
#include <string>
#include <functional>

using std::string;

void listAll(const std::list<string>& strings)
{
  for (auto& s : strings)
    std::cout << s << std::endl;
}

int main()
{
  std::list<string> text;

  // Read the data
  std::cout << "Enter a few lines of text. Just press Enter to end:" << std::endl;
  string sentence;
  while (getline(std::cin, sentence, '\n'), !sentence.empty())
    text.push_front(sentence);

  std::cout << "Your text in reverse order:" << std::endl;
  listAll(text);
  
  text.sort();                            // Sort the data in ascending sequence
  std::cout << "\nYour text in ascending sequence:" << std::endl;
  listAll(text);

  text.sort(std::greater<>());            // Sort the data in descending sequence
  std::cout << "\nYour text in descending sequence:" << std::endl;
  listAll(text);
}
