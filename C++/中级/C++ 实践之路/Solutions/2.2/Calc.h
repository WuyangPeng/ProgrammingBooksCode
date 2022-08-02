#if !defined (CALC_H)
#define CALC_H
// (c) Bartosz Milewski 2000
#include "Stack.h"
#include "Input.h"

class Calculator
{
public:
	Calculator () : _isHex (false) {}
	bool Execute (Input const & input);
	bool IsHex () const { return _isHex; }
	// give access to the stack
	IStack const & GetStack () const { return _stack; }
private:
	int Calculate (int n1, int n2, int token) const;

	IStack  _stack;
	bool	_isHex;
};

#endif
