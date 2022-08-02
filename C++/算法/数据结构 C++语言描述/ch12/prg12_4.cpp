// File: prg12_4.cpp
// the program creates a red-black tree whose elements come from
// the integer array arr. a call to writeContainer() from
// "d_util.h" displays the tree data in ascending order. the
// program calls the displayTree() function from the rbtree
// class to output the tree and then inserts the values 7 and
// 75 into the tree. after each insertion, displayTree() is
// called to display the tree structure. the program concludes
// by deleting 35 (tree root) and displaying the final tree

#include <iostream>

#include "d_rbtree.h"
//#include "d_util.h"

using namespace std;

int main()
{
	// initial red-black tree data
	int arr[] = {23, 35, 55, 17, 8, 67};
	int arrSize = sizeof(arr)/sizeof(int);
	rbtree<int> t(arr, arr+arrSize);

	// display the elements in order
	cout << "Listing of elements: ";
	//writeContainer(t.begin(), t.end());
	cout << endl << endl;

	// display the initial tree
	t.displayTree(3);
	cout << endl;

	// insert operations add 7 and 75
	t.insert(7);
	cout << "Insert 7" << endl;
	t.displayTree(3);
	cout << endl << endl;

	t.insert(75);
	cout << "Insert 75" << endl;
	t.displayTree(3);
	cout << endl << endl;

	// erase the root 35
	t.erase(35);
	cout << "Erase 35" << endl;
	t.displayTree(3);
	cout << endl;

	return 0;
}

/*
Run:

Listing of elements: 8  17  23  35  55  67

              35
      17          55
  8*     23*         67*

Insert 7
                  35
         17*          55
       8      23         67*
  7*


Insert 75
                  35
         17*              67
       8      23     55*     75*
  7*


Erase 35
                  55
         17*          67
       8      23         75*
  7*

*/
