#if !defined (STACK_H)
#define STACK_H
// (c) Bartosz Milewski 2000

class Stack2
{
public:
	Stack2 ();
	void Push (char const * str);
	void Pop ();
	char const * Top () const;
private:
	char const * _last;
	char const * _previous;
};

#endif
