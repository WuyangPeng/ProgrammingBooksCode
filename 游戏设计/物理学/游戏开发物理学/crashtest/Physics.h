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
	Vector		vAcceleration;	// acceleration of cg in earth space
	Vector		vAngularAcceleration; //angular acceleration in body coordinates
	Vector		vAngularVelocity;// angular velocity in body coordinates
	Vector		vEulerAngles;	// Euler angles in body coordinates
	float		fSpeed;			// speed (magnitude of the velocity)

	Quaternion	qOrientation;	// orientation in earth coordinates

	Vector		vForces;		// total force on body
	Vector		vMoments;		// total moment (torque) on body

	Matrix3x3	mIeInverse;		// inverse of moment of inertia in earth coordinates

	Vector		vAngularVelocityGlobal; // angular velocity in terms of earth fixed coords.
	Vector		vAngularAccelerationGlobal; // angular acceleration in terms of earth fixed coords.

	float		fRadius;
	Vector		vVertexList[8];

} RigidBody, *pRigidBody;


typedef struct	_Collision {	
	int				body1;
	int				body2;
	Vector			vCollisionNormal; // outward from face of body2
	Vector			vCollisionPoint;  // in global coordinates
	Vector			vRelativeVelocity;
	Vector			vRelativeAcceleration;
	Vector			vCollisionTangent;
}	Collision, *pCollision;

typedef struct	_Edge {
	int	a;
	int b;
} Edge, *pEdge;


#define		GRAVITY		-32.174f
#define		LINEARDRAGCOEFFICIENT	10.0f
#define		ANGULARDRAGCOEFFICIENT	400.0f

#define		NOCOLLISION				0
#define		COLLISION				1
#define		PENETRATING				-1
#define		CONTACT					2

#define		COLLISIONTOLERANCE		0.1f 
#define		PENETRATIONTOLERANCE	0.05f
#define		CONTACTTOLERANCE		0.1f

#define		FRICTIONFACTOR			0.1f

#define		NUMBODIES				3

#define		CARLENGTH				14.0f
#define		CARWIDTH				5.8f
#define		CARHEIGHT				4.0f

#define		BLOCKSIZE				3.0f 

#define		COEFFICIENTOFRESTITUTION		0.6f
#define		COEFFICIENTOFRESTITUTIONGROUND	0.1f

#define		VELOCITYTOLERANCE		0.05f

#define		FRICTIONCOEFFICIENT		0.3f
#define		DOPENCHECK				true
#define		DOFRICTION				true

#define		CARWEIGHT				2000
#define		BLOCKWEIGHT				1000





//------------------------------------------------------------------------//
// Function headers
//------------------------------------------------------------------------//
void	InitializeObjects(int	configuration);
void	CalcObjectForces(void);			// calcs total forces and moments
void	StepSimulation(float dtime);			// step dt time in the simulation
void	FlushCollisionData(void);
int		CheckForCollisions(bool pencheck);
void	ResolveCollisions(void);
float	CalcDistanceFromPointToPlane(Vector pt, Vector u, Vector v, Vector ptOnPlane);
bool	IsPointOnFace(Vector pt, Vector f[4]);
int	IsPenetratingGround(int body1);
int IsPenetrating(int body1, int body2);
int	CheckVertexFaceCollisions(pCollision CollisionData, int body1, int body2);
int	CheckVertexEdgeCollisions(pCollision CollisionData, int body1, int body2);
int	CheckEdgeEdgeCollisions(pCollision CollisionData, int body1, int body2);
int	CheckBoxCollision(pCollision CollisionData, int body1, int body2);
int	CheckGroundPlaneCollisions(pCollision CollisionData, int body1);
int	CheckGroundPlaneContacts(pCollision CollisionData, int body1);

Vector	GetBodyZAxisVector(int index);
Vector	GetBodyXAxisVector(int index);
Matrix3x3   MakeAngularVelocityMatrix(Vector u);
int	pnpoly(int	npol, Vector *vlist, Vector p);








#endif
