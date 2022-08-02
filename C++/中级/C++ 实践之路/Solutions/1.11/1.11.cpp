#include <cassert>
#include <iostream>

const int maxStack = 16;

class IStack
{
public:
	IStack () :_top (0) {}
	int Count () const;
	void Push (int i);
	int  Pop ();
	int Top () const;
private:
	int _arr [maxStack];
	int _top;
};

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

int IStack::Top () const
{
	assert (_top > 0);
	return _arr [_top - 1];
}

int IStack::Count () const
{
	return _top;
}

int main ()
{
	IStack stack;
	stack.Push (13);
	std::cout << "Count is: " << stack.Count () << std::endl;
	std::cout << "Top is: " << stack.Top () << std::endl;
}