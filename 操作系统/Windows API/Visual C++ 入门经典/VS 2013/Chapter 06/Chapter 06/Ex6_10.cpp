// EX6_10.cpp
// A program to implement a calculator

#include <iostream>                              // For stream input/output
#include <cstdlib>                               // For the exit() function
#include <cctype>                                // For the isdigit() function
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

void eatspaces(char* str);                       // Function to eliminate blanks
double expr(char* str);                          // Function evaluating an expression
double term(const char* str, size_t& index);     // Function analyzing a term
double number(const char* str, size_t& index);   // Function to recognize a number

const size_t MAX{ 80 };                          // Maximum expression length, including '\0'
int main()
{
  char buffer[MAX] {};                           // Input area for expression to be evaluated

  cout << endl
    << "Welcome to your friendly calculator."
    << endl
    << "Enter an expression, or an empty line to quit."
    << endl;

  for (;;)
  {
    cin.getline(buffer, sizeof buffer);          // Read an input line
    eatspaces(buffer);                           // Remove blanks from input

    if (!buffer[0])                              // Empty line ends calculator
      return 0;
    try
    {
      cout << "\t= " << expr(buffer)             // Output value of expression
        << endl << endl;
    }
    catch (const char* pEx)
    {
      cerr << pEx << endl;
      cerr << "Ending program." << endl;
      return 1;
    }
  }
}


// Function to eliminate spaces from a string
void eatspaces(char* str)
{
  size_t i{};                                    // 'Copy to' index to string
  size_t j{};                                    // 'Copy from' index to string

  while ((*(str + i) = *(str + j++)) != '\0')    // Loop while character
    // copied is not \0
  if (*(str + i) != ' ')                         // Increment i as long as
    i++;                                         // character is not a space

  return;
}

// Function to evaluate an arithmetic expression
double expr(char* str)
{
  double value{};                                // Store result here
  size_t index{};                                   // Keeps track of current character position

  value = term(str, index);                      // Get first term

  for (;;)                                       // Indefinite loop, all exits inside
  {
    switch (*(str + index++))                    // Choose action based on current character
    {
    case '\0':                                   // We're at the end of the string
      return value;                              // so return what we have got

    case '+':                                    // + found so add in the
      value += term(str, index);                 // next term
      break;

    case '-':                                    // - found so subtract
      value -= term(str, index);                 // the next term
      break;

    default:                                     // If we reach here the string is junk
      char message[38] {"Expression evaluation error. Found: "};
      strncat_s(message, str + index - 1, 1);    // Append the character
      throw message;
      break;
    }
  }
}

// Function to get the value of a term
double term(const char* str, size_t& index)
{
  double value{};                                // Somewhere to accumulate the result

  value = number(str, index);                    // Get the first number in the term

  // Loop as long as we have a good operator
  while (true)
  {

    if (*(str + index) == '*')                   // If it's multiply,
      value *= number(str, ++index);             // multiply by next number

    else if (*(str + index) == '/')              // If it's divide,
      value /= number(str, ++index);             // divide by next number
    else
      break;
  }
  return value;                                  // We've finished, so return what 
  // we've got
}

// Function to recognize a number in a string
double number(const char* str, size_t& index)
{
  double value{};                               // Store the resulting value

  // There must be at least one digit...
  if (!isdigit(*(str + index)))
  { // There's no digits so input is junk...
    char message[31] {"Invalid character in number: "};
    strncat_s(message, str + index, 1);          // Append the character
    throw message;
  }

  while (isdigit(*(str + index)))                 // Loop accumulating leading digits
    value = 10 * value + (*(str + index++) - '0');

  // Not a digit when we get to here
  if (*(str + index) != '.')                     // so check for decimal point
    return value;                                // and if not, return value

  double factor{ 1.0 };                          // Factor for decimal places
  while (isdigit(*(str + (++index))))            // Loop as long as we have digits
  {
    factor *= 0.1;                               // Decrease factor by factor of 10
    value = value + (*(str + index) - '0')*factor;   // Add decimal place
  }

  return value;                                  // On loop exit we are done
}
