//----------------------------------------------------------------------------------------------------//
/*
	PHYSICS FOR GAME DEVELOPERS
	
	CHAPTER 16 EXAMPLE PROGRAM

	NAME:		Crash Test
	PURPOSE:	To demonstrate multi-rigid body simulation in 3D
	BY:			David Bourg
	DATE:		07/20/01
	COPYRIGHT:	Copyright 2000-2001 by David Bourg
*/
//----------------------------------------------------------------------------------------------------//
#include "Physics.h"

#include <memory.h>
#include <assert.h>

#define	_DTHRUST	10.0f
#define	_MAXTHRUST	3000.0f

//------------------------------------------------------------------------//
// Global variables
//------------------------------------------------------------------------//
Vector		Thrust;			// Thrust vector, assumed to act through the CG
float		ThrustForce;	// Magnitude of the thrust force

RigidBody	Bodies[NUMBODIES];		// rigid body [0] is the car; the others are the blocks
Collision	Collisions[NUMBODIES*8];
int			NumCollisions = 0;

RigidBody	BodiesBackup[NUMBODIES]; // used to store a copy of the body states during the sim.

//------------------------------------------------------------------------//
// This function sets the initial state of the objects
//------------------------------------------------------------------------//
void	InitializeObjects(int	configuration)
{	
	float	iRoll, iPitch, iYaw;
	int		i;
	float	Ixx, Iyy, Izz;
	float	s;

	// Initialize the car:
	// Set initial position
	Bodies[0].vPosition.x = -50.0f;
	Bodies[0].vPosition.y = 0.0f;
	Bodies[0].vPosition.z = CARHEIGHT/2.0f;//+50.0f;

	// Set initial velocity
	switch(configuration)
	{
		case 0: s = 110.0f; break; // ft/s 
		case 1: s = 120.0f; break; // ft/s
		case 2: s = 115.0f; break; // ft/s
	}
	Bodies[0].vVelocity.x = s;//110
	Bodies[0].vVelocity.y = 0.0f;
	Bodies[0].vVelocity.z = 0.0f;
	Bodies[0].fSpeed = s;

	// Set initial angular velocity
	Bodies[0].vAngularVelocity.x = 0.0f;
	Bodies[0].vAngularVelocity.y = 0.0f;
	Bodies[0].vAngularVelocity.z = 0.0f;

	Bodies[0].vAngularAcceleration.x = 0.0f;
	Bodies[0].vAngularAcceleration.y = 0.0f;
	Bodies[0].vAngularAcceleration.z = 0.0f;

	Bodies[0].vAcceleration.x = 0.0f;
	Bodies[0].vAcceleration.y = 0.0f;
	Bodies[0].vAcceleration.z = 0.0f;

	// Set the initial thrust, forces and moments
	Bodies[0].vForces.x = 0.0f;
	Bodies[0].vForces.y = 0.0f;
	Bodies[0].vForces.z = 0.0f;
	ThrustForce = 0.0;

	Bodies[0].vMoments.x = 0.0f;
	Bodies[0].vMoments.y = 0.0f;
	Bodies[0].vMoments.z = 0.0f;

	// Zero the velocity in body space coordinates
	Bodies[0].vVelocityBody.x = 0.0f;
	Bodies[0].vVelocityBody.y = 0.0f;
	Bodies[0].vVelocityBody.z = 0.0f;

	// Set the initial orientation
	iRoll = 0.0f;
	iPitch = 0.0f;
	iYaw = 0.0f;
	Bodies[0].qOrientation = MakeQFromEulerAngles(iRoll, iPitch, iYaw);

	// Set the mass properties
	Bodies[0].fMass = 2000.0f/(-g);

	Ixx = Bodies[0].fMass/12.0f * (CARWIDTH*CARWIDTH + CARHEIGHT*CARHEIGHT);
	Iyy = Bodies[0].fMass/12.0f * (CARHEIGHT*CARHEIGHT + CARLENGTH*CARLENGTH);
	Izz = Bodies[0].fMass/12.0f * (CARWIDTH*CARWIDTH + CARLENGTH*CARLENGTH);

	Bodies[0].mInertia.e11 = Ixx;	Bodies[0].mInertia.e12 = 0;	Bodies[0].mInertia.e13 = 0;
	Bodies[0].mInertia.e21 = 0;		Bodies[0].mInertia.e22 = Iyy;	Bodies[0].mInertia.e23 = 0;
	Bodies[0].mInertia.e31 = 0;		Bodies[0].mInertia.e32 = 0;	Bodies[0].mInertia.e33 = Izz;

	Bodies[0].mInertiaInverse = Bodies[0].mInertia.Inverse();
		
	Bodies[0].fRadius = CARLENGTH/2; // for bounding sphere check
	
	// bounding verteces relative to CG (assumed centered here for now)
	Bodies[0].vVertexList[0].x = CARLENGTH/2.0f;
	Bodies[0].vVertexList[0].y = CARWIDTH/2.0f;
	Bodies[0].vVertexList[0].z = -CARHEIGHT/2.0f;

	Bodies[0].vVertexList[1].x = CARLENGTH/2.0f;
	Bodies[0].vVertexList[1].y = CARWIDTH/2.0f;
	Bodies[0].vVertexList[1].z = CARHEIGHT/2.0f;
	
	Bodies[0].vVertexList[2].x = CARLENGTH/2.0f;
	Bodies[0].vVertexList[2].y = -CARWIDTH/2.0f;
	Bodies[0].vVertexList[2].z = CARHEIGHT/2.0f;
	
	Bodies[0].vVertexList[3].x = CARLENGTH/2.0f;
	Bodies[0].vVertexList[3].y = -CARWIDTH/2.0f;
	Bodies[0].vVertexList[3].z = -CARHEIGHT/2.0f;

	Bodies[0].vVertexList[4].x = -CARLENGTH/2.0f;
	Bodies[0].vVertexList[4].y = CARWIDTH/2.0f;
	Bodies[0].vVertexList[4].z = -CARHEIGHT/2.0f;

	Bodies[0].vVertexList[5].x = -CARLENGTH/2.0f;
	Bodies[0].vVertexList[5].y = CARWIDTH/2.0f;
	Bodies[0].vVertexList[5].z = CARHEIGHT/2.0f;
	
	Bodies[0].vVertexList[6].x = -CARLENGTH/2.0f;
	Bodies[0].vVertexList[6].y = -CARWIDTH/2.0f;
	Bodies[0].vVertexList[6].z = CARHEIGHT/2.0f;
	
	Bodies[0].vVertexList[7].x = -CARLENGTH/2.0f;
	Bodies[0].vVertexList[7].y = -CARWIDTH/2.0f;
	Bodies[0].vVertexList[7].z = -CARHEIGHT/2.0f;	
	
	ThrustForce = 0.0f;


	// Initialize the blocks

	for(i=1; i<NUMBODIES; i++)
	{
		// Set initial position
		
		switch(configuration)
		{
			case 2:		
				if(i==1)
				{
					Bodies[i].vPosition.x = BLOCKSIZE*4;
					Bodies[i].vPosition.y = -(BLOCKSIZE/2.0f+1.0f);
					Bodies[i].vPosition.z = BLOCKSIZE/2.0f;
				} else {
					Bodies[i].vPosition.x = 0.0f;
					Bodies[i].vPosition.y = 0.0f;//BLOCKSIZE/2.0f+1.0f;
					Bodies[i].vPosition.z = BLOCKSIZE/2.0f;
				}		
				break;

			case 1:		
				if(i==1)
				{
					Bodies[i].vPosition.x = BLOCKSIZE*4;
					Bodies[i].vPosition.y = -(BLOCKSIZE/2.0f+1.0f);
					Bodies[i].vPosition.z = BLOCKSIZE/2.0f;
				} else {
					Bodies[i].vPosition.x = 0.0f;
					Bodies[i].vPosition.y = BLOCKSIZE/2.0f+1.0f;
					Bodies[i].vPosition.z = BLOCKSIZE/2.0f;
				}		
				break;

			case 0:		
				if(i==1)
				{
					Bodies[i].vPosition.x = BLOCKSIZE+1.0f;
					Bodies[i].vPosition.y = BLOCKSIZE/2.0f+1.0f;
					Bodies[i].vPosition.z = BLOCKSIZE/2.0f;
				} else {
					Bodies[i].vPosition.x = 0.0f;
					Bodies[i].vPosition.y = BLOCKSIZE/2.0f+1.0f;
					Bodies[i].vPosition.z = BLOCKSIZE/2.0f;
				}		
				break;
		}

		// Set initial velocity
		Bodies[i].vVelocity.x = 0.0f;
		Bodies[i].vVelocity.y = 0.0f;
		Bodies[i].vVelocity.z = 0.0f;
		Bodies[i].fSpeed = 0.0f;

		// Set initial angular velocity
		Bodies[i].vAngularVelocity.x = 0.0f;
		Bodies[i].vAngularVelocity.y = 0.0f;
		Bodies[i].vAngularVelocity.z = 0.0f;

		Bodies[i].vAngularAcceleration.x = 0.0f;
		Bodies[i].vAngularAcceleration.y = 0.0f;
		Bodies[i].vAngularAcceleration.z = 0.0f;

		Bodies[i].vAcceleration.x = 0.0f;
		Bodies[i].vAcceleration.y = 0.0f;
		Bodies[i].vAcceleration.z = 0.0f;


		// Set the initial thrust, forces and moments
		Bodies[i].vForces.x = 0.0f;
		Bodies[i].vForces.y = 0.0f;
		Bodies[i].vForces.z = 0.0f;	

		Bodies[i].vMoments.x = 0.0f;
		Bodies[i].vMoments.y = 0.0f;
		Bodies[i].vMoments.z = 0.0f;

		// Zero the velocity in body space coordinates
		Bodies[i].vVelocityBody.x = 0.0f;
		Bodies[i].vVelocityBody.y = 0.0f;
		Bodies[i].vVelocityBody.z = 0.0f;

		// Set the initial orientation
		iRoll = 0.0f;
		iPitch = 0.0f;
		if(configuration == 2)
			iYaw = 45.0f;
		else
			iYaw = 0.0f;
		Bodies[i].qOrientation = MakeQFromEulerAngles(iRoll, iPitch, iYaw);

		// Set the mass properties
		Bodies[i].fMass = 500.0f/(-g);

		Ixx = Iyy = Izz = Bodies[i].fMass/12.0f * (BLOCKSIZE*BLOCKSIZE + BLOCKSIZE*BLOCKSIZE);
		
		Bodies[i].mInertia.e11 = Ixx;	Bodies[i].mInertia.e12 = 0;	Bodies[i].mInertia.e13 = 0;
		Bodies[i].mInertia.e21 = 0;		Bodies[i].mInertia.e22 = Iyy;	Bodies[i].mInertia.e23 = 0;
		Bodies[i].mInertia.e31 = 0;		Bodies[i].mInertia.e32 = 0;	Bodies[i].mInertia.e33 = Izz;

		Bodies[i].mInertiaInverse = Bodies[i].mInertia.Inverse();
		
		Bodies[i].fRadius = BLOCKSIZE/2; // for bounding sphere check
	
		// bounding verteces relative to CG (assumed centered)
		Bodies[i].vVertexList[0].x = BLOCKSIZE/2.0f;
		Bodies[i].vVertexList[0].y = BLOCKSIZE/2.0f;
		Bodies[i].vVertexList[0].z = -BLOCKSIZE/2.0f;

		Bodies[i].vVertexList[1].x = BLOCKSIZE/2.0f;
		Bodies[i].vVertexList[1].y = BLOCKSIZE/2.0f;
		Bodies[i].vVertexList[1].z = BLOCKSIZE/2.0f;
	
		Bodies[i].vVertexList[2].x = BLOCKSIZE/2.0f;
		Bodies[i].vVertexList[2].y = -BLOCKSIZE/2.0f;
		Bodies[i].vVertexList[2].z = BLOCKSIZE/2.0f;
	
		Bodies[i].vVertexList[3].x = BLOCKSIZE/2.0f;
		Bodies[i].vVertexList[3].y = -BLOCKSIZE/2.0f;
		Bodies[i].vVertexList[3].z = -BLOCKSIZE/2.0f;

		Bodies[i].vVertexList[4].x = -BLOCKSIZE/2.0f;
		Bodies[i].vVertexList[4].y = BLOCKSIZE/2.0f;
		Bodies[i].vVertexList[4].z = -BLOCKSIZE/2.0f;

		Bodies[i].vVertexList[5].x = -BLOCKSIZE/2.0f;
		Bodies[i].vVertexList[5].y = BLOCKSIZE/2.0f;
		Bodies[i].vVertexList[5].z = BLOCKSIZE/2.0f;
	
		Bodies[i].vVertexList[6].x = -BLOCKSIZE/2.0f;
		Bodies[i].vVertexList[6].y = -BLOCKSIZE/2.0f;
		Bodies[i].vVertexList[6].z = BLOCKSIZE/2.0f;
	
		Bodies[i].vVertexList[7].x = -BLOCKSIZE/2.0f;
		Bodies[i].vVertexList[7].y = -BLOCKSIZE/2.0f;
		Bodies[i].vVertexList[7].z = -BLOCKSIZE/2.0f;
	}

	
}

