//----------------------------------------------------------------------------------------------------//
/*
	PHYSICS FOR GAME DEVELOPERS
	
	CHAPTER 17 EXAMPLE PROGRAM

	NAME:		ClothSim
	PURPOSE:	To demonstrate 3D cloth simulation
	BY:			David Bourg
	DATE:		06/30/01
	COPYRIGHT:	Copyright 2001 by David Bourg
*/
//----------------------------------------------------------------------------------------------------//
#include "Physics.h"
#include "assert.h"

int tb_Rnd(int min, int max);

//------------------------------------------------------------------------//
// Global variables
//------------------------------------------------------------------------//
unsigned int		ClothFaces[NUMFACES*3*2];
float				ClothVertices[NUMVERTICES*3*2];

Particle			Particles[NUMROWS+1][NUMCOLUMNS+1];
Spring				StructuralSprings[NUMSTRUCTURALSPRINGS];

Collision			Collisions[NUMVERTICES];
Vector				WindVector;
float				WindForceFactor = WINDFACTOR;



//------------------------------------------------------------------------//
//------------------------------------------------------------------------//
void	Initialize(void)
{	
	int	r, c;
	float f;
	unsigned int	*faceVertex;
	float			*vertices;	
	Vector			L;
	int				count;
	int				n;

	for(r=0; r<=NUMROWS; r++)
	{
		for(c=0; c<=NUMCOLUMNS; c++)
		{
			// calc mass of this particle
			if((r == 0) && (c == 0)) 
				f = 1;
			else if((r == NUMROWS) && (c == 0)) 
				f = 2;
			else if((r == 0) && (c == NUMCOLUMNS)) 
				f = 2;
			else if((r == NUMROWS) && (c == NUMCOLUMNS)) 
				f = 1;
			else if(((r == 0) || (r == NUMROWS)) && ((c != 0) && (c != NUMCOLUMNS))) 
				f = 3;
			else
				f = 6;

			Particles[r][c].fMass = (f * MASSPERFACE) / 3;
			Particles[r][c].fInvMass = 1 / Particles[r][c].fMass;
			
			// set initial position of this particle
			Particles[r][c].vPosition.x = c * CSTEP;
			Particles[r][c].vPosition.y = (CLOTHHEIGHT - (r * RSTEP)) + YOFFSET;
			Particles[r][c].vPosition.z = 0.0f;

			// set initial velocity and forces to zero
			Particles[r][c].vVelocity.x = 0.0f;
			Particles[r][c].vVelocity.y = 0.0f;
			Particles[r][c].vVelocity.z = 0.0f;

			Particles[r][c].vAcceleration.x = 0.0f;
			Particles[r][c].vAcceleration.y = 0.0f;
			Particles[r][c].vAcceleration.z = 0.0f;
			
			Particles[r][c].vForces.x = 0.0f;
			Particles[r][c].vForces.y = 0.0f;
			Particles[r][c].vForces.z = 0.0f;
			if((c == 0) && (r == 0 || r == NUMROWS))
				Particles[r][c].bLocked = TRUE;
			else
				Particles[r][c].bLocked = FALSE;

		}
	}
	
	vertices = ClothVertices;
	for(r=0; r<=NUMROWS; r++)
	{
		for(c=0; c<=NUMCOLUMNS; c++)
		{
			// setup vertices 
			*vertices = Particles[r][c].vPosition.x; vertices++;
			*vertices = Particles[r][c].vPosition.y; vertices++;
			*vertices = Particles[r][c].vPosition.z; vertices++;
		}
	}
	for(r=0; r<=NUMROWS; r++)
	{
		for(c=0; c<=NUMCOLUMNS; c++)
		{
			// setup vertices 
			*vertices = Particles[r][c].vPosition.x; vertices++;
			*vertices = Particles[r][c].vPosition.y; vertices++;
			*vertices = Particles[r][c].vPosition.z; vertices++;
		}
	}

	faceVertex = ClothFaces;	
	for(r=0; r<NUMROWS; r++)
	{
		for(c=0; c<=NUMCOLUMNS; c++)
		{			
			// setup faces
			if(c == 0)
			{
				*faceVertex = ((NUMCOLUMNS+1)*r) + c;						faceVertex++; // vertex 1
				*faceVertex = ((NUMCOLUMNS+1)*r) + (c+1);					faceVertex++; // vertex 2
				*faceVertex = ((NUMCOLUMNS+1)*r) + (NUMCOLUMNS+1) + c;		faceVertex++; // vertex 3
			} else if(c == NUMCOLUMNS) {
				*faceVertex = ((NUMCOLUMNS+1)*r) + c;						faceVertex++; // vertex 1
				*faceVertex = ((NUMCOLUMNS+1)*r) + (NUMCOLUMNS+1) + c;		faceVertex++; // vertex 2
				*faceVertex = ((NUMCOLUMNS+1)*r) + (NUMCOLUMNS+1) + (c-1);	faceVertex++; // vertex 3
			} else {
				*faceVertex = ((NUMCOLUMNS+1)*r) + c;						faceVertex++; // vertex 1
				*faceVertex = ((NUMCOLUMNS+1)*r) + (NUMCOLUMNS+1) + c;		faceVertex++; // vertex 2
				*faceVertex = ((NUMCOLUMNS+1)*r) + (NUMCOLUMNS+1) + (c-1);	faceVertex++; // vertex 3

				*faceVertex = ((NUMCOLUMNS+1)*r) + c;						faceVertex++; // vertex 1
				*faceVertex = ((NUMCOLUMNS+1)*r) + (c+1);					faceVertex++; // vertex 2
				*faceVertex = ((NUMCOLUMNS+1)*r) + (NUMCOLUMNS+1) + c;		faceVertex++; // vertex 3
			}
		}
	}	

	for(r=0; r<NUMROWS; r++)
	{
		for(c=0; c<=NUMCOLUMNS; c++)
		{			
			// setup faces
			if(c == 0)
			{
				*faceVertex = NUMVERTICES + ((NUMCOLUMNS+1)*r) + (NUMCOLUMNS+1) + c;		faceVertex++; // vertex 3
				*faceVertex = NUMVERTICES + ((NUMCOLUMNS+1)*r) + (c+1);					faceVertex++; // vertex 2
				*faceVertex = NUMVERTICES + ((NUMCOLUMNS+1)*r) + c;						faceVertex++; // vertex 1
			} else if(c == NUMCOLUMNS) {
				*faceVertex = NUMVERTICES + ((NUMCOLUMNS+1)*r) + (NUMCOLUMNS+1) + (c-1);	faceVertex++; // vertex 3
				*faceVertex = NUMVERTICES + ((NUMCOLUMNS+1)*r) + (NUMCOLUMNS+1) + c;		faceVertex++; // vertex 2
				*faceVertex = NUMVERTICES + ((NUMCOLUMNS+1)*r) + c;						faceVertex++; // vertex 1
			} else {
				*faceVertex = NUMVERTICES + ((NUMCOLUMNS+1)*r) + (NUMCOLUMNS+1) + (c-1);	faceVertex++; // vertex 3
				*faceVertex = NUMVERTICES + ((NUMCOLUMNS+1)*r) + (NUMCOLUMNS+1) + c;		faceVertex++; // vertex 2
				*faceVertex = NUMVERTICES + ((NUMCOLUMNS+1)*r) + c;						faceVertex++; // vertex 1				

				*faceVertex = NUMVERTICES + ((NUMCOLUMNS+1)*r) + (NUMCOLUMNS+1) + c;		faceVertex++; // vertex 3
				*faceVertex = NUMVERTICES + ((NUMCOLUMNS+1)*r) + (c+1);					faceVertex++; // vertex 2
				*faceVertex = NUMVERTICES + ((NUMCOLUMNS+1)*r) + c;						faceVertex++; // vertex 1
			}
		}
	}	

	// Create a D3D object to represent the cloth
	CreateCloth("test.bmp", ClothFaces, NUMFACES*2, ClothVertices, NUMVERTICES*2, FALSE);

	// setup the structural springs
	// connect springs between each adjacent vertex
	count = 0;
	n = NUMSTRUCTURALSPRINGS;
	//pSprings = StructuralSprings;
	for(r=0; r<=NUMROWS; r++)
	{
		for(c=0; c<=NUMCOLUMNS; c++)
		{			
			if(c<NUMCOLUMNS)
			{
				StructuralSprings[count].p1.r = r;
				StructuralSprings[count].p1.c = c;
				StructuralSprings[count].p2.r = r;
				StructuralSprings[count].p2.c = c+1;
				StructuralSprings[count].k = SPRINGTENSIONCONSTANT;
				StructuralSprings[count].d = SPRINGDAMPINGCONSTANT;				
				L = Particles[r][c].vPosition - Particles[r][c+1].vPosition;
				StructuralSprings[count].L = L.Magnitude();				
				count++;
			}
			if(r<NUMROWS)
			{
				StructuralSprings[count].p1.r = r;
				StructuralSprings[count].p1.c = c;
				StructuralSprings[count].p2.r = r+1;
				StructuralSprings[count].p2.c = c;
				StructuralSprings[count].k = SPRINGTENSIONCONSTANT;
				StructuralSprings[count].d = SPRINGDAMPINGCONSTANT;				
				L = Particles[r][c].vPosition - Particles[r+1][c].vPosition;
				StructuralSprings[count].L = L.Magnitude();				
				count++;
			}
			if(r<NUMROWS && c<NUMCOLUMNS)
			{
				StructuralSprings[count].p1.r = r;
				StructuralSprings[count].p1.c = c;
				StructuralSprings[count].p2.r = r+1;
				StructuralSprings[count].p2.c = c+1;
				StructuralSprings[count].k = SPRINGSHEARCONSTANT;
				StructuralSprings[count].d = SPRINGDAMPINGCONSTANT;				
				L = Particles[r][c].vPosition - Particles[r+1][c+1].vPosition;
				StructuralSprings[count].L = L.Magnitude();				
				count++;
			}
			if(c>0 && r<NUMROWS)
			{
				StructuralSprings[count].p1.r = r;
				StructuralSprings[count].p1.c = c;
				StructuralSprings[count].p2.r = r+1;
				StructuralSprings[count].p2.c = c-1;
				StructuralSprings[count].k = SPRINGSHEARCONSTANT;
				StructuralSprings[count].d = SPRINGDAMPINGCONSTANT;				
				L = Particles[r][c].vPosition - Particles[r+1][c-1].vPosition;
				StructuralSprings[count].L = L.Magnitude();				
				count++;
			}
		}
	}

	
	WindVector.x = 10.0;
	WindVector.y = 0.0;
	WindVector.z = 1.0;


}

