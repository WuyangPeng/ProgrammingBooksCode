#ifndef TREENODE
#define TREENODE

// represents a node in a binary tree
template <typename T>
class tnode
{
   public:
		// tnode is a class implementation structure. making the
		// data public simplifies building class functions
		T nodeValue;
		tnode<T> *left, *right;

		// default constructor. data not initialized
		tnode()
		{}

      // initialize the data members
		tnode (const T& item, tnode<T> *lptr = NULL, 
				 tnode<T> *rptr = NULL):
					nodeValue(item), left(lptr), right(rptr)
		{}
};

#endif	// TREENODE