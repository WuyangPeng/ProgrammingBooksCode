// Soln10_01.cpp
// This uses stream iterator for input and output and a back inserter to transfer
// data from the input stream to the list container.
#include <iostream>
#include <iterator>
#include <list>              

using std::list;
using std::istream_iterator;
using std::ostream_iterator;
using std::back_inserter;

int main()
{
  list<char> characters;
  std::cout << "Enter characters then Enter followed by Ctrl+Z to end:\n";

  istream_iterator<char> charsInput{ std::cin }, charsEnd;   // Input stream iterator for character input

  copy(charsInput, charsEnd, back_inserter<list<char>>(characters));

  characters.sort();

  // Output stream iterator for characters with output separated by spaces
  ostream_iterator<char> out{ std::cout, " " };

  // Output the contents of the container
  std::cout << "You entered the following characters:\n";
  copy(begin(characters), end(characters), out);
  std::cout << std::endl;
}
