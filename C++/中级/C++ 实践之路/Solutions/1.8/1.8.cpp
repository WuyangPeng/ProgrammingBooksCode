#include <iostream>

class Average
{
public:
	Average ()
		: _sum (0), _count (0)
	{}
	void Put (double n)
	{
		_sum = _sum + n;
		++_count;
	}
	double Get () const
	{
		return _sum / _count;
	}
private:
	double	_sum;
	int		_count;
};

int main ()
{
	Average average;
	average.Put (10.0);
	average.Put (20.0);
	std::cout << average.Get () << std::endl;
	average.Put (60.0);
	std::cout << average.Get () << std::endl;
}