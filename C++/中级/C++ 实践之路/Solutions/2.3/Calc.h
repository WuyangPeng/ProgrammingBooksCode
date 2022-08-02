#if !defined (CALC_H)
#define CALC_H
// (c) Bartosz Milewski 2000
#include "Stack.h"
#include "Input.h"

class Calculator
{
public:
	bool Execute (Input const & input);
	// give access to the stack
	BStack const & GetStack () const { return _stack; }
private:
	bool Calculate (bool b1, bool b2, int token) const;

	BStack  _stack;
};

#endif
