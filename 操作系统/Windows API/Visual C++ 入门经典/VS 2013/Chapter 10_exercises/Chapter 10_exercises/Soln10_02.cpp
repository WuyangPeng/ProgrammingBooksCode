// Soln10_02.cpp
// The contents of a priority_queue container are automatically in ascending
// sequence if you create the container so that it uses the greater<T> predicate
// to order the contents.
// Remember a priority_queue container is created through a container adapter
// so no iterators are available for it.
#include <iostream>
#include <iterator>
#include <queue>              
#include <functional>              

using std::priority_queue;
using std::vector;
using std::greater;
using std::istream_iterator;

int main()
{
  priority_queue<char, vector<char>, greater<char>> characters;
  std::cout << "Enter characters then Enter followed by Ctrl+Z to end:\n";

  istream_iterator<char> charsInput{ std::cin }, charsEnd;   // Input stream iterator for character input

  while (charsInput != charsEnd)
    characters.push(*charsInput++);

  std::cout << "You entered the following characters:\n";
  while (!characters.empty())
  {
    std::cout << characters.top() << ' ';
    characters.pop();
  }

  std::cout << std::endl;
}
