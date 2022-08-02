//----------------------------------------------------------------------------------------------------//
/*
	PHYSICS FOR GAME DEVELOPERS
	
	CHAPTERS 12 & 13 EXAMPLE PROGRAM

	NAME:		Hover
	PURPOSE:	To demonstrate 2D rigid body simulation
	BY:			David Bourg
	DATE:		09/01/00
	COPYRIGHT:	Copyright 2000 by David Bourg
*/
//----------------------------------------------------------------------------------------------------//

#include <assert.h>

#include <memory.h>
#include "Physics.h"



#define	_DTHRUST	1.0f
#define	_MAXTHRUST	2000.0f


extern	void	MyBeep();
int	pnpoly(int	npol, Vector *vlist, Vector p);



//------------------------------------------------------------------------//
// Global variables
//------------------------------------------------------------------------//
RigidBody2D	Hovercraft1, Hovercraft2;	// our two hovercraft rigid bodies
Vector		vCollisionNormal;			// the collision normal returned by our collision detection routine
Vector		vCollisionTangent;			// the collision tangent returned by our collision detection routine
Vector		vCollisionPoint;			// the world space point of collision
Vector		vRelativeVelocity;			// the world space relative velocity of the two bodies at the point of collision
float		fCr = COEFFICIENTOFRESTITUTION;				// the coefficient of restitution
float	const	ctol = COLLISIONTOLERANCE;			// the collision tolerance

int			CountDo;

float		Impulse;

pRigidBody2D CollisionBody1;
pRigidBody2D CollisionBody2;



//------------------------------------------------------------------------//
// This function sets the initial state of the hovercraft, i.e., its initial
// location, and speed, along with its thrust and orientation.
//------------------------------------------------------------------------//
void	InitializeHovercraft(pRigidBody2D body)
{	
	// Set initial position
	body->vPosition.x = 0.0f;
	body->vPosition.y = 0.0f;
	body->vPosition.z = 0.0f;	// set all z's to zero b/c this is a 2D example

	// Set initial velocity
	body->vVelocity.x = 0.0f;
	body->vVelocity.y = 0.0f;
	body->vVelocity.z = 0.0f;  // set all z's to zero b/c this is a 2D example
	body->fSpeed = 0.0f;

	// Set initial angular velocity
	body->vAngularVelocity.x = 0.0f;	// will always be zero in 2D
	body->vAngularVelocity.y = 0.0f;	// will always be zero in 2D
	body->vAngularVelocity.z = 0.0f;	// in 2D only this component with be used

	// Set the initial thrust, forces and moments
	body->vForces.x = 0.0f;
	body->vForces.y = 0.0f;
	body->vForces.z = 0.0f;		// set all z's to zero b/c this is a 2D example
	
	body->vMoment.x = 0.0f;		// will always be zero in 2D
	body->vMoment.y = 0.0f;		// will always be zero in 2D
	body->vMoment.z = 0.0f;		// in 2D only this component with be used

	// Zero the velocity in body space coordinates
	body->vVelocityBody.x = 0.0f;
	body->vVelocityBody.y = 0.0f;
	body->vVelocityBody.z = 0.0f;

	// Set the initial orientation
	body->fOrientation = 0.0;
	
	// Now define the mass properties
	body->fMass = 621.6;
	body->fInertia = 383320;
	body->fInertiaInverse = 1.0f / body->fInertia;
		
	body->CP.x = -0.0f;		body->CP.y = 0.0f;		// coordinates of the cushion center of pressure
	body->CD.x = -2.5f;		body->CD.y = 0.0f;		// coordinates of the body center of drag
	body->CT.x = -30.0f;	body->CT.y = 0.0f;		// coordinates of the propeller thrust vector
	body->CPT.x = 30.0f;	body->CPT.y = 25.0f;	// coordinates of the port bow thruster
	body->CST.x = 30.0f;	body->CST.y = -25.0f;	// coordinates of the starboard bow thruster

	body->CushionArea = 3325.0f;					// planform area of the cushion
	body->ProjectedArea = 1500.0f;					// mean projected area of the entire body
	body->ThrustForce = 0;							// initial thrust force

	body->fWidth = 50;								// width of the body (measured along y-axis)
	body->fLength = 70;							// length of the body (measured along x-axis)
}

