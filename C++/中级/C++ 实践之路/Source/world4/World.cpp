#include <iostream>

class World
{
public:
	World (int id)
		: _identifier (id)
	{
		std::cout << "Hello from " << _identifier << ".\n";
	}
	~World ()
	{
		std::cout << "Goodbye from " << _identifier << ".\n";
	}
private:
	int const _identifier;
};

World TheWorld (1);

int main ()
{
	World smallWorld (2);
	for (int i = 3; i < 6; ++i)
	{
		World aWorld (i);
	}
	World oneMoreWorld (6);
}
