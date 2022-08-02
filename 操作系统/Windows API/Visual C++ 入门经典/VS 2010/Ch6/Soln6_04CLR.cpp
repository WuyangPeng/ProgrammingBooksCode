// Soln6_04CLR.cpp : main project file.
// A CLR calculator supporting parentheses, identifying input  errors and supporting exponentiation.

// Exponentiation requires just one extra else if in the term() function..

#include "stdafx.h"
#include <cstdlib>                                            // For exit()

using namespace System;
String^ eatspaces(String^ str);                                             // Function to eliminate blanks
double expr(String^ str, String^ input, int^ inputIndex);                   // Function evaluating an expression
double term(String^ str, int^ index, String^ input, int^ inputIndex);       // Function analyzing a term
double number(String^ str, int^ index, String^ input, int^ inputIndex);     // Function to recognize a number
String^ extract(String^ str, int^ index, String^ input, int^ inputIndex);   // Function to extract a substring
void error(String^ input, int index);                                       // Function to identify an error

int main(array<System::String ^> ^args)
{
  String^ buffer;      // Input area for expression to be evaluated
  int^ inputIndex(0);

   
  Console::WriteLine(L"Welcome to your friendly calculator.");
  Console::WriteLine(L"Enter an expression, or an empty line to quit.");

  for(;;)
  {
    buffer = eatspaces(Console::ReadLine());         // Read an input line

    if(String::IsNullOrEmpty(buffer))                // Empty line ends calculator
      return 0;

    Console::WriteLine(L"  = {0}\n\n",expr(buffer, buffer, inputIndex)); // Output value of expression
  }
  return 0;
}

// Function to eliminate spaces from a string
String^ eatspaces(String^ str)
{
  return str->Replace(L" ", L"");
}

// Function to evaluate an arithmetic expression
double expr(String^ str, String^ input, int^ inputIndex)
{
  int^ index(0);                                          // Keeps track of current character position

  double value(term(str, index, input, inputIndex));      // Get first term

  while(*index < str->Length)
  {
    switch(str[*index])                                   // Choose action based on current character
    {
      case '+':                                           // + found so 
         ++(*index);                                      // increment index and add
         value += term(str, index, input, inputIndex);    // the next term
         break;

      case '-':                                           // - found so
          ++(*index);                                     // increment index and subtract
        value -= term(str, index, input, inputIndex);     // the next term
         break;

      default:                                            // If we reach here the string is junk
        Console::WriteLine(L"Arrrgh!*#!! There's an error.\n");
        error(input, *inputIndex + *index - 1);
        exit(1);
    }
  }
  return value;
}

// Function to get the value of a term
double term(String^ str, int^ index, String^ input, int^ inputIndex)
{
  double value(number(str, index, input, inputIndex));      // Get the first number in the term
  // Loop as long as we have characters and a good operator
  while(*index < str->Length)
  {
    if(L'*' == str[*index])                                 // If it's multiply,
    {
      ++(*index);                                           // increment index and
      value *= number(str, index, input, inputIndex);       // multiply by next number
    }
    else if(L'/' == str[*index])                            // If it's divide
    {
      ++(*index);                                           // increment index and
      value /= number(str, index, input, inputIndex);       // divide by next number
    }
    else if(L'^' == str[*index])                                        // If it's exponentiation
    {
      ++(*index);                                                       // increment index and
      value = Math::Pow(value, number(str, index, input, inputIndex));  // get power of next number
    }
    else
      break;                                // Exit the loop
 }
  // We've finished, so return what we've got
  return value;                             
}

// Function to recognize a number
double number(String^ str, int^ index, String^ input, int^ inputIndex)
{
  double value(0.0);                                           // Store for the resulting value

  // Check for expression between parentheses
  if(L'(' == str[*index])                                      // Start of parentheses
  {
    ++(*index);
    int oldIndex(*inputIndex);                                 // Save current value to restore later
    *inputIndex += *index;                                     // Move input index to substring start
    String^ substr(extract(str, index, input, inputIndex));    // Extract substring in brackets
    double result = expr(substr, input, inputIndex);           // Get substring value
    *inputIndex = oldIndex;                                    // Restore input index
    return result;
  }

  // There must be at least one digit...
  if(!Char::IsDigit(str, *index))
  {
    Console::WriteLine(L"Arrrgh!*#!! There's an error.\n");
    error(input, *inputIndex + *index - 1);
    exit(1);
  }

  // Loop accumulating leading digits
  while((*index < str->Length) && Char::IsDigit(str, *index))
  {
    value = 10.0*value + Char::GetNumericValue(str[(*index)]);
    ++(*index);
  }

  // Not a digit when we get to here
  if((*index == str->Length) || str[*index] != '.')   // so check for decimal point
    return value;                                     // and if not, return value

  double factor(1.0);                  // Factor for decimal places
  ++(*index);                          // Move to digit

  // Loop as long as we have digits
  while((*index < str->Length) && Char::IsDigit(str, *index))   
  {
    factor *= 0.1;                     // Decrease factor by factor of 10
    value = value + Char::GetNumericValue(str[*index])*factor; // Add decimal place
    ++(*index);
  }

  return value;                        // On loop exit we are done
}

// Function to extract a substring between parentheses 
String^ extract(String^ str, int^ index, String^ input, int^ inputIndex)
{
  int numL(0);
  int bufindex(*index);

  while(*index < str->Length)
  {
    switch(str[*index])
    {
      case ')':
        if(0 == numL)
          return str->Substring(bufindex, (*index)++ - bufindex);
        else
          numL--;
        break;

      case '(':
        numL++;
        break;
    }
    ++(*index);
  }

  Console::WriteLine(L"Ran off the end of the expression, must be bad input.");
  error(input, *inputIndex);
  exit(1);
}

// Function to identify an error
void error(String^ str, int index)
{
   Console::WriteLine(str);
   Console::Write(gcnew String(L' ',index));
   Console::WriteLine(L" ^");
   Console::WriteLine(L"Press Enter to end.");
   Console::ReadLine();
}
