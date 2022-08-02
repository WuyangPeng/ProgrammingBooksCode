/*
 * Implementation file for random number generation.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under licence. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software licence.
 */

#include <cstdlib>
#include <cyclone/world.h>

using namespace cyclone;

World::World(unsigned maxContacts, unsigned iterations)
:
firstBody(NULL),
firstContactGen(NULL),
resolver(iterations),
maxContacts(maxContacts)
{
    contacts = new Contact[maxContacts];
    calculateIterations = (iterations == 0);
}

World::~World()
{
    delete[] contacts;
}

///>WorldStartFrame
void World::startFrame()
{
    BodyRegistration *reg = firstBody;
    while (reg)
    {
        // Remove all forces from the accumulator
        reg->body->clearAccumulators();
        reg->body->calculateDerivedData();

        // Get the next registration
        reg = reg->next;
    }
}
///<WorldStartFrame

unsigned World::generateContacts()
{
    unsigned limit = maxContacts;
    Contact *nextContact = contacts;

    ContactGenRegistration * reg = firstContactGen;
    while (reg)
    {
        unsigned used = reg->gen->addContact(nextContact, limit);
        limit -= used;
        nextContact += used;

        // We've run out of contacts to fill. This means we're missing
        // contacts.
        if (limit <= 0) break;

        reg = reg->next;
    }

    // Return the number of contacts used.
    return maxContacts - limit;
}

///>WorldRunPhysics
void World::runPhysics(real duration)
{
    // First apply the force generators
    //registry.updateForces(duration);

    // Then integrate the objects
    BodyRegistration *reg = firstBody;
    while (reg)
    {
        // Remove all forces from the accumulator
        reg->body->integrate(duration);

        // Get the next registration
        reg = reg->next;
    }
///<WorldRunPhysics

    // Generate contacts
    unsigned usedContacts = generateContacts();

    // And process them
    if (calculateIterations) resolver.setIterations(usedContacts * 4);
    resolver.resolveContacts(contacts, usedContacts, duration);
///>WorldRunPhysics
}
///<WorldRunPhysics
