#ifndef HUFFMAN
#define HUFFMAN

#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>

#include "d_bitvec.h"	// bitVector class

using namespace std;

// NIL represents an empty subtree
const short NIL = -1;

// node object for the Huffman tree that goes in the
// compressed file
class diskHuffNode
{
   public:
		// character stored
      unsigned char ch;

		// pointers (indices) of children
		short left;
      short right;

      diskHuffNode (unsigned char c = 0, short lptr = NIL, short rptr = NIL):
				ch(c), left(lptr), right(rptr)
		{}
};

// maximum size of the bit code for a character
const int MAXBITSIZE = 255;

// node used to construct the Huffman tree. the compress application
// builds a node with these attributes plus those of the base class
// diskHuffNode. the attributes in this class are not needed in
// the uncompress application
class huffNode: public diskHuffNode
{
	public:
		int freq;				// frequency of the character ch
		int index;				// my index in the tree
		int parent;				// my parent in the tree
		int numberOfBits;		// number of bits in Huffman code for ch
		bitVector bits;		// bit vector holding the code

      huffNode (unsigned char c = 0, short lptr = NIL, short rptr = NIL,
			       int f = 0, int indx = NIL, int p = 0,
					 int numBits = 0, int maxSizeOfBits = MAXBITSIZE):
				diskHuffNode(c, lptr, rptr), freq(f), index(indx),
				parent(p), numberOfBits(numBits), bits(maxSizeOfBits)
		{}

		// necessary to build the priority queue
		friend bool operator< (const huffNode& lhs, const huffNode& rhs)
		{
			return lhs.freq < rhs.freq;
		}
};


// output tree vertically
void displayHuffmanTree (const vector<huffNode>& tree);

// IMPLEMENTATION OF TREE DISPLAY

// record to hold the pointer value and x,y coordinates for a
// node used in displayHuffmanTree
class infoNode
{
	public:
		huffNode value;						// node value
		int xPosition;							// x position on the line
		int yLevel;								// level (line) position
		infoNode *left, *right;

		infoNode ()
		{}
};

infoNode *createInfoNode(const vector<huffNode>& tree, int i,
								 int& x, int y, int dataWidth)
{
	infoNode *newNode = NULL;
	int dx = dataWidth;

	if (i != NIL)
	{
		newNode = new infoNode;
		// allocate node for left child at next level in tree; attach node
		infoNode *newLeft = createInfoNode(tree, tree[i].left, x, y+1, dataWidth);
		newNode->left = newLeft;

		// initialize data members of new node
		newNode->value = tree[i];
		newNode->xPosition = x;
		newNode->yLevel = y;
		// update x to position dx characters to right of current position
		x+= dx;

		// allocate node for right child at next level in tree; attach node
		infoNode *newRight = createInfoNode(tree, tree[i].right, x, y+1, dataWidth);
		newNode->right = newRight;
	}
	return newNode;
}

// delete the shadow tree
void clearShadowTree(infoNode *t)
{
	if (t != NULL)
	{
		clearShadowTree(t->left);
		clearShadowTree(t->right);
		delete t;
	}
}

// output tree vertically
void displayHuffmanTree (const vector<huffNode>& tree)
{
	const int dataWidth = 7;
   // set xPosition as 1 and the level at 0
	int x = 1, y = 0;
	infoNode *root;
	// launch the inorder scan; root is the base of the shadow tree
	root = createInfoNode(tree, tree.size()-1, x, y, dataWidth);
	infoNode *currNode, *prevNode;
	huffNode h;

	// store siblings of each infoNode object in a queue so that
	// they are visited in order at the next level of the tree
   queue<infoNode *> q;

	// objects to maintain current print position on a line
	int i, currPosition = 0;

	cout.setf(ios::left,ios::adjustfield);

   // insert the root in the queue and initialize prevNode as root
   q.push(root);
	prevNode = root;

   // continue the iterative process until the queue is empty
   while(!q.empty())
   {
      // delete front node from queue and set as current node
      currNode = q.front();
		q.pop();

		// if current node on the next level, output newlines
		// reset currPosition (on line) back to 0
		if (prevNode->yLevel < currNode->yLevel)
		{
			cout << endl << endl;
			currPosition = 0;
		}

		// use spaces to scan from current position to x position of node
		for (i = currPosition; i < currNode->xPosition; i++)
			cout << " ";
		// output data value and update currPosition dataWidth chars
		h = currNode->value;
		if (h.left == NIL)
			if (h.ch >= ' ' && h.ch <= '~')
				cout << h.ch << ':' << setw(5) << h.freq;
			else
				cout << "x" << hex << setw(2) << int(h.ch)
					  << dec << ':' << setw(3) << h.freq;
		else
				cout << setw(7) << h.freq;
		currPosition = currNode->xPosition + dataWidth;
		// update prevNode for the next iteration
		prevNode = currNode;

		// if a left child exists, insert it in the queue
      if(currNode->left != NULL)
			q.push(currNode->left);
      // if a right child exists, insert next to its sibling
      if(currNode->right != NULL)
			q.push(currNode->right);
   }
	cout << endl;

	clearShadowTree(root);

	cout.setf(ios::right,ios::adjustfield);
}

#endif // HUFFMAN
