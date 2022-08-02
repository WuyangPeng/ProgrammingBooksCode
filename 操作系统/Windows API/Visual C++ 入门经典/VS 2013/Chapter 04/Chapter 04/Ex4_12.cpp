// Ex4_12.cpp
// Searching a string
#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

int main()
{
  char str[] { "Smith, where Jones had had \"had had\" had had \"had\"."
    "\n\"Had had\" had had the examiners' approval." };
  const char* word { "had" };
  cout << "The string to be searched is: " << endl << str << endl;

  int count {};                                  // Number of occurrences of word in str
  char* pstr { str };                            // Pointer to search start position
  char* found {};                                // Pointer to occurrence of word in str
  const size_t wordLength { std::strlen(word) };
  while (true)
  {
    found = std::strstr(pstr, word);
    if (!found)
      break;
    ++count;
    pstr = found + wordLength;                   // Set next search start as 1 past the word found
  }
  cout << "\"" << word << "\" was found "
    << count << " times in the string." << endl;
  return 0;
}
