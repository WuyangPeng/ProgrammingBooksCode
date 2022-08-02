//----------------------------------------------------------------------------------------------------//
/*
	PHYSICS FOR GAME DEVELOPERS
	
	CHAPTERS 7 & 15 EXAMPLE PROGRAM

	NAME:		FlightSim
	PURPOSE:	To demonstrate 3D rigid body flight simulation
	BY:			David Bourg
	DATE:		07/24/00
	COPYRIGHT:	Copyright 2000 by David Bourg
*/
//----------------------------------------------------------------------------------------------------//
#include "Physics.h"

#define	_DTHRUST	10.0f
#define	_MAXTHRUST	3000.0f

//------------------------------------------------------------------------//
// Global variables
//------------------------------------------------------------------------//
RigidBody	Airplane;		// Rigid body properties of our airplane
BodyElement	Element[8];		// Mass, inertia and lifting surface properties of our airplane
Vector		Thrust;			// Thrust vector, assumed to act through the plane's CG
float		ThrustForce;	// Magnitude of the thrust force
bool		Stalling;		// Flag to let us know if we are in a stalled condition
bool		Flaps;			// Flag to let us know if the flaps are down

//------------------------------------------------------------------------//
// This function sets the initial state of the plane, i.e., its initial
// location, and speed, along with its thrust and attitude.
// This function also calls another function to calculate the plane's mass
// properties.
//------------------------------------------------------------------------//
void	InitializeAirplane(void)
{	
	float iRoll, iPitch, iYaw;

	// Set initial position
	Airplane.vPosition.x = -5000.0f;
	Airplane.vPosition.y = 0.0f;
	Airplane.vPosition.z = 2000.0f;

	// Set initial velocity
	Airplane.vVelocity.x = 60.0f;
	Airplane.vVelocity.y = 0.0f;
	Airplane.vVelocity.z = 0.0f;
	Airplane.fSpeed = 60.0f;

	// Set initial angular velocity
	Airplane.vAngularVelocity.x = 0.0f;
	Airplane.vAngularVelocity.y = 0.0f;
	Airplane.vAngularVelocity.z = 0.0f;

	// Set the initial thrust, forces and moments
	Airplane.vForces.x = 500.0f;
	Airplane.vForces.y = 0.0f;
	Airplane.vForces.z = 0.0f;
	ThrustForce = 500.0;

	Airplane.vMoments.x = 0.0f;
	Airplane.vMoments.y = 0.0f;
	Airplane.vMoments.z = 0.0f;

	// Zero the velocity in body space coordinates
	Airplane.vVelocityBody.x = 0.0f;
	Airplane.vVelocityBody.y = 0.0f;
	Airplane.vVelocityBody.z = 0.0f;
	
	// Set these to false at first, you can control later using the keyboard
	Stalling = false;
	Flaps = false;

	// Set the initial orientation
	iRoll = 0.0f;
	iPitch = 0.0f;
	iYaw = 0.0f;
	Airplane.qOrientation = MakeQFromEulerAngles(iRoll, iPitch, iYaw);
	
	// Now go ahead and calculate the plane's mass properties
	CalcAirplaneMassProperties();
}

