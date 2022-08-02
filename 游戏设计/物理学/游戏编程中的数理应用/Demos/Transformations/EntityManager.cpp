// EntityManager.cpp - Source file for the EntityManager Class
// 
// ©New Riders, 2003. All rights reserved.
// Created By: Mike Fawcett & Mike Wigand

//////////////
// INCLUDES //
//////////////
#include "stdafx.h"
#include "EntityManager.h"

// Initialize the one static instance of the class
EntityManager* EntityManager::instance = 0;

/////////////////////////
// FUNCTION DEFINTIONS //
/////////////////////////
// Accessor to the one static instance of the class
EntityManager* EntityManager::getInstance()
{
	// Allocates a new EntityManager on the first call
	if (instance == NULL)
	{
		// CEANUP
		instance = new EntityManager();
		instance->selected = instance->newEntity();
		 
	}

	// Return the pointer to the static instance of the class
	return instance;
}

void EntityManager::DestroyEntityManager()
{
	Entity* temp;
	for (entitiesItr = entities.begin(); entitiesItr != entities.end(); entitiesItr++)
	{
		temp = (*entitiesItr);
		delete temp;
	}

	delete instance;
}

// Create and track a new entity in the app
Entity* EntityManager::newEntity()
{
	// CEANUP
	Entity* temp = new Entity;
	
	// Mark the Quad as selected if it is the first or only Entity
	if (entities.size() == 0)
	{
		temp->selection = true;
		selected = temp;
	}
	else
		temp->selection = false;
	
	// Push the Quad on the back of the vector
	entities.push_back(temp);

	return temp;
}

void EntityManager::Picking(CPoint pos)
{
	entitiesItr = entities.begin();
	for (int j = 0; j < entities.size(); j++)
	{
		if ( ((pos.x >= (*entitiesItr)->transVerts[0].pos.vector[0] &&
			pos.x <= (*entitiesItr)->transVerts[2].pos.vector[0]) || 
			(pos.x <= (*entitiesItr)->transVerts[0].pos.vector[0] &&
			pos.x >= (*entitiesItr)->transVerts[2].pos.vector[0])) && 
			((pos.y >= (*entitiesItr)->transVerts[0].pos.vector[1] &&
			pos.y <= (*entitiesItr)->transVerts[2].pos.vector[1]) || 
			(pos.y <= (*entitiesItr)->transVerts[0].pos.vector[1] &&
			pos.y >= (*entitiesItr)->transVerts[2].pos.vector[1])) )
		{	
			selected->selection = false;
			selected = (*entitiesItr);
			selected->selection = true;
			break;
		}

		entitiesItr++;
	}
}