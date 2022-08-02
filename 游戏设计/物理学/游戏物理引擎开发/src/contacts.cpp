/*
 * Implementation file for the contact resolution system.
 * 
 * Part of the Cyclone physics system.
 * 
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under licence. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software licence.
 */

///>ContactResolver
#include <cyclone/contacts.h>
///<ContactResolver
#include <memory.h>
#include <assert.h>

using namespace cyclone;

// Contact implementation

void Contact::setBodyData(RigidBody* one, RigidBody *two,
                          real friction, real restitution)
{
    Contact::body[0] = one;
    Contact::body[1] = two;
    Contact::friction = friction;
    Contact::restitution = restitution;
}

///>MatchAwakeState
void Contact::matchAwakeState()
{
    // Collisions with the world never cause a body to wake up.
    if (!body[1]) return;

    bool body0awake = body[0]->getAwake();
    bool body1awake = body[1]->getAwake();

    // Wake up only the sleeping one
    if (body0awake ^ body1awake) {
        if (body0awake) body[1]->setAwake();
        else body[0]->setAwake();
    }
}
///<MatchAwakeState

///>SwapBodies
/**
 * Swaps the bodies in the current contact, so body 0 is at body 1 and vice
 * versa. This also changes the direction of the contact normal, but doesn't
 * update any calculated internal data. If you are calling this method 
 * manually, then call calculateInternals afterwards to make sure the 
 * internal data is up to date.
 */
void Contact::swapBodies()
{
    contactNormal *= -1;

    RigidBody *temp = body[0];
    body[0] = body[1];
    body[1] = temp;
}
///<SwapBodies

///>OrthonormalBasis
/**
 * Constructs an arbitrary orthonormal basis for the contact.
 * This is stored as a 3x3 matrix, where each vector is a column
 * (in other words the matrix transforms contact space into world
 * space). The x direction is generated from the contact normal,
 * and the y and z directionss are set so they are at right angles to
 * it.
 */
///<OrthonormalBasis
inline
///>OrthonormalBasis
void Contact::calculateContactBasis()
{
    Vector3 contactTangent[2];

    // Check whether the Z-axis is nearer to the X or Y axis
    if(real_abs(contactNormal.x) > real_abs(contactNormal.y))
    { 
        // Scaling factor to ensure the results are normalised
        const real s = (real)1.0f/real_sqrt(contactNormal.z*contactNormal.z +
            contactNormal.x*contactNormal.x);

        // The new X-axis is at right angles to the world Y-axis
        contactTangent[0].x = contactNormal.z*s;
        contactTangent[0].y = 0;
        contactTangent[0].z = -contactNormal.x*s;

        // The new Y-axis is at right angles to the new X- and Z- axes
        contactTangent[1].x = contactNormal.y*contactTangent[0].x;
        contactTangent[1].y = contactNormal.z*contactTangent[0].x - 
            contactNormal.x*contactTangent[0].z;
        contactTangent[1].z = -contactNormal.y*contactTangent[0].x;
    }
    else
    {
        // Scaling factor to ensure the results are normalised
        const real s = (real)1.0/real_sqrt(contactNormal.z*contactNormal.z + 
            contactNormal.y*contactNormal.y);

        // The new X-axis is at right angles to the world X-axis
        contactTangent[0].x = 0;
        contactTangent[0].y = -contactNormal.z*s;
        contactTangent[0].z = contactNormal.y*s;

        // The new Y-axis is at right angles to the new X- and Z- axes
        contactTangent[1].x = contactNormal.y*contactTangent[0].z - 
            contactNormal.z*contactTangent[0].y;
        contactTangent[1].y = -contactNormal.x*contactTangent[0].z;
        contactTangent[1].z = contactNormal.x*contactTangent[0].y;
    }

    // Make a matrix from the three vectors.
    contactToWorld.setComponents(
        contactNormal, 
        contactTangent[0], 
        contactTangent[1]);
}
///<OrthonormalBasis

