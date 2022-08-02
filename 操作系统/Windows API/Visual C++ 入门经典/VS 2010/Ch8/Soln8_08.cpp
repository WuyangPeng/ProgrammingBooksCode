// Exercise 8.8 Searching for and replacing substrings of a string with asterisks. 

#include <iostream>
#include <string>
#include <cctype>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::isalpha;

int main() {
  string text;                                 // The string to be searched
  const size_t maxwords(100);                  // Maximum number of words to be changed
  string words[maxwords];                      // Words to be changed
  size_t wordcount(0);                         // Actual number of words to be changed

  cout << "Enter the text that is to be searched terminated by #:" << endl;
  std::getline(cin, text, '#');
  string textcopy(text);                       // Make a copy of the string
 
  // Convert copy to lowercase
  for(size_t i = 0 ; i<textcopy.length() ; i++)
    textcopy[i] = tolower(textcopy[i]);

  while(true)
  {
    cout << "Enter a word that is to be replaced in the string or enter # to end: ";
    cin >> words[wordcount];
    if(words[wordcount] == "#")
      break;
    if(++wordcount == maxwords)
    {
      cout << endl << "Maximum number of words reached." << endl;
      break;
    }
  }

  for(size_t i = 0 ; i<wordcount ; i++)
  {
    string wordcopy = words[i];                   // Make a copy of the word
    // Convert copy to lowercase
    for(size_t j = 0 ; j<wordcopy.length() ; j++)
      wordcopy[j] = tolower(wordcopy[j]);

    // Create string with the same number of asterisks as there are in word
    string asterisks(wordcopy.length(), '*');

    cout << endl << "Each occurrence of \"" << words[i] 
         << "\" will be replaced by " << asterisks << "." << endl;


    // Search for wordcopy within textcopy object
    // but replace by asterisks in text
    size_t position = 0;
    while((position = textcopy.find(wordcopy, position)) != string::npos)
    {
      // We have to check that the characters before and after the word found
      // are not alphabetic, but we need to take care not to use index values
      // that are illegal - hence all the ifs.
      if(position==0)
      { // We are at the beginning of the text
        if(position+wordcopy.length()==text.length())             // Check for 1 past the word being the end of the text
          text.replace(position, wordcopy.length(), asterisks);   // Replace word
        else if (!isalpha(textcopy[position+wordcopy.length()]))  // Check for 1 past the word not being alphabetic
          text.replace(position, wordcopy.length(), asterisks);   // Replace word
      }
      else if(!isalpha(textcopy[position-1])) 
      {
        if(position+wordcopy.length()==text.length())             // Check for 1 past the word being the end of the text
          text.replace(position, wordcopy.length(), asterisks);   // Replace word
        else if (!isalpha(textcopy[position+wordcopy.length()]))  // Check for 1 past the word not being alphabetic
          text.replace(position, wordcopy.length(), asterisks);   // Replace word
      }
      position += wordcopy.length();
    }
 
    cout << endl << "After processing the original string is now:" << endl
         << text << endl;
  }
  cout << endl << "All substitutions have been made." << endl;

  return 0;
}