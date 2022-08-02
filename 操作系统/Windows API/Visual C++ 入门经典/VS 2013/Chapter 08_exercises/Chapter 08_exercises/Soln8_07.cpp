// Exercise 8.7 Searching for and replacing substrings of a string with asterisks. 

#include <iostream>
#include <string>
#include <cctype>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::isalpha;

int main() 
{
  string text;                                 // The string to be searched
  const size_t MAX_WORDS{ 100 };               // Maximum number of words to be changed
  string words[MAX_WORDS];                     // Words to be changed
  size_t wordcount{};                          // Actual number of words to be changed

  cout << "Enter the text that is to be searched terminated by #:" << endl;
  std::getline(cin, text, '#');
  string textcopy(text);                       // Make a copy of the string

  // Convert copy to lowercase
  for (auto& ch : textcopy)
    ch = tolower(ch);

  while (true)
  {
    cout << "Enter a word that is to be replaced in the string or enter # to end: ";
    cin >> words[wordcount];
    if (words[wordcount] == "#")
      break;
    if (++wordcount == MAX_WORDS)
    {
      cout << endl << "Maximum number of words reached." << endl;
      break;
    }
  }

  for (size_t i{}; i < wordcount; i++)
  {
    string wordcopy{ words[i] };                   // Make a copy of the word
    // Convert copy to lowercase
    for (auto& ch : wordcopy)
      ch = tolower(ch);

    // Create string with the same number of asterisks as there are in word
    string asterisks(wordcopy.length(), '*');

    cout << endl << "Each occurrence of \"" << words[i]
      << "\" will be replaced by " << asterisks << "." << endl;


    // Search for wordcopy within textcopy object
    // but replace by asterisks in text
    size_t position{};
    while ((position = textcopy.find(wordcopy, position)) != string::npos)
    {
      // We have to check that the characters before and after the word found
      // are not alphabetic, but we need to take care not to use index values
      // that are illegal - hence all the ifs.
      if (position == 0)
      { // We are at the beginning of the text
        if (position + wordcopy.length() == text.length())           // Check for 1 past the word being the end of the text
          text.replace(position, wordcopy.length(), asterisks);      // Replace word
        else if (!isalpha(textcopy[position + wordcopy.length()]))   // Check for 1 past the word not being alphabetic
          text.replace(position, wordcopy.length(), asterisks);      // Replace word
      }
      else if (!isalpha(textcopy[position - 1]))
      {
        if (position + wordcopy.length() == text.length())           // Check for 1 past the word being the end of the text
          text.replace(position, wordcopy.length(), asterisks);      // Replace word
        else if (!isalpha(textcopy[position + wordcopy.length()]))   // Check for 1 past the word not being alphabetic
          text.replace(position, wordcopy.length(), asterisks);      // Replace word
      }
      position += wordcopy.length();
    }

    cout << endl << "After processing the original string is now:" << endl
      << text << endl;
  }
  cout << endl << "All substitutions have been made." << endl;
}