//------------------------------------------------------------------------//
// This function calculates all of the forces and moments acting on the 
// plane at any given time.
//------------------------------------------------------------------------//
void	CalcLoads(pRigidBody2D body)
{
	Vector	Fb;				// stores the sum of forces
	Vector	Mb;				// stores the sum of moments
	Vector	Thrust;			// thrust vector
	
	// reset forces and moments:
	body->vForces.x = 0.0f;
	body->vForces.y = 0.0f;
	body->vForces.z = 0.0f;	// always zero in 2D

	body->vMoment.x = 0.0f;	// always zero in 2D
	body->vMoment.y = 0.0f;	// always zero in 2D
	body->vMoment.z = 0.0f;

	Fb.x = 0.0f;	
	Fb.y = 0.0f;	
	Fb.z = 0.0f;	

	Mb.x = 0.0f;
	Mb.y = 0.0f;
	Mb.z = 0.0f;

	// Define the thrust vector, which acts through the craft's CG
	Thrust.x = 1.0f;
	Thrust.y = 0.0f;
	Thrust.z = 0.0f;  // zero in 2D
	Thrust *= body->ThrustForce;
	
	// Calculate forces and moments in body space:
	Vector	vLocalVelocity;
	float	fLocalSpeed;
	Vector	vDragVector;	
	float	tmp;
	Vector	vResultant;	
	Vector	vtmp;	

	// Calculate the aerodynamic drag force:
		// Calculate local velocity:
		// The local velocity includes the velocity due to linear motion of the craft, 
		// plus the velocity at each element due to the rotation of the craft.
		vtmp = body->vAngularVelocity^body->CD; // rotational part
		vLocalVelocity = body->vVelocityBody + vtmp; 

		// Calculate local air speed
		fLocalSpeed = vLocalVelocity.Magnitude();

		// Find the direction in which drag will act.
		// Drag always acts inline with the relative velocity but in the opposing direction
		if(fLocalSpeed > tol) 
		{
			vLocalVelocity.Normalize();
			vDragVector = -vLocalVelocity;		

			// Determine the resultant force on the element.
			tmp = 0.5f * rho * fLocalSpeed*fLocalSpeed * body->ProjectedArea;		
			vResultant = vDragVector * LINEARDRAGCOEFFICIENT * tmp; // simulate fuselage drag

			// Keep a running total of these resultant forces (total force)
			Fb += vResultant;
		
			// Calculate the moment about the CG of this element's force
			// and keep a running total of these moments (total moment)
			vtmp = body->CD^vResultant; 
			Mb += vtmp;
		}

	// Calculate the Port & Starboard bow thruster forces:
		// Keep a running total of these resultant forces (total force)
		Fb += body->PThrust;

		// Calculate the moment about the CG of this element's force
		// and keep a running total of these moments (total moment)
		vtmp = body->CPT^body->PThrust; 
		Mb += vtmp;

		// Keep a running total of these resultant forces (total force)
		Fb += body->SThrust;

		// Calculate the moment about the CG of this element's force
		// and keep a running total of these moments (total moment)
		vtmp = body->CST^body->SThrust; 		
		Mb += vtmp;

	// Calculate rotational drag
		if(body->vAngularVelocity.Magnitude() > tol)
		{
			vtmp.x = 0;
			vtmp.y = 0;
			tmp = 0.5f * rho * body->vAngularVelocity.z*body->vAngularVelocity.z * body->ProjectedArea;
			if(body->vAngularVelocity.z > 0.0)
				vtmp.z = -ANGULARDRAGCOEFFICIENT * tmp;		
			else
				vtmp.z = ANGULARDRAGCOEFFICIENT * tmp;		

			Mb += vtmp;
		}


	// Now add the propulsion thrust
	Fb += Thrust; // no moment since line of action is through CG

	// Convert forces from model space to earth space
	body->vForces = VRotate2D(body->fOrientation, Fb);

	body->vMoment += Mb;	
}

//------------------------------------------------------------------------//
//
//------------------------------------------------------------------------//
Vector	GetBodyZAxisVector(void)
{

	Vector	v;

	v.x = 0.0f;
	v.y = 0.0f;
	v.z = 1.0f;

	return v;
}

