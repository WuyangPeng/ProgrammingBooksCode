//DISPLAY 13.4 Function to Add a Node at the Head of a Linked List
//Function Declaration
struct Node
{
    int data;
    Node *link;
};

typedef Node* NodePtr;

void headInsert(NodePtr& head, int theNumber);
//Precondition: The pointer variable head points to
//the head of a linked list.
//Postcondition: A new node containing theNumber
//has been added at the head of the linked list.
Function Definition
void headInsert(NodePtr& head, int theNumber)
{
    NodePtr tempPtr;
    tempPtr = new Node;

    tempPtr->data = theNumber;

    tempPtr->link = head;
    head = tempPtr;
}


