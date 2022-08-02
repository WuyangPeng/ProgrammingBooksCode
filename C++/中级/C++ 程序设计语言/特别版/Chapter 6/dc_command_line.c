// The desk calulator

// includes character-level input (sec6.1.3) and
// command line input (sec6.1.7),
// but no namespaces and
// no exceptions

// pp 107-119, sec 6.1, A Desk Calculator


// uses += rather than push_back() for string
// to work around standard library bug

// uses istrstream from <strstream> rather than istringstream from <sstream>
// to work around standard library bug

// No guarantees offered. Constructive comments to bs@research.att.com


/*
    program:
	END			   // END is end-of-input
	expr_list END

    expr_list:
	expression PRINT	   // PRINT is semicolon
	expression PRINT expr_list

    expression:
	expression + term
	expression - term
	term

    term:
	term / primary
	term * primary
	primary

    primary:
	NUMBER
	NAME
	NAME = expression
	- primary
	( expression )
*/

#include <string>
#include <cctype>
#include<iostream>
#include<map>

//#include<sstream>	// string streams
#include<strstream>	// C-style string streams

using namespace std;

istream* input;	// pointer to input stream

int no_of_errors;	// note: default initialized to 0

double error(const char* s)
{
    no_of_errors++;
    cerr << "error: " << s << '\n';
    return 1;
}

enum Token_value {
	NAME,		NUMBER,		END,
	PLUS='+',	MINUS='-',	MUL='*',	DIV='/',
	PRINT=';',	ASSIGN='=',	LP='(',		RP=')'
};

Token_value curr_tok = PRINT;
double number_value;
string string_value;

Token_value get_token()
{
	char ch;

	do {	// skip whitespace except '\en'
		if(!input->get(ch)) return curr_tok = END;
	} while (ch!='\n' && isspace(ch));

	switch (ch) {
	case ';':
	case '\n':
		return curr_tok=PRINT;
	case '*':
	case '/':
	case '+':
	case '-':
	case '(':
	case ')':
	case '=':
		return curr_tok=Token_value(ch);
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	case '.':
		input->putback(ch);
		*input >> number_value;
		return curr_tok=NUMBER;
	default:			// NAME, NAME=, or error
		if (isalpha(ch)) {
			string_value = ch;
			while (input->get(ch) && isalnum(ch))
				string_value += ch;	// string_value.push_back(ch);
							// to work around library bug
			input->putback(ch);
			return curr_tok=NAME;
		}
		error("bad token");
		return curr_tok=PRINT;
	}
}

map<string,double> table;

double expr(bool);	// cannot do without


double prim(bool get)		// handle primaries
{
	if (get) get_token();

	switch (curr_tok) {
	case NUMBER:		// floating-point constant
	{	double v = number_value;
		get_token();
		return v;
	}
	case NAME:
	{	double& v = table[string_value];
		if (get_token() == ASSIGN) v = expr(true);
		return v;
	}
	case MINUS:		// unary minus
		return -prim(true);
	case LP:
	{	double e = expr(true);
		if (curr_tok != RP) return error(") expected");
		get_token();		// eat ')'
		return e;
	}
	default:
		return error("primary expected");
	}
}

double term(bool get)		// multiply and divide
{
	double left = prim(get);

	for (;;)
		switch (curr_tok) {
		case MUL:
			left *= prim(true);
			break;
		case DIV:
			if (double d = prim(true)) {
				left /= d;
				break;
			}
			return error("divide by 0");
		default:
			return left;
		}
}

double expr(bool get)		// add and subtract
{
	double left = term(get);

	for (;;)				// ``forever''
		switch (curr_tok) {
		case PLUS:
			left += term(true);
			break;
		case MINUS:
			left -= term(true);
			break;
		default:
			return left;
		}
}



int main(int argc, char* argv[])
{

	switch (argc) {
	case 1:					// read from standard input
		input = &cin;
		break;
	case 2: 				// read argument string
//		input = new istringstream(argv[1]);
		input = new istrstream(argv[1]);
		break;
	default:
		error("too many arguments");
		return 1;
	}

	table["pi"] = 3.1415926535897932385;	// insert predefined names
	table["e"] = 2.7182818284590452354;

	while (*input) {
		get_token();
		if (curr_tok == END) break;
		if (curr_tok == PRINT) continue;
		cout << expr(false) << '\n';
	}

	if (input != &cin) delete input;
	return no_of_errors;
}
