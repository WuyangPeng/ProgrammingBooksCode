// (c) Bartosz Milewski 2000

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
	// void SetValue (int i) { _num = i; }
private:
	int _num;
};

int main()
{
	InputNum num;
	// num.SetValue (10);
	std::cout << "The value is " << num.GetValue() << "\n"; 
}
