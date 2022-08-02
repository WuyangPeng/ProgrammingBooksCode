#include <iostream>
#include <cassert>

const int maxCells = 16;

class DblArray
{
public:
	DblArray ();
	void Set (int i, double val);
	double Get (int i) const;
	bool IsSet (int i) const;
private:
	double	_arr [maxCells];
	bool	_isSet [maxCells];
};

DblArray::DblArray ()
{
	for (int i = 0; i < maxCells; ++i)
		_isSet [i] = false;
}

void DblArray::Set (int i, double val)
{
	assert (i < maxCells);
	assert (!IsSet (i));
	_arr [i] = val;
	_isSet [i] = true;
}

double DblArray::Get (int i) const
{
	assert (i < maxCells);
	assert (_isSet [i]);
	return _arr [i];
}

bool DblArray::IsSet (int i) const
{
	assert (i < maxCells);
	return _isSet [i];
}

int main ()
{
	DblArray arr;
	arr.Set (2, 0.2);
	arr.Set (4, 0.4);
	std::cout << "IsSet (0) returns " << arr.IsSet (0) << std::endl;
	std::cout << "IsSet (2) returns " << arr.IsSet (2) << std::endl;
	std::cout << "Get (2) returns " << arr.Get (2) << std::endl;
	std::cout << "Get (4) returns " << arr.Get (4) << std::endl;
}

	