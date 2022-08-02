#include "Scanner.h"
// (c) Bartosz Milewski 2000
#include <istream>
#include <cctype>
#include <cassert>

Scanner::Scanner (std::istream & in)
	: _in (in)
{
	Accept ();
	_isEmpty = (Token () == tEnd);
}

void Scanner::ReadChar ()
{ 
	_look = _in.get (); 
	while (_look == ' ' || _look == '\t') 
		_look = _in.get (); 
}

void Scanner::Accept ()
{
	ReadChar ();

	switch (_look)
	{
	case '+':
		_token = tPlus;
		break;
	case '-':
		_token = tMinus;
		break;
	case '*':
		_token = tMult;
		break;
	case '/':
		_token = tDivide;
		break;
	case '=':
		_token = tAssign;
		break;
	case '(':
		_token = tLParen;
		break;
	case ')':
		_token = tRParen;
		break;
	case '\n': // end of input 
	case '\r': 
	case EOF: // end of file 
		_token = tEnd;
		break;
	case '0': case '1': case '2': case '3': case '4': 
	case '5': case '6': case '7': case '8': case '9': 
	case '.': 
		_token = tNumber;
		_in.putback (_look); 
		_in >> _number; // read the whole number 
		break;
	default: 
		if (std::isalpha (_look) || _look == '_') 
		{ 
			_token = tIdent;
			_symbol.erase (); // erase string contents 
			do { 
				_symbol += _look;
				_look = _in.get (); 
			} while (std::isalnum (_look));
			_in.putback (_look); 
		}
		else 
			_token = tError; 
		break;
	}
}

void Scanner::AcceptCommand ()
{
	ReadChar ();
	_symbol.erase ();
	while (!std::isspace (_look))
	{
		_symbol += _look;
		_look = _in.get ();
	}
}