//------------------------------------------------------------------------//
//------------------------------------------------------------------------//
void	CalcForces(Particle particles[NUMROWS+1][NUMCOLUMNS+1])
{
	int	r, c, i, r1, c1, r2, c2;
	Vector	dragVector;
	Vector	f1, f2, d, v;
	float	L;

	// zero all forces
	for(r=0; r<=NUMROWS; r++)
	{
		for(c=0; c<=NUMCOLUMNS; c++)
		{				
			particles[r][c].vForces.x = 0;
			particles[r][c].vForces.y = 0;
			particles[r][c].vForces.z = 0;
		}
	}

	// process gravity and drag forces
	for(r=0; r<=NUMROWS; r++)
	{
		for(c=0; c<=NUMCOLUMNS; c++)
		{				
			
			if(particles[r][c].bLocked == FALSE)
			{
				// gravity
				particles[r][c].vForces.y += (float) (GRAVITY * particles[r][c].fMass);

				// viscous drag
				dragVector = -particles[r][c].vVelocity;
				dragVector.Normalize();				
				particles[r][c].vForces += dragVector * (particles[r][c].vVelocity.Magnitude()*particles[r][c].vVelocity.Magnitude()) * DRAGCOEFFICIENT;

				// wind
				SetWindVector(tb_Rnd(0, 10), 0, tb_Rnd(0, 1));
				WindVector.Normalize();
				particles[r][c].vForces += WindVector * tb_Rnd(0, WindForceFactor);			
			}
		}
	}

	// Process spring forces
	for(i = 0; i<NUMSTRUCTURALSPRINGS; i++)
	{
		r1 = StructuralSprings[i].p1.r;
		c1 = StructuralSprings[i].p1.c;
		r2 = StructuralSprings[i].p2.r;
		c2 = StructuralSprings[i].p2.c;

		d = particles[r1][c1].vPosition - particles[r2][c2].vPosition;
		v = particles[r1][c1].vVelocity - particles[r2][c2].vVelocity;
		L = StructuralSprings[i].L;

		f1 = -(StructuralSprings[i].k * (d.Magnitude() - L) + StructuralSprings[i].d * ( (v * d) / d.Magnitude() )) * ( d / d.Magnitude() );
		f2 = -f1;
		
		if(particles[r1][c1].bLocked == FALSE)
			particles[r1][c1].vForces += f1;

		if(particles[r2][c2].bLocked == FALSE)
			particles[r2][c2].vForces += f2;
	}
}

