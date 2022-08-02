// Entity.h - Header file for the Entity Class
//
// ©New Riders, 2003. All rights reserved.
// Created By: Mike Fawcett & Mike Wigand
#pragma once

//////////////
// INCLUDES //
//////////////
//#include "stdafx.h:				// Main MFC header.
#include <list>
#include <vector>
using namespace std;
#include "OpenGL/gl.h"			// OpenGL header.
#include "OpenGL/glu.h"			// Another OpenGL header.
#include "GraphicsUtil.h"

// Entity Class - in this app these are Quads
class Entity
{
public:
	Vertex verts[4];						// 4 Vertices comprising the Quad
	Vertex transVerts[4];
		
	vector <Matrix4*>::iterator matItr;		// Iterator used for both of the above vectors
	vector <Matrix4*> transMats;			// Stack of Transformation Matrices being applied
												// to the Quad
	vector <Matrix4*> undoMats;				// Used for Undo/Redo - stores undone TM*
	Matrix4*  currentMat;					// The current concatenated TM
	
	vector <int> traces;					// Stores how deep into its TM stack to go during 
												// renderingof a copy of the entity
	vector <int> undoTraces;				// Used for Undo/Redo - stores undone traces

	list <int> actions;						// List of actions done on the Entity in order of 
												// application
	list <int> undoActions;					// Used for Undo/Redo - stores undone actions

	bool selection;							// Is this entity selected?
	
	// Constructor
	Entity();

	// Destructor
	~Entity();

	// Send the Quad down the Render pipe
	void drawEntity();

	void drawTraces(bool drawSelect);

	void undo(int action);

	void redo(int action);
};