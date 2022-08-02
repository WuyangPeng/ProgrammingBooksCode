// (c) Bartosz Milewski, 2000

#include <iostream>

class Matter
{
public:
	Matter (int id)
		: _identifier (id)
	{
		std::cout << "  Matter for " << _identifier 
			<< " created\n";
	}
	~Matter ()
	{
		std::cout << "Matter in " << _identifier 
			<< " annihilated\n";
	}
private:
	const int _identifier;
};

class World
{
public:
	World (int id)
		: _identifier (id), 
		  _matter (_identifier) // initializing embeddings
	{
		std::cout << "Hello from world " << _identifier << ".\n";
	}

	~World ()
	{
		std::cout << "Goodbye from world " << _identifier << ".\n";
	}
private:
	const int      _identifier;
	const Matter   _matter; // Embedded object of type Matter
};

World TheUniverse (1);

int main ()
{
	World smallWorld (2);
}