///>CalculateLocalVelocity;CalculateAllLocalVelocity
Vector3 Contact::calculateLocalVelocity(unsigned bodyIndex, real duration)
{
    RigidBody *thisBody = body[bodyIndex];

    // Work out the velocity of the contact point.
    Vector3 velocity = 
        thisBody->getRotation() % relativeContactPosition[bodyIndex];
    velocity += thisBody->getVelocity();

    // Turn the velocity into contact-coordinates.
    Vector3 contactVelocity = contactToWorld.transformTranspose(velocity);

///<CalculateLocalVelocity
    // Calculate the ammount of velocity that is due to forces without
    // reactions.
    Vector3 accVelocity = thisBody->getLastFrameAcceleration() * duration;

    // Calculate the velocity in contact-coordinates.
    accVelocity = contactToWorld.transformTranspose(accVelocity);

    // We ignore any component of acceleration in the contact normal 
    // direction, we are only interested in planar acceleration
    accVelocity.x = 0;

    // Add the planar velocities - if there's enough friction they will 
    // be removed during velocity resolution
    contactVelocity += accVelocity;
///>CalculateLocalVelocity

    // And return it
    return contactVelocity;
}
///<CalculateLocalVelocity;CalculateAllLocalVelocity


void Contact::calculateDesiredDeltaVelocity(real duration)
{
    const static real velocityLimit = (real)0.25f;

///>NewVelocityCalculation
    // Calculate the acceleration induced velocity accumulated this frame
    real velocityFromAcc = body[0]->getLastFrameAcceleration() * duration * contactNormal;

    if (body[1])
    {
        velocityFromAcc -= body[1]->getLastFrameAcceleration() * duration * contactNormal;
    }

    // If the velocity is very slow, limit the restitution
    real thisRestitution = restitution;
    if (real_abs(contactVelocity.x) < velocityLimit)
    {
        thisRestitution = (real)0.0f;
    }

    // Combine the bounce velocity with the removed
    // acceleration velocity.
    desiredDeltaVelocity =
        -contactVelocity.x
        -thisRestitution * (contactVelocity.x - velocityFromAcc);
///<NewVelocityCalculation            
}


///>ContactCalculateInternals
void Contact::calculateInternals(real duration)
{
    // Check if the first object is NULL, and swap if it is.
    if (!body[0]) swapBodies();
    assert(body[0]);

    // Calculate an set of axis at the contact point.
    calculateContactBasis();

    // Store the relative position of the contact relative to each body
    relativeContactPosition[0] = contactPoint - body[0]->getPosition();
    if (body[1]) {
        relativeContactPosition[1] = contactPoint - body[1]->getPosition();
    }

    // Find the relative velocity of the bodies at the contact point.
    contactVelocity = calculateLocalVelocity(0, duration);
    if (body[1]) {
        contactVelocity -= calculateLocalVelocity(1, duration);
    }

    // Calculate the desired change in velocity for resolution
    calculateDesiredDeltaVelocity(duration);
}
///<ContactCalculateInternals

