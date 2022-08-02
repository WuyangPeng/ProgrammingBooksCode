#include <iostream>

class Two
{
public:
	Two ()
	{
		std::cout << "Program ";
	}

	~Two ()
	{
		std::cout << "Program ";
	}
};

class Three
{
public:
	Three ()
	{
		std::cout << "makes ";
	}
	~Three ()
	{
		std::cout << "makes ";
	}
};

class Four
{
public:
	Four ()
	{
		std::cout << "objects ";
	}
	~Four ()
	{
		std::cout << "objects ";
	}
};

class Five
{
public:
	Five ()
	{
		std::cout << "with ";
	}
	~Five ()
	{
		std::cout << "with ";
	}
};

class One: public Two
{
public:
	One ()
	{
		std::cout << "class ";
	}
	~One ()
	{
		std::cout << "class ";
	}
private:
	Three	_three;
	Four    _four;
	Five	_five;
};

int main ()
{
	One one;
	std::cout << std::endl;
}
