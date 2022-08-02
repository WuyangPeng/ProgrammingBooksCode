#if !defined (STACK_H)
#define STACK_H
// (c) Bartosz Milewski 2000

const int maxStack = 16;

class BStack
{
	friend class StackSeq; // give it access to private members
public:
	BStack (): _top (0) {}
	void Push (bool b);
	bool Pop ();
	bool IsFull () const { return _top >= maxStack; }
	bool IsEmpty () const { return _top == 0; }
private:
	bool _arr [maxStack];
	int  _top;
};

class StackSeq
{
public:
	StackSeq (BStack const & stack);
	bool AtEnd () const;   // are we done yet?
	void Advance ();       // move to next item
	bool GetVal () const;  // retrieve current item
private:
	BStack const & _stack; // reference to stack
	int	           _iCur;  // current index into stack
};

#endif