void Contact::applyVelocityChange(Vector3 velocityChange[2], 
                                  Vector3 rotationChange[2])
{
    // Get hold of the inverse mass and inverse inertia tensor, both in
    // world coordinates.
    Matrix3 inverseInertiaTensor[2];
    body[0]->getInverseInertiaTensorWorld(&inverseInertiaTensor[0]);

    // We will calculate the impulse for each contact axis
    Vector3 impulseContact;

    // Use the short format for frictionless contacts
    if (friction == (real)0.0)
    {
///>DeltaVelPerImpulse
        // Build a vector that shows the change in velocity in
        // world space for a unit impulse in the direction of the contact 
        // normal.
        Vector3 deltaVelWorld = relativeContactPosition[0] % contactNormal;
        deltaVelWorld = inverseInertiaTensor[0].transform(deltaVelWorld);
        deltaVelWorld = deltaVelWorld % relativeContactPosition[0];

        // Work out the change in velocity in contact coordiantes.
        real deltaVelocity = deltaVelWorld * contactNormal;

        // Add the linear component of velocity change
        deltaVelocity += body[0]->getInverseMass();

        // Check if we need to the second body's data
        if (body[1])
        {
            // Find the inertia tensor for this body
            body[1]->getInverseInertiaTensorWorld(&inverseInertiaTensor[1]);

            // Go through the same transformation sequence again
            Vector3 deltaVelWorld = relativeContactPosition[1] % contactNormal;
            deltaVelWorld = inverseInertiaTensor[1].transform(deltaVelWorld);
            deltaVelWorld = deltaVelWorld % relativeContactPosition[1];

            // Add the change in velocity due to rotation
            deltaVelocity += deltaVelWorld * contactNormal;

            // Add the change in velocity due to linear motion
            deltaVelocity += body[1]->getInverseMass();
        }
///<DeltaVelPerImpulse

///>ImpulseContact
        // Calculate the required size of the impulse
        impulseContact.x = desiredDeltaVelocity / deltaVelocity;
        impulseContact.y = 0;
        impulseContact.z = 0;
///<ImpulseContact
    }

    // Otherwise we may have impulses that aren't in the direction of the 
    // contact, so we need to build complete matrices.
    else
    {
///>UpdateVelWithFriction
        real inverseMass = body[0]->getInverseMass();

///>AngularVelocityFriction
        // The equivalent of a cross product in matrices is multiplication
        // by a skew symmetric matrix - we build the matrix for converting
        // between linear and angular quantities.
        Matrix3 impulseToTorque;
        impulseToTorque.setSkewSymmetric(relativeContactPosition[0]);

        // Build the matrix to convert contact impulse to change in velocity
        // in world coordinates.
        Matrix3 deltaVelWorld = impulseToTorque; 
        deltaVelWorld *= inverseInertiaTensor[0];
        deltaVelWorld *= impulseToTorque;
        deltaVelWorld *= -1;

        // Check if we need to add body two's data
        if (body[1])
        {
            // Find the inertia tensor for this body
            body[1]->getInverseInertiaTensorWorld(&inverseInertiaTensor[1]);

            // Set the cross product matrix
            impulseToTorque.setSkewSymmetric(relativeContactPosition[1]);

            // Calculate the velocity change matrix
            Matrix3 deltaVelWorld2 = impulseToTorque; 
            deltaVelWorld2 *= inverseInertiaTensor[1];
            deltaVelWorld2 *= impulseToTorque;
            deltaVelWorld2 *= -1;

            // Add to the total delta velocity.
            deltaVelWorld += deltaVelWorld2;
///<AngularVelocityFriction

            // Add to the inverse mass
            inverseMass += body[1]->getInverseMass();
///>AngularVelocityFriction
        }

        // Do a change of basis to convert into contact coordinates.
        Matrix3 deltaVelocity = contactToWorld.transpose();
        deltaVelocity *= deltaVelWorld;
        deltaVelocity *= contactToWorld;
///<AngularVelocityFriction

        // Add in the linear velocity change
        deltaVelocity.data[0] += inverseMass;
        deltaVelocity.data[4] += inverseMass;
        deltaVelocity.data[8] += inverseMass;

        // Invert to get the impulse needed per unit velocity
        Matrix3 impulseMatrix = deltaVelocity.inverse();

        // Find the target velocities to kill
        Vector3 velKill(desiredDeltaVelocity, 
            -contactVelocity.y, 
            -contactVelocity.z);

        // Find the impulse to kill target velocities
        impulseContact = impulseMatrix.transform(velKill);

        // Check for exceeding friction
        real planarImpulse = real_sqrt(impulseContact.y*impulseContact.y +
                                       impulseContact.z*impulseContact.z);
        if (planarImpulse > impulseContact.x * friction)
        {
            // We need to use dynamic friction
            impulseContact.y /= planarImpulse;
            impulseContact.z /= planarImpulse;

            impulseContact.x = deltaVelocity.data[0] + 
                               deltaVelocity.data[1]*friction*impulseContact.y +
                               deltaVelocity.data[2]*friction*impulseContact.z;
            impulseContact.x = desiredDeltaVelocity / impulseContact.x;
            impulseContact.y *= friction * impulseContact.x;
            impulseContact.z *= friction * impulseContact.x;
        }
///<UpdateVelWithFriction
    }    

///>ImpulseToWorld
    // Convert impulse to world coordinates
    Vector3 impulse = contactToWorld.transform(impulseContact);
///<ImpulseToWorld

    // Split in the impulse into linear and rotational components
    Vector3 impulsiveTorque = relativeContactPosition[0] % impulse;
    rotationChange[0] = inverseInertiaTensor[0].transform(impulsiveTorque);
    velocityChange[0].clear();
    velocityChange[0].addScaledVector(impulse, body[0]->getInverseMass());

    // Apply the changes
    body[0]->addVelocity(velocityChange[0]);
    body[0]->addRotation(rotationChange[0]);

    if (body[1])
    {
        // Work out body one's linear and angular changes
        Vector3 impulsiveTorque = impulse % relativeContactPosition[1];
        rotationChange[1] = inverseInertiaTensor[1].transform(impulsiveTorque);
        velocityChange[1].clear();
        velocityChange[1].addScaledVector(impulse, -body[1]->getInverseMass());

        // And apply them.
        body[1]->addVelocity(velocityChange[1]);
        body[1]->addRotation(rotationChange[1]);
    }
}

