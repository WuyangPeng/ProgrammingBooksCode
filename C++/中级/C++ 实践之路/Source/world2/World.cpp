#include <iostream>

class World
{
public:
	World ()  { std::cout << "Hello!\n"; }
	~World () { std::cout << "Goodbye!\n"; }
};

World TheWorld;

int main ()
{
	World smallWorld;
	std::cout << "Hello from main!\n";
}
