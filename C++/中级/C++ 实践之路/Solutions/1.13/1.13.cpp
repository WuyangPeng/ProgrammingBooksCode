#include <cassert>
#include <iostream>

const int maxStack = 32;

class CharStack
{
public:
	CharStack () :_top (0) {}
	void Push (char c);
	char Pop ();
	char Top () const;
	int Count () const;
private:
	char _arr [maxStack];
	int  _top;
};

void CharStack::Push (char c)
{
	assert (_top < maxStack);
	_arr [_top] = c;
	++_top;
}

char CharStack::Pop ()
{
	assert (_top > 0);
	--_top;
	return _arr [_top];
}

char CharStack::Top () const
{
	assert (_top > 0);
	return _arr [_top - 1];
}

int CharStack::Count () const
{
	return _top;
}

int main ()
{
	CharStack stack;
	char str [] = "esreveR";
	for (int i = 0; str [i] != '\0'; ++i)
		stack.Push (str [i]);
	while (stack.Count () > 0)
		std::cout << stack.Pop ();
	std::cout << std::endl;
}