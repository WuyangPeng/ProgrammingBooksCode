#include <iostream>
class World 
{
public:
	World (int i)
	{
		std::cout << "Hello from " << i << ".\n";
	}
	~World ()
	{
		std::cout << "Goodbye.\n";
	}
};

World TheWorld (1);

int main()
{
	World smallWorld (2);
	std::cout << "Hello from main!\n";
}