//------------------------------------------------------------------------//
// This function calculates all of the forces and moments acting on the 
// objects at any given time.
//------------------------------------------------------------------------//
void	CalcObjectForces(void)
{
	Vector	Fb, Mb;
	Vector	vDragVector;
	Vector	vAngularDragVector;
	int	i, j;
	Vector	ContactForce;
	Vector	pt;
	int		check = NOCOLLISION;
	pCollision	pCollisionData;
	Vector	FrictionForce;
	Vector	fDir;
	
	for(i=0; i<NUMBODIES; i++)
	{
		// reset forces and moments:
		Bodies[i].vForces.x = 0.0f;
		Bodies[i].vForces.y = 0.0f;
		Bodies[i].vForces.z = 0.0f;

		Bodies[i].vMoments.x = 0.0f;
		Bodies[i].vMoments.y = 0.0f;
		Bodies[i].vMoments.z = 0.0f;

		Fb.x = 0.0f;	Mb.x = 0.0f;
		Fb.y = 0.0f;	Mb.y = 0.0f;
		Fb.z = 0.0f;	Mb.z = 0.0f;

		// Define the thrust vector, which acts through the CG
		if(i==0)
		{
			Thrust.x = 1.0f;
			Thrust.y = 0.0f;
			Thrust.z = 0.0f;
			Thrust *= ThrustForce;
			Fb += Thrust;
		}

		// do drag force
		vDragVector = -Bodies[i].vVelocityBody;			
		vDragVector.Normalize();
		Fb += vDragVector * (Bodies[i].fSpeed * Bodies[i].fSpeed * rho * LINEARDRAGCOEFFICIENT * Bodies[i].fRadius*Bodies[i].fRadius); 

		vAngularDragVector = -Bodies[i].vAngularVelocity;
		vAngularDragVector.Normalize();
		Mb += vAngularDragVector * (Bodies[i].vAngularVelocity.Magnitude()*Bodies[i].vAngularVelocity.Magnitude() * rho * ANGULARDRAGCOEFFICIENT * Bodies[i].fRadius*Bodies[i].fRadius*6.0f);


		// Convert forces from model space to earth space
		Bodies[i].vForces = QVRotate(Bodies[i].qOrientation, Fb);

		// Apply gravity
		Bodies[i].vForces.z += GRAVITY * Bodies[i].fMass;		

		// save the moments
		Bodies[i].vMoments += Mb;

		// handle contacts with ground plane	
		Bodies[i].vAcceleration = Bodies[i].vForces / Bodies[i].fMass;
		Bodies[i].vAngularAcceleration = Bodies[i].mInertiaInverse * 
										(Bodies[i].vMoments - 
										(Bodies[i].vAngularVelocity^
										(Bodies[i].mInertia * Bodies[i].vAngularVelocity)));

		pCollisionData = Collisions;
		NumCollisions = 0;
		check = CheckGroundPlaneContacts(pCollisionData, i);
		if(check == CONTACT)
		{// have contact....
			for(j=0; j<NumCollisions; j++)
			{
				ContactForce = (Bodies[i].fMass/NumCollisions * (-Collisions[j].vRelativeAcceleration*Collisions[j].vCollisionNormal)) * Collisions[j].vCollisionNormal;
				FrictionForce = (ContactForce.Magnitude()*FRICTIONCOEFFICIENT)*Collisions[j].vCollisionTangent;
				Bodies[i].vForces += ContactForce;
				Bodies[i].vForces += FrictionForce;
				ContactForce = QVRotate(~Bodies[i].qOrientation, ContactForce);
				FrictionForce = QVRotate(~Bodies[i].qOrientation, FrictionForce);
				pt = Collisions[j].vCollisionPoint - Bodies[i].vPosition;
				Bodies[i].vMoments += pt^ContactForce;
				Bodies[i].vMoments += pt^FrictionForce;
			}
		}
	}	
}

