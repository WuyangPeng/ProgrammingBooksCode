#if !defined (TREE_H)
#define TREE_H

#include "FunTab.h"
#include "AutoVector.h"
#include <vector>
#include <memory>
#include <cassert>
class Store;

class Node
{
public:
	virtual ~Node () {}
	virtual double Calc () const = 0;
	virtual bool IsLvalue () const { return false; }
	virtual void Assign (double) 
	{
		assert (!"Assign called incorrectly");
	}
};

class NumNode: public Node
{
public:
	NumNode (double num) : _num (num ) {}
	double Calc () const;
private:
	const double _num;
};

class VarNode: public Node
{
public:
	VarNode (std::size_t id, Store & store)
		: _id (id), _store (store) {}
	double Calc () const;
	bool IsLvalue () const;
	void Assign (double val);
private:
	const std::size_t _id;
	Store & _store;
};

class UniNode: public Node
{
public:
	UniNode (std::auto_ptr<Node> & pChild)
		: _pChild (pChild) // <- "transfer" constructor
	{}
protected:
	std::auto_ptr<Node> _pChild;
};

class BinNode: public Node
{
public:
	BinNode (std::auto_ptr<Node> & pLeft, 
			 std::auto_ptr<Node> & pRight)
		: _pLeft (pLeft), _pRight (pRight)
	{}
protected: 
	std::auto_ptr<Node> _pLeft;
	std::auto_ptr<Node> _pRight;
};

// Generic multiple node: an abstract class 
class MultiNode: public Node
{
public:
	MultiNode (std::auto_ptr<Node> & pNode)
	{
		AddChild (pNode, true);
	}
	void AddChild (std::auto_ptr<Node> & pNode, bool isPositive)
	{
		_aChild.push_back (pNode);
		_aIsPositive.push_back (isPositive);
	}
protected: 
	auto_vector<Node>  _aChild;
	std::vector<bool>  _aIsPositive;
};

// Summing
class SumNode: public MultiNode
{
public:
	SumNode (std::auto_ptr<Node> & pNode)
		: MultiNode (pNode) {}
	double Calc () const;
};

// Multiplying and dividing.
// Sign in this case refers to
// the exponent: positive means multiply,
// negative means divide
class ProductNode: public MultiNode
{
public:
	ProductNode (std::auto_ptr<Node> pNode)
		: MultiNode (pNode) {}
	double Calc () const;
};

class AssignNode : public BinNode
{
public:
	AssignNode (std::auto_ptr<Node> & pLeft, 
				std::auto_ptr<Node> & pRight)
		: BinNode (pLeft, pRight)
	{
		assert (_pLeft->IsLvalue ());
	}
	double Calc () const;
};

class FunNode: public UniNode
{
public:
	FunNode (PtrFun pFun, std::auto_ptr<Node> & pNode)
		: UniNode (pNode), _pFun (pFun)
	{}
	double Calc () const;
private:
	PtrFun       _pFun;
};

class UMinusNode: public UniNode
{
public:
	UMinusNode (std::auto_ptr<Node> & pNode)
		: UniNode (pNode)
	{}

	double Calc () const;
};

#endif