//------------------------------------------------------------------------//
//
//------------------------------------------------------------------------//
Vector	GetBodyXAxisVector(int	craft)
{
	Vector v;

	v.x = 1.0f;
	v.y = 0.0f;
	v.z = 0.0f;

	if(craft == 1)	
		return VRotate2D(Hovercraft1.fOrientation, v);
	else
		return VRotate2D(Hovercraft2.fOrientation, v);
	
}

//------------------------------------------------------------------------//
//
//------------------------------------------------------------------------//
void	IncThrust(int craft)
{
	if(craft == 1)
	{	
		Hovercraft1.ThrustForce += _DTHRUST;
		if(Hovercraft1.ThrustForce > _MAXTHRUST)
			Hovercraft1.ThrustForce = _MAXTHRUST;
	} else {
		Hovercraft2.ThrustForce += _DTHRUST;
		if(Hovercraft2.ThrustForce > _MAXTHRUST)
			Hovercraft2.ThrustForce = _MAXTHRUST;
	}
}

//------------------------------------------------------------------------//
//
//------------------------------------------------------------------------//
void	DecThrust(int craft)
{
	
	if(craft == 1)
	{
		Hovercraft1.ThrustForce -= _DTHRUST;
		if(Hovercraft1.ThrustForce < -_MAXTHRUST)
			Hovercraft1.ThrustForce = -_MAXTHRUST;
	} else {
		Hovercraft2.ThrustForce -= _DTHRUST;
		if(Hovercraft2.ThrustForce < -_MAXTHRUST)
			Hovercraft2.ThrustForce = -_MAXTHRUST;
	}	
}

//------------------------------------------------------------------------//
//
//------------------------------------------------------------------------//
void	PortThruster(int craft)
{			
	if(craft == 1)	
		Hovercraft1.PThrust.y = -500.0f;
	else
		Hovercraft2.PThrust.y = -500.0f;
}

//------------------------------------------------------------------------//
//
//------------------------------------------------------------------------//
void	STBDThruster(int craft)
{	
	if(craft == 1)
		Hovercraft1.SThrust.y = 500.0f;
	else
		Hovercraft2.SThrust.y = 500.0f;
}

//------------------------------------------------------------------------//
//
//------------------------------------------------------------------------//
void	ZeroThrusters(int craft)
{	
	if(craft == 1)
	{	
		Hovercraft1.PThrust.x = 0.0f;
		Hovercraft1.PThrust.y = 0.0f;
		Hovercraft1.PThrust.z = 0.0f;

		Hovercraft1.SThrust.x = 0.0f;
		Hovercraft1.SThrust.y = 0.0f;
		Hovercraft1.SThrust.z = 0.0f;
	} else {
		Hovercraft2.PThrust.x = 0.0f;
		Hovercraft2.PThrust.y = 0.0f;
		Hovercraft2.PThrust.z = 0.0f;

		Hovercraft2.SThrust.x = 0.0f;
		Hovercraft2.SThrust.y = 0.0f;
		Hovercraft2.SThrust.z = 0.0f;
	}
}


void	Initialize(void)
{
	InitializeHovercraft(&Hovercraft1);
	InitializeHovercraft(&Hovercraft2);

	Hovercraft2.vPosition.y = 60;	//0;
	Hovercraft2.vPosition.x = 500;//1500;	
	Hovercraft2.fOrientation = 0;//135;	
}

// Without collision response
/*void StepSimulation(float dt)
{
	UpdateBody(&Hovercraft1, dt);		
	UpdateBody(&Hovercraft2, dt);		
}*/