//------------------------------------------------------------------------//
// This model uses a set of eight descrete elements to represent the 
// airplane.  The elements are described below:
//
//		Element 1:	Outboard, Port (left) wing section fitted with ailerons
//		Element 2:  Inboard, Port wing section fitted with landing flaps
//		Element 3:  Inboard, Starboard (right) wing section fitted with landing flaps
//		Element 4:	Outboard, Starboard wing section fitted with ailerons
//		Element 5:	Port elevator fitted with flap
//		Element 6:	Starboard elevator fitted with flap
//		Element 7:	Vertical tail/rudder (no flap the whole thing rotates)
//		Element 8:  The fuselage
//
//	This function first sets up each element and then goes on to calculate
//  the combined weight, center of gravity, and inertia tensor for the plane.
//  Some other properties of each element are also calculated which you'll
//  need when calculating the lift and drag forces on the plane.
//------------------------------------------------------------------------//
void	CalcAirplaneMassProperties(void)
{
	float	mass;
	Vector	vMoment;
	Vector	CG;
	int		i;
	float	Ixx, Iyy, Izz, Ixy, Ixz, Iyz;
	float	in, di;

	// Initialize the elements here
	// Initially the coordinates of each element are referenced from
	// a design coordinates system located at the very tail end of the plane,
	// its baseline and center line.  Later, these coordinates will be adjusted
	// so that each element is referenced to the combined center of gravity of
	// the airplane.
	Element[0].fMass = 6.56f;
	Element[0].vDCoords = Vector(14.5f,12.0f,2.5f);
	Element[0].vLocalInertia = Vector(13.92f,10.50f,24.00f);
	Element[0].fIncidence = -3.5f;
	Element[0].fDihedral = 0.0f;
	Element[0].fArea = 31.2f;
	Element[0].iFlap = 0;

	Element[1].fMass = 7.31f;
	Element[1].vDCoords = Vector(14.5f,5.5f,2.5f);
	Element[1].vLocalInertia = Vector(21.95f,12.22f,33.67f);
	Element[1].fIncidence = -3.5f;
	Element[1].fDihedral = 0.0f;
	Element[1].fArea = 36.4f;
	Element[1].iFlap = 0;

	Element[2].fMass = 7.31f;
	Element[2].vDCoords = Vector(14.5f,-5.5f,2.5f);
	Element[2].vLocalInertia = Vector(21.95f,12.22f,33.67f);
	Element[2].fIncidence = -3.5f;
	Element[2].fDihedral = 0.0f;
	Element[2].fArea = 36.4f;
	Element[2].iFlap = 0;

	Element[3].fMass = 6.56f;
	Element[3].vDCoords = Vector(14.5f,-12.0f,2.5f);
	Element[3].vLocalInertia = Vector(13.92f,10.50f,24.00f);
	Element[3].fIncidence = -3.5f;
	Element[3].fDihedral = 0.0f;
	Element[3].fArea = 31.2f;
	Element[3].iFlap = 0;

	Element[4].fMass = 2.62f;
	Element[4].vDCoords = Vector(3.03f,2.5f,3.0f);
	Element[4].vLocalInertia = Vector(0.837f,0.385f,1.206f);
	Element[4].fIncidence = 0.0f;
	Element[4].fDihedral = 0.0f;
	Element[4].fArea = 10.8f;
	Element[4].iFlap = 0;

	Element[5].fMass = 2.62f;
	Element[5].vDCoords = Vector(3.03f,-2.5f,3.0f);
	Element[5].vLocalInertia = Vector(0.837f,0.385f,1.206f);
	Element[5].fIncidence = 0.0f;
	Element[5].fDihedral = 0.0f;
	Element[5].fArea = 10.8f;
	Element[5].iFlap = 0;

	Element[6].fMass = 2.93f;
	Element[6].vDCoords = Vector(2.25f,0.0f,5.0f);
	Element[6].vLocalInertia = Vector(1.262f,1.942f,0.718f);
	Element[6].fIncidence = 0.0f;
	Element[6].fDihedral = 90.0f;
	Element[6].fArea = 12.0f;
	Element[6].iFlap = 0;

	Element[7].fMass = 31.8f;
	Element[7].vDCoords = Vector(15.25f,0.0f,1.5f);
	Element[7].vLocalInertia = Vector(66.30f,861.9f,861.9f);
	Element[7].fIncidence = 0.0f;
	Element[7].fDihedral = 0.0f;
	Element[7].fArea = 84.0f;
	Element[7].iFlap = 0;

	// Calculate the vector normal (perpendicular) to each lifting surface.
	// This is required when calculating the relative air velocity for
	// lift and drag calculations.
	for (i = 0; i< 8; i++)
	{
		in = DegreesToRadians(Element[i].fIncidence);
		di = DegreesToRadians(Element[i].fDihedral);
		Element[i].vNormal = Vector((float)sin(in), (float)(cos(in)*sin(di)), (float)(cos(in)*cos(di)));
		Element[i].vNormal.Normalize();
	}

	// Calculate total mass
	mass = 0;
	for (i = 0; i< 8; i++)	
		mass += Element[i].fMass;
	
	// Calculate combined center of gravity location
	vMoment = Vector(0.0f, 0.0f, 0.0f);
	for (i = 0; i< 8; i++)
	{
		vMoment += Element[i].fMass*Element[i].vDCoords;
	}
	CG = vMoment/mass;

	// Calculate coordinates of each element with respect to the combined CG 
	for (i = 0; i< 8; i++)
	{
		Element[i].vCGCoords = Element[i].vDCoords - CG;
	}

	// Now calculate the moments and products of inertia for the combined elements
	// (This inertia matrix (tensor) is in body coordinates)
	Ixx = 0;	Iyy = 0;	Izz = 0;
	Ixy = 0;	Ixz = 0;	Iyz = 0;
	for (i = 0; i< 8; i++)
	{
		Ixx += Element[i].vLocalInertia.x + Element[i].fMass * (Element[i].vCGCoords.y*Element[i].vCGCoords.y + Element[i].vCGCoords.z*Element[i].vCGCoords.z);
		Iyy += Element[i].vLocalInertia.y + Element[i].fMass * (Element[i].vCGCoords.z*Element[i].vCGCoords.z + Element[i].vCGCoords.x*Element[i].vCGCoords.x);
		Izz += Element[i].vLocalInertia.z + Element[i].fMass * (Element[i].vCGCoords.x*Element[i].vCGCoords.x + Element[i].vCGCoords.y*Element[i].vCGCoords.y);
		Ixy += Element[i].fMass * (Element[i].vCGCoords.x * Element[i].vCGCoords.y);
		Ixz += Element[i].fMass * (Element[i].vCGCoords.x * Element[i].vCGCoords.z);
		Iyz += Element[i].fMass * (Element[i].vCGCoords.y * Element[i].vCGCoords.z);
	}	
	
	// Finally setup the airplane's mass and its inertia matrix and take the inverse of the inertia matrix
	Airplane.fMass = mass;
	Airplane.mInertia.e11 = Ixx;	Airplane.mInertia.e12 = -Ixy;	Airplane.mInertia.e13 = -Ixz;
	Airplane.mInertia.e21 = -Ixy;	Airplane.mInertia.e22 = Iyy;	Airplane.mInertia.e23 = -Iyz;
	Airplane.mInertia.e31 = -Ixz;	Airplane.mInertia.e32 = -Iyz;	Airplane.mInertia.e33 = Izz;

	Airplane.mInertiaInverse = Airplane.mInertia.Inverse();	
}

