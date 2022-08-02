#if !defined (STACK_H)
#define STACK_H
// (c) Bartosz Milewski 2000

const int maxStack = 16;

class IStack
{
	friend class StackSeq; // give it access to private members
public:
	IStack (): _top (0) {}
	void Push (int i);
	int  Pop ();
	bool IsFull () const { return _top >= maxStack; }
	bool IsEmpty () const { return _top == 0; }
private:
	int _arr [maxStack];
	int _top;
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
