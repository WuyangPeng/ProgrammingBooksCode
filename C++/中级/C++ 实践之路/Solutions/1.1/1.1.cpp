#include <iostream>

class World
{
public:
	World (int id)
		: _identifier (id)
	{
		std::cout << "Hello from " << _identifier << "!\n";
	}
	~World ()
	{
		std::cout << "Goodbye from " << _identifier << std::endl;
	}
private:
	const int _identifier;
};

int main ()
{
	// first solution: the for loop
	for (int i = 1; i < 3; ++i)
		World world (i);
	// second solution: two local scopes
	{
		World world (1);
	}
	{
		World world (2);
	}
}