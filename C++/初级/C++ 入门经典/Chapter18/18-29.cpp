// Linked list of a simple Node class using traditional pointers.
// Note that this version has a memory leak when execution returns to
// main.
#include <iostream>

using std::cout;
using std::endl;

// A simple Node class. A full-featured class would have
// several more functions.
class Node
{
private:
	int num;
	Node *next;
public:
	Node();
	~Node();
	Node(int num, Node *nextPtr);
	int getNum();
	Node* getNext();
	void setNext(Node *nextPtr);
};

Node::Node() : num(0), next(nullptr)
{ }

Node::Node(int numVal, Node *nextPtr) : num(numVal), next(nextPtr)
{ }

Node::~Node()
{
	cout << "Deleting " << num << endl;
}

int Node::getNum()
{
	return num;
}

Node* Node::getNext()
{
	return next;
}

void Node::setNext(Node *nextPtr)
{
	next = nextPtr;
}

void listTest()
{
	// Create a linked list with 10->20->30
	Node *root = new Node(10, nullptr);
	root->setNext(new Node(20, nullptr));
	root->getNext()->setNext(new Node(30, nullptr));

	// Output the list
	Node *temp;
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
}
