#if !defined (INPUT_H)
#define INPUT_H
// (c) Bartosz Milewski 2000

const int maxBuf = 100;

// Tokens are tokValue, tokError, &, |, !

const int tokValue = 1;
const int tokError = 2;

// Gets input from stdin, converts to token.

class Input
{
public:
	Input ();
	int Token () const { return _token; }
	bool Value () const;
private:
	int  _token;
	bool _value;
};

#endif
