#ifndef VECTOR_BASED_STACK_CLASS
#define VECTOR_BASED_STACK_CLASS

#ifdef _MSC_VER
// disable warning messages that identifier was truncated
// to 'number' characters in the debug information
#pragma warning(disable:4786)
#endif	// _MSC_VER

#include <vector>			// vector class used by object composition

#include "d_except.h"	// for underflowError exception

using namespace std;

template <typename T>
class miniStack
{
	public:
		miniStack();
			// constructor. create an empty stack

		void push(const T& item);
			// push (insert) item onto the stack.
			// Postcondition: the stack has a new topmost element and
			// the stack size increases by 1

		void pop();
			// remove the item from the top of the stack.
			// Precondition: the stack is not empty.
			// if the stack is empty, the function throws
			// the underflowError exception
     
		T& top();
			// return a reference to the element on the top
			// of the stack.
			// Precondition: the stack is not empty.
			// if the stack is empty, the function throws
			// the underflowError exception
		const T& top() const;
			// constant version of top()

		bool empty() const;
			// determine whether the stack is empty

		int size() const;
			// return the number of elements in the stack

	private:
    	vector<T> stackVector;
			// a vector object maintains the stack items and size
};

// the constructor has nothing to do. the default
// constructor for the vector class initializes
// stackVector to be empty
template <typename T>
miniStack<T>::miniStack()
{}

// push item on the stack by inserting it at
// the rear of the vector
template <typename T>
void miniStack<T>::push(const T& item)
{
	stackVector.push_back(item);
}

// pop the stack by removing the item at
// the rear of the vector
template <typename T>
void miniStack<T>::pop()
{
	// check for an empty stack
	if (empty())
		throw underflowError("miniStack pop(): stack empty");

	// pop the stack
	stackVector.pop_back();
}

// the top of the stack is at the rear of the vector
template <typename T>
T& miniStack<T>::top()
{
	// check for an empty stack
	if (empty())
		throw underflowError("miniStack top(): stack empty");

	// return the element at the rear of the vector
	return stackVector.back();
}
  
// constant version of top()
template <typename T>
const T& miniStack<T>::top() const
{
	// check for an empty stack
	if (empty())
		throw underflowError("miniStack top(): stack empty");

	// return the element at the rear of the vector
	return stackVector.back();
}
  
template <typename T>
bool miniStack<T>::empty() const
{
	return stackVector.size() == 0;
}

template <typename T>
int miniStack<T>::size() const
{
	return stackVector.size();
}

#endif	// VECTOR_BASED_STACK_CLASS
