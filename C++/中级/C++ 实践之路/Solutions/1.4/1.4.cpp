#include <iostream>

class HorBar
{
public:
	HorBar (int n)
	{
		std::cout << "+";
		for (int i = 0; i < n; ++i)
			std::cout << "-";
		std::cout << "+\n";
	}
};

class VerBar
{
public:
	VerBar (int n)
	{
		for (int i = 0; i < n; ++i)
			std::cout << "|\n";
	}
};

class Frame
{
public:
	Frame (int hor, int ver)
	: _upper (hor),
	  _ver (ver),
	  _lower (hor)
	{}
private:
	HorBar _upper;
	VerBar _ver;
	HorBar _lower;
};

class Ladder
{
public:
	Ladder (int hor, int ver)
	: _upper (hor, ver),
	  _middle (ver),
	  _lower (hor, ver)
	{}
private:
	Frame	_upper;
	VerBar	_middle;
	Frame	_lower;
};

int main ()
{
	Ladder ladder (10, 2);
}