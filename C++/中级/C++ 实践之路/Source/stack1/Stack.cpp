// (c) Bartosz Milewski 2000
#include "stack.h"
#include <cassert>
#include <iostream>

void IStack::Push (int i)
{
	assert (_top < maxStack);
	_arr [_top] = i;
	++_top;
}

int IStack::Pop ()
{
	assert (_top > 0);
	--_top;
	return _arr [_top];
}

int main ()
{
	IStack stack;
	stack.Push (1);
	stack.Push (2);
	std::cout << "Popped " << stack.Pop() << std::endl;
	std::cout << "Popped " << stack.Pop() << std::endl;
}
