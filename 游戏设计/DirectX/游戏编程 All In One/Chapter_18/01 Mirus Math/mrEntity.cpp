 /* 'mrEntity.cpp' */

 /* Complement header file */
#include "mrEntity.h"

 /* Default constructor */
mrEntity::mrEntity (void)
{
 m_fMass                       = 0;
 m_fInertia                    = 0;
 m_fStaticFrictionCoefficient  = 0;
 m_fKineticFrictionCoefficient = 0;
 m_fAngularVelocity            = 0;
 m_fOrientation                = 0;
 m_fTotalTorque                = 0;
 m_fTotalImpulse               = 0;
 m_kCenterOfMass               = mrVector2D (0, 0);
 m_kPosition                   = mrVector2D (0, 0);
 m_kLinearVelocity             = mrVector2D (0, 0);
 m_kTotalForce                 = mrVector2D (0, 0);
 m_kFrictionForce              = mrVector2D (0, 0);
}

 /* Default destructor */
mrEntity::~mrEntity (void)
{
 m_fMass                       = 0;
 m_fInertia                    = 0;
 m_fStaticFrictionCoefficient  = 0;
 m_fKineticFrictionCoefficient = 0;
 m_fAngularVelocity            = 0;
 m_fOrientation                = 0;
 m_fTotalTorque                = 0;
 m_fTotalImpulse               = 0;
 m_kCenterOfMass               = mrVector2D (0, 0);
 m_kPosition                   = mrVector2D (0, 0);
 m_kLinearVelocity             = mrVector2D (0, 0);
 m_kTotalForce                 = mrVector2D (0, 0);
 m_kFrictionForce              = mrVector2D (0, 0);
}

 /* Apply a linear force to the entity */
void mrEntity::ApplyLinearForce (mrVector2D & rkForce)
{
 m_kTotalForce += rkForce;
}

 /* Apply torque to the entity */
void mrEntity::ApplyTorque (mrReal32 fTorque)
{
 m_fTotalTorque += fTorque;
}

 /* Apply a force to the entity */
void mrEntity::ApplyForce (mrVector2D & rkForce, 
                           mrVector2D & rkPointOfContact)
{
 m_kTotalForce += rkForce;

 mrVector2D rkArm;

  /* Calculate arm of force */
 rkArm = rkPointOfContact - m_kCenterOfMass;

 m_fTotalTorque += rkArm.PerpDotProduct (rkForce);
}

 /* Apply a friction force to the entity */
void mrEntity::ApplyFriction (mrReal32 fGravity)
{
 mrVector2D kFrictionVector;

  /* If velocity is too small, use static friction, otherwise, 
     use kinetic */
 if (m_kLinearVelocity.Length () < 1)
 {
			/* Calculate friction vector */
		kFrictionVector = m_kTotalForce;
		kFrictionVector.Normalize ();

  kFrictionVector *= -(fGravity * m_fMass) * 
                     m_fStaticFrictionCoefficient;
 }
 else
 {
			/* Calculate friction vector */
		kFrictionVector = m_kLinearVelocity;
		kFrictionVector.Normalize ();

  kFrictionVector *= -(fGravity * m_fMass) * 
                     m_fKineticFrictionCoefficient;
 }
 m_kFrictionForce += kFrictionVector;
}

 /* Handle collisions between two objects */
void mrEntity::HandleCollision (mrEntity & rkOtherEntity, 
                                mrVector2D & rkCollisionNormal)
{
 mrReal32 fImpulse;
 mrVector2D kRelativeVelocity;

  /* Normalize collision normal */
 rkCollisionNormal.Normalize ();

  /* Get relative velocities */
 kRelativeVelocity = (m_kLinearVelocity - 
                      rkOtherEntity.GetLinearVelocity ());
 kRelativeVelocity *= - (1 + m_fCoefficientOfRestitution);

  /* Calculate sum of inverse of entities mass */
 mrReal32 fInverseMassSum;
 fInverseMassSum = (1 / m_fMass) + (1 / rkOtherEntity.GetMass ());
 
  /* Calculate impulse */
 fImpulse = (kRelativeVelocity.DotProduct (rkCollisionNormal)) /
   rkCollisionNormal.DotProduct (rkCollisionNormal * fInverseMassSum);

  /* Get object velocity */
 m_kLinearVelocity = m_kLinearVelocity + 
                     rkCollisionNormal * (fImpulse / m_fMass);

  /* Get other object velocity */
 mrVector2D kOtherVelocity;
 rkOtherEntity.SetLinearVelocity (rkOtherEntity.GetLinearVelocity () - 
             rkCollisionNormal * (fImpulse / rkOtherEntity.GetMass ()));
}

 /* Simulate (integrate) the entity */
