#ifdef __BORLANDC__
// turn off Borland warning message about comparison of signed and
// unsigned values
#pragma warn -8012
#endif	// __BORLANDC__

#ifndef POSTFIX_EVALUATION
#define POSTFIX_EVALUATION

#include <iostream>
#include <string>
#include <stack>
#include <ctype.h>

#include "d_except.h"	// for expressionError exception

using namespace std;

class postfixEval
{
	public:
		postfixEval();
			// default constructor. postfix expression is NULL string

		string getPostfixExp() const;
			// return the postfix expression

		void setPostfixExp(const string& postfixExp);
			// change the postfix expression

		int evaluate();
			// evaluate the postfix expression and return
			// its value. the function throws expressionError
			// if an error occurs during evaluation
	private:
		string postfixExpression;
			// the postfix expression to evaluate
		stack<int> operandStack;
			// stack of operands

		void getOperands(int& left, int& right);
			// pop left and right operands from stack.
			// Precondition: the stack must have at least two entries.
			// if the stack is empty prior to a pop() operation, the
			// function throws the exception expressionError

		int compute(int left, int right, char op) const;
			// compute "left op right". if right is 0 and op
			// is '/' or '%', the function throws expressionError

		bool isOperator(char ch) const;
			// is ch one of '+','-','*','/','%','^'
};

void postfixEval::getOperands(int& left, int& right)
{
	// can we pop the right operand?
	if (operandStack.empty())
		throw  expressionError("postfixEval: Too many operators");

	// pop right operand
	right = operandStack.top();
	operandStack.pop();

	// can we pop the left operand?
	if (operandStack.empty())
		throw  expressionError("postfixEval: Too many operators");

	// pop left operand
	left = operandStack.top();
	operandStack.pop();
}

int postfixEval::compute(int left, int right, char op) const
{
	int value;

	// evaluate "left op right"
	switch(op)
	{
		case '+':	value = left + right;
						break;

		case '-':	value = left - right;
						break;

		case '*':	value = left * right;
						break;

		case '%':	if (right == 0)
							throw
								expressionError("postfixEval: divide by 0");
						value = left % right;
						break;

		case '/':	if (right == 0)
							throw
								expressionError("postfixEval: divide by 0");
						value = left / right;
						break;

		case '^':	// make sure we are not computing 0^0
						if (left == 0 && right == 0)
							throw
								expressionError("postfixEval: 0^0 undefined");

						value = 1;
						// general case. compute value =  1*left*...*left.
						// if right == 0, skip the loop and left^0 is 1
						while (right > 0)
						{
							value *= left;
							right--;
						}
						break;
	}

	return value;
}

bool postfixEval::isOperator(char ch) const
{
	return ch == '+' || ch == '-' || ch == '*' ||
			 ch == '%' || ch == '/' || ch == '^';
}

// default constructor
postfixEval::postfixEval()
{}

string postfixEval::getPostfixExp() const
{
	return postfixExpression;
}

void postfixEval::setPostfixExp(const string& postfixExp)
{
	postfixExpression = postfixExp;
}

int postfixEval::evaluate()
{
	// expValue contains the evaluated expression
	int left, right, expValue;
	char ch;
	int i;

	// process characters until the end of the string is reached
	// or an error occurs
	for (i=0; i < postfixExpression.length(); i++)
	{
		// get the current character
		ch = postfixExpression[i];

		// look for an operand, which is a single digit
		// non-negative integer
		if (isdigit(ch))
			// value of operand goes on the stack
			operandStack.push(ch - '0');
		// look for an operator
		else if (isOperator(ch))
		{
			// pop the stack twice and get the
			// left and right operands
			getOperands(left, right);
			// evaluate "left op right" and push on stack
			operandStack.push(compute(left, right, ch));
		}
		// any other character must be whitespace.
		// whitespace includes blank, tab, and newline
		else if (!isspace(ch))
			throw expressionError("postfixEval: Improper char");
	}

	// the expression value is on the top of the stack.
	// pop it off
	expValue = operandStack.top();
	operandStack.pop();

	// if data remains on the stack, there are too
	// many operands
	if (!operandStack.empty())
		throw expressionError("postfixEval: Too many operands");

	return expValue;
}

#endif	// POSTFIX_EVALUATION
