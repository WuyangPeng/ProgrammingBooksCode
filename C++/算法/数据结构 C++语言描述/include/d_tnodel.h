#ifndef TREE_LIBRARY_FUNCTIONS
#define TREE_LIBRARY_FUNCTIONS

#include <iostream>
#include <strstream>
#include <iomanip>
#include <string>
#include <queue>

#ifndef NULL
#include <cstddef>
#endif  // NULL

#include "d_tnode.h"		// use tnode class

using namespace std;

// objects hold a formatted label string and the level,column
// coordinates for a shadow tree node
class tnodeShadow
{
	public:
		string nodeValueStr;	// formatted node value
		int level,column;
		tnodeShadow *left, *right;

		tnodeShadow ()
		{}
};

// create one of three binary trees with character data.
// the argument n selects from tree 0 - tree 2
tnode<char> *buildTree(int n);

// inorder recursive output of the nodes in a binary tree.
// output separator after each node value. default value
// of separator is "  "
template <typename T>
void inorderOutput(tnode<T> *t, const string& separator);

// postorder recursive output of the nodes in a binary tree.
// output separator after each node value. default value
// of separator is "  "
template <typename T>
void postorderOutput(tnode<T> *t, const string& separator);

// traverse the tree level by level and output each node in a
// binary tree. output separator after each node value. default value
// of separator is "  "
template <typename T>
void levelorderOutput(tnode<T> *t, const string& separator);

// accumulate the number of leaf nodes in count
template <typename T>
void countLeaf(tnode<T> *t, int& count);

// return the depth of the binary tree
template <typename T>
int depth (tnode<T> *t);

// create copy of tree t and return a pointer to the new root
template <typename T>
tnode<T> *copyTree(tnode<T> *t);

// traverse the nodes in the binary tree and delete each node
template <typename T>
void deleteTree(tnode<T> *t);

// delete all tree nodes using deleteTree() and then assign
// t to be NULL
template <typename T>
void clearTree(tnode<T> * & t);

// recursive inorder scan used to build the shadow tree
template <typename T>
tnodeShadow *buildShadowTree(tnode<T> *t, int level, int& column);

// display a binary tree. output of a node value requires
// no more than maxCharacters
template <typename T>
void displayTree(tnode<T> *t, int maxCharacters);

// delete the nodes in the shadow tree
void deleteShadowTree(tnodeShadow *t);

tnode<char> *buildTree(int n)
{
	// 9 tnode pointers; points to the 9 items in the tree
	tnode<char> *root, *b, *c, *d, *e, *f, *g, *h, *i;

	// parameter n specifies a tree in the range 0 - 2
	switch(n)
	{
		// nodes d and e are leaf nodes
		case 0:
			d = new tnode<char> ('D');
			e = new tnode<char> ('E');
			b = new tnode<char> ('B',(tnode<char> *)NULL, d);
			c = new tnode<char> ('C',e, (tnode<char> *)NULL);
			root = new tnode<char> ('A',b, c);
			break;

		// nodes g, h, i, and d are leaf nodes
		case 1:
			g = new tnode<char> ('G');
			h = new tnode<char> ('H');
			i = new tnode<char> ('I');
			d = new tnode<char> ('D');
			e = new tnode<char> ('E',g, (tnode<char> *)NULL);
			f = new tnode<char> ('F',h, i);
			b = new tnode<char> ('B',d, e);
			c = new tnode<char> ('C',(tnode<char> *)NULL, f);
			root = new tnode<char> ('A',b, c);
			break;

		// nodes g, h, i and f are leaf nodes
		case 2:
			g = new tnode<char> ('G');
			h = new tnode<char> ('H');
			i = new tnode<char> ('I');
			d = new tnode<char> ('D',(tnode<char> *)NULL, g);
			e = new tnode<char> ('E',h, i);
			f = new tnode<char> ('F');
			b = new tnode<char> ('B',d, (tnode<char> *)NULL);
			c = new tnode<char> ('C',e, f);
			root = new tnode<char> ('A',b, c);
			break;
	}

	return root;
}

template <typename T>
void inorderOutput(tnode<T> *t, const string& separator = "  ")
{
   // the recursive scan terminates on a empty subtree
   if (t != NULL)
   {
      inorderOutput(t->left, separator);	// descend left
      cout << t->nodeValue << separator;	// output the node
      inorderOutput(t->right, separator);	// descend right
   }
}

template <typename T>
void postorderOutput(tnode<T> *t, const string& separator = "  ")
{
   // the recursive scan terminates on a empty subtree
   if (t != NULL)
   {
      postorderOutput(t->left, separator);	// descend left
      postorderOutput(t->right, separator);	// descend right
      cout << t->nodeValue << separator;			// output the node
   }
}

template <typename T>
void levelorderOutput(tnode<T> *t, const string& separator = "  ")
{
   // store siblings of each node in a queue so that they are
   // visited in order at the next level of the tree
   queue<tnode<T> *> q;
   tnode<T> *p;

   // initialize the queue by inserting the root in the queue
   q.push(t);

   // continue the iterative process until the queue is empty
   while(!q.empty())
   {
      // delete front node from queue and output the node value
      p = q.front();
		q.pop();
      cout << p->nodeValue << separator;

		// if a left child exists, insert it in the queue
      if(p->left != NULL)
			q.push(p->left);
      // if a right child exists, insert next to its sibling
      if(p->right != NULL)
			q.push(p->right);
   }
}

