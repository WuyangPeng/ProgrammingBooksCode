#include <string>
#include "d_stree.h"			// stree class

using namespace std;

int main()
{
	string str = "globe";
	string list[] = {"Dolan", "Wren", "Gates", "Smith", "Brand"}; 

	// declare a character tree
	stree<char> charTree;
	int i;

	for (i=0; i < str.length(); i++)
	{
		charTree.insert(str[i]);

		// display tree after each insert
		charTree.drawTrees(1);
	}

	stree<string> strTree(list, list+5);
	strTree.drawTree(5);

	return 0;
}
