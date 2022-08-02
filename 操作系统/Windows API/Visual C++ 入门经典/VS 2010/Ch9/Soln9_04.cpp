// Soln 9_04.cpp
// The rand_s() function generates random integers from 0 to UINT_MAX
// To use rand_s function you must first define _CRT_RAND_S

#define _CRT_RAND_S             // For secure random number generator
#include <iostream>
#include <iomanip>
#include <cstdlib>              // For rand_s function

using std::cout;
using std::endl;
using std::setw;

class CBinaryTree
{
private:
  class CNode
  {
  public:
    // Node constructor
    CNode(int n) : value(n), m_pLeft(nullptr), m_pRight(nullptr) {}
	~CNode()
	{
		if(m_pLeft)
			delete m_pLeft;                   // This will call the destructor for the left node
		if(m_pRight)
			delete m_pRight;                  // This will call the destructor for the right node
	}

    // List the node values in order
    void listNode()
    {

      if(m_pLeft)                      // If there's a left node
        m_pLeft->listNode();           // Output its value

      cout << setw(12) << value;       // Output the current node value
      if(++listCount % 5 == 0)
        cout << endl;

      if(m_pRight)                     // If there's a right node
        m_pRight->listNode();          // Output its value
    }

    int value;                         // Value of the node
    CNode* m_pLeft;                    // Pointer to left node
    CNode* m_pRight;                   // Pointer to right node
    static int listCount;              // Count of number of output values
  };

public:
  CBinaryTree() : m_pRoot(nullptr){}   // Constructor
  ~CBinaryTree()                       // Destructor              
  {
	if(m_pRoot)
      delete m_pRoot;  
  }

  void add(int n);                     // Adds a value to the tree
  void add(int n, CNode* pNode);       // Adds n relative to pNode node

  // List the nodes in sequences
  void listNodes()
  {
    CNode::listCount = 0;
    if(!m_pRoot)
      cout << "Binary tree is empty." << endl;
    else 
      m_pRoot->listNode();
  }

private:
   CNode* m_pRoot;                     // Pointer to the roor node
};

int CBinaryTree::CNode::listCount = 0; // Initialize static member

// Add a value to the tree
void CBinaryTree::add(int n)
{
  if(!m_pRoot)                         // If there's no root node
    m_pRoot = new CNode(n);            // the new node is the root
  else                                 // otherwise
    add(n, m_pRoot);                   // add the node (recursive)
}

// Add a value relative to a given node
void CBinaryTree::add(int n, CNode* pNode)
{
  if(n == pNode->value)                // If value equals current node
  { // Always add equal values as left node
    CNode* pNewNode = new CNode(n);    // Create the new node for the value
    CNode* pTemp = pNode->m_pLeft;     // Save left ptr for current node
    pNode->m_pLeft = pNewNode;         // then make it point to new node
    pNewNode->m_pLeft = pTemp;         // Left ptr for new node point to old left node
  }
  else if(n > pNode->value)            // If new value is greater than right node value
  {                                    // it must go to the right
    if(!pNode->m_pRight)               // so if there's no right node
      pNode->m_pRight = new CNode(n);  // make the new node the right node
    else                               // Otherwise
      add(n, pNode->m_pRight);         // add it relative to right node(recursive)
  }
  else                                 // New number is less than current node value
  {
    if(!pNode->m_pLeft)                // so if there's no left node
      pNode->m_pLeft = new CNode(n);   // make the new node the left node
    else                               // Otherwise
      add(n, pNode->m_pLeft);          // add it relative to the left node(recursive)
  }
}


int main()
{
  CBinaryTree tree;                    // Create a binary tree
  unsigned int number = 0;             // Stores a number to be added to the tree

  cout << "Random values inserted in the tree are:" << endl;

  // Add 100 random number to the tree in the range from 1 to 1,000,000
  double max = 1000000.0;
  for(int i = 0 ; i<100 ; i++)
  {
    if(rand_s(&number) != 0)
      cout << "Random number generator failed!" << endl;

    // Change the range from (0 to UINTMAX) to (1 to max)
    number = static_cast<unsigned int>(static_cast<double>(number)/UINT_MAX*max)+1;

    tree.add(number);
    cout << setw(12) << number;
    if((i+1) % 5 == 0)
      cout << endl;
  }
  cout << endl << "Output from the tree is:" << endl;
  tree.listNodes();

   return 0;
}
