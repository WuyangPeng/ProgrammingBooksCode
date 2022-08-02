#include <iostream>
#include <cassert>

const int maxPuts = 8;

class Queue
{
public:
	Queue ();
	double Get ();
	void Put (double x);
private:
	double	_arr [maxPuts];
	int		_putIdx;
	int		_getIdx;
};

Queue::Queue ()
: _putIdx (0),
  _getIdx (0)
{}

double Queue::Get ()
{
	assert (_getIdx < _putIdx);
	++_getIdx;
	return _arr [_getIdx - 1];
}

void Queue::Put (double x)
{
	assert (_putIdx < maxPuts);
	_arr [_putIdx] = x;
	++_putIdx;
}

int main ()
{
	Queue queue;
	queue.Put (0.1);
	queue.Put (0.2);
	std::cout << "Getting: " << queue.Get () << ", " 
		<< queue.Get () << std::endl;
	queue.Put (0.3);
	std::cout << "Getting more: " << queue.Get () << std::endl; 
}