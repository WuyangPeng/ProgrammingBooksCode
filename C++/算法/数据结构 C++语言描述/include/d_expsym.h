#ifndef INFIX_SYMBOLS
#define INFIX_SYMBOLS

// a class that maintains the precedence of symbols
class expressionSymbol
{
	public:
		expressionSymbol();
			// default constructor
		expressionSymbol(char ch);
			// initializes the object for operator ch

		friend bool operator>= (const expressionSymbol& left,
										const expressionSymbol& right);
			// return true if stackPrecedence of left is
			// >= inputPrecedence of right. determines whether
			// operator left on the stack should be output before
			// pushing operator right on the stack

		char getOp() const;
			// return operator        

	private:
		char op;
			// operator
		int inputPrecedence;
			// input precedence of op
		int stackPrecedence;
			// stack precedence of op
};

// default constructor
expressionSymbol::expressionSymbol()
{}

// constructor that assigns operator and precedence values
expressionSymbol::expressionSymbol(char ch)
{
	op = ch;    // assign operator

	switch(op)
	{
		// '+' and '-' have input/stack precedence 1
		case '+':   
		case '-':  inputPrecedence = 1;
					  stackPrecedence = 1;
					  break;
                       
		// '*', '%', and '/' have input/stack precedence 2
		case '*':   
		case '%':   
		case '/':  inputPrecedence = 2;
					  stackPrecedence = 2;
					  break;
                   
		// '^' is right associative. input precedence 4
		// and stack precedence 3
		case '^':  inputPrecedence = 4;
					  stackPrecedence = 3;
					  break;

		// '(' has input precendence 5, stack precedence -1
		case '(':  inputPrecedence = 5;
					  stackPrecedence = -1;
					  break;
                   
		// ')' has input/stack precedence 0
		case ')':  inputPrecedence = 0;
					  stackPrecedence = 0;
					  break;
	}
}

char expressionSymbol::getOp() const
{
	return op;
}

bool operator>= (const expressionSymbol& left, const expressionSymbol& right )
{
	return left.stackPrecedence >= right.inputPrecedence;
}
       
#endif // INFIX_SYMBOLS

