// (c) Bartosz Milewski 2000
#include "stack.h"
#include <cassert>
#include <iostream>

IStack::IStack ()
	: _top (0), _capacity (initStack)
{
	_arr = new int [initStack]; // allocate memory
}

IStack::~IStack ()
{
	delete []_arr; // free memory
}

void IStack::Push (int i)
{
	assert (_top <= _capacity);
	if (_top == _capacity)
		Grow ();
	_arr [_top] = i;
	++_top;
}

int IStack::Pop ()
{
	// Do not Pop an empty stack
	assert (_top > 0);
	--_top;
	return _arr [_top];
}

int IStack::Top () const
{
	// Don't call Top on an empty stack
	assert (_top > 0);
	return _arr [_top - 1];
}

bool IStack::IsEmpty () const
{
	assert (_top >= 0);
	return _top == 0;
}

void IStack::Grow ()
{
	std::cout << "Doubling stack from " 
			  << _capacity << ".\n";
	// allocate new array
	int * arrNew = new int [2 * _capacity];
	// copy all entries
	for (int i = 0; i < _capacity; ++i)
		arrNew [i] = _arr [i];
	_capacity = 2 * _capacity;
	// free old memory
	delete []_arr;
	// substitute new array for old array
	_arr = arrNew;
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
