#if !defined (STACK_H)
#define STACK_H
// (c) Bartosz Milewski 2000

const int initStack = 1;

class IStack
{
	friend class StackSeq; // give it access to private members
public:
	IStack ();
	~IStack ();
	void Push (int i);
	int  Pop ();
	int  Top () const;
	bool IsFull () const { return false; }
	bool IsEmpty () const;
private:
	void Grow ();
	void Shrink ();
private:
	int * _arr;
	int   _capacity; // size of the array
	int   _top;
};

class StackSeq
{
public:
	StackSeq (IStack const & stack);
	bool AtEnd () const;   // are we done yet?
	void Advance ();       // move to next item
	int GetNum ()const;    // retrieve current item
private:
	IStack const & _stack; // reference to stack
	int	           _iCur;  // current index into stack
};

#endif
