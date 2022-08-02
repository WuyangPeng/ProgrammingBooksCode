#include "d_tnodel.h"			// tnode library
#include "d_tdraw.h"

using namespace std;

int main()
{
	// declare a character tree
	tnode<char> *root;
	tnode<string> *strroot, *b, *c, *d, *e, *f;
	int i;

	for (i=0;i <= 2;i++)
	{
		root = buildTree(i);
		// each node requires one character
		drawTree(root,1);

		// delete the tree
		clearTree(root);
	}

	f = new tnode<string> ("Dolan");
	e = new tnode<string> ("Wren");
	d = new tnode<string> ("Gates");
	c = new tnode<string> ("Smith",e, f);
	b = new tnode<string> ("Brand",(tnode<string> *)NULL, d);
	strroot = new tnode<string> ("Daly",b, c);
	drawTree(strroot,5);

	return 0;
}