//------------------------------------------------------------------------//
//  Using Euler's method
//------------------------------------------------------------------------//
void	StepSimulation(float dtime)
{

	Vector Ae;	
	int		i;
	bool	tryAgain = true;
	int		check = NOCOLLISION;
	float	dt = dtime;

memcpy(BodiesBackup, Bodies, sizeof(RigidBody)*NUMBODIES);// make a backup here

while(tryAgain && (dt > tol))
{
	tryAgain = false;

	// Calculate all of the forces and moments on the airplane:
	CalcObjectForces();

	// Integrate
	for(i=0; i<NUMBODIES; i++) 
	{
		// calculate the acceleration of the airplane in earth space:
		Ae = Bodies[i].vForces / Bodies[i].fMass;
		Bodies[i].vAcceleration = Ae;

		// calculate the velocity of the airplane in earth space:
		Bodies[i].vVelocity += Ae * dt;

		// calculate the position of the airplane in earth space:
		Bodies[i].vPosition += Bodies[i].vVelocity * dt;

		// Now handle the rotations:
		float		mag;

		Bodies[i].vAngularAcceleration = Bodies[i].mInertiaInverse * 
										(Bodies[i].vMoments - 
										(Bodies[i].vAngularVelocity^
										(Bodies[i].mInertia * Bodies[i].vAngularVelocity)));													

		Bodies[i].vAngularVelocity += Bodies[i].vAngularAcceleration * dt;	

		// calculate the new rotation quaternion:
		Bodies[i].qOrientation +=	(Bodies[i].qOrientation * Bodies[i].vAngularVelocity) *									
									(0.5f * dt);

		// now normalize the orientation quaternion:
		mag = Bodies[i].qOrientation.Magnitude();
		if (mag != 0)
			Bodies[i].qOrientation /= mag;

		// calculate the velocity in body space:
		// (we'll need this to calculate lift and drag forces)
		Bodies[i].vVelocityBody = QVRotate(~Bodies[i].qOrientation, Bodies[i].vVelocity);
		
		// calculate the air speed:
		Bodies[i].fSpeed = Bodies[i].vVelocity.Magnitude();

		// get the Euler angles for our information
		Vector u;
		
		u = MakeEulerAnglesFromQ(Bodies[i].qOrientation);
		Bodies[i].vEulerAngles.x = u.x;	// roll
		Bodies[i].vEulerAngles.y = u.y;	// pitch
		Bodies[i].vEulerAngles.z = u.z;	// yaw
	}

	// Check Collisions
	check = CheckForCollisions();
	//assert(check != PENETRATING);
	if(check == COLLISION) {		
		int count = 0;

		/*do
		{*/
			ResolveCollisions(); // do collision response		
		/*	count++;
			check = CheckForCollisions();
		} while((check == COLLISION) && (count < 10));*/
		
		tryAgain = false;
	} else if(check == PENETRATING)
	{
		dt = dt/2.0f;
		/*if(dt>tol)
		{*/
			tryAgain = true;
			memcpy(Bodies, BodiesBackup, sizeof(RigidBody)*NUMBODIES);// restore original config
		/*} else {
			tryAgain = false;			
		}*/
		//assert(dt>tol);// penetrated too far
	} else
		tryAgain = false;

}// while
	

}

