#include "Nodes.h"
// (c) Bartosz Milewski 2000
#include "Store.h"
#include "Output.h"
#include <cmath>

double NumNode::Calc () const
{
	return _num;
}

double SumNode::Calc () const
{
	double sum = 0.0;
	auto_vector<Node>::const_iterator childIt =
			_aChild.begin ();
	std::vector<bool>::const_iterator isPosIt =
			_aIsPositive.begin ();
	for (; childIt != _aChild.end (); ++childIt, ++isPosIt)
	{
		assert (isPosIt != _aIsPositive.end ());
		double val = childIt->Calc ();
		if (*isPosIt)
			sum += val;
		else
			sum -= val;
	}
	assert (isPosIt == _aIsPositive.end ());
	return sum;
}

// Notice: the calculation is left associative
double ProductNode::Calc () const
{
	double prod = 1.0;
	for (std::size_t i = 0; i < _aChild.size (); ++i)
	{
		double val = _aChild [i]->Calc ();
		if (_aIsPositive [i])
			prod *= val;
		else if (val != 0.0)
			prod /= val;
		else
		{
            TheOutput.Error ("Division by zero");
			return HUGE_VAL;
		}
	}
	return prod;
}

double FunNode::Calc () const
{
	assert (_pFun != 0);
	return (*_pFun)(_pChild->Calc ());
}

double UMinusNode::Calc () const
{
	return - _pChild->Calc ();
}

double AssignNode::Calc () const
{
	double x = _pRight->Calc ();
	_pLeft->Assign (x);
	return x;
}

double VarNode::Calc () const
{
	double x = 0.0;
	if (_store.IsInit (_id))
		x = _store.Value (_id);
	else
		TheOutput.Error ("Use of uninitialized variable");
	return x;
}

void VarNode::Assign (double val)
{
	_store.SetValue (_id, val);
}

bool VarNode::IsLvalue () const
{
	return true;
}
