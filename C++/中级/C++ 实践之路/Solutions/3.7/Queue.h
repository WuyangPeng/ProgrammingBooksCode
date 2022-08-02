#if !defined (QUEUE_H)
#define QUEUE_H
// (c) Bartosz Milewski 2000

class Link
{
public:
	Link (int i)
	: _next (0), _i (i)
	{}
	~Link ();
	int Value () const { return _i; }
	Link * Next () { return _next; }
	void SetNext (Link * next)
	{
		_next = next;
	}
private:
	Link  * _next;
	int		_i;
};

class Queue
{
public:
	Queue ();
	~Queue ();
	void Put (int i);
	int Get ();
private:
	Link * _head;
	Link * _tail;
};

#endif
