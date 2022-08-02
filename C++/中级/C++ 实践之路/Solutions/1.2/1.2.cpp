#include <iostream>

class Hand
{
public:
	Hand (int numFingers)
		: _n (numFingers)
	{}
private:
	int _n;
};

class Glove
{
public:
	Glove (int numFingers)
	// solution 1: don't use one data member to initialize another
		: _n (numFingers), _hand (numFingers)
	{
		std::cout << "Glove with " << _n << " fingers\n";
	}
private:
	// solution 2: change embedding order
	int   _n;
	Hand  _hand;
};

int main ()
{
	Glove glove (5);
}