int	CheckForCollisions(void)
{
	int	status = NOCOLLISION;
	int	i, j;
	Vector	d;
	pCollision	pCollisionData;
	int		check = NOCOLLISION;

	pCollisionData = Collisions;
	NumCollisions = 0;
	
	// check object collisions with each other	
	for(i=0; (i<NUMBODIES) && (status!=PENETRATING); i++)	
		for(j=0; (j<NUMBODIES) && (status!=PENETRATING); j++)
			if(j!=i) // don't check object against itself
			{
				// do a bounding sphere check first	
				d = Bodies[i].vPosition - Bodies[j].vPosition;
				if(d.Magnitude() < (Bodies[i].fRadius + Bodies[j].fRadius))				
				{// possible collision, do a vertex check
					check = CheckBoxCollision(pCollisionData, i, j);
					if(check == PENETRATING)
						status = PENETRATING;
					else if(check == COLLISION)
						status = COLLISION;
				}
			}

	// check object collisions with the ground			
	
	for(i=0; (i<NUMBODIES) && (status!=PENETRATING); i++)
	{
		check = CheckGroundPlaneCollisions(pCollisionData, i);
		if(check == PENETRATING)
			status = PENETRATING;
		else if(check == COLLISION)
			status = COLLISION;
	}
	
	return status;
}