void Contact::applyPositionChange(Vector3 velocityChange[2], 
                                 Vector3 rotationDirection[2], 
                                 real rotationAmount[2], 
                                 real penetration)
{
    real angularLimit = (real)1000;//0.1f;
    real angularMove[2],linearMove[2];
    int b;

    real totalInertia = 0;
    real linearInertia[2];
    real angularInertia[2];

///>AngularInertia
    // We need to work out the inertia of each object in the direction
    // of the contact normal, due to angular inertia only. 
    for (unsigned i = 0; i < 2; i++) {
        if (body[i]) {
            Matrix3 inverseInertiaTensor;
            body[i]->getInverseInertiaTensorWorld(&inverseInertiaTensor);

            // Use the same procedure as for calculating frictionless
            // velocity change to work out the angular inertia.
            Vector3 angularInertiaWorld = relativeContactPosition[i] % contactNormal;
            angularInertiaWorld = inverseInertiaTensor.transform(angularInertiaWorld);
            angularInertiaWorld = angularInertiaWorld % relativeContactPosition[i];
            angularInertia[i] = angularInertiaWorld * contactNormal;

            // The linear component is simply the inverse mass
            linearInertia[i] = body[i]->getInverseMass();

            // Keep track of the total inertia from all components
            totalInertia += linearInertia[i] + angularInertia[i];
        }
    }
///<AngularInertia

    real inverseMass[2];

    totalInertia = angularInertia[0] + body[0]->getInverseMass();

    if(body[1])
    {
        inverseMass[1] = angularInertia[1] + body[1]->getInverseMass();
        totalInertia+=inverseMass[1];

        angularMove[1] = -penetration*angularInertia[1]/totalInertia;
        linearMove[1] = -penetration*body[1]->getInverseMass()/totalInertia;

        // To avoid angular projections that are too great (when mass is large
        // but inertia tensor is small) limit the angular move.
        Vector3 projection = relativeContactPosition[1];
        projection.addScaledVector(contactNormal, 
            -relativeContactPosition[1].scalarProduct(contactNormal));
        real max = angularLimit*relativeContactPosition[0].magnitude();

        if(real_abs(angularMove[1]) > max)
        {
            real pp=angularMove[1]+linearMove[1];
            angularMove[1]=angularMove[1]>0?max:-max;
            linearMove[1]=pp-angularMove[1];
        }
    }

    angularMove[0] = penetration*angularInertia[0]/totalInertia;
    linearMove[0] = penetration*body[0]->getInverseMass()/totalInertia;

    // To avoid angular projections that are too great (when mass is large
    // but inertia tensor is small) limit the angular move.
    Vector3 projection = relativeContactPosition[0];
    projection.addScaledVector(contactNormal, 
        -relativeContactPosition[0].scalarProduct(contactNormal));
    real max = angularLimit*relativeContactPosition[0].magnitude();

    if(real_abs(angularMove[0]) > max)
    {
        real pp=angularMove[0]+linearMove[0];
        angularMove[0]=angularMove[0]>0?max:-max;
        linearMove[0]=pp-angularMove[0];
    }

    for(b=0;b<2;b++) if(body[b])
    {
        Vector3 t;
        if(angularMove[b]!=((real)0.0))
        {
            t = relativeContactPosition[b].vectorProduct(contactNormal);

            Matrix3 inverseInertiaTensor;
            body[b]->getInverseInertiaTensorWorld(&inverseInertiaTensor);
            rotationDirection[b] = inverseInertiaTensor.transform(t);

            rotationAmount[b] = angularMove[b] / angularInertia[b];

            assert(rotationAmount[b]!=((real)0.0));
        }
        else
        {
            rotationDirection[b].clear();
            rotationAmount[b]=1;
        }

        velocityChange[b] = contactNormal;
        velocityChange[b] *= linearMove[b]/rotationAmount[b];

        Vector3 pos;
        body[b]->getPosition(&pos);
        pos.addScaledVector(contactNormal,linearMove[b]);
        body[b]->setPosition(pos);

        Quaternion q;
        body[b]->getOrientation(&q);
        q.addScaledVector(rotationDirection[b], rotationAmount[b] * ((real)0.5));
        body[b]->setOrientation(q);
    }
}