// With collision response
/*void	StepSimulation(float dt)
{		
	float	dtime = dt;
	bool	tryAgain = true;
	int		check;
	RigidBody2D	craft1Copy, craft2Copy;
	bool	didPen = false;
	int		count = 0;

	// do Hovercraft 1 first...		
	while(tryAgain && dtime > tol)
	{
		tryAgain = false;
		memcpy(&craft1Copy, &Hovercraft1, sizeof(RigidBody2D));
		memcpy(&craft2Copy, &Hovercraft2, sizeof(RigidBody2D));

		UpdateBody(&craft1Copy, dtime);		
		//check = CheckForCollisionSimple(&craft1Copy, &Hovercraft2);
		
		check = CheckForCollision(&craft1Copy, &Hovercraft2);
		
		if(check == -1) // penetrating
		{
			dtime = dtime/2;
			tryAgain = true;
			didPen = true;
		} else if(check == 1 || didPen) // colliding
		{
			CountDo = 0;
			do
			{
				CountDo++;

				// Applies only linear impulse using bounding circle collision detection
				//ApplyLinearImpulse(&craft1Copy, &craft2Copy);
				//check = CheckForCollisionSimple(&craft1Copy, &craft2Copy);

				// Applies both linear and angular effects
				ApplyImpulse(&craft1Copy, &craft2Copy);				
				check = CheckForCollision(&craft1Copy, &craft2Copy);

				count++;
			} while(check == 1 && count < 150);
		}
	}	

	memcpy(&Hovercraft1, &craft1Copy, sizeof(RigidBody2D));
	memcpy(&Hovercraft2, &craft2Copy, sizeof(RigidBody2D));

	// now handle the second hovercraft	
	tryAgain = true;
	//dtime = dt;
	didPen = false;
	count = 0;
	while(tryAgain && dtime > tol)
	{
		tryAgain = false;
		memcpy(&craft1Copy, &Hovercraft1, sizeof(RigidBody2D));
		memcpy(&craft2Copy, &Hovercraft2, sizeof(RigidBody2D));

		UpdateBody(&craft2Copy, dtime);		
		//check = CheckForCollisionSimple(&craft2Copy, &Hovercraft1);
		
		check = CheckForCollision(&craft2Copy, &Hovercraft1);
		
		if(check == -1) // penetrating
		{
			dtime = dtime/2;
			tryAgain = true;
			didPen = true;
		} else if(check == 1 || didPen) // colliding
		{
			do
			{
				//ApplyLinearImpulse(&craft2Copy, &craft1Copy);
				//check = CheckForCollisionSimple(&craft2Copy, &craft1Copy);

				ApplyImpulse(&craft2Copy, &craft1Copy);				
				check = CheckForCollision(&craft2Copy, &craft1Copy);

				count++;
			} while(check == 1 && count < 150);
		}
	}

	memcpy(&Hovercraft1, &craft1Copy, sizeof(RigidBody2D));
	memcpy(&Hovercraft2, &craft2Copy, sizeof(RigidBody2D));

}*/

void	StepSimulation(float dt)
{		
	float			dtime = dt;
	bool			tryAgain = true;
	int				check=0;	
	RigidBody2D		craft1Copy, craft2Copy;
	bool			didPen = false;
		
	while(tryAgain && (dtime > tol))
	{
		tryAgain = false;
		memcpy(&craft1Copy, &Hovercraft1, sizeof(RigidBody2D));
		memcpy(&craft2Copy, &Hovercraft2, sizeof(RigidBody2D));

		UpdateBody(&craft1Copy, dtime);		
		UpdateBody(&craft2Copy, dtime);

		//UpdateBodyEuler(&craft1Copy, dtime);		
		//UpdateBodyEuler(&craft2Copy, dtime);
		
		CollisionBody1 = 0;
		CollisionBody2 = 0;
		check = CheckForCollision(&craft1Copy, &craft2Copy);
		//check = CheckForCollisionSimple(&craft1Copy, &craft2Copy);

		if(check == PENETRATING)
		{
			dtime = dtime/2;
			tryAgain = true;
			didPen = true;			
		} else if(check == COLLISION)
		{
			if(CollisionBody1 != 0 && CollisionBody2 != 0)
				ApplyImpulse(CollisionBody1,  CollisionBody2);	
				//ApplyLinearImpulse(CollisionBody1, CollisionBody2);
		}		
	}	

	if(!didPen)
	{
		memcpy(&Hovercraft1, &craft1Copy, sizeof(RigidBody2D));
		memcpy(&Hovercraft2, &craft2Copy, sizeof(RigidBody2D));
	}
}