//------------------------------------------------------------------------//
// This function calculates all of the forces and moments acting on the 
// plane at any given time.
//------------------------------------------------------------------------//
void	CalcAirplaneLoads(void)
{
	Vector	Fb, Mb;
	
	// reset forces and moments:
	Airplane.vForces.x = 0.0f;
	Airplane.vForces.y = 0.0f;
	Airplane.vForces.z = 0.0f;

	Airplane.vMoments.x = 0.0f;
	Airplane.vMoments.y = 0.0f;
	Airplane.vMoments.z = 0.0f;

	Fb.x = 0.0f;	Mb.x = 0.0f;
	Fb.y = 0.0f;	Mb.y = 0.0f;
	Fb.z = 0.0f;	Mb.z = 0.0f;

	// Define the thrust vector, which acts through the plane's CG
	Thrust.x = 1.0f;
	Thrust.y = 0.0f;
	Thrust.z = 0.0f;
	Thrust *= ThrustForce;
	
	// Calculate forces and moments in body space:
	Vector	vLocalVelocity;
	float	fLocalSpeed;
	Vector	vDragVector;
	Vector	vLiftVector;
	float	fAttackAngle;
	float	tmp;
	Vector	vResultant;
	int		i;
	Vector	vtmp;
	
	Stalling = false;
		
	for(i=0; i<8; i++) // loop through the seven lifting elements skipping the fuselage
	{
		if (i == 6) // The tail/rudder is a special case since it can rotate
		{           // thus you have to recalculate the normal vector
			float in, di;
			in = DegreesToRadians(Element[i].fIncidence); // incidence angle
			di = DegreesToRadians(Element[i].fDihedral);  // dihedral angle
			Element[i].vNormal = Vector(	(float)sin(in), 
											(float)(cos(in)*sin(di)), 
											(float)(cos(in)*cos(di))); // surface normal vector
			Element[i].vNormal.Normalize();
		}

		// Calculate local velocity at element
		// The local velocity includes the velocity due to linear motion of the airplane, 
		// plus the velocity at each element due to the rotation of the airplane.
		vtmp = Airplane.vAngularVelocity^Element[i].vCGCoords; // rotational part
		vLocalVelocity = Airplane.vVelocityBody + vtmp; 

		// Calculate local air speed
		fLocalSpeed = vLocalVelocity.Magnitude();

		// Find the direction in which drag will act.
		// Drag always acts inline with the relative velocity but in the opposing direction
		if(fLocalSpeed > 1.) 
			vDragVector = -vLocalVelocity/fLocalSpeed;

		// Find the direction in which lift will act.
		// Lift is always perpendicular to the drag vector
		vLiftVector = (vDragVector^Element[i].vNormal)^vDragVector;
		tmp = vLiftVector.Magnitude();
		vLiftVector.Normalize();

		// Find the angle of attack.
		// The attack angle is the angle between the lift vector and the
		// element normal vector. Note, the sine of the attack angle,
		// is equal to the cosine of the angle between the drag vector and
		// the normal vector.
		tmp = vDragVector*Element[i].vNormal;
		if(tmp > 1.) tmp = 1;
		if(tmp < -1) tmp = -1;
		fAttackAngle = RadiansToDegrees((float) asin(tmp));

		// Determine the resultant force (lift and drag) on the element.
		tmp = 0.5f * rho * fLocalSpeed*fLocalSpeed * Element[i].fArea;		
		if (i == 6) // Tail/rudder
		{
			vResultant =	(vLiftVector*RudderLiftCoefficient(fAttackAngle) +
							vDragVector*RudderDragCoefficient(fAttackAngle) ) * tmp;
		} else if (i == 7)
		{
			vResultant = vDragVector * 0.5f * tmp; // simulate fuselage drag
		}else
			vResultant =	(vLiftVector*LiftCoefficient(fAttackAngle, Element[i].iFlap) +
							vDragVector*DragCoefficient(fAttackAngle, Element[i].iFlap) ) * tmp;
		// Check for stall.
		// We can easily determine when stalled by noting when the coefficient
		// of lift is zero. In reality stall warning devices give warnings well
		// before the lift goes to zero to give the pilot time to correct.
		if (i<=3)
		{
			if (LiftCoefficient(fAttackAngle, Element[i].iFlap) == 0)
				Stalling = true;			
		}

		// Keep a running total of these resultant forces (total force)
		Fb += vResultant;

		// Calculate the moment about the CG of this element's force
		// and keep a running total of these moments (total moment)
		vtmp = Element[i].vCGCoords^vResultant; 
		Mb += vtmp;
	}

	// Now add the thrust
	Fb += Thrust;

	// Convert forces from model space to earth space
	Airplane.vForces = QVRotate(Airplane.qOrientation, Fb);

	// Apply gravity (g is defined as -32.174 ft/s^2)
	Airplane.vForces.z += g * Airplane.fMass;

	// experimental spring connecting the plane to a point 2000 ft above
	// the earth-space origin.
		/*float	dist;
		Vector	vSpring;

		vSpring+=Airplane.vPosition;
		vSpring.z-=2000;
		dist = vSpring.Magnitude();
		vSpring.Normalize();
		vSpring.Reverse();
		
		vSpring*=(10.0f*dist);		

		Airplane.vForces += vSpring;*/




	// end experimental stuff

	Airplane.vMoments += Mb;
	
// testing ...	
	//Airplane.vMoments = QVRotate(Airplane.qOrientation, Airplane.vMoments);
// ... end testing
	
}

