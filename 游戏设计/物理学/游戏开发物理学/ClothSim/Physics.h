#ifndef _PHYSICS
#define _PHYSICS

#include "mymath.h"
#include <windows.h>

//------------------------------------------------------------------------//
// Notes:
//------------------------------------------------------------------------//
/* 

	Note:	Direct3D's coordinates system is a left handed one with the z-axis pointing
			into the screen, the x-axis pointing to the right and the y-axis pointing up
	
	Units:	English system,			
							distance	--> feet
							time		-->	seconds
							mass		--> slugs
							force		--> pounds
							moment		--> foot-pounds
							velocity	--> feet-per-second
							acceleration-->	feet-per-second^2
							density		--> slugs-per-feet^3

			


*/
typedef	struct _Particle {
	float	fMass;
	float	fInvMass;
	Vector	vPosition;
	Vector	vVelocity;
	Vector	vAcceleration;
	Vector	vForces;
	BOOL	bLocked;
} Particle, *pParticle;

typedef struct _ParticleRef {
	int	r;		// row index
	int c;		// column index
} ParticleRef;

typedef	struct	_Spring {
	ParticleRef		p1;			// reference to connected particle #1
	ParticleRef		p2;			// reference to connected particle #2
	float	k;					// tensile spring constant
	float	d;					// damping factor	
	float	L;					// rest length of spring
} Spring, *pSpring;

typedef struct	_Collision {	
	ParticleRef		p1;
	Vector			n;		
}	Collision, *pCollision;


#define		CLOTHWIDTH	100
#define		CLOTHHEIGHT	75
#define		NUMCOLUMNS	10
#define		NUMROWS		7
#define		NUMVERTICES	((NUMCOLUMNS+1) * (NUMROWS+1))
#define		NUMFACES	((NUMCOLUMNS*NUMROWS) * 2)
#define		CLOTHMASS	100.0f
#define		MASSPERFACE	(CLOTHMASS/(float) NUMFACES)
#define		CSTEP		((float) CLOTHWIDTH / (float) NUMCOLUMNS)
#define		RSTEP		((float) CLOTHHEIGHT / (float) NUMROWS)
#define		NUMSTRUCTURALSPRINGS		(NUMCOLUMNS*(NUMROWS+1) + NUMROWS*(NUMCOLUMNS+1) + NUMCOLUMNS*NUMROWS*2)


#define		GRAVITY					-32.174
#define		SPRINGTENSIONCONSTANT	500.0f
#define		SPRINGSHEARCONSTANT		600.0f
#define		SPRINGDAMPINGCONSTANT	2.0f
#define		YOFFSET					120.0f
#define		DRAGCOEFFICIENT			0.01f
#define		WINDFACTOR				100
#define		FLAGPOLEHEIGHT			200
#define		FLAGPOLERADIUS			10
#define		COLLISIONTOLERANCE		0.05f
#define		KRESTITUTION			0.25f
#define		FRICTIONFACTOR			0.5f

#define		NOCOLLISION				0
#define		COLLISION				1
#define		PENETRATING				-1


//------------------------------------------------------------------------//
// Function headers
//------------------------------------------------------------------------//
void	Initialize(void);
void	CalcForces(Particle particles[NUMROWS+1][NUMCOLUMNS+1]);			// calcs total forces and moments
void	StepSimulation(float dt);			// step dt time in the simulation

void	ReleaseLockedParticles(void);
void	SetWindVector(float x, float y, float z);
void	SetWindForceFactor(float f);
void	UpdateClothGeometry(void);
void	CopyParticles(Particle src[NUMROWS+1][NUMCOLUMNS+1], Particle dst[NUMROWS+1][NUMCOLUMNS+1]);
int		CheckForCollisions(Particle p[NUMROWS+1][NUMCOLUMNS+1]);
void	ResolveCollisions(Particle p[NUMROWS+1][NUMCOLUMNS+1]);


extern	BOOL	CreateCloth(char *ftex, unsigned int *faces, int faceCount, float *vertices, int vertexCount, BOOL makechild);
extern	void	UpdateCloth(unsigned int *faces, int faceCount, float *vertices, int vertexCount);


#endif