void	UpdateBody(pRigidBody2D craft, float dtime)
{
		Vector Ae;	
		float Aa;
		RigidBody2D	body;
		Vector		k1, k2;
		float		k1a, k2a;		
		float		dt = dtime;			
	
		// make a copy of the hovercraft's state		
		memcpy(&body, craft, sizeof(RigidBody2D));
		
		// calculate the k1 terms for both linear and angular velocity
		CalcLoads(&body);		
		Ae = body.vForces / body.fMass;		
		k1 = Ae * dt;

		Aa = body.vMoment.z / body.fInertia;
		k1a = Aa * dt;

		// add the k1 terms to the respective initial velocities
		body.vVelocity += k1;
		body.vAngularVelocity.z += k1a;

		// calculate new loads and the k2 terms
		CalcLoads(&body);
		Ae = body.vForces / body.fMass;		
		k2 = Ae * dt;

		Aa = body.vMoment.z / body.fInertia;
		k2a = Aa * dt;
		
		// now calculate the hovercraft's new velocities at time t + dt
		craft->vVelocity += (k1 + k2) / 2.0f;
		craft->vAngularVelocity.z += (k1a + k2a) / 2.0f;
				
		// calculate the new position 
		craft->vPosition += craft->vVelocity * dt;		
		craft->fSpeed = craft->vVelocity.Magnitude();		

		// calculate the new orientation
		craft->fOrientation += RadiansToDegrees(craft->vAngularVelocity.z * dt);
		craft->vVelocityBody = VRotate2D(-craft->fOrientation, craft->vVelocity);	
	
}

void	UpdateBodyEuler(pRigidBody2D craft, float dt)
{
		Vector a;
		Vector dv;
		Vector ds;
		float  aa;
		float  dav;
		float  dr;
	
		// Calculate forces and moments:
		CalcLoads(craft);
		
		// Integrate linear equation of motion:
		a = craft->vForces / craft->fMass;
		
		dv = a * dt;
		craft->vVelocity += dv;

		ds = craft->vVelocity * dt;
		craft->vPosition += ds;

		// Integrate angular equation of motion:
		aa = craft->vMoment.z / craft->fInertia;

		dav = aa * dt;
		
		craft->vAngularVelocity.z += dav;
		
		dr = RadiansToDegrees(craft->vAngularVelocity.z * dt);
		craft->fOrientation += dr; 
		
		// Misc. calculations:
		craft->fSpeed = craft->vVelocity.Magnitude();		
		craft->vVelocityBody = VRotate2D(-craft->fOrientation, craft->vVelocity);	
}



// Applies impulse that includes both linear and angular effects
void		ApplyImpulse(pRigidBody2D body1, pRigidBody2D body2)
{
	double	j, Vrt;
	double	mu = FRICTIONCOEFFICIENT;
	Vector	n;

	j = (-(1+fCr) * (vRelativeVelocity*vCollisionNormal)) /						
		( (1/body1->fMass + 1/body2->fMass) +
		(vCollisionNormal * ( ( (body1->vCollisionPoint ^ vCollisionNormal)/body1->fInertia )^body1->vCollisionPoint) ) +
		(vCollisionNormal * ( ( (body2->vCollisionPoint ^ vCollisionNormal)/body2->fInertia )^body2->vCollisionPoint) )
		);

	Impulse = j;
	
	Vrt = vRelativeVelocity * vCollisionTangent;

	if(fabs(Vrt) > 0.0) {
		// with friction
		body1->vVelocity += ( (j * vCollisionNormal) + ((mu * j) * vCollisionTangent) ) / body1->fMass;										
		body1->vAngularVelocity += (body1->vCollisionPoint ^ ((j * vCollisionNormal) + ((mu * j) * vCollisionTangent))) / body1->fInertia;

		body2->vVelocity += ((-j * vCollisionNormal) + ((mu * j) * vCollisionTangent)) / body2->fMass;										
		body2->vAngularVelocity += (body2->vCollisionPoint ^ ((-j * vCollisionNormal) + ((mu * j) * vCollisionTangent))) / body2->fInertia;

	} else {
		// without friction
		body1->vVelocity += (j * vCollisionNormal) / body1->fMass;
		body1->vAngularVelocity += (body1->vCollisionPoint ^ (j * vCollisionNormal)) / body1->fInertia;

		body2->vVelocity -= (j * vCollisionNormal) / body2->fMass;										
		body2->vAngularVelocity -= (body2->vCollisionPoint ^ (j * vCollisionNormal)) / body2->fInertia;
	}
}


