// (c) Bartosz Milewski 2000
#include "Tree.h"
#include <iostream>

double NumNode::Calc () const
{
	std::cout << "Numeric node " << _num << std::endl;
	return _num;
}

BinNode::~BinNode ()
{
	delete _pLeft;
	delete _pRight;
}

double AddNode::Calc () const
{
	std::cout << "Adding\n";
	return _pLeft->Calc () + _pRight->Calc ();
}

double MultNode::Calc () const
{
	std::cout << "Multiplying\n";
	return _pLeft->Calc () * _pRight->Calc ();
}

int main ()
{	
	// ( 20.0 + (-10.0) ) * 0.1
	Node * pNode1 = new NumNode (20.0);
	Node * pNode2 = new NumNode (-10.0);
	Node * pNode3 = new AddNode (pNode1, pNode2);
	Node * pNode4 = new NumNode (0.1);
	Node * pNode5 = new MultNode (pNode3, pNode4);
	std::cout << "Calculating the tree\n";
	// tell the root to calculate itself
	double x = pNode5->Calc ();
	std::cout << "Result: " << x << std::endl;
	delete pNode5; // and all children
}
