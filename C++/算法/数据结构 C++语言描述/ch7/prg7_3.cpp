// File: prg7_3.cpp
// the program inputs an infix expression until the user enters an empty
// string. it uses the class infix2Postfix to convert the infix expression
// to postfix, handling errors that may occur by catching the corresponding
// expressionError exception. if there is no error, the postfix string is
// correctly formatted. use the class postfixEval to evaluate the postfix
// expression and output the result. this is the value of the original
// infix expression

#include <iostream>
#include <string>

// if Microsoft VC++, compensate for a getline() bug in <string>
#ifdef _MSC_VER
#include "d_util.h"
#endif _MSC_VER

#include "d_inftop.h"		// infix2Postfix class
#include "d_rpn.h"			// postfixEval class

using namespace std;

int main()
{
	// use iexp for infix to postfix conversion
	infix2Postfix iexp;
	// infix expression input and postfix expression output
	string infixExp, postfixExp;
	// use pexp to evaluate postfix expressions
	postfixEval pexp;

	// input and evaluate infix expressions until the
	// user enters an empty string

	// get the first expression
	cout << "Enter an infix expression: ";
	getline(cin, infixExp);

	while (infixExp != "")
	{
		// an exception may occur. enclose the conversion
		// to postfix and the output of the expression
		// value in a try block
		try
		{
			// convert to postfix
			iexp.setInfixExp(infixExp);
			postfixExp = iexp.postfix();

			// output the postfix expression
			cout << "The postfix form is " << postfixExp
				  << endl;

			// use pexp to evaluate the postfix expression
			pexp.setPostfixExp(postfixExp);
			
			cout << "Value of the expression = "
				  << pexp.evaluate() << endl << endl;
		}

		// catch an exception and output the error
		catch (const expressionError& ee)
		{
			cout << ee.what() << endl << endl;
		}
		// input another expression
		cout << "Enter an infix expression: ";
		getline(cin, infixExp);
	}

	return 0;
}

/*
Run:

Enter an infix expression: 3 ^ 2 ^ (1+2)
The postfix form is 3 2 1 2 + ^ ^
Value of the expression = 6561

Enter an infix expression: 3 * (4 - 2 ^ 5) + 6
The postfix form is 3 4 2 5 ^ - * 6 +
Value of the expression = -78

Enter an infix expression: (7 + 8*7
infix2Postfix: Missing ')'

Enter an infix expression: (9 + 7) 4
infix2Postfix: Operator expected

Enter an infix expression: 2*4*8/
infix2Postfix: Operand expected

Enter an infix expression:
*/
