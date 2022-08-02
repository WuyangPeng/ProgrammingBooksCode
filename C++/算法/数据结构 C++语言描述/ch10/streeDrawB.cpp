#include <iostream>

#include "d_stree.h"		// stree class

using namespace std;

int main()
{
	int list[] = {50, 30, 75, 55, 60, 25, 52, 37, 53, 62, 10, 85, 33};

	stree<int> tree;

	int i;

	for (i = 0; i < 13; i++)
	{
		tree.insert(list[i]);
		tree.drawTrees(2);
	}

	tree.erase(60);
	tree.drawTrees(2);

	tree.erase(30);
	tree.drawTrees(2);

	tree.erase(50);
	tree.drawTree(2);

	return 0;
}