//------------------------------------------------------------------------//
//  Using Euler's method
//------------------------------------------------------------------------//
void	StepSimulation(float dt)
{
	// Take care of translation first:
	// (If this body were a particle, this is all you would need to do.)

		Vector Ae;	

		// calculate all of the forces and moments on the airplane:
		CalcAirplaneLoads();

		// calculate the acceleration of the airplane in earth space:
		Ae = Airplane.vForces / Airplane.fMass;

		// calculate the velocity of the airplane in earth space:
		Airplane.vVelocity += Ae * dt;

		// calculate the position of the airplane in earth space:
		Airplane.vPosition += Airplane.vVelocity * dt;

// experimental...
/*		if(Airplane.vPosition.z <= 0.0f)
		{
			Airplane.vVelocity.z = -Airplane.vVelocity.z;
			Airplane.vPosition.z = 0.0f;
		}*/
// ...end experimental stuff

	
	// Now handle the rotations:
		Matrix3x3	mAngularVelocity;		
		float		mag;

		// make a matrix out of the angular velocity vector:
		mAngularVelocity = MakeAngularVelocityMatrix(Airplane.vAngularVelocity);
		
// testing ...
		Airplane.vAngularVelocity += Airplane.mInertiaInverse * 
									(Airplane.vMoments - 
									(Airplane.vAngularVelocity^
									(Airplane.mInertia * Airplane.vAngularVelocity)))
									* dt;	

		Airplane.p1 = (Airplane.vMoments - (Airplane.vAngularVelocity^(Airplane.mInertia * Airplane.vAngularVelocity)));
		Airplane.p2 = (Airplane.vMoments - mAngularVelocity * Airplane.mInertia * Airplane.vAngularVelocity);

		Airplane.p1-=Airplane.p2;
// ... end testing



		
		// calculate the angular velocity of the airplane in body space:
		//vtemp = -(Vector)(mAngularVelocity * Airplane.mInertia * Airplane.vAngularVelocity);
/*		Airplane.vAngularVelocity += Airplane.mInertiaInverse * 
									(Airplane.vMoments - 
									mAngularVelocity * Airplane.mInertia * Airplane.vAngularVelocity) 
									* dt;
*/		
		// calculate the new rotation quaternion:
		Airplane.qOrientation +=	(Airplane.qOrientation * Airplane.vAngularVelocity) *									
									(0.5f * dt);

		// now normalize the orientation quaternion:
		mag = Airplane.qOrientation.Magnitude();
		if (mag != 0)
			Airplane.qOrientation /= mag;

		// calculate the velocity in body space:
		// (we'll need this to calculate lift and drag forces)
		Airplane.vVelocityBody = QVRotate(~Airplane.qOrientation, Airplane.vVelocity);
		
		// calculate the air speed:
		Airplane.fSpeed = Airplane.vVelocity.Magnitude();

		// get the Euler angles for our information
		Vector u;
		
		u = MakeEulerAnglesFromQ(Airplane.qOrientation);
		Airplane.vEulerAngles.x = u.x;	// roll
		Airplane.vEulerAngles.y = u.y;	// pitch
		Airplane.vEulerAngles.z = u.z;	// yaw

}

