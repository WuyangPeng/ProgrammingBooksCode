// (c) Bartosz Milewski, 2000

#include <iostream>

class CelestialBody 
{
public:
	CelestialBody (double mass)
		: _mass (mass)
	{
		std::cout << "Creating celestial body of mass " 
			<< _mass << "\n"; 
	}
	~CelestialBody () 
	{ 
		std::cout << "Destroying celestial body of mass " 
			<< _mass << "\n"; 
	}
private: 
	const double _mass; 
}; 

class Star: public CelestialBody // Star is a CelestialBody 
{
public: 
	Star (double mass, double brightness) 
		: CelestialBody (mass), 
		 _brightness (brightness) 
	{ 
		std::cout << "Creating a star of brightness " 
			<< _brightness << "\n"; 
	}
	~Star () 
	{ 
		std::cout << "Destroying a star of brightness " 
			<< _brightness << "\n"; 
	}
private: 
	const double _brightness; 
};

int main () 
{ 
	std::cout << "          Entering main.\n"; 
	Star aStar ( 1234.5, 0.1 ); 
	std::cout << "          Exiting main.\n"; 
}