// Contact resolver implementation

ContactResolver::ContactResolver(unsigned iterations,
                                 real velocityEpsilon, 
                                 real positionEpsilon)
{
    setIterations(iterations, iterations);
    setEpsilon(velocityEpsilon, positionEpsilon);
}

ContactResolver::ContactResolver(unsigned velocityIterations, 
                                 unsigned positionIterations,
                                 real velocityEpsilon, 
                                 real positionEpsilon)
{
    setIterations(velocityIterations);
    setEpsilon(velocityEpsilon, positionEpsilon);
}

void ContactResolver::setIterations(unsigned iterations)
{
    setIterations(iterations, iterations);
}

void ContactResolver::setIterations(unsigned velocityIterations, 
                                    unsigned positionIterations)
{
    ContactResolver::velocityIterations = velocityIterations;
    ContactResolver::positionIterations = positionIterations;
}

void ContactResolver::setEpsilon(real velocityEpsilon, 
                                 real positionEpsilon)
{
    ContactResolver::velocityEpsilon = velocityEpsilon;
    ContactResolver::positionEpsilon = positionEpsilon;
}

///>ContactResolverBase
void ContactResolver::resolveContacts(Contact *contacts, 
                                      unsigned numContacts,
                                      real duration)
{
    // Make sure we have something to do.
    if (numContacts == 0) return;
///<ContactResolverBase
    if (!isValid()) return;
///>ContactResolverBase

    // Prepare the contacts for processing
    prepareContacts(contacts, numContacts, duration);

    // Resolve the interpenetration problems with the contacts.
    adjustPositions(contacts, numContacts, duration);

    // Resolve the velocity problems with the contacts.
    adjustVelocities(contacts, numContacts, duration);
}
///<ContactResolverBase

///>PrepareContacts
void ContactResolver::prepareContacts(Contact* contacts,
                                      unsigned numContacts,
                                      real duration)
{
    // Generate contact velocity and axis information.
    Contact* lastContact = contacts + numContacts;
    for(Contact* contact=contacts; contact < lastContact; contact++)
    {
        // Calculate the inernal contact data (inertia, basis, etc).
        contact->calculateInternals(duration);
    } 
}
///<PrepareContacts

