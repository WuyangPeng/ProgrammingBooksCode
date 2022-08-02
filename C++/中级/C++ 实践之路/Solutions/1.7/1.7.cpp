#include <iostream>

class Two
{
public:
	Two ()
	{
		std::cout << "Program ";
	}
};

class Three
{
public:
	Three ()
	{
		std::cout << "objects ";
	}
};

class Four
{
public:
	Four ()
	{
		std::cout << "makes ";
	}
};

class One: public Two
{
public:
	One ()
	{
		Three three;
		std::cout << "with class ";
	}
private:
	Four    _four;
};

int main ()
{
	One one;
}
