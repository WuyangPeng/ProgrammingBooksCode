#ifndef _PHYSICS
#define _PHYSICS

#include "mymath.h"

//------------------------------------------------------------------------//
// Notes:
//------------------------------------------------------------------------//
/* 
	
	Earth coordinates:	x points North
						y points West
						z points up


						Z   X
						|  /
						| /
						|/
				 Y------+
                 

    Body coordinates:	x points to the front	
						y points to left
						z points up 

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


//------------------------------------------------------------------------//
// Rigid body structure
//------------------------------------------------------------------------//
typedef struct _RigidBody {

	float		fMass;			// total mass (constant)
	Matrix3x3	mInertia;		// mass moment of inertia in body coordinates (constant)
	Matrix3x3	mInertiaInverse;// inverse of mass moment of inertia matrix	(constant)
	
	Vector		vPosition;		// position in earth coordinates
	Vector		vVelocity;		// velocity in earth coordinates
	Vector		vVelocityBody;	// velocity in body coordinates
	Vector		vAngularVelocity;// angular velocity in body coordinates
	Vector		vEulerAngles;	// Euler angles in body coordinates
	float		fSpeed;			// speed (magnitude of the velocity)

	Quaternion	qOrientation;	// orientation in earth coordinates
	//Matrix3x3	mRotation;		// rotation matrix

	Vector		vForces;		// total force on body
	Vector		vMoments;		// total moment (torque) on body

	Matrix3x3	mIeInverse;		// inverse of moment of inertia in earth coordinates

// testing...
	Vector p1, p2;
// ... end testing


} RigidBody, *pRigidBody;

typedef struct _BodyElement {
	float	fMass;
	Vector	vDCoords;
	Vector	vCGCoords;
	Vector	vLocalInertia;
	float	fIncidence;
	float	fDihedral;
	Vector	vNormal;
	float	fArea;
	int		iFlap;
} BodyElement, *pBodyElement;


//------------------------------------------------------------------------//
// Function headers
//------------------------------------------------------------------------//
void	InitializeAirplane(void);
void	CalcAirplaneMassProperties(void);	// calcs total mass and inertia
void	CalcAirplaneLoads(void);			// calcs total forces and moments
void	StepSimulation(float dt);			// step dt time in the simulation
Vector	GetBodyZAxisVector(void);
Vector	GetBodyXAxisVector(void);
Matrix3x3   MakeAngularVelocityMatrix(Vector u);
float	LiftCoefficient(float angle, int flaps);
float	DragCoefficient(float angle, int flaps);
float	RudderLiftCoefficient(float angle);
float	RudderDragCoefficient(float angle);
void	IncThrust(void);
void	DecThrust(void);
void	LeftRudder(void);
void	RightRudder(void);
void	ZeroRudder(void);
void	RollLeft(void);
void	RollRight(void);
void	PitchUp(void);
void	PitchDown(void);
void	ZeroAilerons(void);
void	ZeroElevators(void);
void	FlapsDown(void);
void	ZeroFlaps(void);








#endif
