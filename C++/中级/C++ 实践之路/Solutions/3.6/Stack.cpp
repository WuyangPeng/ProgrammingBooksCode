// (c) Bartosz Milewski 2000
#include "stack.h"
#include <cassert>
#include <iostream>

int main ()
{
	Stack2 stack;
	char const * str = stack.Top ();
	assert (str == 0);
	stack.Push ("one");
	stack.Push ("two");
	stack.Push ("three");
	std::cout << stack.Top () << std::endl;
	stack.Pop ();
	std::cout << stack.Top () << std::endl;
	stack.Pop ();
	assert (stack.Top () == 0);
}

Stack2::Stack2 ()
	: _last (0), _previous (0)
{}

void Stack2::Push (char const * str)
{
	_previous = _last;
	_last = str;
}

void Stack2::Pop ()
{
	_last = _previous;
	_previous = 0;
}

char const * Stack2::Top () const
{
	return _last;
}
