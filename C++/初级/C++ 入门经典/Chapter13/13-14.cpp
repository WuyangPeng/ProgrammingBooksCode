//DISPLAY 13.14 Implementation File for a Node Class
// This is the implementation file Node.cpp.
// It implements logic for the Node class.  The interface
// file is in the header file Node.h
#include <iostream>
#include "Node.h"

namespace linkedlistofclasses
{
	Node::Node( ) : data(0), link(NULL)
	{
	// deliberately empty
	}

	Node::Node(int value, Node *next) : data(value), link(next)
	{
	// deliberately empty
	}

	// Accessor and Mutator methods follow

	int Node::getData( ) const
	{
	return data;
	}

	Node* Node::getLink( ) const
	{
	return link;
	}

	void Node::setData(int value)
	{
	data = value;
	}

	void Node::setLink(Node *next)
	{
	link = next;
	}
}  // linkedlistofclasses
// Node.cpp