/*
//------------------------------------------------------------------------//
//  Using modified Euler's method -- midpoint method
//------------------------------------------------------------------------//
void	StepSimulation(float dt)
{
	// Take care of translation first:
	// (If this body were a particle, this is all you would need to do.)

		Vector Ae;	
		Vector Vdot;
		Vector Pdot;

		// calculate all of the forces and moments on the airplane:
		CalcAirplaneLoads();

		// calculate the acceleration of the airplane in earth space:
		Ae = Airplane.vForces / Airplane.fMass;

		// calculate the velocity of the airplane in earth space:
		Vdot = Ae * (dt/2.0f);
		Pdot = Airplane.vVelocity + Vdot * (dt/2.0f);

		Airplane.vVelocity += Vdot * dt;

		// calculate the position of the airplane in earth space:		
		Airplane.vPosition += Pdot * dt;

	
	// Now handle the rotations:
		Matrix3x3	mAngularVelocity;		
		float		mag;

		// make a matrix out of the angular velocity vector:
		mAngularVelocity = MakeAngularVelocityMatrix(Airplane.vAngularVelocity);
		
		// calculate the angular velocity of the airplane in body space:
		//vtemp = -(Vector)(mAngularVelocity * Airplane.mInertia * Airplane.vAngularVelocity);
		Airplane.vAngularVelocity += Airplane.mInertiaInverse * 
									(Airplane.vMoments - 
									mAngularVelocity * Airplane.mInertia * Airplane.vAngularVelocity) 
									* dt;
		
		// calculate the new rotation quaternion:
		Airplane.qOrientation +=	(Airplane.qOrientation * Airplane.vAngularVelocity) *									
									(0.5f * dt);

		// now normalize the orientation quaternion:
		mag = Airplane.qOrientation.Magnitude();
		if (mag != 0)
			Airplane.qOrientation /= mag;

		// calculate the velocity in body space:
		// (we'll need this to calculate lift and drag forces)
		Airplane.vVelocityBody = QVRotate(~Airplane.qOrientation, Airplane.vVelocity);
		
		// calculate the air speed:
		Airplane.fSpeed = Airplane.vVelocity.Magnitude();

		// get the Euler angles for our information
		Vector u;
		
		u = MakeEulerAnglesFromQ(Airplane.qOrientation);
		Airplane.vEulerAngles.x = u.x;	// roll
		Airplane.vEulerAngles.y = u.y;	// pitch
		Airplane.vEulerAngles.z = u.z;	// yaw

}*/