void mrEntity::Simulate (mrReal32 fStep)
{
  /* Use Euler integration */
 m_kLinearVelocity  += (m_kTotalForce / m_fMass) * fStep;
 m_kPosition        += m_kLinearVelocity * fStep;
 
 m_fAngularVelocity += (m_fTotalTorque / m_fInertia) * fStep;
 m_fOrientation     += m_fAngularVelocity * fStep;

  /* Only apply friction if it doesn't cause movement */
  /* Use separate vector components */
 if (fabs (m_kLinearVelocity [0]) >= 
     fabs ((m_kFrictionForce [0] / m_fMass) * fStep))
 {
  m_kLinearVelocity [0] += (m_kFrictionForce [0] / m_fMass) * fStep;
 }
 else
 {
  m_kLinearVelocity [0] = 0;
 }
 if (fabs (m_kLinearVelocity [1]) >= 
     fabs ((m_kFrictionForce [1] / m_fMass) * fStep))
 {
  m_kLinearVelocity [1] += (m_kFrictionForce [1] / m_fMass) * fStep;
 }
 else
 {
  m_kLinearVelocity [1] = 0;
 }

  /* Apply some damping to solve problems of floating accuracy */
 if (fabs (m_kLinearVelocity [0]) <= 0.1f)
 {
  m_kLinearVelocity [0] = 0;
 }
 if (fabs (m_kLinearVelocity [1]) <= 0.1f)
 {
  m_kLinearVelocity [1] = 0;
 }
  /* Applies damping since we don't apply any friction to angular
     velocity */
 m_fAngularVelocity *= 0.99f;

  /* Reset forces */
 m_fTotalTorque                = 0;
 m_fTotalImpulse               = 0;
 m_kTotalForce                 = mrVector2D (0, 0);
 m_kFrictionForce              = mrVector2D (0, 0);
}

void mrEntity::SetPosition (mrVector2D & rkPosition)
{
 m_kPosition = rkPosition;
}

void mrEntity::SetOrientation (mrReal32 fOrientation)
{
 m_fOrientation = fOrientation;
}

void mrEntity::SetLinearVelocity (mrVector2D & rkLinearVelocity)
{
 m_kLinearVelocity = rkLinearVelocity;
}

void mrEntity::SetAngularVelocity (mrReal32 fAngularVelocity)
{
 m_fAngularVelocity = fAngularVelocity;
}

void mrEntity::SetMass (mrReal32 fMass)
{
 m_fMass = fMass;
}

void mrEntity::SetCenterOfMass (mrVector2D & rkCenterOfMass)
{
 m_kCenterOfMass = rkCenterOfMass;
}

void mrEntity::SetInertia (mrReal32 fInertia)
{
 m_fInertia = fInertia;
}

void mrEntity::SetStaticFriction (mrReal32 fStaticFrictionCoefficient)
{
 m_fStaticFrictionCoefficient = fStaticFrictionCoefficient;
}

void mrEntity::SetKineticFriction (mrReal32 fKineticFrictionCoefficient)
{
 m_fKineticFrictionCoefficient = fKineticFrictionCoefficient;
}

void mrEntity::SetCoefficientOfRestitution (
                                     mrReal32 fCoefficientOfRestitution)
{
  m_fCoefficientOfRestitution = fCoefficientOfRestitution;
}

mrVector2D mrEntity::GetPosition (void)
{
 return m_kPosition;
}

mrReal32 mrEntity::GetOrientation (void)
{
 return m_fOrientation;
}

mrVector2D mrEntity::GetLinearVelocity (void)
{
 return m_kLinearVelocity;
}

mrReal32 mrEntity::GetAngularVelocity (void)
{
 return m_fAngularVelocity;
}

mrReal32 mrEntity::GetMass (void)
{
 return m_fMass;
}

mrVector2D mrEntity::GetCenterOfMass (void)
{
 return m_kCenterOfMass;
}

mrReal32 mrEntity::GetInertia (void)
{
 return m_fInertia;
}

mrReal32 mrEntity::GetStaticFriction (void)
{
 return m_fStaticFrictionCoefficient;
}

mrReal32 mrEntity::GetKineticFriction (void)
{
 return m_fKineticFrictionCoefficient;
}

mrReal32 mrEntity::GetCoefficientOfRestitution (void)
{
 return m_fCoefficientOfRestitution;
}
