// (c) Bartosz Milewski 2000
#include "queue.h"
#include <cassert>
#include <iostream>

int main ()
{
	Queue q;
	std::cout << "Putting 1, 2 and 3\n";
	q.Put (1);
	q.Put (2);
	q.Put (3);
	std::cout << "Getting three elements\n";
	std::cout << q.Get () << std::endl;
	std::cout << q.Get () << std::endl;
	std::cout << q.Get () << std::endl;
	std::cout << "Putting and getting one more\n";
	q.Put (4);
	std::cout << q.Get () << std::endl;
}

Link::~Link ()
{
	delete _next;
}

Queue::Queue ()
: _head (0), _tail (0)
{}

Queue::~Queue ()
{
	delete _head;
}

void Queue::Put (int i)
{
	Link * newLink = new Link (i);
	if (_tail == 0)
	{
		_head = newLink;
	}
	else
	{
		_tail->SetNext (newLink);
	}
	_tail = newLink;
}

int Queue::Get ()
{
	assert (_head != 0);
	int i = _head->Value ();
	Link * tmp = _head;
	_head = _head->Next ();
	// don't delete recursively!
	tmp->SetNext (0); 
	delete tmp;
	if (_head == 0)
		_tail = 0;
	return i;
}