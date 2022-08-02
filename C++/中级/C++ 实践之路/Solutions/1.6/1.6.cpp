#include <iostream> 

class CelestialBody 
{
public:
	CelestialBody (double mass)
		: _mass (mass)
	{
		std::cout << "Creating celestial body of mass " 
			<< _mass << std::endl; 
	}
	~CelestialBody () 
	{ 
		std::cout << "Destroying celestial body of mass " 
			<< _mass << std::endl; 
	}
private: 
	const double _mass; 
}; 

class Planet: public CelestialBody
{
public:
	Planet (double mass, double albedo)
		: CelestialBody (mass),
		  _albedo (albedo)
	{
		std::cout << "Creating a planet with albedo "
				<< _albedo << std::endl;
	}
	~Planet ()
	{
		std::cout << "Destroying a planet with albedo "
				<< _albedo << std::endl;
	}
private:
	double _albedo;
};

int main ()
{
	Planet planet (123.4, 0.25);
}