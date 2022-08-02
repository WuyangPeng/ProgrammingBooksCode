// (c) Bartosz Milewski 2000

#include <iostream> 

class InputNum 
{
public:
	InputNum (char msg [])
	{
		std::cout << msg; 
		std::cin >> _num;
	}
	int GetValue () const { return _num; }
	void AddInput (char msg [])
	{
		InputNum aNum (msg);
		_num = GetValue () + aNum.GetValue ();
	}
private:
	int _num;
}; 

const char SumString [] = "The sum is "; 

int main()
{
	InputNum num ("Enter number "); 
	num.AddInput ("Another one "); 
	num.AddInput ("One more "); 
	std::cout << SumString << num.GetValue () << "\n"; 
}
