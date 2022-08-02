// File: prg9_2.cpp
// the program tests the linkedQueue class by pushing
// the values in an array onto a queue. by using front()
// followed by pop(), the programs displays the contents
// of the queue as it empties it. when the queue is empty,
// a call to pop() causes the underflowError exception.
// after catching the exception and displaying an error
// message, the program terminates 

#include <iostream>

#include "d_lqueue.h"

using namespace std;

int main()
{
	// declare an integer array and compute its size
	int arr[] = {6, 9, 2, 5}, i;
	int arrSize = sizeof(arr)/sizeof(int);

	// declare an empty queue of integer elements
	linkedQueue<int> q;

	// insert the array elements in q and output their value
	for (i = 0; i < arrSize; i++)
		q.push(arr[i]);

	// display the resulting size of the queue
	cout << "Queue size is " << q.size() << endl;

	// clear the queue
	while (!q.empty())
	{
		// display the element at the front and then
		// erase it from the queue
		cout << q.front() << "  ";
		q.pop();
	}
	cout << endl;

	// handle the underflowError exception thrown by a call to pop()
	try
	{
		q.pop();
	}
	catch (const underflowError& ue)
	{
		cout << ue.what() << endl;
	}

	return 0;
}

/*
Run:

Queue size is 4
6  9  2  5
queue pop(): empty queue
*/
