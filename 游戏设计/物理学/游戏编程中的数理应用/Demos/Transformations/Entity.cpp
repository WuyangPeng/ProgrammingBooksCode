// Entity.cpp - Source file for the Entity Class
//
// ©New Riders, 2003. All rights reserved.
// Created By: Mike Fawcett & Mike Wigand
//////////////
// INCLUDES //
//////////////
#include "stdafx.h"
#define _USE_MATH_DEFINES 1
#include <math.h>
#include "Entity.h"

//#pragma warning (disable : 4244)

/////////////////////
// CLASS FUNCTIONS //
/////////////////////
Entity::Entity()
{
	// Set up the default position and color of each vert in the Quad
	Vec4 tpos(0.0, 0.0, 0.0, 1.0);
	Vec3 tcol(1.0, 0.0, 0.0);

	verts[0].InitVert(&tpos, &tcol);

	tpos = Vec4(1.0, 0.0, 0.0, 1.0);
	tcol = Vec3(1.0, 1.0, 0.0);

	verts[1].InitVert(&tpos, &tcol);
	
	tpos = Vec4(1.0, 1.0, 0.0, 1.0);
	tcol = Vec3(0.0, 1.0, 0.0);

	verts[2].InitVert(&tpos, &tcol);

	tpos = Vec4(0.0, 1.0, 0.0, 1.0);
	tcol = Vec3(0.0, 0.0, 1.0);

	verts[3].InitVert(&tpos, &tcol);

	// Initialize the vector storage
	transMats.clear();
	undoMats.clear();

	currentMat = IdentityMat();

	transMats.push_back(IdentityMat());	
}

Entity::~Entity() 
{
	Matrix4* temp = NULL;

	while (!transMats.empty() && matItr != transMats.begin())
	{
		matItr = transMats.end();
		matItr--;
		temp = (*matItr);
		transMats.erase(matItr);
		delete temp;
	}
};

// Send the Quad down the Render pipe
// This object is Oriented in World Space
// - i.e. Rotated about & Translated from the origin of the world
void Entity::drawEntity()
{
	// Push a new Matrix on the stack
	glPushMatrix();
	glScalef(15.0, 15.0, 15.0);

	glPushMatrix();
	
	// Set the Iterator to the last matric pushed onto the Quad
	matItr = transMats.end();

	currentMat = IdentityMat();
	
	// Apply each TM of the Quad to the Matrix Stack
	for (int y = transMats.size(); y > 0; y--)
	{
		matItr--;
		(*currentMat) = (*currentMat) * (*matItr);	
	}

	for (int k = 0; k < 4; k++)
	{
		transVerts[k].pos = ((*currentMat) * &verts[k].pos);
	}

	glMultMatrixd(currentMat->mat);
	
	// Draw the Quad
	glBegin(GL_QUADS);
		for (int x = 0; x < 4; x++)
		{
			glColor3d(verts[x].col.vector[0], verts[x].col.vector[1],
				verts[x].col.vector[2]);
			glVertex3d(verts[x].pos.vector[0], verts[x].pos.vector[1], 
				verts[x].pos.vector[2]);
		}
	glEnd();

	// If this Quad is currently selected draw a white border around it
	if (selection == true)
	{
		glLineWidth(5.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINE_STRIP);	
			for (int i = 0; i < 4; i++)
			{
				glVertex3d(verts[i].pos.vector[0], verts[i].pos.vector[1],
					verts[i].pos.vector[2]);
			}
			glVertex3d(verts[0].pos.vector[0], verts[0].pos.vector[1],
				verts[0].pos.vector[2]);
		glEnd();
		glLineWidth(1.0f);
	}

	// Pop the current Matrix off the Stack
	glPopMatrix();
	glPopMatrix();
}

void Entity::drawTraces(bool drawSelect)
{
	glPushMatrix();
	glScalef(15.0, 15.0, 15.0);

	if (traces.size() != 0)
	{
		// Apply each TM of the Quad to the Matrix Stack
		for (int y = 0; y < traces.size(); y++)
		{
			glPushMatrix();
			
			matItr = transMats.begin();

			// Set the Iterator to the last matric pushed onto the Quad
			for (int k = 0; k < traces[y] - 1; k++)
				matItr++;
		
			// Apply each TM of the Quad to the Matrix Stack
			for (int z = traces[y]; z > 0; z--)
			{
				glMultMatrixd((*matItr)->mat);
				matItr--;
			}	

			// Draw the Quad
			glBegin(GL_QUADS);
			
			glColor3d(.5f, .5f,	.5f);

			for (int x = 0; x < 4; x++)
			{
				glVertex3d(verts[x].pos.vector[0], verts[x].pos.vector[1], 
					verts[x].pos.vector[2]);
			}
			glEnd();

			if (drawSelect == true)
			{
				glLineWidth(5.0f);
				glColor3f(.8f, .8f, .8f);
				glBegin(GL_LINE_STRIP);	
					for (int i = 0; i < 4; i++)
					{
						glVertex3d(verts[i].pos.vector[0], verts[i].pos.vector[1],
							verts[i].pos.vector[2]);
					}
					glVertex3d(verts[0].pos.vector[0], verts[0].pos.vector[1],
						verts[0].pos.vector[2]);
				glEnd();
				glLineWidth(1.0f);
			}

			glPopMatrix();
		}
	}
	glPopMatrix();
}

void Entity::undo(int action)
{
	if (action == 1)
	{
		if (transMats.size() != 0)
		{
			Matrix4* temp;
			temp = transMats.back();
			transMats.pop_back();
			undoMats.push_back(temp);
		}
	}

	if (action == 2)
	{
		if (traces.size() != 0)
		{
			int temp;
			temp = traces.back();
			traces.pop_back();
			undoTraces.push_back(temp);		
		}
	}

	int iTemp;
	iTemp = actions.front();
	actions.pop_front();
	undoActions.push_front(iTemp);
}

void Entity::redo(int action)
{
	if (action == 1)
	{
		if (undoMats.size() != 0)
		{
			Matrix4* temp;
			temp = undoMats.back();
			undoMats.pop_back();
			transMats.push_back(temp);
		}
	}

	if (action == 2)
	{
		if (undoTraces.size() != 0)
		{
			int temp;
			temp = undoTraces.back();
			undoTraces.pop_back();
			traces.push_back(temp);
		}
	}

	int iTemp;
	iTemp = undoActions.front();
	undoActions.pop_front();
	actions.push_front(iTemp);
}