void ContactResolver::adjustVelocities(Contact *c,
                                       unsigned numContacts,
                                       real duration)
{
    Vector3 velocityChange[2], rotationChange[2];
    Vector3 cp;

    // iteratively handle impacts in order of severity.
    velocityIterationsUsed = 0;
    while(velocityIterationsUsed < velocityIterations) 
    {
        // Find contact with maximum magnitude of probable velocity change.
        real max = velocityEpsilon;
        unsigned index = numContacts;
        for(unsigned i = 0; i < numContacts; i++)
        {
            if (c[i].desiredDeltaVelocity > max)
            {
                max = c[i].desiredDeltaVelocity;
                index = i;
            }
        }
        if (index == numContacts) break;

        // Match the awake state at the contact
        c[index].matchAwakeState();

        // Do the resolution on the contact that came out top.
        c[index].applyVelocityChange(velocityChange, rotationChange);

        // With the change in velocity of the two bodies, the update of 
        // contact velocities means that some of the relative closing 
        // velocities need recomputing.
        for (unsigned i = 0; i < numContacts; i++)
        {
            if (c[i].body[0])
            {
                if (c[i].body[0] == c[index].body[0])
                {
                    cp = rotationChange[0].vectorProduct(c[i].
                        relativeContactPosition[0]);

                    cp += velocityChange[0];

                    c[i].contactVelocity += 
                        c[i].contactToWorld.transformTranspose(cp);
                    c[i].calculateDesiredDeltaVelocity(duration);

                }
                else if (c[i].body[0]==c[index].body[1])
                {
                    cp = rotationChange[1].vectorProduct(c[i].
                        relativeContactPosition[0]);

                    cp += velocityChange[1];

                    c[i].contactVelocity += 
                        c[i].contactToWorld.transformTranspose(cp);
                    c[i].calculateDesiredDeltaVelocity(duration);
                }
            }

            if (c[i].body[1])
            {
                if (c[i].body[1]==c[index].body[0])
                {
                    cp = rotationChange[0].vectorProduct(c[i].
                        relativeContactPosition[1]);

                    cp += velocityChange[0];

                    c[i].contactVelocity -= 
                        c[i].contactToWorld.transformTranspose(cp);
                    c[i].calculateDesiredDeltaVelocity(duration);
                }
                else if (c[i].body[1]==c[index].body[1])
                {
                    cp = rotationChange[1].vectorProduct(c[i].
                        relativeContactPosition[1]);

                    cp += velocityChange[1];

                    c[i].contactVelocity -= 
                        c[i].contactToWorld.transformTranspose(cp);
                    c[i].calculateDesiredDeltaVelocity(duration);
                }
            }
        }
        velocityIterationsUsed++;
    }
}

///>AdjustPositions
void ContactResolver::adjustPositions(Contact *c, 
                                      unsigned numContacts,
                                      real duration)
{
    unsigned i,index;
    Vector3 velocityChange[2], rotationChange[2];
    real rotationAmount[2];
    real max;
    Vector3 cp;

    // TODO: Remove this
    for(i=0; i<numContacts; i++) c[i].calculateInternals(duration);

    // iteratively resolve interpenetration in order of severity.
    positionIterationsUsed = 0;
    while(positionIterationsUsed < positionIterations)
    {
        // Find biggest penetration
        max = positionEpsilon;
        index = numContacts;
        for(i=0;i<numContacts;i++) {
            if(c[i].penetration > max)
            {
                max=c[i].penetration;
                index=i;
            }
        }
        if (index == numContacts) break;

        // Match the awake state at the contact
        c[index].matchAwakeState();

        // Resolve the penetration.
        c[index].applyPositionChange(velocityChange,
            rotationChange,
            rotationAmount,
            max);//-positionEpsilon);

        // Again this action may have changed the penetration of other 
        // bodies, so we update contacts.
        for(i = 0; i < numContacts; i++)
        {
            if(c[i].body[0] == c[index].body[0])
            {
                cp = rotationChange[0].vectorProduct(c[i].
                    relativeContactPosition[0]);

                cp += velocityChange[0];

                c[i].penetration -= 
                    rotationAmount[0]*cp.scalarProduct(c[i].contactNormal);
            }
            else if(c[i].body[0]==c[index].body[1])
            {
                cp = rotationChange[1].vectorProduct(c[i].
                    relativeContactPosition[0]);

                cp += velocityChange[1];

                c[i].penetration -= 
                    rotationAmount[1]*cp.scalarProduct(c[i].contactNormal);
            }

            if(c[i].body[1])
            {
                if(c[i].body[1]==c[index].body[0])
                {
                    cp = rotationChange[0].vectorProduct(c[i].
                        relativeContactPosition[1]);

                    cp += velocityChange[0];

                    c[i].penetration += 
                        rotationAmount[0]*cp.scalarProduct(c[i].contactNormal);
                }
                else if(c[i].body[1]==c[index].body[1])
                {
                    cp = rotationChange[1].vectorProduct(c[i].
                        relativeContactPosition[1]);

                    cp += velocityChange[1];

                    c[i].penetration += 
                        rotationAmount[1]*cp.scalarProduct(c[i].contactNormal);
                }
            }
        }
        positionIterationsUsed++;
    }
}
///<AdjustPositions


