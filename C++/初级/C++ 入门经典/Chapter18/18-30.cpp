// Linked list of a simple Node class using smart pointers.
// There is no memory leak since ths shared_ptr class
// handles reference counting and memory deallocation.
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::shared_ptr;

// Class modified to use shared_ptr of Nodes.
class Node
{
private:
	int num;
	shared_ptr<Node> next;
public:
	Node();
	~Node();
	Node(int num, shared_ptr<Node> nextPtr);
	int getNum();
	shared_ptr<Node> getNext();
	void setNext(shared_ptr<Node> nextPtr);
};

Node::Node() : num(0), next(nullptr)
{ }

Node::~Node()
{
	cout << "Deleting " << num << endl;
}

Node::Node(int numVal, shared_ptr<Node> nextPtr) : num(numVal), next(nextPtr)
{ }

int Node::getNum()
{
	return num;
}

shared_ptr<Node> Node::getNext()
{
	return next;
}

void Node::setNext(shared_ptr<Node> nextPtr)
{
	next = nextPtr;
}

void listTest()
{
	shared_ptr<Node> root(new Node(10, nullptr));
	shared_ptr<Node> next1(new Node(20, nullptr));
	shared_ptr<Node> next2;
	// After a shared_ptr is declared we can set it
	// using the reset function
	next2.reset(new Node(30, nullptr));
	// Link the nodes together
	root->setNext(next1);
	next1->setNext(next2);

	// Output the list
	shared_ptr<Node> temp;
	temp = root;
	while (temp != nullptr)
	{
		cout << temp->getNum() << endl;
		temp = temp->getNext();
	}
}

int main()
{
	listTest();
	cout << "Exiting program." << endl;
}
