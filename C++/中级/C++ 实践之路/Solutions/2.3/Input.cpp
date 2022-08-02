// (c) Bartosz Milewski 2000

#include "Input.h"
#include <iostream>
#include <cassert>

Input::Input ()
{
	char c;
	std::cin >> c;

	// first char of input is usually enough to decide
	// what token it is

	if (c == '&' || c == '|' || c == '!')
		_token = c;
	else if (c == 't')
	{
		_token = tokValue;
		_value = true;
	}
	else if (c == 'f')
	{
		_token = tokValue;
		_value = false;
	}
	else
		_token = tokError;
}

bool Input::Value () const
{
	assert (_token == tokValue);
	return _value;
}