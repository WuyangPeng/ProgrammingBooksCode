
//----------------------------------------------------------------------------------------------------//
// Define a custom type to represent
// the three components of a 2D vector, where
// i represents the x-component, j represents
// the y-component
//----------------------------------------------------------------------------------------------------//
typedef struct TVectorTag
{
	double i;
	double j;	
} TVector;

//----------------------------------------------------------------------------------------------------//
// Global variables required for this simulation
//----------------------------------------------------------------------------------------------------//
TVector		V1;		// Initial Velocity (given), m/s
TVector		V2;		// Velocity vector at time t, m/s
double		m;      // Projectile mass (given), kg
TVector		s1;		// Initial position (given), m
TVector		s2;		// The projectile's position (displacement) vector, m
double		time;	// The time from the instant the projectile is launched, s
double		tInc;	// The time increment to use when stepping through the simulation, s
double		g;		// acceleration due to gravity (given), m/s^2
double		spin;	// spin in rpm (given)
double		omega;	// spin in radians per second
double		radius;	// radius of projectile (given), m

#define		PI	3.14159f
#define		RHO	1.225f		// kg/m^3