//------------------------------------------------------------------------//
//
//------------------------------------------------------------------------//
Vector	GetBodyZAxisVector(void)
{

	Vector	v;

	v.x = 0.0f;
	v.y = 0.0f;
	v.z = 1.0f;

	return QVRotate(Airplane.qOrientation, v);
}

//------------------------------------------------------------------------//
//
//------------------------------------------------------------------------//
Vector	GetBodyXAxisVector(void)
{

	Vector v;

	v.x = 1.0f;
	v.y = 0.0f;
	v.z = 0.0f;

	return QVRotate(Airplane.qOrientation, v);
	
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
//  Given the attack angle and the status of the flaps, this function
//  returns the appropriate lift coefficient for a cambered airfoil with
//  a plain trailing edge flap (+/- 15 degree deflection).
//------------------------------------------------------------------------//
float	LiftCoefficient(float angle, int flaps)
{
	float clf0[9] = {-0.54f, -0.2f, 0.2f, 0.57f, 0.92f, 1.21f, 1.43f, 1.4f, 1.0f};
	float clfd[9] = {0.0f, 0.45f, 0.85f, 1.02f, 1.39f, 1.65f, 1.75f, 1.38f, 1.17f};
	float clfu[9] = {-0.74f, -0.4f, 0.0f, 0.27f, 0.63f, 0.92f, 1.03f, 1.1f, 0.78f};
	float a[9]	 = {-8.0f, -4.0f, 0.0f, 4.0f, 8.0f, 12.0f, 16.0f, 20.0f, 24.0f};
	float cl;
	int	  i;

	cl = 0;
	for (i=0; i<8; i++)
	{
		if( (a[i] <= angle) && (a[i+1] > angle) )
		{
			switch(flaps)
			{
				case 0:// flaps not deflected
					cl = clf0[i] - (a[i] - angle) * (clf0[i] - clf0[i+1]) / (a[i] - a[i+1]);
					break;
				case -1: // flaps down
					cl = clfd[i] - (a[i] - angle) * (clfd[i] - clfd[i+1]) / (a[i] - a[i+1]);
					break;
				case 1: // flaps up
					cl = clfu[i] - (a[i] - angle) * (clfu[i] - clfu[i+1]) / (a[i] - a[i+1]);
					break;
			}
			break;
		}
	}	

	return cl;
}

//------------------------------------------------------------------------//
//  Given the attack angle and the status of the flaps, this function
//  returns the appropriate drag coefficient for a cambered airfoil with
//  a plain trailing edge flap (+/- 15 degree deflection).
//------------------------------------------------------------------------//
float	DragCoefficient(float angle, int flaps)
{
	float cdf0[9] = {0.01f, 0.0074f, 0.004f, 0.009f, 0.013f, 0.023f, 0.05f, 0.12f, 0.21f};
	float cdfd[9] = {0.0065f, 0.0043f, 0.0055f, 0.0153f, 0.0221f, 0.0391f, 0.1f, 0.195f, 0.3f};
	float cdfu[9] = {0.005f, 0.0043f, 0.0055f, 0.02601f, 0.03757f, 0.06647f, 0.13f, 0.18f, 0.25f};
	float a[9]	 = {-8.0f, -4.0f, 0.0f, 4.0f, 8.0f, 12.0f, 16.0f, 20.0f, 24.0f};
	float cd;
	int	  i;

	cd = 0.75;
	for (i=0; i<8; i++)
	{
		if( (a[i] <= angle) && (a[i+1] > angle) )
		{
			switch(flaps)
			{
				case 0:// flaps not deflected
					cd = cdf0[i] - (a[i] - angle) * (cdf0[i] - cdf0[i+1]) / (a[i] - a[i+1]);
					break;
				case -1: // flaps down
					cd = cdfd[i] - (a[i] - angle) * (cdfd[i] - cdfd[i+1]) / (a[i] - a[i+1]);
					break;
				case 1: // flaps up
					cd = cdfu[i] - (a[i] - angle) * (cdfu[i] - cdfu[i+1]) / (a[i] - a[i+1]);
					break;
			}
			break;
		}
	}	

	return cd;

}

//------------------------------------------------------------------------//
//  Given the attack angle this function returns the proper lift coefficient
//  for a symmetric (no camber) airfoil without flaps.
//------------------------------------------------------------------------//
float	RudderLiftCoefficient(float angle)
{
	float clf0[7] = {0.16f, 0.456f, 0.736f, 0.968f, 1.144f, 1.12f, 0.8f};
	float a[7]	 = {0.0f, 4.0f, 8.0f, 12.0f, 16.0f, 20.0f, 24.0f};
	float cl;
	int	  i;
	float	aa = (float) fabs(angle);

	cl = 0;
	for (i=0; i<6; i++)
	{
		if( (a[i] <= aa) && (a[i+1] > aa) )
		{			
			cl = clf0[i] - (a[i] - aa) * (clf0[i] - clf0[i+1]) / (a[i] - a[i+1]);
			if (angle < 0) cl = -cl;
			break;
		}
	}	
	return cl;
}

//------------------------------------------------------------------------//
//  Given the attack angle this function returns the proper drag coefficient
//  for a symmetric (no camber) airfoil without flaps.
//------------------------------------------------------------------------//
float	RudderDragCoefficient(float angle)
{
	float cdf0[7] = {0.0032f, 0.0072f, 0.0104f, 0.0184f, 0.04f, 0.096f, 0.168f};
	float a[7]	 = {0.0f, 4.0f, 8.0f, 12.0f, 16.0f, 20.0f, 24.0f};
	float cd;
	int	  i;
	float	aa = (float) fabs(angle);

	cd = 0.75;
	for (i=0; i<6; i++)
	{
		if( (a[i] <= aa) && (a[i+1] > aa) )
		{			
			cd = cdf0[i] - (a[i] - aa) * (cdf0[i] - cdf0[i+1]) / (a[i] - a[i+1]);			
			break;
		}
	}	
	return cd;
}

//------------------------------------------------------------------------//
//
//------------------------------------------------------------------------//
void	IncThrust(void)
{
	ThrustForce += _DTHRUST;
	if(ThrustForce > _MAXTHRUST)
		ThrustForce = _MAXTHRUST;
}

//------------------------------------------------------------------------//
//
//------------------------------------------------------------------------//
void	DecThrust(void)
{
	ThrustForce -= _DTHRUST;
	if(ThrustForce < 0)
		ThrustForce = 0;
}

//------------------------------------------------------------------------//
//
//------------------------------------------------------------------------//
void	LeftRudder(void)
{
	Element[6].fIncidence = 16;
}

//------------------------------------------------------------------------//
//
//------------------------------------------------------------------------//
void	RightRudder(void)
{
	Element[6].fIncidence = -16;
}

//------------------------------------------------------------------------//
//
//------------------------------------------------------------------------//
void	ZeroRudder(void)
{
	Element[6].fIncidence = 0;
}

//------------------------------------------------------------------------//
//
//------------------------------------------------------------------------//
void	RollLeft(void)
{
	Element[0].iFlap = 1;
	Element[3].iFlap = -1;
}

//------------------------------------------------------------------------//
//
//------------------------------------------------------------------------//
void	RollRight(void)
{
	Element[0].iFlap = -1;
	Element[3].iFlap = 1;
}

//------------------------------------------------------------------------//
//
//------------------------------------------------------------------------//
void	PitchUp(void)
{
	Element[4].iFlap = 1;
	Element[5].iFlap = 1;
}

//------------------------------------------------------------------------//
//
//------------------------------------------------------------------------//
void	PitchDown(void)
{
	Element[4].iFlap = -1;
	Element[5].iFlap = -1;
}

//------------------------------------------------------------------------//
//
//------------------------------------------------------------------------//
void	ZeroAilerons(void)
{
	Element[0].iFlap = 0;
	Element[3].iFlap = 0;
}

//------------------------------------------------------------------------//
//
//------------------------------------------------------------------------//
void	ZeroElevators(void)
{
	Element[4].iFlap = 0;
	Element[5].iFlap = 0;
}

//------------------------------------------------------------------------//
//
//------------------------------------------------------------------------//
void	FlapsDown(void)
{
	Element[1].iFlap = -1;
	Element[2].iFlap = -1;
	Flaps = true;
}

//------------------------------------------------------------------------//
//
//------------------------------------------------------------------------//
void	ZeroFlaps(void)
{
	Element[1].iFlap = 0;
	Element[2].iFlap = 0;
	Flaps = false;
}