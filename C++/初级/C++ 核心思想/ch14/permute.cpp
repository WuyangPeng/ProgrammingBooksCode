#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
   Computes n!
   @param n a nonnegative integer
   @return n! = 1 * 2 * 3 * . . . * n
*/
int factorial(int n)
{
   if (n == 0) return 1;
   int smaller_factorial = factorial(n - 1);
   int result = smaller_factorial * n;
   return result;
}

/**
   Generates all permutations of the characters in a string
   @param word a string
   @return a vector that is filled with all permutations 
   of the word
*/
vector<string> generate_permutations(string word)
{
   vector<string> result;
   if (word.length() == 1) 
   {
      result.push_back(word);
      return result;
   }

   for (int i = 0; i < word.length(); i++)
   {
      string shorter_word = word.substr(0, i)
         + word.substr(i + 1, word.length() - i - 1);
      vector<string> shorter_permutations
         = generate_permutations(shorter_word);
      for (int j = 0; j < shorter_permutations.size(); j++)
      {
         string longer_word = word[i] + shorter_permutations[j];
         result.push_back(longer_word);
      }   
   }
   return result;
}

int main()
{
   cout << "Enter a string: ";
   string input;
   getline(cin, input);   
   cout << "There are " << factorial(input.length()) 
      << "permutations.\n";
   vector<string> v = generate_permutations(input);
   for (int i = 0; i < v.size(); i++)
      cout << v[i] << "\n";
   return 0;
}
