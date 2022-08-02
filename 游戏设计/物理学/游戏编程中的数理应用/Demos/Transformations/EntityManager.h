// EntityManager.h - Header file for the EntityManager Class
// Entities will either be refered to as Quads or Entities
//
// ©New Riders, 2003. All rights reserved.
// Created By: Mike Fawcett & Mike Wigand
#pragma once
#include "Entity.h"

// Entity Manager - Singleton Class
class EntityManager
{
public:
	vector<Entity*>  entities;				// Quads being displayed
	vector<Entity*>::iterator entitiesItr;	// Iterator for the entities vector
	Entity* selected;						// The current Quad selected

private:
	static EntityManager *instance;			// Pointer to the one instance of itself

	// Constructor
	EntityManager()							
	{		
		// Initialize the pointer to the selected Quad to NULL
		selected = NULL;	
	};

	// Destructor
	~EntityManager() {};

public:
	// Used to obtain the pointer to the ine instance of this class
	static EntityManager* getInstance();
	
	void DestroyEntityManager();

	// Add a new Entity(Quad) to the app
	Entity* newEntity();
	void Picking(CPoint pos);
};