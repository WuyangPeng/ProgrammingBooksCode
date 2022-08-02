
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

//-------------------------------------------------------------------//
// Define a custom type to represent each particle in the effect.
//-------------------------------------------------------------------//
typedef	struct _TParticle
{	
	float		x;			// x-coordinate of the particle
	float		y;			// y-coordinate of the particle
	float		vi;			// initial velocity
	float		angle;		// initial trajectory (direction)
	int			life;		// duration in milliseconds
	int			r;          // red component of particle's color
	int			g;          // green component of particle's color
	int			b;          // blue component of particle's color
	int			time;       // keeps track of the effect's time
	float		gravity;    // gravity factor
	BOOL		Active;	    // indicates whether this particle is active or dead
} TParticle;

#define	_MAXPARTICLES 50

typedef struct _TParticleExplosion
{
	TParticle		p[_MAXPARTICLES];  // list of particles making up this effect
	int				V0; // initial velocity, or strength, of the effect
	int				x;  // initial x location
	int				y;  // initial y location
	BOOL		Active;	// indicates whether this effect is active or dead	
} TParticleExplosion;

//----------------------------------------------------------------------------------------------------//
// Now define the variables required for this simulation
//----------------------------------------------------------------------------------------------------//
TParticleExplosion	Explosion;

int					xc;			// x-coordinate of the effect
int					yc;         // y-coordinate of the effect
int					V0;         // initial velocity
int					Duration;   // life in milliseconds
float				Gravity;    // gravity factor (acceleration)
float				Angle;      // indicates particles' direction

#define		PI	3.14159f
#define		RHO	1.225f		// kg/m^3