void ResolveCollisions(void)
{
	int	i;
	Vector pt1, pt2;
	float	j;	
	float	fCr = COEFFICIENTOFRESTITUTION;	
	int		b1, b2;
	float Vrt;
	float	mu = FRICTIONCOEFFICIENT;

	for(i=0; i<NumCollisions; i++)
	{
		b1 = Collisions[i].body1;
		b2 = Collisions[i].body2;

		if(b2 != -1) // not ground plane
		{
			pt1 = Collisions[i].vCollisionPoint - Bodies[b1].vPosition;
			pt2 = Collisions[i].vCollisionPoint - Bodies[b2].vPosition;
		
			// calculate impulse
			j = (-(1+fCr) * (Collisions[i].vRelativeVelocity*Collisions[i].vCollisionNormal)) /						
				( (1/Bodies[b1].fMass + 1/Bodies[b2].fMass) +
				(Collisions[i].vCollisionNormal * ( ( (pt1 ^ Collisions[i].vCollisionNormal)*Bodies[b1].mInertiaInverse )^pt1) ) +
				(Collisions[i].vCollisionNormal * ( ( (pt2 ^ Collisions[i].vCollisionNormal)*Bodies[b2].mInertiaInverse )^pt2) )
				);

			Vrt = Collisions[i].vRelativeVelocity * Collisions[i].vCollisionTangent;
	
			if(fabs(Vrt) > 0.0) {
				Bodies[b1].vVelocity += ( (j * Collisions[i].vCollisionNormal) + ((mu * j) * Collisions[i].vCollisionTangent) ) / Bodies[b1].fMass;										
				Bodies[b1].vAngularVelocity += (pt1 ^ ((j * Collisions[i].vCollisionNormal) + ((mu * j) * Collisions[i].vCollisionTangent)))*Bodies[b1].mInertiaInverse;

				Bodies[b2].vVelocity -= ((j * Collisions[i].vCollisionNormal) + ((mu * j) * Collisions[i].vCollisionTangent)) / Bodies[b2].fMass;										
				Bodies[b2].vAngularVelocity -= (pt2 ^ ((j * Collisions[i].vCollisionNormal) + ((mu * j) * Collisions[i].vCollisionTangent)))*Bodies[b2].mInertiaInverse;

			} else {					
				// apply impulse
				Bodies[b1].vVelocity += (j * Collisions[i].vCollisionNormal) / Bodies[b1].fMass;										
				Bodies[b1].vAngularVelocity += (pt1 ^ (j * Collisions[i].vCollisionNormal))*Bodies[b1].mInertiaInverse;

				Bodies[b2].vVelocity -= (j * Collisions[i].vCollisionNormal) / Bodies[b2].fMass;										
				Bodies[b2].vAngularVelocity -= (pt2 ^ (j * Collisions[i].vCollisionNormal))*Bodies[b2].mInertiaInverse;
			}
		} else { // ground plane
			fCr = COEFFICIENTOFRESTITUTIONGROUND;
			pt1 = Collisions[i].vCollisionPoint - Bodies[b1].vPosition;
		
			// calculate impulse
			j = (-(1+fCr) * (Collisions[i].vRelativeVelocity*Collisions[i].vCollisionNormal)) /						
				( (1/Bodies[b1].fMass) +
				(Collisions[i].vCollisionNormal * ( ( (pt1 ^ Collisions[i].vCollisionNormal)*Bodies[b1].mInertiaInverse )^pt1)));

			Vrt = Collisions[i].vRelativeVelocity * Collisions[i].vCollisionTangent;
	
			if(fabs(Vrt) > 0.0) {
				Bodies[b1].vVelocity += ( (j * Collisions[i].vCollisionNormal) + ((mu * j) * Collisions[i].vCollisionTangent) ) / Bodies[b1].fMass;										
				Bodies[b1].vAngularVelocity += (pt1 ^ ((j * Collisions[i].vCollisionNormal) + ((mu * j) * Collisions[i].vCollisionTangent)))*Bodies[b1].mInertiaInverse;
			} else {					
				// apply impulse
				Bodies[b1].vVelocity += (j * Collisions[i].vCollisionNormal) / Bodies[b1].fMass;			
				Bodies[b1].vAngularVelocity += (pt1 ^ (j * Collisions[i].vCollisionNormal))*Bodies[b1].mInertiaInverse;
			}


		}
	
	}
}

float	CalcDistanceFromPointToPlane(Vector pt, Vector u, Vector v, Vector ptOnPlane)
{
	Vector n = u^v;
	Vector PQ = pt - ptOnPlane;
	
	n.Normalize();
	
	return PQ*n;
}

bool	IsPointOnFace(Vector pt, Vector f[4])
{
	Vector u, v, n;
	Vector vList[4];
	int i;
	Vector p;

	u = f[1] - f[0];
	v = f[3] - f[0];
	n = u^v;
	
	if((fabs(n.x) > fabs(n.y)) && (fabs(n.x) > fabs(n.z)))
	{// flatten in yz plane
		for(i=0; i<4; i++)
		{
			vList[i].x = f[i].y;	
			vList[i].y = f[i].z;	
			vList[i].z = 0.0f;
		}
		p.x = pt.y;
		p.y = pt.z;
		p.z = 0.0;

		if(pnpoly(4, vList, p) == 1)
			return true;
	} else if((fabs(n.y) > fabs(n.x)) && (fabs(n.y) > fabs(n.z)))
	{// flatten in xz plane
		for(i=0; i<4; i++)
		{
			vList[i].x = f[i].x;	
			vList[i].y = f[i].z;	
			vList[i].z = 0.0f;
		}
		p.x = pt.x;
		p.y = pt.z;
		p.z = 0.0;

		if(pnpoly(4, vList, p) == 1)
			return true;
	} else if((fabs(n.z) > fabs(n.x)) && (fabs(n.z) > fabs(n.y)))
	{// flatten in xy plane
		for(i=0; i<4; i++)
		{
			vList[i].x = f[i].x;	
			vList[i].y = f[i].y;	
			vList[i].z = 0.0f;
		}
		p.x = pt.x;
		p.y = pt.y;
		p.z = 0.0;

		if(pnpoly(4, vList, p) == 1)
			return true;
	}

	return false;
}