// Applies only linear impulse
void		ApplyLinearImpulse(pRigidBody2D body1, pRigidBody2D body2)
{
	float j;	



	// calculate the impulse:
	j = (-(1+fCr) * (vRelativeVelocity*vCollisionNormal)) /
		((1/body1->fMass + 1/body2->fMass));
	
	Impulse = j;

	// calculate the new velocities after impact:
	body1->vVelocity += (j * vCollisionNormal) / body1->fMass;	
	body2->vVelocity -= (j * vCollisionNormal) / body2->fMass;	
}


// simple bounding circle algorithm
int		CheckForCollisionSimple(pRigidBody2D body1, pRigidBody2D body2)
{
	float	r, Vrn, s;	
	Vector	d, v1, v2;
	int		retval = 0;

	// calculate separation:
	r = body1->fLength/2 + body2->fLength/2;
	d = body1->vPosition - body2->vPosition;
	s = d.Magnitude() - r;
	
	// set collision normal vector:
	d.Normalize();		
	vCollisionNormal = d;
	
	// calculate relative normal velocity:
	v1 = body1->vVelocity;
	v2 = body2->vVelocity;					
	vRelativeVelocity = v1 - v2;
	Vrn = vRelativeVelocity * vCollisionNormal;

	// test:
	if((fabs(s) <= ctol) && (Vrn < 0.0))
	{
		retval = COLLISION;
		CollisionBody1 = body1;
		CollisionBody2 = body2;
	} else 	if(s < -ctol) 
	{
		retval = PENETRATING;
	} else 
		retval = NOCOLLISION;

	return retval;
}

