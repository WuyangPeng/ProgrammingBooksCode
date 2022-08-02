
//----------------------------------------------------------------------------------------------------//
// Define a custom type to represent
// the three components of a 3D vector, where
// i represents the x-component, j represents
// the y-component, and k represents the z-
// component
//----------------------------------------------------------------------------------------------------//
typedef struct TVectorTag
{
	double i;
	double j;
	double k;
} TVector;

//----------------------------------------------------------------------------------------------------//
// Now define the variables required for this simulation
//----------------------------------------------------------------------------------------------------//
double		Vm;		// Magnitude of muzzle velocity
double		Alpha;	// Angle from y-axis (upward) to the cannon.
					// When this angle is zero the cannon is pointing
					// straight up, when it is 90 degrees, the cannon
					// is horizontal
double		Gamma;	// Angle from x-axis, in the x-z plane to the cannon.
					// When this angle is zero the cannon is pointing in
					// the positive x-direction, positive values of this angle
					// are toward the positive z-axis
double		L;		// This is the length of the cannon
double		Yb;		// This is the base elevation of the cannon

double		X;		// The x-position of the center of the target
double		Y;		// The y-position of the center of the target
double		Z;		// The z-position of the center of the target
double		Length;	// The length of the target measured along the x-axis
double		Width;	// The width of the target measured along the z-axis
double		Height; // The height of the target measure along the y-axis

TVector		s;		// The shell position (displacement) vector

double		time;	// The time from the instant the shell leaves the cannon
double		tInc;	// The time increment to use when stepping through the simulation

double		g;		// acceleration due to gravity

//-----------------------------------------------------------------------------------
// New variables:
double		m;      // Projectile mass
double		Vw;     // Wind speed 
double		GammaW; // Wind direction
double		Cw;     // Wind force coefficient
double		Cd;     // Drag coefficient
//-----------------------------------------------------------------------------------


