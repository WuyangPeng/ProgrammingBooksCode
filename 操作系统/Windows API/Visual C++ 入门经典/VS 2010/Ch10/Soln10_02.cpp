// Soln10_02.cpp
// The contents of a priority_queue container are automatically in ascending
// sequence if you create the container so that it uses the greater<T> predicate
// to order the contents.
// Remember a priority_queue container is created through a container adapter
// so no iterators are available for it.
#include <iostream>
#include <iterator>
#include <queue>              
#include <vector>              

using std::cout;
using std::endl;
using std::cin;
using std::priority_queue;
using std::queue;
using std::vector;
using std::greater;
using std::istream_iterator;
using std::ostream_iterator;
using std::back_inserter;

int main()
{
  priority_queue<char, vector<char>, greater<char>> characters;
  cout << "Enter characters then Enter followed by Ctrl+Z to end:" << endl;

  istream_iterator<char> charsInput(cin), charsEnd;   // Input stream iterator for character input
  
  while(charsInput != charsEnd)
    characters.push(*charsInput++);

  // Output the contents of the container
  cout << "You entered the following characters:" << endl;
  while(!characters.empty())
  {
    cout << characters.top() << ' ';
    characters.pop();
  }

  cout << endl;

   return 0;
}