// vertex-vertex or vertex-edge collisions
int		CheckForCollision(pRigidBody2D body1, pRigidBody2D body2)
{
	Vector	d, vList1[4], vList2[4], v1, v2, u, edge, p, proj;
	float	r, wd, lg, s, dist, dot, Vrn;
	int		i, j, retval = 0;
	bool	interpenetrating = false;
	bool	haveNodeEdge = false;	
	
	// First check to see if the bounding circles are colliding
	r = body1->fLength/2 + body2->fLength/2;
	d = body1->vPosition - body2->vPosition;
	s = d.Magnitude() - r;
	if(s <= ctol)
	{   // We have a possible collision, check further
		// build vertex lists for each hovercraft
		wd = body1->fWidth;
		lg = body1->fLength;
		vList1[0].y = wd/2;		vList1[0].x = lg/2;
		vList1[1].y = -wd/2;	vList1[1].x = lg/2;
		vList1[2].y = -wd/2;	vList1[2].x = -lg/2;
		vList1[3].y = wd/2;		vList1[3].x = -lg/2;		
		for(i=0; i<4; i++)
		{
			v1 = VRotate2D(body1->fOrientation, vList1[i]);
			vList1[i] = v1 + body1->vPosition;			
		}

		wd = body2->fWidth;
		lg = body2->fLength;
		vList2[0].y = wd/2;		vList2[0].x = lg/2;
		vList2[1].y = -wd/2;	vList2[1].x = lg/2;
		vList2[2].y = -wd/2;	vList2[2].x = -lg/2;
		vList2[3].y = wd/2;		vList2[3].x = -lg/2;		
		for(i=0; i<4; i++)
		{
			v2 = VRotate2D(body2->fOrientation, vList2[i]);
			vList2[i] = v2 + body2->vPosition;			
		}
		
		// Check for vertex-edge collision		
		for(i=0; i<4 && !haveNodeEdge; i++)
		{
				for(j=0; j<4 && !haveNodeEdge; j++)
				{							
					if(j==3)
						edge = vList2[j/*0*/] - vList2[0/*j*/];
					else
						edge = vList2[j+1] - vList2[j];				
					u = edge;
					u.Normalize();

					p = vList1[i] - vList2[j];					
					proj = (p * u) * u;

					d = p^u;					
					dist = d.Magnitude();

					dot = p * edge;
					if(dot > 0)
						dist = -dist; // point is on inside

					vCollisionPoint = vList1[i];
					body1->vCollisionPoint = vCollisionPoint - body1->vPosition;
					body2->vCollisionPoint = vCollisionPoint - body2->vPosition;

										
					vCollisionNormal = ((u^p)^u);
					vCollisionNormal.Normalize();
					
					v1 = body1->vVelocity + (body1->vAngularVelocity^body1->vCollisionPoint);
					v2 = body2->vVelocity + (body2->vAngularVelocity^body2->vCollisionPoint);


					vRelativeVelocity = (v1 - v2);
					Vrn = vRelativeVelocity * vCollisionNormal;

					vCollisionTangent = (vCollisionNormal^vRelativeVelocity)^vCollisionNormal;
					vCollisionTangent.Normalize();

					if( (proj.Magnitude() > tol) && 
						(proj.Magnitude() <= edge.Magnitude()) && 
						(dist <= ctol) && 
						(Vrn < 0.0f)						
						)
					{
						haveNodeEdge = true;
						CollisionBody1 = body1;
						CollisionBody2 = body2;

					}
				}
		}			

		for(i=0; i<4 && !haveNodeEdge; i++)
		{
				for(j=0; j<4 && !haveNodeEdge; j++)
				{							
					if(j==3)
						edge = vList1[j/*0*/] - vList1[0/*j*/];
					else
						edge = vList1[j+1] - vList1[j];				
					u = edge;
					u.Normalize();

					p = vList2[i] - vList1[j];					
					proj = (p * u) * u;

					d = p^u;					
					dist = d.Magnitude();

					dot = p * edge;
					if(dot > 0)
						dist = -dist; // point is on inside

					vCollisionPoint = vList2[i];
					body1->vCollisionPoint = vCollisionPoint - body1->vPosition;
					body2->vCollisionPoint = vCollisionPoint - body2->vPosition;


					vCollisionNormal = ((u^p)^u);
					vCollisionNormal.Normalize();
					
					v1 = body1->vVelocity + (body1->vAngularVelocity^body1->vCollisionPoint);
					v2 = body2->vVelocity + (body2->vAngularVelocity^body2->vCollisionPoint);


					vRelativeVelocity = (v1 - v2);
					Vrn = vRelativeVelocity * vCollisionNormal;

					vCollisionTangent = (vCollisionNormal^vRelativeVelocity)^vCollisionNormal;
					vCollisionTangent.Normalize();

					if( (proj.Magnitude() > tol) && 
						(proj.Magnitude() <= edge.Magnitude()) && 
						(dist <= ctol) && 
						(Vrn < 0.0f)						
						)
					{
						haveNodeEdge = true;
						CollisionBody1 = body2;
						CollisionBody2 = body1;
					}
				}
		}		

		if(!haveNodeEdge)
		{
			for(i=0; i<4 && !interpenetrating; i++)
			{
				if(pnpoly(4, vList2, vList1[i]) == 1)
					interpenetrating = true;

				if(pnpoly(4, vList1, vList2[i]) == 1)
					interpenetrating = true;
			}
		}

		if(interpenetrating)
			retval = PENETRATING;					
		else if(haveNodeEdge)
			retval = COLLISION;
		else
			retval = NOCOLLISION;		

	} else
	{
		retval = NOCOLLISION;	
	}

	return retval;
}

bool	ArePointsEqual(Vector p1, Vector p2)
{	
	// Points are equal if each component is within ctol of each other
	if(	(fabs(p1.x - p2.x) <= 0.1) &&
		(fabs(p1.y - p2.y) <= 0.1) &&
		(fabs(p1.z - p2.z) <= 0.1) )
		return true;
	else
		return false;	
}

Vector	VRotate2D( float angle, Vector u)
{
	float	x,y;

	x = u.x * cos(DegreesToRadians(-angle)) + u.y * sin(DegreesToRadians(-angle));
	y = -u.x * sin(DegreesToRadians(-angle)) + u.y * cos(DegreesToRadians(-angle));

	return Vector( x, y, 0);
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