// assume that count initialized to 0
template <typename T>
void countLeaf (tnode<T> *t, int& count)
{
   if (t != NULL)
   {
      // check if t is a leaf node (no children).
      // if so, increment count
      if (t->left == NULL && t->right == NULL)
         count++;

		countLeaf(t->left, count);		// descend left
		countLeaf(t->right, count);	// descend right
   }
}

// determine the depth of the tree using a postorder scan
template <typename T>
int depth (tnode<T> *t)
{
   int depthLeft, depthRight, depthval;

   if (t == NULL)
		// depth of an empty tree is -1
	  depthval = -1;
   else
	{
		// find the depth of the left subtree of t
		depthLeft= depth(t->left);
		// find the depth of the right subtree of t
		depthRight= depth(t->right);
		// depth of the tree with root t is 1 + maximum
		// of the depths of the two subtrees
		depthval = 1 +
			(depthLeft > depthRight ? depthLeft : depthRight);
   }

	return depthval;
}

template <typename T>
tnode<T> *copyTree(tnode<T> *t)
{
   // newNode points at a new node that the algorithm
	// creates. newLptr. and newRptr point to the subtrees
	// of newNode
   tnode<T> *newLeft, *newRight, *newNode;

   // stop the recursive scan when we arrive at empty tree
   if (t == NULL)
      return NULL;

   // build the new tree from the bottom up by building the two
   // subtrees and then building the parent. at node t, make
	// a copy of the left subtree and assign its root node pointer
	// to newLeft. make a copy of the right subtree and assign its
	// root node pointer to newRight
	newLeft = copyTree(t->left);
	newRight = copyTree(t->right);

   // create a new node whose value is the same as the value in t
	// and whose children are the copied subtrees
   newNode = new tnode<T> (t->nodeValue, newLeft, newRight);

   // return a pointer to the root of the newly copied tree
   return newNode;
}

template <typename T>
void deleteTree(tnode<T> *t)
{
	// postorder scan. delete left and right
	// subtrees of t and then node t
   if (t != NULL)
   {
      deleteTree(t->left);
      deleteTree(t->right);
      delete t;
   }
}

template <typename T>
void clearTree(tnode<T> * & t)
{
	deleteTree(t);
	t = NULL;
}

template <typename T>
tnodeShadow *buildShadowTree(tnode<T> *t, int level, int& column)
{
	// pointer to new shadow tree node
	tnodeShadow *newNode = NULL;
	// text and ostr used to perform format conversion
	char text[80];
	ostrstream ostr(text,80);

	if (t != NULL)
	{
		// create the new shadow tree node
		newNode = new tnodeShadow;

		// allocate node for left child at next level in tree; attach node
		tnodeShadow *newLeft = buildShadowTree(t->left, level+1, column);
		newNode->left = newLeft;

		// initialize data members of the new node
		ostr << t->nodeValue << ends;	// format conversion
		newNode->nodeValueStr = text;
		newNode->level = level;
		newNode->column = column;

		// update column to next cell in the table
		column++;

		// allocate node for right child at next level in tree; attach node
		tnodeShadow *newRight = buildShadowTree(t->right, level+1, column);
		newNode->right = newRight;
	}

	return newNode;
}

template <typename T>
void displayTree(tnode<T> *t, int maxCharacters)
{
	string label;
	int level = 0, column = 0;
	int colWidth = maxCharacters + 1;
	//
	int currLevel = 0, currCol = 0;

	if (t == NULL)
		return;

	// build the shadow tree
	tnodeShadow *shadowRoot = buildShadowTree(t, level, column);

	// use during the level order scan of the shadow tree
	tnodeShadow *currNode;

   // store siblings of each tnodeShadow object in a queue so that
	// they are visited in order at the next level of the tree
   queue<tnodeShadow *> q;

   // insert the root in the queue and set current level to 0
   q.push(shadowRoot);

   // continue the iterative process until the queue is empty
   while(!q.empty())
   {
      // delete front node from queue and make it the current node
      currNode = q.front();
		q.pop();

		// if level changes, output a newline
		if (currNode->level > currLevel)
		{
			currLevel = currNode->level;
			currCol = 0;
			cout << endl;
		}

		// if a left child exists, insert the child in the queue
      if(currNode->left != NULL)
			q.push(currNode->left);

		// if a right child exists, insert the child in the queue
      if(currNode->right != NULL)
			q.push(currNode->right);

		// output formatted node label
		if (currNode->column > currCol)
		{
			cout << setw((currNode->column-currCol)*colWidth) << " ";
			currCol = currNode->column;
		}
		cout << setw(colWidth) << currNode->nodeValueStr;
		currCol++;
   }
	cout << endl;

	// delete the shadow tree
	deleteShadowTree(shadowRoot);
}

void deleteShadowTree(tnodeShadow *t)
{
	// if current root node is not NULL, delete its left subtree,
	// its right subtree and then the node itself
	if (t != NULL)
	{
		deleteShadowTree(t->left);
		deleteShadowTree(t->right);
		delete t;
	}
}

#endif   // TREE_LIBRARY_FUNCTIONS

