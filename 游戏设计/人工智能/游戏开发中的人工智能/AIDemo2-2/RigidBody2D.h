#ifndef _RIGIDBODY2DHEADER
#define _RIGIDBODY2DHEADER

#include "mymath.h"

#define	 _THRUSTFORCE				20.0f/2
#define	 _MAXTHRUST					80.0f/2
#define	 _MINTHRUST					0.0f
#define	 _DTHRUST					0.01f
#define  _STEERINGFORCE				6.0f
#define  _LINEARDRAGCOEFFICIENT		0.3f
#define  _ANGULARDRAGCOEFFICIENT	5000.0f

//------------------------------------------------------------------------//
// Rigid body structure (2D only)
//------------------------------------------------------------------------//
class RigidBody2D {
public:
	float	fMass;				// total mass (constant)
	float	fInertia;			// mass moment of inertia in body coordinates (constant)
	float	fInertiaInverse;	// inverse of mass moment of inertia (constant)
	
	Vector	vPosition;			// position in earth coordinates
	Vector	vVelocity;			// velocity in earth coordinates
	Vector	vVelocityBody;		// velocity in body coordinates
	Vector	vAngularVelocity;	// angular velocity in body coordinates
		
	float	fSpeed;				// speed (magnitude of the velocity)
	float	fOrientation;		// orientation 	

	Vector	vForces;			// total force on body
	Vector	vMoment;			// total moment (torque) on body (2D: about z-axis only)

	float	ThrustForce;		// Magnitude of the thrust force
	Vector	PThrust, SThrust;	// bow thruster forces

	float	fWidth;				// bounding dimensions
	float	fLength;
	float	fHeight;

	Vector	CD;
	Vector	CT;
	Vector	CPT;
	Vector	CST;

	float	ProjectedArea;

	Vector	Fa;// other applied force
	Vector  Pa;// location of other applied force

	//Vector	vCollisionPoint;	// point of impact in local coordinates	

	RigidBody2D(void);
	void	CalcLoads(void);
	void	UpdateBodyEuler(double dt);
	void	SetThrusters(bool p, bool s);
	void	ModulateThrust(bool up);


};

Vector	VRotate2D( float angle, Vector u);

#endif