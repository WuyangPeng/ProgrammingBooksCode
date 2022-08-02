 /* 'mrEntity.h' */

 /* Mirus base types header */
#include "mrDatatypes.h"

 /* Include this file only once */
#pragma once

 /* Mirus Entity class */
class mrEntity
{
protected:
  /* Physical attributes */
 mrVector2D     m_kCenterOfMass;
 mrReal32       m_fMass;
 mrReal32       m_fInertia;
 mrReal32       m_fStaticFrictionCoefficient;
 mrReal32       m_fKineticFrictionCoefficient;
 mrReal32       m_fCoefficientOfRestitution;

  /* Physics variables */
 mrVector2D     m_kPosition;
 mrVector2D     m_kLinearVelocity;
 mrReal32       m_fOrientation;
 mrReal32       m_fAngularVelocity;
 
 mrVector2D     m_kTotalForce;
 mrReal32       m_fTotalTorque;
 mrVector2D     m_kFrictionForce;
 mrReal32       m_fTotalImpulse;
 
public:
   /* Constructor / Destructor */
 mrEntity (void);
 ~mrEntity (void);

 void Simulate (mrReal32 fStep);

 void ApplyLinearForce (mrVector2D & rkForce);
 void ApplyTorque (mrReal32 fTorque);
 void ApplyForce (mrVector2D & rkForce, mrVector2D & rkPointOfContact);
 void ApplyFriction (mrReal32 fGravity); 

 void HandleCollision (mrEntity & rkOtherEntity, 
                       mrVector2D & rkCollisionNormal);

  /* Entity maintainance methods */
 void SetPosition (mrVector2D & rkPosition); 
 void SetOrientation (mrReal32 fOrientation); 
 void SetLinearVelocity (mrVector2D & rkLinearVelocity); 
 void SetAngularVelocity (mrReal32 fAngularVelocity); 
 void SetMass (mrReal32 fMass); 
 void SetCenterOfMass (mrVector2D & rkCenterOfMass); 
 void SetInertia (mrReal32 fInertia);
 void SetStaticFriction (mrReal32 fStaticFrictionCoefficient);
 void SetKineticFriction (mrReal32 fKineticFrictionCoefficient);
 void SetCoefficientOfRestitution (mrReal32 fCoefficientOfRestitution);

 mrVector2D GetPosition (void); 
 mrReal32 GetOrientation (void); 
 mrVector2D GetLinearVelocity (void); 
 mrReal32 GetAngularVelocity (void); 
 mrReal32 GetMass (void); 
 mrVector2D GetCenterOfMass (void); 
 mrReal32 GetInertia (void);
 mrReal32 GetStaticFriction (void);
 mrReal32 GetKineticFriction (void);
 mrReal32 GetCoefficientOfRestitution (void);
};