//------------------------------------------------------------------------//
//------------------------------------------------------------------------//
/*void	StepSimulation(float dt)
{
	Vector	Ae;
	int		r, c;
	Particle	p[NUMROWS+1][NUMCOLUMNS+1];
	float	dtime = dt;
	bool	tryAgain = TRUE;
	int		check = 0;
	BOOL	didPen = FALSE;


	while(tryAgain && (dtime > tol))
	{
		tryAgain = FALSE;		
		CopyParticles(Particles, p);

		// calculate all of the forces 
		CalcForces(p);

		// integrate
		for(r=0; r<=NUMROWS; r++)
		{
			for(c=0; c<=NUMCOLUMNS; c++)
			{				
				Ae = p[r][c].vForces * p[r][c].fInvMass;
				p[r][c].vAcceleration = Ae;
				p[r][c].vVelocity += Ae * dtime;
				p[r][c].vPosition += p[r][c].vVelocity * dtime;
			}
		}	

		// check for collisions
		check = CheckForCollisions(p);

		if(check == PENETRATING) 
		{
			dtime = dtime/2;
			tryAgain = TRUE;
			didPen = TRUE;
			//assert(dtime <= tol);	
		} else if(check == COLLISION) {
			ResolveCollisions(p);
			didPen = FALSE;
		}
	}

	CopyParticles(p, Particles);	
	// update the D3D cloth object's geometry
	UpdateClothGeometry();

}*/


