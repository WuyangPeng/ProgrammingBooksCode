// File: prg10_3.cpp
// the program builds the sample Tree 2 and displays the tree.
// by using copyTree(), the program makes a copy of Tree 2,and
// displays the copied tree. the program terminates after using
// clearTree() to delete the nodes in both trees

#include <iostream>

#include "d_tnode.h"		// tnode class
#include "d_tnodel.h"	// tnode library

using namespace std;

int main()
{
	// roots for two trees
	tnode<char> *root1, *root2;

	// build the character Tree 2 with root root2
	root1 = buildTree(2);

	// display the tree
	cout << "Original tree (Tree 2)" << endl;
	displayTree(root1, 1);
	cout << endl << endl;

	// make a copy of root1 so its root is root2
	root2 = copyTree(root1);

	// display the tree copy
	cout << "Copy of Tree 2" << endl;
	displayTree(root2, 1);
	cout << endl;

	// delete the nodes in the two trees
	clearTree(root1);
	clearTree(root2);

	return 0;
}

/*
Run:

Original tree (Tree 2)
       A
     B         C
 D         E     F
   G     H   I


Copy of Tree 2
       A
     B         C
 D         E     F
   G     H   I
*/
