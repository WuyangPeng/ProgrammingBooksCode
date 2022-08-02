//----------------------------------------------------------------------------------------------------//
/*
	PHYSICS FOR GAME DEVELOPERS
	
	CHAPTER 16 EXAMPLE PROGRAM

	NAME:		Crash Test
	PURPOSE:	To demonstrate multi-rigid body simulation in 3D
	BY:			David Bourg
	DATE:		07/20/01
	COPYRIGHT:	Copyright 2000-2003 by David Bourg
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
Collision	Collisions[NUMBODIES*16];
int			NumCollisions = 0;

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
	Bodies[0].vPosition.z = CARHEIGHT/2.0f;

	// Set initial velocity
	switch(configuration)
	{
		case 0: s = 110.0f; break; // ft/s 
		case 1: s = 120.0f; break; // ft/s
		case 2: s = 115.0f; break; // ft/s
	}
	
	s = 200;
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
	Bodies[0].fMass = CARWEIGHT/(-g);

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
					Bodies[i].vPosition.x = BLOCKSIZE*8;
					Bodies[i].vPosition.y = -(BLOCKSIZE/2.0f+1.0f);
					Bodies[i].vPosition.z = BLOCKSIZE/2.0f;
				} else {
					Bodies[i].vPosition.x = 0.0f;
					Bodies[i].vPosition.y = 0.0f;
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
					Bodies[i].vPosition.x = BLOCKSIZE*8;
					Bodies[i].vPosition.y = -(BLOCKSIZE/2.0f+1.0f);
					Bodies[i].vPosition.z = BLOCKSIZE/2.0f;
				} else {
					Bodies[i].vPosition.x = BLOCKSIZE*10;
					Bodies[i].vPosition.y = -(BLOCKSIZE/2.0f+1.0f);
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
		//if(configuration == 2)
			iYaw = 45.0f;
		//else
		//	iYaw = 0.0f;
		Bodies[i].qOrientation = MakeQFromEulerAngles(iRoll, iPitch, iYaw);

		// Set the mass properties
		Bodies[i].fMass = BLOCKWEIGHT/(-g);

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
	int		i, j;
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

		// Do drag force
		vDragVector = -Bodies[i].vVelocityBody;			
		vDragVector.Normalize();
		Fb += vDragVector * (Bodies[i].fSpeed * Bodies[i].fSpeed * rho * LINEARDRAGCOEFFICIENT * Bodies[i].fRadius*Bodies[i].fRadius); 

		vAngularDragVector = -Bodies[i].vAngularVelocity;
		vAngularDragVector.Normalize();
		Mb += vAngularDragVector * (Bodies[i].vAngularVelocity.Magnitude()*Bodies[i].vAngularVelocity.Magnitude() * rho * ANGULARDRAGCOEFFICIENT * Bodies[i].fRadius*Bodies[i].fRadius);


		// Convert forces from model space to earth space
		Bodies[i].vForces = QVRotate(Bodies[i].qOrientation, Fb);

		// Apply gravity
		Bodies[i].vForces.z += GRAVITY * Bodies[i].fMass;		

		// Save the moments
		Bodies[i].vMoments += Mb;

		// Handle contacts with ground plane	
		Bodies[i].vAcceleration = Bodies[i].vForces / Bodies[i].fMass;
		Bodies[i].vAngularAcceleration = Bodies[i].mInertiaInverse * 
										(Bodies[i].vMoments - 
										(Bodies[i].vAngularVelocity^
										(Bodies[i].mInertia * Bodies[i].vAngularVelocity)));

		FlushCollisionData();
		pCollisionData = Collisions;
		NumCollisions = 0;
		check = CheckGroundPlaneContacts(pCollisionData, i);
		if(check == CONTACT)
		{// have contact....
			for(j=0; j<NumCollisions; j++)
			{
				ContactForce = ContactForce = (Bodies[i].fMass * (-Bodies[i].vAcceleration*Collisions[j].vCollisionNormal)) * Collisions[j].vCollisionNormal;
				FrictionForce = (ContactForce.Magnitude()*FRICTIONCOEFFICIENT)*Collisions[j].vCollisionTangent;
				Bodies[i].vForces += ContactForce;
				Bodies[i].vForces += FrictionForce;
				ContactForce = QVRotate(~Bodies[i].qOrientation, ContactForce);
				FrictionForce = QVRotate(~Bodies[i].qOrientation, FrictionForce);
				pt = Collisions[j].vCollisionPoint - Bodies[i].vPosition;
				pt = QVRotate(~Bodies[i].qOrientation, pt);
				Bodies[i].vMoments += pt^ContactForce;
				Bodies[i].vMoments += pt^FrictionForce;
			}
		}
	}	
}

void	FlushCollisionData(void)
{
	int	i;
	Vector vNull;
	vNull.x = 0;
	vNull.y = 0;
	vNull.z = 0;

	for(i=0; i<NUMBODIES*16; i++)
	{
		Collisions[i].body1 = -1;
		Collisions[i].body2 = -1;
		Collisions[i].vCollisionNormal = vNull;
		Collisions[i].vCollisionPoint = vNull;
		Collisions[i].vCollisionTangent = vNull;
		Collisions[i].vRelativeAcceleration = vNull;
		Collisions[i].vRelativeVelocity = vNull;
	}
	NumCollisions = 0;
}

//------------------------------------------------------------------------//
//  Using Euler's method
//------------------------------------------------------------------------//
void	StepSimulation(float dtime)
{

	Vector Ae;	
	int		i;	
	float	dt = dtime;
	int		check = NOCOLLISION;
	int		c = 0;
	bool	pencheck = DOPENCHECK;

	// Calculate all of the forces and moments on the airplane:
	CalcObjectForces();


tryagain:
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
		
		
		// get the angular velocity in global coords:
		Bodies[i].vAngularVelocityGlobal = QVRotate(Bodies[i].qOrientation, Bodies[i].vAngularVelocity);

		// get the angular acceleration in global coords:
		Bodies[i].vAngularAccelerationGlobal = QVRotate(Bodies[i].qOrientation, Bodies[i].vAngularAcceleration);
		
		// Get the inverse intertia tensor in global coordinates
		Matrix3x3 R, RT;		
		R = MakeMatrixFromQuaternion(Bodies[i].qOrientation);
		RT = R.Transpose();
		Bodies[i].mIeInverse = R * Bodies[i].mInertiaInverse * RT;

		
		// calculate the air speed:
		Bodies[i].fSpeed = Bodies[i].vVelocity.Magnitude();

		// get the Euler angles for our information
		Vector u;
		
		u = MakeEulerAnglesFromQ(Bodies[i].qOrientation);
		Bodies[i].vEulerAngles.x = u.x;	// roll
		Bodies[i].vEulerAngles.y = u.y;	// pitch
		Bodies[i].vEulerAngles.z = u.z;	// yaw
	}

	// Handle Collisions	
	check = CheckForCollisions(pencheck); 
	if(check == COLLISION)
		ResolveCollisions();
	else if(check == PENETRATING)
	{
		// back up -dt and try again at dt/2
		dt = -dt;

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


		// get the angular velocity in global coords:
		Bodies[i].vAngularVelocityGlobal = QVRotate(Bodies[i].qOrientation, Bodies[i].vAngularVelocity);

		// get the angular acceleration in global coords:
		Bodies[i].vAngularAccelerationGlobal = QVRotate(Bodies[i].qOrientation, Bodies[i].vAngularAcceleration);
		
		// Get the inverse intertia tensor in global coordinates
		Matrix3x3 R, RT;		
		R = MakeMatrixFromQuaternion(Bodies[i].qOrientation);
		RT = R.Transpose();
		Bodies[i].mIeInverse = R * Bodies[i].mInertiaInverse * RT;

		
		// calculate the air speed:
		Bodies[i].fSpeed = Bodies[i].vVelocity.Magnitude();

		// get the Euler angles for our information
		Vector u;
		
		u = MakeEulerAnglesFromQ(Bodies[i].qOrientation);
		Bodies[i].vEulerAngles.x = u.x;	// roll
		Bodies[i].vEulerAngles.y = u.y;	// pitch
		Bodies[i].vEulerAngles.z = u.z;	// yaw

		dt = -dt;
		dt = dt/2;
		c++;
		if(c < 10)
			goto tryagain;
		else
		{
			pencheck = false;
			//dt = dtime/2;
			goto tryagain;
		}

	}

	

}

int	CheckForCollisions(bool pencheck)
{
	int	status = NOCOLLISION;
	int	i, j;
	Vector	d;
	pCollision	pCollisionData;
	int		check = NOCOLLISION;

	FlushCollisionData();
	pCollisionData = Collisions;
	NumCollisions = 0;
	
	// check object collisions with each other	
	for(i=0; i<NUMBODIES; i++)
	{
		for(j=0; j<NUMBODIES; j++)
			if(j!=i) // don't check object against itself
			{
				// do a bounding sphere check first	
				d = Bodies[i].vPosition - Bodies[j].vPosition;
				if(d.Magnitude() < (Bodies[i].fRadius + Bodies[j].fRadius))				
				{// possible collision
					if(pencheck)
						check = IsPenetrating(i, j);
					if(check == PENETRATING)
					{
						status = PENETRATING;
						break;
					} else {
						check = CheckBoxCollision(pCollisionData, i, j);
						if(check == COLLISION)
						{
							status = COLLISION;
							pCollisionData++;
						}
					}
				}
			}
			if(status == PENETRATING) 
				break;
	}

	if(status != PENETRATING)
	{
		// check object collisions with the ground	
		for(i=0; i<NUMBODIES; i++)
		{
			if(pencheck)
				check = IsPenetratingGround(i);
			if(check == PENETRATING)
			{
				status = PENETRATING;
				break;
			} else {
				check = CheckGroundPlaneCollisions(pCollisionData, i);
				if(check == COLLISION)
				{
					status = COLLISION;
					pCollisionData++;
				}
			}
		}
	}
	
	return status;
}


void ResolveCollisions(void)
{
	int		i;
	double	j;
	Vector	pt1, pt2, vB1V, vB2V, vB1AV, vB2AV;
	float	fCr = COEFFICIENTOFRESTITUTION;	
	int		b1, b2;
	float	Vrt;
	float	mu = FRICTIONCOEFFICIENT;
	bool	dofriction = DOFRICTION;

	for(i=0; i<NumCollisions; i++)
	{
		b1 = Collisions[i].body1;
		b2 = Collisions[i].body2;

		if( (b1 != -1) && (b1 != b2) )
		{
			if(b2 != -1) // not ground plane
			{
				pt1 = Collisions[i].vCollisionPoint - Bodies[b1].vPosition;
				pt2 = Collisions[i].vCollisionPoint - Bodies[b2].vPosition;
				
				// calculate impulse
				j = (-(1+fCr) * (Collisions[i].vRelativeVelocity*Collisions[i].vCollisionNormal)) /						
					( (1/Bodies[b1].fMass + 1/Bodies[b2].fMass) +
					(Collisions[i].vCollisionNormal * ( ( (pt1 ^ Collisions[i].vCollisionNormal)*Bodies[b1].mIeInverse )^pt1) ) +
					(Collisions[i].vCollisionNormal * ( ( (pt2 ^ Collisions[i].vCollisionNormal)*Bodies[b2].mIeInverse )^pt2) )
					);
			
				Vrt = Collisions[i].vRelativeVelocity * Collisions[i].vCollisionTangent;
	
				if(fabs(Vrt) > 0.0 && dofriction) {
					Bodies[b1].vVelocity += ( (j * Collisions[i].vCollisionNormal) + ((mu * j) * Collisions[i].vCollisionTangent) ) / Bodies[b1].fMass;										
					Bodies[b1].vAngularVelocityGlobal += (pt1 ^ ((j * Collisions[i].vCollisionNormal) + ((mu * j) * Collisions[i].vCollisionTangent)))*Bodies[b1].mIeInverse;
					Bodies[b1].vAngularVelocity = QVRotate(~Bodies[b1].qOrientation, Bodies[b1].vAngularVelocityGlobal);

					Bodies[b2].vVelocity += ((-j * Collisions[i].vCollisionNormal) + ((mu * j) * Collisions[i].vCollisionTangent)) / Bodies[b2].fMass;										
					Bodies[b2].vAngularVelocityGlobal += (pt2 ^ ((-j * Collisions[i].vCollisionNormal) + ((mu * j) * Collisions[i].vCollisionTangent)))*Bodies[b2].mIeInverse;
					Bodies[b2].vAngularVelocity = QVRotate(~Bodies[b2].qOrientation, Bodies[b2].vAngularVelocityGlobal);

				} else {					
					// apply impulse
					Bodies[b1].vVelocity += (j * Collisions[i].vCollisionNormal) / Bodies[b1].fMass;										
					Bodies[b1].vAngularVelocityGlobal += (pt1 ^ (j * Collisions[i].vCollisionNormal))*Bodies[b1].mIeInverse;
					Bodies[b1].vAngularVelocity = QVRotate(~Bodies[b1].qOrientation, Bodies[b1].vAngularVelocityGlobal);
					
					Bodies[b2].vVelocity -= (j * Collisions[i].vCollisionNormal) / Bodies[b2].fMass;										
					Bodies[b2].vAngularVelocityGlobal -= (pt2 ^ (j * Collisions[i].vCollisionNormal))*Bodies[b2].mIeInverse;
					Bodies[b2].vAngularVelocity = QVRotate(~Bodies[b2].qOrientation, Bodies[b2].vAngularVelocityGlobal);
				}

			} else { // ground plane
				fCr = COEFFICIENTOFRESTITUTIONGROUND;
				pt1 = Collisions[i].vCollisionPoint - Bodies[b1].vPosition;
				
				// calculate impulse
				j = (-(1+fCr) * (Collisions[i].vRelativeVelocity*Collisions[i].vCollisionNormal)) /						
					( (1/Bodies[b1].fMass) +
					(Collisions[i].vCollisionNormal * ( ( (pt1 ^ Collisions[i].vCollisionNormal)*Bodies[b1].mIeInverse )^pt1)));
			
				Vrt = Collisions[i].vRelativeVelocity * Collisions[i].vCollisionTangent;
	
				if(fabs(Vrt) > 0.0 && dofriction) {
					Bodies[b1].vVelocity += ( (j * Collisions[i].vCollisionNormal) + ((mu * j) * Collisions[i].vCollisionTangent) ) / Bodies[b1].fMass;										
					Bodies[b1].vAngularVelocityGlobal += (pt1 ^ ((j * Collisions[i].vCollisionNormal) + ((mu * j) * Collisions[i].vCollisionTangent)))*Bodies[b1].mIeInverse;
					Bodies[b1].vAngularVelocity = QVRotate(~Bodies[b1].qOrientation, Bodies[b1].vAngularVelocityGlobal);
				} else {					
					// apply impulse
					Bodies[b1].vVelocity += (j * Collisions[i].vCollisionNormal) / Bodies[b1].fMass;			
					Bodies[b1].vAngularVelocityGlobal += (pt1 ^ (j * Collisions[i].vCollisionNormal))*Bodies[b1].mIeInverse;
					Bodies[b1].vAngularVelocity = QVRotate(~Bodies[b1].qOrientation, Bodies[b1].vAngularVelocityGlobal);
				}
		
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

int	IsPenetratingGround(int body1)
{
	int		i;
	Vector	v1[8];
	
	Vector	tmp;
	Vector	u, v;
	
	Vector	f[4];
	Vector	vel1;
	Vector	pt1;
	Vector	Vr;
	
	Vector	n;
	int	status = NOCOLLISION;
	bool	inside = true;
	int		c = 0;

	//rotate bounding vertices and covert to global coordinates
	for(i=0; i<8; i++)
	{
		tmp = Bodies[body1].vVertexList[i];
		v1[i] = QVRotate(Bodies[body1].qOrientation, tmp);
		v1[i] += Bodies[body1].vPosition;//+ Bodies[body1].vVelocity*0.0005;
	}
	
	//check each vertex of body 1 against ground plane
	for(i=0; i<8; i++)
	{
		if(v1[i].z <= -COLLISIONTOLERANCE) // should this be the collision tolerance
			return PENETRATING;			
	}
	return status;

}

int IsPenetrating(int body1, int body2)
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
	Vector	n;
	int	status = NOCOLLISION;
	bool	outside = false;

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
	
	//check each vertex of body 1 against each face of body 2
	for(i=0; i<8; i++)
	{
		outside = false;

		// Front face of body 2:
		u = v2[1]-v2[0];
		v = v2[3]-v2[0];		
		d = CalcDistanceFromPointToPlane(v1[i], u, v, u);
		if(d>-PENETRATIONTOLERANCE) 
			outside = true;
	
		// Aft face of body 2:   
		v = v2[6]-v2[7];
		u = v2[4]-v2[7];
		d = CalcDistanceFromPointToPlane(v1[i], u, v, u);
		if(d>-PENETRATIONTOLERANCE) 
			outside = true;

		// Top face of body 2:  
		v = v2[2]-v2[6];
		u = v2[5]-v2[6];
		d = CalcDistanceFromPointToPlane(v1[i], u, v, u);
		if(d>-PENETRATIONTOLERANCE) 
			outside = true;

		// Bottom face of body 2:
		u = v2[0]-v2[4];
		v = v2[7]-v2[4];
		d = CalcDistanceFromPointToPlane(v1[i], u, v, u);
		if(d>-PENETRATIONTOLERANCE) 
			outside = true;

		// Left face of body 2:   
		v = v2[5]-v2[4];
		u = v2[0]-v2[4];
		d = CalcDistanceFromPointToPlane(v1[i], u, v, u);
		if(d>-PENETRATIONTOLERANCE) 
			outside = true;

		// Right face of body 2:
		u = v2[6]-v2[2];
		v = v2[3]-v2[2];
		d = CalcDistanceFromPointToPlane(v1[i], u, v, u);
		if(d>-PENETRATIONTOLERANCE) 
			outside = true;
		
		if(!outside)
			return PENETRATING;
			
	}
	return status;


	
}

int	CheckVertexFaceCollisions(pCollision CollisionData, int body1, int body2)
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
		if(d < COLLISIONTOLERANCE)
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

				
				vel1 = Bodies[body1].vVelocity + (Bodies[body1].vAngularVelocityGlobal^pt1);
				vel2 = Bodies[body2].vVelocity + (Bodies[body2].vAngularVelocityGlobal^pt2);

				
				n = u^v;
				n.Normalize();
				
				Vr = (vel1 - vel2);
				Vrn = Vr * n;

				if(Vrn < 0.0f)
				{
					// have a collision, fill the data structure and return
					assert(NumCollisions < (NUMBODIES*16));
					if(NumCollisions < (NUMBODIES*16))
					{
						CollisionData->body1 = body1;
						CollisionData->body2 = body2;
						CollisionData->vCollisionNormal = n;					
						CollisionData->vCollisionPoint = v1[i];
						CollisionData->vRelativeVelocity = Vr;				
						
						
						CollisionData->vCollisionTangent = (n^Vr)^n;
						

						CollisionData->vCollisionTangent.Normalize();
						CollisionData++;
						NumCollisions++;
						status = COLLISION;
					}									
				}
			}
		}


		// Aft face of body 2:
		v = v2[6]-v2[7];
		u = v2[4]-v2[7];
		d = CalcDistanceFromPointToPlane(v1[i], u, v, v2[7]);		
		if(d < COLLISIONTOLERANCE)
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

				
				vel1 = Bodies[body1].vVelocity + (Bodies[body1].vAngularVelocityGlobal^pt1);
				vel2 = Bodies[body2].vVelocity + (Bodies[body2].vAngularVelocityGlobal^pt2);

				
				n = u^v;
				n.Normalize();
				
				Vr = (vel1 - vel2);
				Vrn = Vr * n;
				
				if(Vrn < 0.0f)
				{
					// have a collision, fill the data structure and return
					assert(NumCollisions < (NUMBODIES*16));
					if(NumCollisions < (NUMBODIES*16))
					{
						CollisionData->body1 = body1;
						CollisionData->body2 = body2;
						CollisionData->vCollisionNormal = n;					
						CollisionData->vCollisionPoint = v1[i];
						CollisionData->vRelativeVelocity = Vr;
						
						
						CollisionData->vCollisionTangent = (n^Vr)^n;
						

						CollisionData->vCollisionTangent.Normalize();
						CollisionData++;
						NumCollisions++;
						status = COLLISION;
					}									
				}
			}
		}

		// Top face of body 2:
		v = v2[2]-v2[6];
		u = v2[5]-v2[6];
		d = CalcDistanceFromPointToPlane(v1[i], u, v, v2[6]);		
		if(d < COLLISIONTOLERANCE)
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

			
				vel1 = Bodies[body1].vVelocity + (Bodies[body1].vAngularVelocityGlobal^pt1);
				vel2 = Bodies[body2].vVelocity + (Bodies[body2].vAngularVelocityGlobal^pt2);

				
				n = u^v;
				n.Normalize();
				
				Vr = (vel1 - vel2);
				Vrn = Vr * n;
				
				if(Vrn < 0.0f)
				{
					// have a collision, fill the data structure and return
					assert(NumCollisions < (NUMBODIES*16));
					if(NumCollisions < (NUMBODIES*16))
					{
						CollisionData->body1 = body1;
						CollisionData->body2 = body2;
						CollisionData->vCollisionNormal = n;					
						CollisionData->vCollisionPoint = v1[i];
						CollisionData->vRelativeVelocity = Vr;

						
						CollisionData->vCollisionTangent = (n^Vr)^n;
						

						CollisionData->vCollisionTangent.Normalize();
						CollisionData++;
						NumCollisions++;
						status = COLLISION;
					}									
				}
			}
		}

		// Bottom face of body 2:
		u = v2[0]-v2[4];
		v = v2[7]-v2[4];
		d = CalcDistanceFromPointToPlane(v1[i], u, v, v2[4]);		
		if(d < COLLISIONTOLERANCE)
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

			
				vel1 = Bodies[body1].vVelocity + (Bodies[body1].vAngularVelocityGlobal^pt1);
				vel2 = Bodies[body2].vVelocity + (Bodies[body2].vAngularVelocityGlobal^pt2);

				
				n = u^v;
				n.Normalize();
				
				Vr = (vel1 - vel2);
				Vrn = Vr * n;
				
				if(Vrn < 0.0f)
				{

					// have a collision, fill the data structure and return
					assert(NumCollisions < (NUMBODIES*16));
					if(NumCollisions < (NUMBODIES*16))
					{
						CollisionData->body1 = body1;
						CollisionData->body2 = body2;
						CollisionData->vCollisionNormal = n;					
						CollisionData->vCollisionPoint = v1[i];
						CollisionData->vRelativeVelocity = Vr;
						
						
						CollisionData->vCollisionTangent = (n^Vr)^n;
						
						
						CollisionData->vCollisionTangent.Normalize();
						CollisionData++;
						NumCollisions++;
						status = COLLISION;
					}									
				}
			}
		}

		// Left face of body 2:???
		v = v2[5]-v2[4];
		u = v2[0]-v2[4];
		d = CalcDistanceFromPointToPlane(v1[i], u, v, v2[4]);		
		if(d < COLLISIONTOLERANCE)
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

			
				vel1 = Bodies[body1].vVelocity + (Bodies[body1].vAngularVelocityGlobal^pt1);
				vel2 = Bodies[body2].vVelocity + (Bodies[body2].vAngularVelocityGlobal^pt2);

			
				n = u^v;
				n.Normalize();
				
				Vr = (vel1 - vel2);
				Vrn = Vr * n;
				
				if(Vrn < 0.0f)
				{
					// have a collision, fill the data structure and return
					assert(NumCollisions < (NUMBODIES*16));
					if(NumCollisions < (NUMBODIES*16))
					{
						CollisionData->body1 = body1;
						CollisionData->body2 = body2;
						CollisionData->vCollisionNormal = n;					
						CollisionData->vCollisionPoint = v1[i];
						CollisionData->vRelativeVelocity = Vr;
						
						
						CollisionData->vCollisionTangent = (n^Vr)^n;
						
						
						CollisionData->vCollisionTangent.Normalize();
						CollisionData++;
						NumCollisions++;
						status = COLLISION;
					}									
				}
			}
		}

		// Right face of body 2:
		u = v2[6]-v2[2];
		v = v2[3]-v2[2];
		d = CalcDistanceFromPointToPlane(v1[i], u, v, v2[2]);		
		if(d < COLLISIONTOLERANCE)
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

				
				vel1 = Bodies[body1].vVelocity + (Bodies[body1].vAngularVelocityGlobal^pt1);
				vel2 = Bodies[body2].vVelocity + (Bodies[body2].vAngularVelocityGlobal^pt2);

				
				n = u^v;
				n.Normalize();
				
				Vr = (vel1 - vel2);
				Vrn = Vr * n;
				
				if(Vrn < 0.0f)
				{

					// have a collision, fill the data structure and return
					assert(NumCollisions < (NUMBODIES*16));
					if(NumCollisions < (NUMBODIES*16))
					{
						CollisionData->body1 = body1;
						CollisionData->body2 = body2;
						CollisionData->vCollisionNormal = n;					
						CollisionData->vCollisionPoint = v1[i];
						CollisionData->vRelativeVelocity = Vr;
						
						
						CollisionData->vCollisionTangent = (n^Vr)^n;
						
						
						CollisionData->vCollisionTangent.Normalize();
						CollisionData++;
						NumCollisions++;
						status = COLLISION;
					}									
				}
			}
		}		
		
	}

	return status;

}

int CheckEdgeEdgeCollisions(pCollision CollisionData, int body1, int body2)
{
	int		i;
	Vector	v1[8];
	Vector	v2[8];
	Vector	tmp;
	Vector	u, v;
	
	Vector	f[4];
	Vector	vel1, vel2;
	Vector	pt1, pt2;
	Vector	Vr;
	float	Vrn;
	Vector	n;
	int	status = NOCOLLISION;
	bool	inside = true;
	Edge	e[12];
	int		j;
	float	t, tx, ty, tz;
	float	num, denom;
	int		a1, b1;
	int		a2, b2;
	Vector  vE1, vE2;
	

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

	e[0].a = 0;		e[0].b = 1;
	e[1].a = 1;		e[1].b = 2;
	e[2].a = 2;		e[2].b = 3;
	e[6].a = 3;		e[6].b = 0;	
	e[3].a = 4;		e[3].b = 5;
	e[4].a = 5;		e[4].b = 6;
	e[5].a = 6;		e[5].b = 7;	
	e[7].a = 7;		e[7].b = 4;
	e[8].a = 1;		e[8].b = 5;
	e[9].a = 2;		e[9].b = 6;
	e[10].a = 3;	e[10].b = 7;
	e[11].a = 0;	e[11].b = 4;

	//check each edge of body 1 against each edge of body 2
	for(i=0; i<12; i++)
	{
		a1 = e[i].a;
		b1 = e[i].b;
		for(j=0; j<12; j++)
		{
			// calc tx
			a2 = e[j].a;
			b2 = e[j].b;
			num = v1[a1].x - v2[a2].x;
			denom = v2[b2].x - v2[a2].x - v1[b1].x + v1[a1].x;
			
			if(fabs(denom) < tol)
				tx = -1; // parallel in x direction			
			else
				tx = num / denom;

			// calc ty
			a2 = e[j].a;
			b2 = e[j].b;
			num = v1[a1].y - v2[a2].y;
			denom = v2[b2].y - v2[a2].y - v1[b1].y + v1[a1].y;
			
			if(fabs(denom) < tol)
				ty = -1; // parallel in x direction			
			else
				ty = num / denom;

			// calc tz
			a2 = e[j].a;
			b2 = e[j].b;
			num = v1[a1].z - v2[a2].z;
			denom = v2[b2].z - v2[a2].z - v1[b1].z + v1[a1].z;
			
			if(fabs(denom) < tol)
				tz = -1; // parallel in x direction			
			else
				tz = num / denom;

			// test for intersection
			t = tx;
			if( ((fabs(t-ty)<PENETRATIONTOLERANCE/2) && (fabs(t-tz)<PENETRATIONTOLERANCE/2)) && (t>=0) && (t <=1))
			{ // have intersection

				tmp.x = v1[a1].x + (v1[b1].x - v1[a1].x) * t;
				tmp.y = v1[a1].y + (v1[b1].y - v1[a1].y) * t;
				tmp.z = v1[a1].z + (v1[b1].z - v1[a1].z) * t;				
				
				// calc relative velocity, if <0 collision
				pt1 = tmp - Bodies[body1].vPosition;
				pt2 = tmp - Bodies[body2].vPosition;

			
				vel1 = Bodies[body1].vVelocity + (Bodies[body1].vAngularVelocityGlobal^pt1);
				vel2 = Bodies[body2].vVelocity + (Bodies[body2].vAngularVelocityGlobal^pt2);

			
				vE1 = v1[b1] - v1[a1];
				vE2 = v2[b2] - v2[a2];
				
				n = vE1^vE2;
				
				n.Normalize();
				
				
				Vr = (vel1 - vel2);
				Vrn = Vr * n;
				
				if(Vrn < 0.0f)
				{

					// have a collision, fill the data structure and return
					assert(NumCollisions < (NUMBODIES*16));
					if(NumCollisions < (NUMBODIES*16))
					{
						CollisionData->body1 = body1;
						CollisionData->body2 = body2;
						CollisionData->vCollisionNormal = n;					
						CollisionData->vCollisionPoint = tmp;
						CollisionData->vRelativeVelocity = Vr;
						
						
						CollisionData->vCollisionTangent = (n^Vr)^n;
						

						CollisionData->vCollisionTangent.Normalize();
						CollisionData++;
						NumCollisions++;
						status = COLLISION;
					}									
				}
			}
		}
	}

	
	return status;
}

int	CheckVertexEdgeCollisions(pCollision CollisionData, int body1, int body2)
{
	int	status = NOCOLLISION;
	
	return status;
}

int	CheckBoxCollision(pCollision CollisionData, int body1, int body2)
{
	int	status1 = NOCOLLISION;
	int	status2 = NOCOLLISION;
	int	status3 = NOCOLLISION;
	
	status1 = CheckVertexFaceCollisions(CollisionData, body1, body2);
	status2 = CheckVertexEdgeCollisions(CollisionData, body1, body2);
	status3 = CheckEdgeEdgeCollisions(CollisionData, body1, body2);

	if((status1 == PENETRATING) || (status2 == PENETRATING) || (status3 == PENETRATING))
		return PENETRATING;
	else if((status1 == COLLISION) || (status2 == COLLISION) || (status3 == COLLISION))
		return COLLISION;
	else
		return NOCOLLISION;

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
		
		if(v1[i].z < COLLISIONTOLERANCE)
		{
			// calc relative velocity, if <0 collision
			pt1 = v1[i] - Bodies[body1].vPosition;

				
			vel1 = Bodies[body1].vVelocity+ (Bodies[body1].vAngularVelocityGlobal^pt1);
			
			
			n.x = 0;
			n.y = 0;
			n.z = 1;
				
			Vr = vel1;
			Vrn = Vr * n;
				
			if(Vrn < 0.0f)
			{

				// have a collision, fill the data structure and return
				assert(NumCollisions < (NUMBODIES*16));
				if(NumCollisions < (NUMBODIES*16))
				{
					CollisionData->body1 = body1;
					CollisionData->body2 = -1;
					CollisionData->vCollisionNormal = n;					
					CollisionData->vCollisionPoint = v1[i];
					CollisionData->vRelativeVelocity = Vr;
										
					CollisionData->vCollisionTangent = (n^Vr)^n;
					CollisionData->vCollisionTangent.Reverse();					
					
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

	//check each vertex of body1 against the ground plane
	for(i=0; i<8; i++)
	{	
		
		if(v1[i].z < COLLISIONTOLERANCE)
		{			
			pt1 = v1[i] - Bodies[body1].vPosition;

				
			vel1 = Bodies[body1].vVelocity + (Bodies[body1].vAngularVelocityGlobal^pt1);
			
			
			n.x = 0;
			n.y = 0;
			n.z = 1;
				
			Vr = vel1;
			Vrn = Vr * n;
				
			
			if(fabs(Vrn) <= sqrt(2*32.174*CONTACTTOLERANCE))//VELOCITYTOLERANCE) // at rest
			{
				// Check the relative acceleration
				Ar = Bodies[body1].vAcceleration + (Bodies[body1].vAngularVelocity^(Bodies[body1].vAngularVelocity^pt1)) + 
					 (Bodies[body1].vAngularAcceleration ^ pt1);
								
				Arn = Ar * n;

				if(Arn <= 0.0f)
				{
					// We have a contact, fill the data structure and return
					assert(NumCollisions < (NUMBODIES*16));
					if(NumCollisions < (NUMBODIES*16))
					{
						CollisionData->body1 = body1;
						CollisionData->body2 = -1;
						CollisionData->vCollisionNormal = n;					
						CollisionData->vCollisionPoint = v1[i];
						CollisionData->vRelativeVelocity = Vr;
						CollisionData->vRelativeAcceleration = Ar;
						
						
						CollisionData->vCollisionTangent = (n^Vr)^n;
						CollisionData->vCollisionTangent.Reverse();

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