void	StepSimulation(float dt)
{
	Vector	Ae;
	int		r, c;
	int		check = 0;

	// Calculate all of the forces 
	CalcForces(Particles);

	// Integrate
	for(r=0; r<=NUMROWS; r++)
	{
		for(c=0; c<=NUMCOLUMNS; c++)
		{				
			Ae = Particles[r][c].vForces * Particles[r][c].fInvMass;
			Particles[r][c].vAcceleration = Ae;
			Particles[r][c].vVelocity += Ae * dt;
			Particles[r][c].vPosition += Particles[r][c].vVelocity * dt;
		}
	}	

	// Check for collisions
	check = CheckForCollisions(Particles);

	if(check == COLLISION)
		ResolveCollisions(Particles);

	// Update the D3D cloth object's geometry
	UpdateClothGeometry();
}






int tb_Rnd(int min, int max) {
	int	number;
		
    //number = min + rand()%max;
    //number = min +tb_Trunc(max*rand());
    number = (((abs(rand())%(max-min+1))+min));    
    
    if(number>max) {
    	number = max;
    	//tb_Beep();
    }
    
    if(number<min) {
    	number = min;
    	//tb_Beep();
    }	
		
	return number;
}

void	ReleaseLockedParticles(void)
{
	int r, c;

	for(r=0; r<=NUMROWS; r++)
	{
		for(c=0; c<=NUMCOLUMNS; c++)
		{
			Particles[r][c].bLocked = FALSE;
		}
	}
}

void	SetWindVector(float x, float y, float z)
{
	WindVector.x = x;
	WindVector.y = y;
	WindVector.z = z;

}

void	SetWindForceFactor(float f)
{
	WindForceFactor = f;
}

