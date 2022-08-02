#if !defined (INPUT_H)
#define INPUT_H
// (c) Bartosz Milewski 2000
#include <iostream>

const int tokError = 0;
const int tokNumber = 1;

class Input
{
public:
	Input ()
	{
		std::cout << "Input created\n";
	}
	int Token () const { return tokError; }
	int Number () const { return 13; }
};

#endif