int	CheckBoxCollision(pCollision CollisionData, int body1, int body2)
{
	int		i;
	Vector	v1[8];
	Vector	v2[8];
	Vector	tmp;
	Vector	u, v;
	float	d;	
	Vector	f[4];
	Vector	vel1, vel2;
	Vector	pt1, pt2;
	Vector	Vr;
	float	Vrn;
	Vector	n;
	int	status = NOCOLLISION;
	bool	inside = true;

	//rotate bounding vertices and covert to global coordinates
	for(i=0; i<8; i++)
	{
		tmp = Bodies[body1].vVertexList[i];
		v1[i] = QVRotate(Bodies[body1].qOrientation, tmp);
		v1[i] += Bodies[body1].vPosition;

		tmp = Bodies[body2].vVertexList[i];
		v2[i] = QVRotate(Bodies[body2].qOrientation, tmp);
		v2[i] += Bodies[body2].vPosition;
	}

	//check each vertex of body i against each face of body j
	for(i=0; i<8; i++)
	{
		inside = true;
		// Front face of body 2:
		u = v2[1]-v2[0];
		v = v2[3]-v2[0];
		d = CalcDistanceFromPointToPlane(v1[i], u, v, v2[0]);		
		if(fabs(d) < COLLISIONTOLERANCE)
		{
			f[0] = v2[0]; 
			f[1] = v2[1]; 
			f[2] = v2[2]; 
			f[3] = v2[3]; 
			if(IsPointOnFace(v1[i], f))
			{	
				// calc relative velocity, if <0 collision
				pt1 = v1[i] - Bodies[body1].vPosition;
				pt2 = v1[i] - Bodies[body2].vPosition;

				vel1 = Bodies[body1].vVelocityBody + (Bodies[body1].vAngularVelocity^pt1);
				vel2 = Bodies[body2].vVelocityBody + (Bodies[body2].vAngularVelocity^pt2);

				vel1 = QVRotate(Bodies[body1].qOrientation, vel1);
				vel2 = QVRotate(Bodies[body2].qOrientation, vel2);

				n = u^v;
				n.Normalize();
				
				Vr = (vel1 - vel2);
				Vrn = Vr * n;

				if(Vrn < 0.0f)
				{
					// have a collision, fill the data structure and return
					assert(NumCollisions < (NUMBODIES*8));
					if(NumCollisions < (NUMBODIES*8))
					{
						CollisionData->body1 = body1;
						CollisionData->body2 = body2;
						CollisionData->vCollisionNormal = n;					
						CollisionData->vCollisionPoint = v1[i];
						CollisionData->vRelativeVelocity = Vr;						
						CollisionData->vCollisionTangent = -(Vr - ((Vr*n)*n));
						CollisionData->vCollisionTangent.Normalize();
						CollisionData->vCollisionTangent.Normalize();
						CollisionData++;
						NumCollisions++;
						status = true;
					}									
				}
			}
		}


		// Aft face of body 2:
		u = v2[6]-v2[7];
		v = v2[4]-v2[7];
		d = CalcDistanceFromPointToPlane(v1[i], u, v, v2[7]);		
		if(fabs(d) < COLLISIONTOLERANCE)
		{
			f[0] = v2[7]; 
			f[1] = v2[6]; 
			f[2] = v2[5]; 
			f[3] = v2[4]; 
			if(IsPointOnFace(v1[i], f))
			{	
				// calc relative velocity, if <0 collision
				pt1 = v1[i] - Bodies[body1].vPosition;
				pt2 = v1[i] - Bodies[body2].vPosition;

				vel1 = Bodies[body1].vVelocityBody + (Bodies[body1].vAngularVelocity^pt1);
				vel2 = Bodies[body2].vVelocityBody + (Bodies[body2].vAngularVelocity^pt2);

				vel1 = QVRotate(Bodies[body1].qOrientation, vel1);
				vel2 = QVRotate(Bodies[body2].qOrientation, vel2);

				n = u^v;
				n.Normalize();
				
				Vr = (vel1 - vel2);
				Vrn = Vr * n;
				
				if(Vrn < 0.0f)
				{
					// have a collision, fill the data structure and return
					assert(NumCollisions < (NUMBODIES*8));
					if(NumCollisions < (NUMBODIES*8))
					{
						CollisionData->body1 = body1;
						CollisionData->body2 = body2;
						CollisionData->vCollisionNormal = n;					
						CollisionData->vCollisionPoint = v1[i];
						CollisionData->vRelativeVelocity = Vr;
						CollisionData->vCollisionTangent = -(Vr - ((Vr*n)*n));
						CollisionData->vCollisionTangent.Normalize();
						CollisionData->vCollisionTangent.Normalize();
						CollisionData++;
						NumCollisions++;
						status = true;
					}									
				}
			}
		}

		// Top face of body 2:
		u = v2[2]-v2[6];
		v = v2[5]-v2[6];
		d = CalcDistanceFromPointToPlane(v1[i], u, v, v2[6]);		
		if(fabs(d) < COLLISIONTOLERANCE)
		{
			f[0] = v2[6]; 
			f[1] = v2[2]; 
			f[2] = v2[1]; 
			f[3] = v2[5]; 
			if(IsPointOnFace(v1[i], f))
			{	
				// calc relative velocity, if <0 collision
				pt1 = v1[i] - Bodies[body1].vPosition;
				pt2 = v1[i] - Bodies[body2].vPosition;

				vel1 = Bodies[body1].vVelocityBody + (Bodies[body1].vAngularVelocity^pt1);
				vel2 = Bodies[body2].vVelocityBody + (Bodies[body2].vAngularVelocity^pt2);

				vel1 = QVRotate(Bodies[body1].qOrientation, vel1);
				vel2 = QVRotate(Bodies[body2].qOrientation, vel2);

				n = u^v;
				n.Normalize();
				
				Vr = (vel1 - vel2);
				Vrn = Vr * n;
				
				if(Vrn < 0.0f)
				{
					// have a collision, fill the data structure and return
					assert(NumCollisions < (NUMBODIES*8));
					if(NumCollisions < (NUMBODIES*8))
					{
						CollisionData->body1 = body1;
						CollisionData->body2 = body2;
						CollisionData->vCollisionNormal = n;					
						CollisionData->vCollisionPoint = v1[i];
						CollisionData->vRelativeVelocity = Vr;
						CollisionData->vCollisionTangent = -(Vr - ((Vr*n)*n));
						CollisionData->vCollisionTangent.Normalize();
						CollisionData->vCollisionTangent.Normalize();
						CollisionData++;
						NumCollisions++;
						status = true;
					}									
				}
			}
		}

		// Bottom face of body 2:
		u = v2[0]-v2[4];
		v = v2[7]-v2[4];
		d = CalcDistanceFromPointToPlane(v1[i], u, v, v2[4]);		
		if(fabs(d) < COLLISIONTOLERANCE)
		{
			f[0] = v2[4]; 
			f[1] = v2[0]; 
			f[2] = v2[3]; 
			f[3] = v2[7]; 
			if(IsPointOnFace(v1[i], f))
			{	
				// calc relative velocity, if <0 collision
				pt1 = v1[i] - Bodies[body1].vPosition;
				pt2 = v1[i] - Bodies[body2].vPosition;

				vel1 = Bodies[body1].vVelocityBody + (Bodies[body1].vAngularVelocity^pt1);
				vel2 = Bodies[body2].vVelocityBody + (Bodies[body2].vAngularVelocity^pt2);

				vel1 = QVRotate(Bodies[body1].qOrientation, vel1);
				vel2 = QVRotate(Bodies[body2].qOrientation, vel2);

				n = u^v;
				n.Normalize();
				
				Vr = (vel1 - vel2);
				Vrn = Vr * n;
				
				if(Vrn < 0.0f)
				{

					// have a collision, fill the data structure and return
					assert(NumCollisions < (NUMBODIES*8));
					if(NumCollisions < (NUMBODIES*8))
					{
						CollisionData->body1 = body1;
						CollisionData->body2 = body2;
						CollisionData->vCollisionNormal = n;					
						CollisionData->vCollisionPoint = v1[i];
						CollisionData->vRelativeVelocity = Vr;
						CollisionData->vCollisionTangent = -(Vr - ((Vr*n)*n));
						CollisionData->vCollisionTangent.Normalize();
						CollisionData->vCollisionTangent.Normalize();
						CollisionData++;
						NumCollisions++;
						status = true;
					}									
				}
			}
		}

		// Left face of body 2:
		u = v2[5]-v2[4];
		v = v2[0]-v2[4];
		d = CalcDistanceFromPointToPlane(v1[i], u, v, v2[4]);		
		if(fabs(d) < COLLISIONTOLERANCE)
		{
			f[0] = v2[4]; 
			f[1] = v2[5]; 
			f[2] = v2[1]; 
			f[3] = v2[0]; 
			if(IsPointOnFace(v1[i], f))
			{	
				// calc relative velocity, if <0 collision
				pt1 = v1[i] - Bodies[body1].vPosition;
				pt2 = v1[i] - Bodies[body2].vPosition;

				vel1 = Bodies[body1].vVelocityBody + (Bodies[body1].vAngularVelocity^pt1);
				vel2 = Bodies[body2].vVelocityBody + (Bodies[body2].vAngularVelocity^pt2);

				vel1 = QVRotate(Bodies[body1].qOrientation, vel1);
				vel2 = QVRotate(Bodies[body2].qOrientation, vel2);

				n = u^v;
				n.Normalize();
				
				Vr = (vel1 - vel2);
				Vrn = Vr * n;
				
				if(Vrn < 0.0f)
				{
					// have a collision, fill the data structure and return
					assert(NumCollisions < (NUMBODIES*8));
					if(NumCollisions < (NUMBODIES*8))
					{
						CollisionData->body1 = body1;
						CollisionData->body2 = body2;
						CollisionData->vCollisionNormal = n;					
						CollisionData->vCollisionPoint = v1[i];
						CollisionData->vRelativeVelocity = Vr;
						CollisionData->vCollisionTangent = -(Vr - ((Vr*n)*n));
						CollisionData->vCollisionTangent.Normalize();
						CollisionData->vCollisionTangent.Normalize();
						CollisionData++;
						NumCollisions++;
						status = true;
					}									
				}
			}
		}

		// Right face of body 2:
		u = v2[6]-v2[2];
		v = v2[3]-v2[2];
		d = CalcDistanceFromPointToPlane(v1[i], u, v, v2[2]);		
		if(fabs(d) < COLLISIONTOLERANCE)
		{
			f[0] = v2[2]; 
			f[1] = v2[6]; 
			f[2] = v2[7]; 
			f[3] = v2[3]; 
			if(IsPointOnFace(v1[i], f))
			{	
				// calc relative velocity, if <0 collision
				pt1 = v1[i] - Bodies[body1].vPosition;
				pt2 = v1[i] - Bodies[body2].vPosition;

				vel1 = Bodies[body1].vVelocityBody + (Bodies[body1].vAngularVelocity^pt1);
				vel2 = Bodies[body2].vVelocityBody + (Bodies[body2].vAngularVelocity^pt2);

				vel1 = QVRotate(Bodies[body1].qOrientation, vel1);
				vel2 = QVRotate(Bodies[body2].qOrientation, vel2);

				n = u^v;
				n.Normalize();
				
				Vr = (vel1 - vel2);
				Vrn = Vr * n;
				
				if(Vrn < 0.0f)
				{

					// have a collision, fill the data structure and return
					assert(NumCollisions < (NUMBODIES*8));
					if(NumCollisions < (NUMBODIES*8))
					{
						CollisionData->body1 = body1;
						CollisionData->body2 = body2;
						CollisionData->vCollisionNormal = n;					
						CollisionData->vCollisionPoint = v1[i];
						CollisionData->vRelativeVelocity = Vr;
						CollisionData->vCollisionTangent = -(Vr - ((Vr*n)*n));
						CollisionData->vCollisionTangent.Normalize();
						CollisionData->vCollisionTangent.Normalize();
						CollisionData++;
						NumCollisions++;
						status = true;
					}									
				}
			}
		}		
		
	}

	return status;
}

