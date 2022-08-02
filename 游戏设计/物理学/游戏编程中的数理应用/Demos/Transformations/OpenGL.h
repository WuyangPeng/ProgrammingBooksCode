// OpenGL.h : main header file for the OpenGL Wrapper Class
//
// ©New Riders, 2003. All rights reserved.
// Created By: Mike Fawcett & Mike Wigand

// Include OpenGL Libraries
#pragma once

#pragma comment( lib, "glu32" )
#pragma comment( lib, "glaux" )
#pragma comment( lib, "opengl32" )

#include "stdafx.h"

class OpenGL
{
public:
	CDC* hDC;
    HGLRC hRC;

	CPoint cursorPos;
	
	bool InitializeGL(CDC *DeviceContext);
	void Reshape(int width, int height);
	void DestroyGL();
	int SetupPixelFormat();
    void Render();

private:
	static OpenGL *instance;			// Pointer to the one instance of itself

	// Constructor
	OpenGL()							
	{		
	};

	// Destructor
	~OpenGL() {};

public:
	// Used to obtain the pointer to the ine instance of this class
	static OpenGL* getInstance();
	
	void DestroyOpenGL();
};