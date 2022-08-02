// File: prg7_2.cpp
// the program initializes an integer stack whose values come from an array.
// push the numbers on the stack from the end of the array to the front, so
// the top of the stack is the first array element. output the contents of
// the stack by calling writeArray() to display the array elements. call the
// function uncouple() in an attempt to remove elements 14 and 17 from the
// stack, and then pop the stack until it is empty, outputting each stack
// element

#include <iostream>
#include <stack>

#include "d_util.h"	// for writeArray()

using namespace std;

// remove the first occurrence of target (if any) from stack s.
// return true if target was removed and false otherwise
template <typename T>
bool uncouple(stack<T>& s, const T& target);

int main()
{
	int arr[] = { 19, 14, 37, 43, 11, 12}, i;
	int arrSize = sizeof(arr)/sizeof(int);
	stack<int> intStack;

	cout << "Creating a stack with values (top to bottom): ";
	writeArray(arr, arrSize);
	cout << endl;
	// push items in arr onto intStack in order
	// arr[arrSize-1] ... arr[0], so arr[0] is on the
	// top of the stack
	for (i= arrSize-1;i >= 0;i--)
		intStack.push(arr[i]);

	// attempt to remove 14 and 17 from intStack
	if (uncouple(intStack, 14))
		cout << "Uncoupled 14" << endl;
	else
		cout << "14 is not on the stack" << endl;

	if (uncouple(intStack, 17))
		cout << "Uncoupled 17" << endl;
	else
		cout << "17 is not on the stack" << endl;

	cout << "Final stack (top to bottom): ";
	while (!intStack.empty())
	{
		cout << intStack.top() << "  ";
		intStack.pop();
	}
	cout << endl;

	return 0;
}

template <typename T>
bool uncouple(stack<T>& s, const T& target)
{
	stack<T> tmpStk;
	// assume the target is on the stack
	bool foundTarget = true;

	// pop elements from the stack s and push
	// them onto tmpStk until we locate target
	// or the stack becomes empty
	while (!s.empty() && s.top() != target)
	{
		tmpStk.push(s.top());
		s.pop();
	}
	
	// the while loop locates item if s is not empty
	if (!s.empty())
		s.pop();
	else
		// the target is not on the stack
		foundTarget = false;

	// restore the items from tmpStk by popping
	// it and pushing each element onto s
	while (!tmpStk.empty())
	{
		s.push(tmpStk.top());
		tmpStk.pop();
	}

	return foundTarget;
}

/*
Run:

Creating a stack with values (top to bottom): 19  14  37  43  11  12

Uncoupled 14
17 is not on the stack
Final stack (top to bottom): 19  37  43  11  12
*/
