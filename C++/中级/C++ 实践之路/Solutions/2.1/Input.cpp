// (c) Bartosz Milewski 2000

#include "Input.h"
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cassert>

Input::Input ()
{
	std::cin >> _buf;

	// first char of input is usually enough to decide
	// what token it is

	int c = _buf [0]; 

	if (std::isdigit (c))
	{
		_token = tokNumber;
	}
	else if (c == '+' || c == '*' || c == '/' || c == '&'
		  || c == '|' || c == '^' || c == '~')
	{
		_token = c;
	}
	else if (c == '<' || c == '>')
	{
		// these are two-character combinations
		if (_buf [1] != c)
			_token = tokError;
		else
			_token = c; // use first char as token
	}
	else if (c == '-') // allow entering negative numbers
	{
		if (std::isdigit (_buf [1])) // peek at next char
			_token = tokNumber;
		else
			_token = c;
	}
	else
		_token = tokError;
}

int Input::Number () const
{
	assert (_token == tokNumber);
	return std::atoi (_buf);   // convert string to integer
}