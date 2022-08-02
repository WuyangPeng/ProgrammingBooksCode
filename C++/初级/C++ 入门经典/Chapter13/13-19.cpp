//DISPLAY 13.19 Implementation of the Stack Class
//This is the implementation file stack.cpp.
//This is the implementation of the class Stack.
//The interface for the class Stack is in the header file stack.h.
#include <iostream>
#include <cstddef>
#include "stack.h"
using namespace std;

namespace stacksavitch
{
    //Uses cstddef:
    Stack::Stack( ) : top(NULL)
    {
        //Body intentionally empty.
    }

    Stack::Stack(const Stack& aStack)
         //The definition of the copy constructor is Self-Test Exercise 11.
    Stack::~Stack( )
    {
        char next;
        while (! empty( ))
           next = pop( );//pop calls delete.
    }


    //Uses cstddef:
    bool Stack::empty( ) const
    {
        return (top == NULL);
    }


    void Stack::push(char theSymbol)
    //The rest of the definition is Self-Test Exercise 10.
    
    //Uses iostream and cstdlib:
    char Stack::pop( )
    {
        if (empty( ))
        {
            cout << "Error: popping an empty stack.\n";
			exit(1);
        }

        char result = top->data;

        StackFramePtr temp_ptr;
        temp_ptr = top;
        top = top->link;

        delete temp_ptr;

        return result;
    }
}//stacksavitch
