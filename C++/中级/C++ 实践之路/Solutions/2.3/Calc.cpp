// (c) Bartosz Milewski 2000
#include "Calc.h"
#include "Input.h"
#include <iostream>
#include <cassert>

bool Calculator::Execute (Input const & input)
{
	int token = input.Token ();
	bool status = false; // assume failure

	if (token == tokError)
	{
		std::cout << "Unknown token\n";
	}
	else if (token == tokValue)
	{
		if (_stack.IsFull ())
		{
			std::cout << "Stack is full\n";
		}
		else
		{
			_stack.Push (input.Value ());
			status = true; // success
		}
	}
	else
	{
		assert (token == '&' || token == '|' || token == '!');
		if (_stack.IsEmpty ())
		{
			std::cout << "Stack is empty\n";
		}
		else
		{ 
			bool b2 = _stack.Pop ();
			if (token == '!')
			{
				_stack.Push (!b2);
				status = true;
			}
			else
			{
				bool b1;

				// Special case, when only one number on the stack:
				// use this number for both operands.

				if (_stack.IsEmpty ())
					b1 = b2;
				else
					b1 = _stack.Pop ();

				_stack.Push (Calculate (b1, b2, token));
				status = true;
			}
		}
	}
	return status;
}

bool Calculator::Calculate (bool b1, bool b2, int token) const 
{ 
	bool result;

	if (token == '&') 
		result = b1 && b2; 
	else if (token == '|') 
		result = b1 || b2; 
	return result; 
} 

int main ()
{
	Calculator TheCalculator;
	bool status;
	do
	{
		// Prompt for input
		std::cout << "> ";
		Input input;
		status = TheCalculator.Execute (input);
		if (status)
		{
			std::cout << std::boolalpha;
			for (StackSeq seq (TheCalculator.GetStack ());
				 !seq.AtEnd ();
				 seq.Advance () )
			{
				std::cout << "    " << seq.GetVal () << std::endl;
			}
		}
	} while (status);
}
