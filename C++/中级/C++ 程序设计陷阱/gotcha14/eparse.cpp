#include <cstring>
#include <cctype>
#include "e.h"
#include "eparse.h"

using namespace std;


/*
	Scanner:  return the next token in the input stream.
		attributes for integer constants and identifiers
		available until next invocation
*/
void
ExprLex::scan() {
	int c;
	while( true )
		switch( c = nextchar() ) {
		case '+': case '-':
		case '*': case '/':
		case '(': case ')':
		case '=':
			tok = c;
			return;
		case ' ': case '\t':
			continue;
		case '\n':
			tok = EOLN;
			return;
		default:
			if( isdigit( c ) ) {
				char *s = str;
				do
					*s++ = c;
				while( isdigit( c = nextchar() ) );
				*s = '\0';
				unnextchar( c );
				tok = INT;
				return;
			}
			if( isalpha( c ) ) {
				char *s = str;
				do
					*s++ = c;
				while( isalnum(c = nextchar()) );
				*s = '\0';
				unnextchar( c );
				tok = ID;
				return;
			}
			tok = BAD;
			return;
		}
}


E *
ExprParser::parse() {
	scan();
	E *ast = s();
	if( token() != EOLN )
		error();
	return ast;
}

void
ExprParser::error() {
	throw std::range_error( "syntax error" );
}

E *
ExprParser::s() {
	E *root = 0;
	if( token() != EOLN )
		root = e();
	return root;
}

E *
ExprParser::e() {
	E *root = t();
	while( true )
		switch( token() ) {
		case '+':
			scan();
			root = new Plus( root, t() );
			break;
		case '-':
			// uncomment out if allowing binary minus
			//scan();
			//root = new Minus( root, t() );
			error(); // comment out if allowing binary minus
			break;
		default:
			return root;
		}
}

E *
ExprParser::f() {
	E *root;
	switch( token() ) {
	case ID:
		root = new Var( lexeme() );
		scan();
		if( token() == '=' ) {
			scan();
			root = new Assign( static_cast<Var *>(root), e() );
		}
		return root;
	case INT:
		root = new Int( atoi( lexeme() ) );
		scan();
		return root;
	case '(':
		scan();
		root = e();
		if( token() != ')' )
			error();
		scan();
		return root;
	case '-':
		// uncomment out if allowing unary minus
		scan();
		return new Uminus( f() );
	default:
		error();
	}
	return 0;	// will never execute, but some compilers
				// complain if not there
}

E *
ExprParser::t() {
	E *root = f();
	while( true )
		switch( token() ) {
		case '*':
			scan();
			root = new Times( root, f() );
			break;
		case '/':
			// uncomment out if allowing binary /
			//scan();
			//root = new Div( root, f() );
			error(); // remove if parsing binary /
			break;
		default:
			return root;
		}
}
