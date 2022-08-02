#ifndef ARRAY_BASED_QUEUE_CLASS
#define ARRAY_BASED_QUEUE_CLASS

#include "d_except.h"

using namespace std;

const int MAXQSIZE = 50;

template <typename T>
class bqueue
{
	public:
		bqueue();
			// constructor. create an empty queue with MAXQSIZE available slots
		
		void push(const T& item);
			// insert an element at the back of the queue.
			// Precondition: count < MAXQSIZE. throws exception
			// overflowError if the queue is full

		void pop();
			// remove an element from the front of the queue.
			// Precondition: the queue is not empty. throws exception
			// underflowError if the queue is empty

		T& front();
			// return the front of the queue.
			// Precondition: the queue is not empty. throw the underflowError
			// exception if the queue is empty
		const T& front() const;
			// constant version
                               
      int size() const;
			// return the queue size
		
		bool empty() const;
			// is the queue empty?

		bool full() const;
			// is the queue full?

    private:
		// array holding the queue elements
		T queueArray[MAXQSIZE];
		// index of the front and back of the queue
		int qfront, qback;
		// the number of elements in the queue, 0 <= count <= MAXQSIZE		
		int count;
};

template <typename T>
bqueue<T>::bqueue():
	qfront(0), qback(0), count(0)
{}

template <typename T>
void bqueue<T>::push(const T& item)
{
	// is the array filled up? if so, throw overflowError
	if (count == MAXQSIZE)
		throw overflowError("bqueue push(): queue full");

	// perform a circular queue insertion
	queueArray[qback] = item;
	qback = (qback+1) % MAXQSIZE;

	// increment the queue size
	count++;
}

template <typename T>
void bqueue<T>::pop()
{
	// if queue is empty, throw underflowError
	if (count == 0)
		throw underflowError("bqueue pop(): empty queue");

	// perform a circular queue deletion
	qfront = (qfront+1) % MAXQSIZE;

	// decrement the queue size
	count--;
}

template <typename T>
T& bqueue<T>::front()
{
	// if queue is empty, throw underflowError
	if (count == 0)
		throw underflowError("bqueue front(): empty queue");

	return queueArray[qfront];
}
          
template <typename T>
const T& bqueue<T>::front() const
{
	// if queue is empty, throw underflowError
	if (count == 0)
		throw underflowError("bqueue front(): empty queue");

	return queueArray[qfront];
}
          
template <typename T>
int bqueue<T>::size() const
{
	return count;
}

template <typename T>
bool bqueue<T>::empty() const
{
	return count == 0;
}

template <typename T>
bool bqueue<T>::full() const
{
	return count == MAXQSIZE;
}

#endif	// ARRAY_BASED_QUEUE_CLASS
