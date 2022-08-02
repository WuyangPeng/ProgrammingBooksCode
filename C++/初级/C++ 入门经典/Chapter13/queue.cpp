//DISPLAY 13.23 Implementation of the Queue Class
//This is the implementation file queue.cpp.
//This is the implementation of the class Queue.
//The interface for the class Queue is in the header file queue.h.
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include "queue.h"
using namespace std;

namespace queuesavitch
{
    //Uses cstddef:
    Queue::Queue( ) : front(NULL), back(NULL)
    {
        //Intentionally empty.
    }

    Queue::Queue(const Queue& aQueue)
          //The definition of the copy constructor is Self-Test Exercise 12.

    Queue::~Queue( )
          //The definition of the destructor is Self-Test Exercise 13.

    //Uses cstddef:
    bool Queue::empty( ) const
    {
        return (back == NULL);//front == NULL would also work
    }

    //Uses cstddef:
    void Queue::add(char item)
    {
        if (empty( ))
        {
            front = new QueueNode;
            front->data = item;
            front->link = NULL;
            back = front;
        }

        else
        {
            QueueNodePtr tempPtr;
            tempPtr = new QueueNode;

				tempPtr->data = item;
            tempPtr->link = NULL;
            back->link = tempPtr;
            back = tempPtr;
        }
    }

    //Uses cstdlib and iostream:
    char Queue::remove( )
    {
        if (empty( ))
        {
            cout << "Error: Removing an item from an empty queue.\n";
            exit(1);
        }

        char result = front->data;

        QueueNodePtr discard;
        discard = front;
        front = front->link;
        if (front == NULL) //if you removed the last node
            back = NULL;

        delete discard;

        return result;
    }
}//queuesavitch

