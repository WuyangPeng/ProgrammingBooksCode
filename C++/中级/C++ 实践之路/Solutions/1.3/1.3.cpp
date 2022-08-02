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

int main ()
{
	Frame frame (10, 2);
}