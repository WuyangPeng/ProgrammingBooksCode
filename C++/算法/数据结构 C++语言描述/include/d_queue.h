#ifndef QUEUE_CLASS
#define QUEUE_CLASS

#include <list>	// list class used by object composition

#include "d_except.h"

using namespace std;

// implements a queue
template <typename T>
class miniQueue
{
    public:
		miniQueue();
			// constructor; create an empty queue
		
		void push(const T& item);
			// insert an element at the back of the queue.
			// Postcondition: the queue has one more element

		void pop();
			// remove an element from the front of the queue.
			// Precondition: the queue is not empty. if the
			// queue is empty, the function throws the
			// underflowError exception
			// Postcondition: the queue has one less element

		T& front();
			// return a reference to the front of the queue.
			// Preconditon: the queue is not empty. if the
			// the queue is empty, the function throws the
			// underflowError exception
		const T& front() const;
			// constant version of front()
                
     int size() const;
			// return the queue size
		
		bool empty() const;
			// is the queue empty?

    private:
		list<T> qlist;
			// a list object maintains the queue items and size
};
  
// the constructor has nothing to do. the default
// constructor for the list class initializes
// qlist to be empty
template <typename T>
miniQueue<T>::miniQueue()
{}

// insert item into the queue by inserting it at
// the back of the list
template <typename T>
void miniQueue<T>::push(const T& item)
{
	qlist.push_back(item);
}

// remove the item at the front of the queue
// by erasing the front of the list
template <typename T>
void miniQueue<T>::pop()
{
	// if queue is empty, throw underflowError
	if (qlist.size() == 0)
		throw underflowError("miniQueue pop(): empty queue");

	// erase the front
	qlist.pop_front();
}

template <typename T>
T& miniQueue<T>::front()
{
	// if queue is empty, throw underflowError
	if (qlist.size() == 0)
		throw underflowError("miniQueue front(): empty queue");

	return qlist.front();
}
          
template <typename T>
const T& miniQueue<T>::front() const
{
	// if queue is empty, throw underflowError
	if (qlist.size() == 0)
		throw underflowError("miniQueue front(): empty queue");

	return qlist.front();
}
 template <typename T>
T& miniQueue<T>::back()
{
	// if queue is empty, throw underflowError
	if (qlist.size() == 0)
		throw underflowError("miniQueue back(): empty queue");

	return qlist.back();
}
          
template <typename T>
const T& miniQueue<T>::back() const
{
	// if queue is empty, throw underflowError
	if (qlist.size() == 0)
		throw underflowError("miniQueue back(): empty queue");

	return qlist.back();
}
          
// return the queue size
template <typename T>
int miniQueue<T>::size() const
{
	return qlist.size();
}

// is the queue empty?
template <typename T>
bool miniQueue<T>::empty() const
{
	return qlist.empty();
}

#endif	// QUEUE_CLASS
