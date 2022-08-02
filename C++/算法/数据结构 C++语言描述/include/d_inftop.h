#ifdef __BORLANDC__
// suppress the warning message about comparing signed and unsigned values
#pragma warn -8012
#endif	// __BORLANDC__

#ifndef INFIX_TO_POSTFIX
#define INFIX_TO_POSTFIX

#include <iostream>
#include <string>
#include <stack>
#include <ctype.h>

#include "d_expsym.h"	// expressionSymbol class
#include "d_except.h"	// for expressionError exception

using namespace std;

// labels designating the parentheses characters
const char lParen  = '(', rParen = ')';

class infix2Postfix
{
	public:
		infix2Postfix();
			// default constructor. infix expression is NULL string
		infix2Postfix(const string& infixExp);
			// initialize the infix expression

		void setInfixExp(const string& infixExp);
			// change the infix expression

		string postfix();
			// return a string that contains the equivalent postfix
			// expression. the function throws expressionError if an
			// error occurs during conversion

	private:

		string infixExpression;
			// the infix expression to convert
		string postfixExpression;
			// built to contain the postfix equivalent of infixExpression
		stack<expressionSymbol> operatorStack;
			// stack of expressionSymbol objects

		void outputHigherOrEqual(const expressionSymbol& op);
			// the expressionSymbol object op holds the current
			// symbol. pop the stack and output as long as the symbol
			// on the top of the stack has a precedence >= that of
			// the current operator

		bool isOperator(char ch) const;
			// is ch one of '+','-','*','/','%','^'
};


void infix2Postfix::outputHigherOrEqual(const expressionSymbol& op)
{
	expressionSymbol op2;

	while(!operatorStack.empty() &&
			(op2 = operatorStack.top()) >= op)
	{
		operatorStack.pop();
		postfixExpression += op2.getOp();
		postfixExpression += ' ';
	}
}

bool infix2Postfix::isOperator(char ch) const
{
	return ch == '+' || ch == '-' || ch == '*' ||
			 ch == '%' || ch == '/' || ch == '^';
}

infix2Postfix::infix2Postfix()
{}

infix2Postfix::infix2Postfix(const string& infixExp):
		infixExpression(infixExp)
{}

void infix2Postfix::setInfixExp(const string& infixExp)
{
	// assign a new infix expression
	infixExpression = infixExp;
	// make postfixExpression the NULL string
	postfixExpression = "";
}

string infix2Postfix::postfix()
{
	expressionSymbol op;
	// maintain rank for error checking
	int rank = 0, i;
	char ch;

	// process until end of the expression
	for (i=0; i < infixExpression.length(); i++)
	{
		ch = infixExpression[i];

		//  ********  process an operand  ********
		// an operand is a single digit non-negative integer
		if (isdigit(ch))
		{
			// just add operand to output expression, followed by
			// a blank
			postfixExpression += ch;
			postfixExpression += ' ';
			// rank of an operand is 1, accumulated rank
			// must be 1
			rank++;
			if (rank > 1)
				throw expressionError("infix2Postfix: Operator expected");
		}
		//  *********  process an operator or '('  **********
		else if (isOperator(ch) || ch == '(')
		{
			// rank of an operator is -1. rank of '(' is 0.
			// accumulated rank should be 0
			if (ch != '(')
					rank--;

			if (rank < 0)
				throw expressionError("infix2Postfix: Operand expected");	else
			{
				// output the operators on the stack with higher
				// or equal precedence. push the current operator
				// on the stack
				op = expressionSymbol(ch);
				outputHigherOrEqual(op);
				operatorStack.push(op);
			}
		}
		//  *********  process a right parenthesis  **********
		else if (ch == rParen)
		{
			// build an expressionSymbol object holding ')', which
			// has precedence lower than the stack precedence
			// of any operator except '('. pop the operator stack
			// and output operators from the subexpression until
			// '(' surfaces or the stack is empty. if the stack is
			// empty, a '(' is missing; otherwise, pop off '('.
			op = expressionSymbol(ch);
			outputHigherOrEqual(op);
			if(operatorStack.empty())
				throw expressionError("infix2Postfix: Missing '('");
			else
				operatorStack.pop(); // get rid of '('
		}
		//  *********  make sure ch is whitespace  **********
		else if (!isspace(ch))
			throw expressionError("infix2Postfix: Invalid input");
	}

	// finish processing
	if (rank != 1)
		throw expressionError("infix2Postfix: Operand expected");
	else
	{
		// flush operator stack and complete expression evaluation.
		// if find left parenthesis, a right parenthesis is
		// missing.
 		while (!operatorStack.empty())
		{
			op = operatorStack.top();
			operatorStack.pop();
			if (op.getOp() == lParen)
				throw expressionError("infix2Postfix: Missing ')'");
			else
			{
				postfixExpression += op.getOp();
				postfixExpression += ' ';
			}
		}
	}

	return postfixExpression;
}

#endif	// INFIX_TO_POSTFIX