void	UpdateClothGeometry(void)
{
	int		r, c;
	float	*vertices;

	// fill the vertex array to pass to Direct3D
	vertices = ClothVertices;
	for(r=0; r<=NUMROWS; r++)
	{
		for(c=0; c<=NUMCOLUMNS; c++)
		{
			// setup vertices 
			*vertices = Particles[r][c].vPosition.x; vertices++;
			*vertices = Particles[r][c].vPosition.y; vertices++;
			*vertices = Particles[r][c].vPosition.z; vertices++;
		}
	}
	for(r=0; r<=NUMROWS; r++)
	{
		for(c=0; c<=NUMCOLUMNS; c++)
		{
			// setup vertices 
			*vertices = Particles[r][c].vPosition.x; vertices++;
			*vertices = Particles[r][c].vPosition.y; vertices++;
			*vertices = Particles[r][c].vPosition.z; vertices++;
		}
	}

	UpdateCloth(ClothFaces, NUMFACES*2, ClothVertices, NUMVERTICES*2);
}


void	CopyParticles(Particle src[NUMROWS+1][NUMCOLUMNS+1], Particle dst[NUMROWS+1][NUMCOLUMNS+1])
{
	int r, c;	

	for(r=0; r<=NUMROWS; r++)
	{
		for(c=0; c<=NUMCOLUMNS; c++)
		{
			dst[r][c].fMass = src[r][c].fMass;
			dst[r][c].fInvMass = src[r][c].fInvMass;
			dst[r][c].vPosition = src[r][c].vPosition;
			dst[r][c].vVelocity = src[r][c].vVelocity;
			dst[r][c].vForces = src[r][c].vForces;
			dst[r][c].bLocked = src[r][c].bLocked;
		}
	}

}

int		CheckForCollisions(Particle p[NUMROWS+1][NUMCOLUMNS+1])
{
	int	i;
	int	r, c;
	int	count = 0;
	int	state = NOCOLLISION;
	float	d;
	Vector	n;
	float	Vn;

	for(i=0; i<NUMVERTICES; i++)
	{
		Collisions[i].p1.r = -1;
		Collisions[i].p1.c = -1;
		Collisions[i].n.x = 0;
		Collisions[i].n.y = 0;
		Collisions[i].n.z = 0;
	}

	// Check for collisions with ground
	for(r=0; r<=NUMROWS; r++)
	{
		for(c=0; c<=NUMCOLUMNS; c++)
		{			
			if(!p[r][c].bLocked)
			{
				if(	(p[r][c].vPosition.y <= COLLISIONTOLERANCE) && (p[r][c].vVelocity.y < tol) )
				{
					state = COLLISION;
					Collisions[count].p1.r = r;
					Collisions[count].p1.c = c;
					Collisions[count].n.x = 0.0f;
					Collisions[count].n.y = 1.0f;
					Collisions[count].n.z = 0.0f;
					Collisions[count].n.Normalize();
					count++;
				}
			}
		}
	}

	// Check for collisions with flag pole
	for(r=0; r<=NUMROWS; r++)
	{
		for(c=0; c<=NUMCOLUMNS; c++)
		{			
			if(!p[r][c].bLocked)
			{
				d = sqrt(p[r][c].vPosition.x * p[r][c].vPosition.x + p[r][c].vPosition.z * p[r][c].vPosition.x);
				n.x = p[r][c].vPosition.x;
				n.y = 0.0f;
				n.z = p[r][c].vPosition.z;
				Vn = (p[r][c].vVelocity * n);			

				if(	(d <= (FLAGPOLERADIUS + COLLISIONTOLERANCE)) && 
					(p[r][c].vPosition.y < FLAGPOLEHEIGHT) &&
					(p[r][c].vPosition.y > 0.0f) &&								
					(Vn < tol) 				
					)
				{
					state = COLLISION;
					Collisions[count].p1.r = r;
					Collisions[count].p1.c = c;
					Collisions[count].n = n;
					Collisions[count].n.Normalize();
					count++;
				}
			}
		}
	}
	
	return state;
}

void	ResolveCollisions(Particle p[NUMROWS+1][NUMCOLUMNS+1])
{
	int i;
	int	r, c;
	Vector	Vn, Vt;
	
	for(i=0; i<NUMVERTICES; i++)
	{
		if(Collisions[i].p1.r != -1)
		{
			r = Collisions[i].p1.r;
			c = Collisions[i].p1.c;
			Vn = (Collisions[i].n * p[r][c].vVelocity) * Collisions[i].n;
			Vt = p[r][c].vVelocity - Vn;
			p[r][c].vVelocity = (-(KRESTITUTION+1) * Vn) + (FRICTIONFACTOR*Vt);
		}
	}
}