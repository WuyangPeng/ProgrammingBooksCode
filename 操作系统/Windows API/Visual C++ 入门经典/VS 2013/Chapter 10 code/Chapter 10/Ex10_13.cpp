// Ex10_13.cpp
// A simple word collocation
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <iterator>

int main()
{
  std::map<std::string, int> words;                            // Map to store words and word counts
  std::cout << "Enter some text, press Enter followed by Ctrl+Z then Enter to end:\n"
    << std::endl;

  std::istream_iterator<std::string> stream_begin{ std::cin }; // Stream iterator
  std::istream_iterator<std::string> stream_end;               // End stream iterator

  while (stream_begin != stream_end)                           // Iterate over words in the stream
    words[*stream_begin++]++;                                  // Increment and store a word count

  // Output the words and their counts
  std::cout << "Here are the word counts for the text you entered:" << std::endl;
  const int wordsPerLine{ 4 };
  int wordCount{};
  std::cout << std::setiosflags(std::ios::left);               // Ouput left-justified
  for (const auto& word : words)
  {
    std::cout << std::setw(15) << word.first << " " << std::setw(5) << word.second;
    if (++wordCount % wordsPerLine == 0) std::cout << std::endl;
  }
  std::cout << std::endl;
}