int	CheckGroundPlaneCollisions(pCollision CollisionData, int body1)
{
	int		i;
	Vector	v1[8];
	Vector	tmp;
	Vector	u, v;
	float	d;	
	Vector	f[4];
	Vector	vel1;
	Vector	pt1;
	Vector	Vr;
	float	Vrn;
	Vector	n;
	int	status = NOCOLLISION;

	//rotate bounding vertices and covert to global coordinates
	for(i=0; i<8; i++)
	{
		tmp = Bodies[body1].vVertexList[i];
		v1[i] = QVRotate(Bodies[body1].qOrientation, tmp);
		v1[i] += Bodies[body1].vPosition;
	}

	//check each vertex of body i against each face of body j
	for(i=0; i<8; i++)
	{
		// Check the ground plane
		u.x = 1.0f;
		u.y = 0.0f;
		u.z = 0.0f;
		v.x = 0.0f;
		v.y = 1.0f;
		v.z = 0.0f;
		tmp.x = 0.0f;
		tmp.y = 0.0f;
		tmp.z = 0.0f;
		d = CalcDistanceFromPointToPlane(v1[i], u, v, tmp);
		if(d < COLLISIONTOLERANCE)
		{
			// calc relative velocity, if <0 collision
			pt1 = v1[i] - Bodies[body1].vPosition;
			
			vel1 = Bodies[body1].vVelocityBody + (Bodies[body1].vAngularVelocity^pt1);
			
			vel1 = QVRotate(Bodies[body1].qOrientation, vel1);
			
			n = u^v;
			n.Normalize();
				
			Vr = vel1;
			Vrn = Vr * n;
				
			if(Vrn < 0.0f)
			{

				// have a collision, fill the data structure and return
				assert(NumCollisions < (NUMBODIES*8));
				if(NumCollisions < (NUMBODIES*8))
				{
					CollisionData->body1 = body1;
					CollisionData->body2 = -1;
					CollisionData->vCollisionNormal = n;					
					CollisionData->vCollisionPoint = v1[i];
					CollisionData->vRelativeVelocity = Vr;
					CollisionData->vCollisionTangent = -(Vr - ((Vr*n)*n));
					CollisionData->vCollisionTangent.Normalize();
					CollisionData->vCollisionTangent.Normalize();
					CollisionData++;
					NumCollisions++;
					status = COLLISION;
				}				
			}
		}


	}

	return status;
}

