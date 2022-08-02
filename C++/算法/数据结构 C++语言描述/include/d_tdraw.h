#ifndef TREE_DRAW_FUNCTION
#define TREE_DRAW_FUNCTION

#include <iostream>
#include <strstream>
#include <string>
#include <queue>

#include "d_tnode.h"		// use tnode class
#include "d_circsh.h"	// for drawing a node
#include "d_linesh.h"	// for drawing an edge
#include "d_textsh.h"	// for drawing the node value

using namespace std;


class stnodeShadow;

// recursive function that builds a subtree of the shadow tree,
// rooted at node t of the tree we are drawing. level is the
// level-coordinate for the root of the subtree, and column is the
// changing column-coordinate of the tree nodes
template <typename T>
stnodeShadow *buildShadowTreeD(tnode<T> *t, int level, int& column);

// draw the tree. maxCharacters is maximum number of characters
// it takes to display the data in a node
template <typename T>
void drawTree (tnode<T> *t, int maxCharacters);

// objects hold a formatted label string and the level,column
// coordinates for a shadow tree node
class stnodeShadow
{
	public:
		string nodeValueStr;	// formatted node value
		int level,column;
		stnodeShadow *left, *right;

		stnodeShadow ()
		{}
};

// recursive inorder scan used to build the shadow tree
template <typename T>
stnodeShadow *buildShadowTreeD(tnode<T> *t, int level, int& column)
{
	// pointer to new shadow tree node
	stnodeShadow *newNode = NULL;
	// text and ostr used to perform format conversion
	char text[80];
	ostrstream ostr(text,80);

	if (t != NULL)
	{
		// create the new shadow tree node
		newNode = new stnodeShadow;

		// allocate node for left child at next level in tree; attach node
		stnodeShadow *newLeft = buildShadowTreeD(t->left, level+1, column);
		newNode->left = newLeft;

		// initialize data members of the new node
		ostr << t->nodeValue << ends;	// format conversion
		newNode->nodeValueStr = text;
		newNode->level = level;
		newNode->column = column;

		// update column to next cell in the table
		column++;

		// allocate node for right child at next level in tree; attach node
		stnodeShadow *newRight = buildShadowTreeD(t->right, level+1, column);
		newNode->right = newRight;
	}

	return newNode;
}

template <typename T>
void drawTree(tnode<T> *t, int maxCharacters)
{
	// approximate width of a character drawn by textShape
	const double UNITS_PER_CHAR = .15;

	// estimated width of a formatted node value.
	// add .2 to allow space outside the label
	double cellSide = maxCharacters*UNITS_PER_CHAR + 0.2;

	string label;

	int level = 0, column = 0;

	// build the shadow tree
	stnodeShadow *root = buildShadowTreeD(t, level, column);

	// use during the level order scan of the shadow tree
	stnodeShadow *currNode;

	// node draws the circle shape that represents a node.
	// the radius is (cellSide + .20)/2.0
	circleShape node(0,0,cellSide/2.0, lightblue);

	// text draws the formatted value in a node
	textShape text(0,0,"",darkgray);

	// edge draws edges in the tree
	lineShape edge(0,0,0,0,black);

	// x, y coordinates of a circle center on the screen
	double x, childx, y, childy;

	// open the drawing window
	openWindow();

   // store siblings of each stnodeShadow object in a queue so that
	// they are visited in order at the next level of the tree
   queue<stnodeShadow *> q;

   // insert the root in the queue
   q.push(root);

   // continue the iterative process until the queue is empty
   while(!q.empty())
   {
		// delete front node from queue and make it the current node
		currNode = q.front();
		q.pop();

		// assign formatted node label to string label
		label = currNode->nodeValueStr;

		// convert each (level, column) coordinate into screen
		// coordinates for the center of the node. add .1 so
		// we stay away from the edges of the screen
		x = currNode->column * cellSide + cellSide/2.0 + 0.1;
		y = currNode->level * cellSide + cellSide/2.0 + 0.1;

		// if a left child exists, draw an edge from the current
		// node center to the child node center. insert the child
		// in the queue
		if(currNode->left != NULL)
		{
			edge.move(x, y);
			// compute the center of the left child node
			childx = currNode->left->column * cellSide + cellSide/2.0 + 0.1;
			childy = currNode->left->level * cellSide + cellSide/2.0 + 0.1;
			edge.setEndPoint(childx, childy);
			edge.draw();
			q.push(currNode->left);
		}

		// if a right child exists, draw an edge from the current
		// node center to the child node center. insert the child
		// in the queue
      if(currNode->right != NULL)
		{
			edge.move(x, y);
			// compute the center of the right child node
			childx = currNode->right->column * cellSide + cellSide/2.0 + 0.1;
			childy = currNode->right->level * cellSide + cellSide/2.0 + 0.1;
			edge.setEndPoint(childx, childy);
			edge.draw();
			q.push(currNode->right);
		}

		// draw the current node
		node.move(x,y);
		node.draw();
		// draw the node data. use an appropriate offset from the node
		// center so the text is approximately aligned in the node
		text.move(x - label.length() * UNITS_PER_CHAR /2.0,
					 y - UNITS_PER_CHAR);
		text.setText(label);
		text.draw();
   }

	// pause to view the tree
	viewWindow();
	// done
	closeWindow();
}

#endif  // TREE_DRAW_FUNCTION
