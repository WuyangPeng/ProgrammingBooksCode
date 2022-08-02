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

StackSeq::StackSeq (IStack const & stack )
	: _iCur (0), _stack (stack) // init reference
{}

bool StackSeq::AtEnd () const
{
	return _iCur == _stack._top;  // friend: can access _top
}

void StackSeq::Advance ()
{
	assert (!AtEnd()); // not at end
	++_iCur;
}

int StackSeq::GetNum () const
{
	return _stack._arr [_iCur]; // friend: can access _arr
}

int main ()
{
	IStack TheStack;
	TheStack.Push (1);
	TheStack.Push (2);
	TheStack.Push (3);

	for (StackSeq seq (TheStack);
		 !seq.AtEnd();
		 seq.Advance() )
	{
		std::cout << "    " << seq.GetNum() << std::endl;
	}
}
