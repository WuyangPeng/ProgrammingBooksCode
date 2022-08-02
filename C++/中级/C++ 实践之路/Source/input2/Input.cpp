// (c) Bartosz Milewski 2000

#include <iostream>

class  InputNum
{
public:
	InputNum ()
	{
		std::cout << "Enter number ";
		std::cin >> _num;
	}

	int GetValue () const { return _num; }

	void AddInput ()
	{
		InputNum aNum;  // get a number from user
		_num = _num + aNum.GetValue ();
	}

private:
	int _num;
};

int main()
{
	InputNum num;
	std::cout << "The value is " << num.GetValue() << "\n";
	num.AddInput();
	std::cout << "Now the value is " << num.GetValue() << "\n";
}
