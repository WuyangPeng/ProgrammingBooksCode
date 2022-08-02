//DISPLAY 13.9 Function to Add a Node in the Middle of a Linked List
//Function Declaration
struct Node
{
    int data;
    Node *link;
};

typedef Node* NodePtr;

void insert(NodePtr afterMe, int theNumber);
//Precondition: afterMe points to a node in a linked
//list.
//Postcondition: A new node containing theNumber
//has been added after the node pointed to by afterMe.
//Function Definition
void insert(NodePtr afterMe, int theNumber)
{
    NodePtr tempPtr;
    tempPtr = new Node;

    tempPtr->data = theNumber;

    tempPtr->link = afterMe->link;
    afterMe->link = tempPtr;
}
