#ifndef EPARSE_H
#define EPARSE_H

#include "e.h"
#include <cstring>


class Lex {	// generic lexical analyser interface
  public:
	Lex( std::size_t lexeme_size = 81 )
		: str( new char[ lexeme_size ] ) {}
	virtual ~Lex()
		{ delete [] str; }
	virtual void scan() = 0;
	int token() const
		{ return tok; }
	const char *lexeme() const
		{ return str; }
  protected:
	int tok;
	char *str;
};

class CharLex : public Lex {	// reads char stream
  protected:
	// unless overridden, reads from stdin
	virtual int nextchar()
		{ return getchar(); }
	virtual void unnextchar( char c )
		{ ungetc( c, stdin ); }
};

class ExprLex : public CharLex {	// lex for exprs
  public:
	void scan();
};

enum { ID = 257, INT, EOLN, BAD };

class Parser {	// generic parser interface
  public:
	Parser( Lex *lp )
		: lex( lp ) {}
	virtual ~Parser()
		{ delete lex; }
	virtual E *parse() = 0;
  protected:
	void scan()
		{ lex->scan(); }
	int token() const
		{ return lex->token(); }
	const char *lexeme() const
		{ return lex->lexeme(); }
  private:
	Lex *lex;
};

/*
	Predictive parser for a simple expression grammar:

		S --> E eoln
		E --> T {(+|-)T}
		T --> F {(*|/)F}
		F --> id | int | ( E ) | ID = E | -F
*/
class ExprParser : public Parser {
  public :
	ExprParser( Lex *lp )
		: Parser( lp ) {}
	~ExprParser()
		{}
	E *parse();
  private:
	E *s();
	E *e();
	E *t();
	E *f();
	void error();
};

#endif
