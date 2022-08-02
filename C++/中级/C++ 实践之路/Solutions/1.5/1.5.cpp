#include <iostream>

class InputNum
{
public:
	InputNum ()
	{
		std::cout << "Enter number ";
		std::cin >> _num; 
	}
	int GetValue () const { return _num; }
private:
	int _num;
};

int main ()
{
	InputNum num;
	int factorial = 1;
	for (int i = 2; i < num.GetValue (); ++i)
		factorial = factorial * i;
	factorial = factorial * num.GetValue ();
	std::cout << num.GetValue () << "! = " << factorial << std::endl;
}