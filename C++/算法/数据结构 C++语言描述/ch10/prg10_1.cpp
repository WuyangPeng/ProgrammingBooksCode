// File: prg10_1.cpp
// the program demonstrates the inorder and postorder
// recursive binary tree scanning algorithms and the
// iterative level-order scanning algorithm. using the
// function buildTree(), construct Tree 1 and call the
// tree output algorithms from the library "d_tlib.h".

#include <iostream>

#include "d_tnode.h"		// tnode class
#include "d_tnodel.h"	// tnode library

using namespace std;

int main()
{
	// root of the tree
	tnode<char> *root;

	// use the character Tree 1 
	root = buildTree(1);

	// give inorder scan of nodes  
	cout << "Inorder scan:      " ;
	inorderOutput(root);
	cout << endl;

	// give postorder scan of nodes   
	cout << "Postorder scan:    " ;
	postorderOutput(root);
	cout << endl;

	// give level order scan of nodes   
	cout << "Level-order scan:  " ;
	levelorderOutput(root);
	cout << endl;

	return 0;
}

/*
Run:

Inorder scan:      D  B  G  E  A  C  H  F  I
Postorder scan:    D  G  E  B  H  I  F  C  A
Level-order scan:  A  B  C  D  E  F  G  H  I
*/
