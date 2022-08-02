// (c) Bartosz Milewski 2000
#include "stack.h"
#include <cassert>
#include <iostream>

//compile with NDEBUG=1 to get rid of assertions

void BStack::Push (bool b)
{
	assert (_top < maxStack);
	_arr [_top] = b;
	++_top;
}

bool BStack::Pop ()
{
	assert (_top > 0);
	--_top;
	return _arr [_top];
}

StackSeq::StackSeq (BStack const & stack )
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

bool StackSeq::GetVal () const
{
	return _stack._arr [_iCur]; // friend: can access _arr
}
