#if !defined (SCANNER_H)
#define SCANNER_H
// (c) Bartosz Milewski 2000
#include <string>
#include <cassert>

enum EToken
{
	tEnd,
	tError,
	tNumber,    // literal number
	tPlus,      // +
	tMult,      // *
	tMinus,     // -
	tDivide,    // /
	tLParen,    // (
	tRParen,    // )
	tAssign,    // =
	tIdent      // identifier (symbolic name)
};

class Scanner
{
public:
	explicit Scanner (std::istream & in);
	bool IsDone () const { return _token == tEnd; }
	bool IsEmpty () const { return _isEmpty; }
	EToken    Token () const { return _token; }
	void    Accept ();
	void    AcceptCommand ();
	std::string GetSymbolName () const { return _symbol; }
	double Number () const { return _number; }
private:
	void ReadChar ();

	std::istream  & _in;
	int            _look;    // lookahead character
	bool           _isEmpty;
	EToken         _token;
	double         _number;
	std::string    _symbol;
};

#endif