int	CheckGroundPlaneContacts(pCollision CollisionData, int body1)
{
	int		i;
	Vector	v1[8];
	Vector	tmp;
	Vector	u, v;
	float	d;	
	Vector	f[4];
	Vector	vel1;
	Vector	pt1;
	Vector	Vr;
	float	Vrn;
	Vector	n;
	int	status = NOCOLLISION;
	Vector	Ar;
	float	Arn;

	//rotate bounding vertices and covert to global coordinates
	for(i=0; i<8; i++)
	{
		tmp = Bodies[body1].vVertexList[i];
		v1[i] = QVRotate(Bodies[body1].qOrientation, tmp);
		v1[i] += Bodies[body1].vPosition;
	}

	//check each vertex of body i against each face of body j
	for(i=0; i<8; i++)
	{
		// Check the ground plane too
		u.x = 1.0f;
		u.y = 0.0f;
		u.z = 0.0f;
		v.x = 0.0f;
		v.y = 1.0f;
		v.z = 0.0f;
		tmp.x = 0.0f;
		tmp.y = 0.0f;
		tmp.z = 0.0f;
		d = CalcDistanceFromPointToPlane(v1[i], u, v, tmp);
		if(d < COLLISIONTOLERANCE)
		{
			// calc relative velocity, if <0 collision
			pt1 = v1[i] - Bodies[body1].vPosition;
			
			vel1 = Bodies[body1].vVelocityBody + (Bodies[body1].vAngularVelocity^pt1);
			
			vel1 = QVRotate(Bodies[body1].qOrientation, vel1);
			
			n = u^v;
			n.Normalize();
				
			Vr = vel1;
			Vrn = Vr * n;
				
			if(fabs(Vrn) <= VELOCITYTOLERANCE) // at rest
			{
				// now check the relative acceleration
				Ar = Bodies[body1].vAcceleration + (Bodies[body1].vAngularVelocity^(Bodies[body1].vAngularVelocity^pt1)) + 
					 (Bodies[body1].vAngularAcceleration ^ pt1);
								
				Arn = Ar * n;

				if(Arn <= 0.0f)
				{
					// have a contact, fill the data structure and return
					assert(NumCollisions < (NUMBODIES*8));
					if(NumCollisions < (NUMBODIES*8))
					{
						CollisionData->body1 = body1;
						CollisionData->body2 = -1;
						CollisionData->vCollisionNormal = n;					
						CollisionData->vCollisionPoint = v1[i];
						CollisionData->vRelativeVelocity = Vr;
						CollisionData->vRelativeAcceleration = Ar;
						CollisionData->vCollisionTangent = -(Vr - ((Vr*n)*n));
						CollisionData->vCollisionTangent.Normalize();
						CollisionData++;
						NumCollisions++;
						status = CONTACT;
					}				
				}
			}
		}


	}

	return status;
}



//------------------------------------------------------------------------//
//
//------------------------------------------------------------------------//
Vector	GetBodyZAxisVector(int index)
{

	Vector	v;

	v.x = 0.0f;
	v.y = 0.0f;
	v.z = 1.0f;

	return QVRotate(Bodies[index].qOrientation, v);
}

//------------------------------------------------------------------------//
//
//------------------------------------------------------------------------//
Vector	GetBodyXAxisVector(int index)
{

	Vector v;

	v.x = 1.0f;
	v.y = 0.0f;
	v.z = 0.0f;

	return QVRotate(Bodies[index].qOrientation, v);
	
}

//------------------------------------------------------------------------//
//
//------------------------------------------------------------------------//
Matrix3x3   MakeAngularVelocityMatrix(Vector u)
{
	return Matrix3x3(	0.0f, -u.z, u.y,
						u.z, 0.0f, -u.x,
						-u.y, u.x, 0.0f);
}

//------------------------------------------------------------------------//
// Adapted from Rourke's Computational Geometry FAQ
//------------------------------------------------------------------------//
int	pnpoly(int	npol, Vector *vlist, Vector p)
{
	int	i, j, c = 0;

	for (i = 0, j = npol-1; i<npol; j = i++) {
		if ((((vlist[i].y<=p.y) && (p.y<vlist[j].y)) ||
			 ((vlist[j].y<=p.y) && (p.y<vlist[i].y))) &&
			(p.x < (vlist[j].x - vlist[i].x) * (p.y - vlist[i].y) / (vlist[j].y - vlist[i].y) + vlist[i].x))

		   c = !c;
	}
	return c;
}


